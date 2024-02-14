import telebot
import src.config
import adapter
import json
from game import Game


bot = telebot.TeleBot(src.config.TOKEN)

keys_level = telebot.types.ReplyKeyboardMarkup(one_time_keyboard=True, resize_keyboard=True)
keys_level.row('1', '2', '3')

keys_commands = telebot.types.ReplyKeyboardMarkup(True)
keys_commands.row('insert', 'erase', 'cancel', 'next', 'hint')

keys_regime = telebot.types.ReplyKeyboardMarkup(True)
keys_regime.row('/help', '/sudoku')

curr_players = []
games = dict()


def start(message):
    try:
        level = int(message.text)
        if level not in range(1, 4): raise Exception
        if message.from_user.id not in curr_players: curr_players.append(message.from_user.id)
        if message.from_user.id in games.keys(): del games[message.from_user.id]
        game = Game(level)
        games[message.from_user.id] = game
        bot.send_message(message.from_user.id, games[message.from_user.id].field.print(), reply_markup=keys_commands)
    except Exception:
        bot.send_message(message.from_user.id, f'Некорректные данные!')
    return


def inserting(message):
    try:
        x, y, num = map(int, message.text.split())
        games[message.from_user.id].inserting(x, y, num, message.from_user.id)
    except Exception:
        bot.send_message(message.from_user.id, f'Некорректные данные!')
    return


def erasing(message):
    try:
        x, y = map(int, message.text.split())
        print(x, y)
        games[message.from_user.id].erasing(x, y, message.from_user.id)
    except Exception:
        bot.send_message(message.from_user.id, f'Некорректные данные!')
    return


def cancellation(id):
    games[id].cancellation(id)


def next_version(id):
    games[id].next_version(id)


def get_hint(id):
    games[id].get_hint(id)


def solve(id):
    games[id].solving(id)


def show(id):
    games[id].show_version(id)


def end(id):
    if games[id].field.is_win():
        bot.send_message(id, 'Ты победил!', reply_markup=keys_regime)
        curr_players.remove(id)
        del games[id]


@bot.message_handler(content_types=['text'])
def get_text_messages(message):
    if message.text == '/start':
        bot.send_message(message.from_user.id, f'Бот запущен!', reply_markup=keys_regime)
        return
    if message.text == '/help':
        bot.send_message(message.from_user.id,
                         f'Привет! Я бот - судоку! '
                         f'Чтобы начать игру, напиши /sudoku! '
                         f'Во время игры ты можешь вставлять (insert) или удалять (erase) числа! '
                         f'Вводите координаты как на координатной плоскости (ось X, ось Y) числами от 1 до 9 '
                         f'Ты также можешь перемещаться по версиям (cancel, next), или просить подсказки (hint)!',
                         reply_markup=keys_regime)
        return
    if message.text == '/sudoku':
        bot.send_message(message.from_user.id, f'Напишите уровень сложности:', reply_markup=keys_level)
        bot.register_next_step_handler(message, start)
        return

    if message.from_user.id in curr_players:
        if message.text == 'insert':
            bot.send_message(message.from_user.id, f'Введи координыты (стобец, строка) и число: все через пробел!')
            bot.register_next_step_handler(message, inserting)
            end(message.from_user.id)
            return
        if message.text == 'erase':
            bot.send_message(message.from_user.id, f'Введи координыты (стобец, строка) через пробел!')
            bot.register_next_step_handler(message, erasing)
            end(message.from_user.id)
            return
        if message.text == 'cancel':
            cancellation(message.from_user.id)
            return
        if message.text == 'next':
            next_version(message.from_user.id)
            return
        if message.text == 'hint':
            get_hint(message.from_user.id)
            return
        if message.text == 'solve' and message.from_user.id in src.config.VIP_IDs:
            solve(message.from_user.id)
            end(message.from_user.id)
            return
        if message.text == 'show' and message.from_user.id in src.config.VIP_IDs:
            show(message.from_user.id)
            return
        bot.send_message(message.from_user.id, f'Я тебя не понимаю(( Напиши /help!', reply_markup=keys_commands)
        return

    bot.send_message(message.from_user.id, f'Я тебя не понимаю(( Напиши /help!', reply_markup=keys_regime)


if __name__ == '__main__':
    with open('src/players.json') as file:
        data = json.load(file)
        curr_players = data["curr"]

    with open('src/games.json') as file:
        data = json.load(file)
        for s_id in data.keys():
            games[int(s_id)] = adapter.get_game(data[s_id])

    try:
        bot.polling(none_stop=True, interval=0)
    except Exception as e:
        print(e)

    with open('src/players.json', 'w') as file:
        data = {"curr": curr_players}
        json.dump(data, file)

    with open('src/games.json', 'w') as file:
        data = dict()
        for i_id in games.keys():
            data[f'{i_id}'] = adapter.dict_game(games[i_id])
        json.dump(data, file)
