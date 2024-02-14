from game import Game
import time
import json


class Command:

    @staticmethod
    def play():
        print("Введите cложность:")
        print("1: легкая")
        print("2: средняя")
        print("3: тяжелая")
        level = int(input())
        game = Game(level)
        start_time = time.time()
        game.play()
        curr_time = round(time.time() - start_time, 1)
        if game.is_win:
            with open('data.json') as file:
                data = json.load(file)
                if data.get(f"{level}")[0] == 0:
                    data.get(f"{level}")[0] = curr_time
                else:
                    data.get(f"{level}")[0] = min(data.get(f"{level}")[0], curr_time)
            with open('data.json', 'w') as file:
                json.dump(data, file, ensure_ascii=False, indent=4)

    @staticmethod
    def score():
        with open("data.json") as file:
            data = json.load(file)
            print("Ваши лучшие результаты:")
            print(f'Легкая по сложности игра:  {data["1"][0]}  секунд')
            print(f'Средняя по сложности игра:  {data["2"][0]} секунд')
            print(f'Тяжелая по сложности игра:  {data["3"][0]} секунд')

    @staticmethod
    def execute():
        print("Игра судоку!")
        while True:
            print("Введите команду:")
            print("/play -- /score -- /exit")
            command = str(input())
            if command == "/play":
                Command.play()
            elif command == "/score":
                Command.score()
            elif command == "/exit":
                print("Вы вышли из игры!")
                break
            else:
                print("Нет такой команды! Попробуйте еще раз!")
