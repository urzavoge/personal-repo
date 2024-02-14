import json


# НЕ ЗАПУСКАТЬ! НЕ ЗАПУСКАТЬ! DO NOT RUN! DO NOT RUN!
# ОНО УДАЛИТ ВСЕ СОХРАНЕНИЯ! IT WILL DELETE ALL SAVES!

if __name__ == '__main__':
    with open('players.json', 'w') as file:
        data = {"curr": []}
        json.dump(data, file)

    with open('games.json', 'w') as file:
        data = dict()
        json.dump(data, file)
