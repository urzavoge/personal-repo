from field import Field
from field import Hint
from game import Game


def dict_hint(curr_hint: Hint) -> dict:
    ans = dict()
    ans['x'] = curr_hint.x
    ans['y'] = curr_hint.y
    ans['num'] = curr_hint.num
    return ans


def dict_field(curr_field: Field) -> dict:
    ans = dict()
    ans['field'] = curr_field.field
    ans['empty_cages'] = curr_field.empty_cages
    tmp = [dict_hint(hint) for hint in curr_field.hints]
    ans['hints'] = tmp
    return ans


def dict_game(curr_game: Game) -> dict:
    ans = dict()
    ans['level'] = curr_game.level
    ans['curr_field'] = curr_game.curr_field
    ans['field'] = dict_field(curr_game.field)
    tmp = [dict_field(field) for field in curr_game.prev_fields]
    ans['prev_fields'] = tmp
    return ans


def get_hint(curr: dict) -> Hint:
    return Hint(curr['x'], curr['y'], curr['num'])


def get_field(curr: dict) -> Field:
    tmp = [get_hint(d_hint) for d_hint in curr['hints']]
    field = Field()
    field.field = curr['field']
    field.hints = tmp
    field.empty_cages = curr['empty_cages']
    return field


def get_game(curr: dict) -> Game:
    tmp = [get_field(d_field) for d_field in curr['prev_fields']]
    game = Game(curr['level'])
    game.prev_fields = tmp
    game.field = get_field(curr['field'])
    game.curr_field = curr['curr_field']
    return game
