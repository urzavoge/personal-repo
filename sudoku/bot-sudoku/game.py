from field import Field
import src.config
import telebot


bot = telebot.TeleBot(src.config.TOKEN)


class Game:

    field = Field()
    prev_fields = []
    curr_field = 0

    level = 0

    def __init__(self, n):
        self.level = n
        self.field.generate(self.level)
        self.prev_fields = []
        self.prev_fields.append(self.field.copy())

    def check(self, x, y, num, id):
        if not self.field.check_column(x):
            bot.send_message(id, f'Ой! В столбце {x} уже есть число {num}! '
                                 f'Я удалю его оттуда!')
            self.field.erase(x, y)
            bot.send_message(id, self.field.print())
            return False
        if not self.field.check_line(y):
            bot.send_message(id, f'Ой! В строке {y} уже есть число {num}! '
                                 f'Я удалю его оттуда!')
            self.field.erase(x, y)
            bot.send_message(id, self.field.print())
            return False
        if not self.field.check_square(((x - 1) // 3) + ((y - 1) // 3) * 3 + 1):
            bot.send_message(id, f'Ой! В квадрате {((x - 1) // 3) + ((y - 1) // 3) * 3 + 1} уже есть число {num}! '
                                 f'Я удалю его оттуда!')
            self.field.erase(x, y)
            bot.send_message(id, self.field.print())
            return False
        return True

    def inserting(self, x, y, num, id):
        if not (0 < x < 10 and 0 < y < 10 and 0 < num < 10):
            bot.send_message(id, f'Неверные данные! Попробуй еще раз!')
            return
        if self.prev_fields[0].field[9 - y][(x - 1) * 2] != '#':
            bot.send_message(id, f'Ты не можешь вставить туда число!')
            return
        self.field.insert(x, y, num)
        bot.send_message(id, self.field.print())
        if self.check(x, y, num, id):
            self.prev_fields.append(self.field.copy())
            self.curr_field = len(self.prev_fields) - 1

    def cancellation(self, id):
        if self.curr_field == 0:
            bot.send_message(id, f'Это и так первая версия поля!')
            return
        self.curr_field -= 1
        self.field = self.prev_fields[self.curr_field].copy()
        bot.send_message(id, self.field.print())

    def next_version(self, id):
        if self.curr_field + 1 == len(self.prev_fields):
            bot.send_message(id, f'Это и так последняя версия поля!')
            return
        self.curr_field += 1
        self.field = self.prev_fields[self.curr_field].copy()
        bot.send_message(id, self.field.print())

    def erasing(self, x, y, id):
        if not (0 < x < 10 and 0 < y < 10):
            bot.send_message(id, f'Неверные данные! Попробуй еще раз!')
            return
        if self.prev_fields[0].field[9 - y][(x - 1) * 2] != '#':
            bot.send_message(id, f'Ты не можешь удалить это число!')
            return
        self.field.erase(x, y)
        bot.send_message(id, self.field.print())
        self.prev_fields.append(self.field.copy())
        self.curr_field = len(self.prev_fields) - 1

    def get_hint(self, id):
        for hint in self.field.hints:
            if self.field.is_useful(hint):
                bot.send_message(id, f'На пересечении {hint.x} столбца и {hint.y} строки лучше поставить {hint.num}!')
                return
        bot.send_message(id, f'Нет доступных подсказок!')

    def solving(self, id):
        for hint in self.field.hints:
            if self.field.is_useful(hint):
                self.field.insert(hint.x, hint.y, hint.num)
        bot.send_message(id, self.field.print())

    def show_version(self, id):
        for fie in self.prev_fields:
            bot.send_message(id, fie.print())
