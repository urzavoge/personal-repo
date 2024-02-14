#include "../game.h"

Game::Game(Interface* inter) : interface(inter),
                               npc(nullptr), user(new Player(inter)), level_(1) {}

void Game::make_npc() {
  if (user->curr_room->curr_npc != nullptr) {
    npc = user->curr_room->curr_npc;
    user->curr_room->curr_npc = nullptr;
    return;
  }
  if (level_ == 2) {
    npc = npcs.lola1;
    return;
  }
  if (level_ == 12) {
    npc = npcs.lola2;
    return;
  }
  if (level_ != 10) {
    size_t val = get_rnd();
    if (val % 6 == 1) {
      npc = (level_ < 10) ? npcs.ura1 : npcs.pasha1;
      return;
    }
    if (val % 6 == 4) {
      npc = (level_ < 10) ? npcs.ura2 : npcs.pasha2;
      return;
    }
    if (val % 6 == 2) {
      npc = (level_ < 10) ? npcs.egor1 : npcs.null1;
      return;
    }
    if (val % 6 == 5) {
      npc = (level_ < 10) ? npcs.egor2 : npcs.null2;
      return;
    }
    if (val % 6 == 3) {
      npc = (level_ < 10) ? npcs.ars1 : npcs.tan1;
      return;
    }
    if (val % 6 == 0) {
      npc = (level_ < 10) ? npcs.ars2 : npcs.tan2;
      return;
    }
  }
  if (level_ == 10) {
    npc = npcs.boss1;
    return;
  }
}

void Game::start_game() {
  interface->print_start_game1();
  user->make_player();
  interface->print_start_game2();
}

void Game::play() {
  while (user->get_exp() <= 30) {
    if (level_ > 10 && user->get_exp() < 10) {
      user->change_exp(10);
    }
    if (level_ <= 10 && user->get_exp() < 5) {
      user->change_exp(5);
    }
    make_npc();
    interface->print_base_iteration();
    user->action(npc);
    ++level_;
  }
}

void Game::end_game(string&& path) {
  interface->print_end_game(user->get_exp());
  int size = level_;
  Field field(interface, 4 * size + 1);
  user->curr_room->generate(field, 2 * size + 1, 2 * size + 1);
  field.print();
  ofstream file(path);
  file << "THE END";
  file.close();
}

void Game::download(string&& path) {
  ifstream info(path);
  string status;
  info >> status;
  if (status != "READY_TO_LOAD") throw wrong_data();
  info >> level_;
  int tmp;
  info >> tmp;
  user->change_exp(tmp);
  string name;
  info >> name;
  user->change_name(std::move(name));
}
