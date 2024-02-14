from field import Field


class Game:

    field = Field()
    prev_fields = []
    curr_field = 0

    level = 0
    is_win = False

    def __init__(self, n):
        self.level = n
        self.field.generate(self.level)
        while not self.field.check_all():
            self.field.generate(self.level)
        self.prev_fields.append(self.field.copy())

    def check(self, x, y, num):
        if not self.field.check_column(x):
            print(f"Ой! В столбце {x} уже есть число {num}!")
            print("Я удалю его оттуда!")
            self.field.erase(x, y)
            self.field.print()
            return False
        if not self.field.check_line(y):
            print(f"Ой! В строке {y} уже есть число {num}")
            print("Я удалю его оттуда!")
            self.field.erase(x, y)
            self.field.print()
            return False
        if not self.field.check_square(((x - 1) // 3) + ((y - 1) // 3) * 3 + 1):
            print(f"Ой! В квадрате {((x - 1) // 3) + ((y - 1) // 3) * 3 + 1} уже есть число {num}")
            print("Я удалю его оттуда!")
            self.field.erase(x, y)
            self.field.print()
            return False
        return True

    def inserting(self):
        print("Введите координаты (столбец, строка) и число:")
        x, y, num = map(int, input().split())
        if not (0 < x < 10 and 0 < y < 10 and 0 < num < 10):
            print("Неверные данные! Попробуйте еще раз!")
            return
        if self.prev_fields[0].field[9 - y][(x - 1) * 2] != '.':
            print("Вы не можете вставить туда число!")
            return
        self.field.insert(x, y, num)
        self.field.print()
        if self.check(x, y, num):
            self.prev_fields.append(self.field.copy())
            self.curr_field = len(self.prev_fields) - 1

    def cancellation(self):
        if self.curr_field == 0:
            print("Это и так первая версия поля!")
            return
        self.curr_field -= 1
        self.field = self.prev_fields[self.curr_field]
        self.field.print()

    def next_version(self):
        if self.curr_field + 1 == len(self.prev_fields):
            print("Это и так последняя версия поля!")
            return
        self.curr_field += 1
        self.field = self.prev_fields[self.curr_field]
        self.field.print()

    def erasing(self):
        print("Введите координаты (столбец, строка):")
        x, y = map(int, input().split())
        if not (0 < x < 10 and 0 < y < 10):
            print("Неверные данные! Попробуйте еще раз!")
            return
        if self.prev_fields[0].field[9 - y][(x - 1) * 2] != '.':
            print("Вы не можете удалить это число!")
            return
        self.field.erase(x, y)
        self.field.print()
        self.prev_fields.append(self.field.copy())
        self.curr_field = len(self.prev_fields) - 1

    def show_version(self):
        for fie in self.prev_fields:
            fie.print()

    def get_hint(self):
        for hint in self.field.hints:
            if self.field.is_useful(hint):
                print(f"На пересечении {hint.x} столбца и {hint.y} строки лучше поставить {hint.num}!")
                break

    def solving(self):
        for hint in self.field.hints:
            if self.field.is_useful(hint):
                self.field.insert(hint.x, hint.y, hint.num)

    def play(self):
        self.field.print()
        while True:
            print("Введите команду:")
            print("/insert, или /erase, или /cancel, или /next, или /hint, или /exit")
            command = input().split()
            if command[0] == "/insert":
                self.inserting()
            elif command[0] == "/erase":
                self.erasing()
            elif command[0] == "/cancel":
                self.cancellation()
            elif command[0] == "/next":
                self.next_version()
            elif command[0] == "/hint":
                self.get_hint()
            elif command[0] == "/exit":
                print("Вы вышли из игры!")
                break
            elif command[0] == "/show":
                self.show_version()
            elif command[0] == "/pass":
                print("...")
                self.solving()
                self.field.print()
            else:
                print("Вы ввели неправильную команду! Попробуйте еще раз!")
            if self.field.is_win():
                print("Вы победили!")
                self.is_win = True
                break
