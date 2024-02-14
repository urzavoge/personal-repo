import itertools
import random
import copy


class Hint:

    def __init__(self, x1, y1, num):
        self.x = x1
        self.y = y1
        self.num = num


class Field:

    field = []
    empty_cages = 81
    hints = []

    def __init__(self):
        for i in range(9):
            self.field.append(list(itertools.chain(['.', ' '] * 8, ['.'])))

    def insert(self, x1, y1, num):
        x = x1 - 1
        y = y1 - 1
        self.field[8 - y][2 * x] = num
        self.empty_cages -= 1

    def erase(self, x1, y1):
        x = x1 - 1
        y = y1 - 1
        if self.field[8 - y][2 * x] != '.':
            self.field[8 - y][2 * x] = '.'
            self.empty_cages += 1

    def check_line(self, n):
        y = n - 1
        for i in range(9):
            if self.field[8 - y].count(i) > 1:
                return False
        return True

    def check_column(self, n):
        x = n - 1
        tmp = []
        for i in range(9):
            tmp.append(self.field[8 - i][2 * x])
        for i in range(9):
            if tmp.count(i) > 1:
                return False
        return True

    def check_square(self, n):
        num = n - 1
        x = (num % 3) * 3
        y = (num // 3) * 3
        tmp = []
        for i in range(x, x + 3):
            for j in range(y, y + 3):
                tmp.append(self.field[8 - j][2 * i])
        for i in range(9):
            if tmp.count(i) > 1:
                return False
        return True

    def check_all(self):
        flag = True
        for to_check in range(1, 10):
            flag = flag and self.check_line(to_check)
            flag = flag and self.check_column(to_check)
            flag = flag and self.check_square(to_check)
        return flag

    def is_win(self):
        return (self.empty_cages == 0) and self.check_all()

    def base(self):
        for i in range(9):
            for j in range(9):
                self.field[i][2 * j] = (j + i * 3 + i // 3) % 9 + 1
        self.empty_cages = 0

    def transposing(self):
        for i in range(9):
            for j in range(i):
                self.field[i][2 * j], self.field[j][2 * i] = self.field[j][2 * i], self.field[i][2 * j]

    def switch_lines(self):
        area = random.randrange(0, 3)
        line1 = random.randrange(area * 3, area * 3 + 3)
        line2 = random.randrange(area * 3, area * 3 + 3)
        while line1 == line2:
            line2 = random.randrange(area * 3, area * 3 + 3)
        self.field[line1], self.field[line2] = self.field[line2], self.field[line1]

    def switch_columns(self):
        area = random.randrange(0, 3)
        column1 = random.randrange(area * 3, area * 3 + 3)
        column2 = random.randrange(area * 3, area * 3 + 3)
        while column2 == column1:
            column2 = random.randrange(area * 3, area * 3 + 3)
        for i in range(9):
            self.field[i][column1 * 2], self.field[i][column2 * 2] =\
                self.field[i][column2 * 2], self.field[i][column1 * 2]

    def switch_areas_lines(self):
        area1 = random.randrange(0, 3)
        area2 = random.randrange(0, 3)
        while area1 == area2:
            area2 = random.randrange(0, 3)
        for i in range(3):
            self.field[area1 * 3 + i], self.field[area2 * 3 + i] =\
                self.field[area2 * 3 + i], self.field[area1 * 3 + i]

    def switch_areas_columns(self):
        area1 = random.randrange(0, 3)
        area2 = random.randrange(0, 3)
        while area1 == area2:
            area2 = random.randrange(0, 3)
        for j in range(3):
            for i in range(9):
                self.field[i][(area1 * 3 + 1) * 2], self.field[i][(area2 * 3 + 1) * 2] =\
                    self.field[i][(area2 * 3 + 1) * 2], self.field[i][(area1 * 3 + 1) * 2]

    def mix_changes(self, amt):
        mix_func = ["transposing()",
                    "switch_lines()",
                    "switch_columns()",
                    "switch_areas_lines()",
                    "switch_areas_columns()"]
        for i in range(amt):
            id_func = random.randrange(0, len(mix_func))
            eval(f"self.{mix_func[id_func]}")

    def deleting(self, level):
        if level == 1:
            count = 50
        elif level == 2:
            count = 55
        else:
            count = 60
        self.hints = []
        for i in range(count):
            x = random.randrange(1, 10)
            y = random.randrange(1, 10)
            if self.field[9 - y][(x - 1) * 2] != '.':
                self.hints.append(Hint(x, y, self.field[9 - y][(x - 1) * 2]))
                self.erase(x, y)

    def generate(self, level):
        self.base()
        self.mix_changes(15)
        self.deleting(level)
        return

    def copy(self):
        new_field = Field()
        new_field.field = copy.deepcopy(self.field)
        new_field.empty_cages = self.empty_cages
        return new_field

    def is_useful(self, hint):
        if self.field[9 - hint.y][(hint.x - 1) * 2] != hint.num:
            return True
        return False


    def print(self):
        print('-' * 21)
        for y in range(9):
            print('|', end='')
            for x in range(17):
                print(self.field[y][x], end='')
                if x % 2 == 0 and (x // 2) % 3 == 2:
                    print('|', end='')
            print()
            if y % 3 == 2:
                print('-' * 21)