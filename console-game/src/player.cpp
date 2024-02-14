#include "../player.h"

Player::Player(Interface* inter) : interface(inter) {
  Room* new_room = new Room(1, nullptr, Side::NONE);
  curr_room = new_room;
  exp_ = 5;
  name_ = "default";
}

Player::~Player() {
  curr_room->clear(Side::NONE);
}

int Player::get_exp() const {
  return exp_;
}

string Player::get_name() const {
  return name_;
}

void Player::change_exp(int exp) {
  exp_ = exp;
}

void Player::change_name(string&& name) {
  name_ = name;
}

void Player::make_player() {
  interface->print_get_name();
  name_ = interface->get_string();
}

void Player::change_room() {
  interface->print_get_room();
  Side side = interface->get_command_room();
  curr_room = curr_room->change_room(side);
  interface->print_new_room(side);
}

void Player::get_item() {
  if (get_rnd() % 3 == 1 and curr_item_ == nullptr) {
    interface->print_get_item_base();
    if (get_rnd() % 2 == 0) {
      curr_item_ = items.sword;
      interface->print_get_sword();
    } else {
      curr_item_ = items.stick;
      interface->print_get_stick();
    }
  }
}

void Player::get_item_while_running() {
  if (get_rnd() % 3 != 2 and curr_item_ == nullptr) {
    interface->print_get_item_run();
    if (get_rnd() % 2 == 0) {
      curr_item_ = items.sword;
        interface->print_get_sword();
    } else {
      curr_item_ = items.stick;
        interface->print_get_stick();
    }
  }
}

void Player::fight(Npc* opponent) {
  if (opponent->is_kill(exp_ / 2)) {
    interface->print_death();
    curr_item_ = nullptr;
    exp_ = 5;
    curr_room->curr_npc = opponent;
    return;
  }
  if (opponent->is_get_death(exp_ / 3)) {
    exp_ += opponent->get_exp();
    interface->print_win(opponent->name(), opponent->get_exp());
    get_item();
    return;
  }
  interface->print_draw();
  curr_room->curr_npc = opponent;
}

void Player::use_and_fight(Npc *opponent) {
  if (curr_item_->name == Name::RED_SWORD) {
    interface->print_use_sword();
    exp_ += curr_item_->change_exp();
    fight(opponent);
    exp_ -= curr_item_->change_exp();
    curr_item_ = nullptr;
    return;
  } else if (curr_item_->name == Name::FROST_STICK) {
    if (curr_item_->skip()) {
      exp_ += opponent->get_exp();
      interface->print_use_stick_true(opponent->get_exp());
    } else {
      interface->print_use_stick_false();
      fight(opponent);
    }
    curr_item_ = nullptr;
    return;
  } else if (curr_item_->name == Name::QUEST) {
    interface->print_use_quest(curr_item_->get_level());
    exp_ -= curr_item_->get_level();
    int save = exp_;
    fight(opponent);
    if (exp_ > save && exp_ != 5) {
      interface->print_pass_quest(3 * curr_item_->get_level());
      exp_ += 3 * curr_item_->get_level();
      if (curr_item_->name == Name::QUEST) {
        curr_item_ = nullptr;
      }
    }
    return;
  }
}

void Player::boss_game(Npc* opponent) {
  interface->print_boss_1();
  while (interface->get_string() != name_) {
    interface->print_boss_wrong_1();
  }
  interface->print_boss_2();
  while (interface->get_int() != exp_) {
    interface->print_boss_wrong_2();
  }
  if (exp_ < 17) {
    interface->print_boss_weak(opponent->get_exp());
  } else {
    interface->print_boss_3();
    while (interface->get_string() != "живой") {
      interface->print_boss_wrong_3();
    }
    interface->print_boss_strong(opponent->get_exp());
  }
  exp_ += opponent->get_exp();
}

void Player::prepare_for_fight(Npc* npc) {
    if (curr_item_ != nullptr) {
      interface->print_fight();
    } else {
      interface->print_fight_use();
    }
    Commands_fight act = interface->get_command_fight();
    if (act == Commands_fight::FIGHT) {
      fight(npc);
    } else if (act == Commands_fight::RUN) {
      exp_ -= 3;
      interface->print_run();
      curr_room->curr_npc = npc;
      get_item_while_running();
    } else if (act == Commands_fight::USE and curr_item_ != nullptr) {
        use_and_fight(npc);
    }
}

void Player::get_quest(Npc *npc) {
    Commands_quest act = interface->get_command_quest();
    if (act == Commands_quest::ACCEPT) {
      if (npc->get_exp() == 2) {
        curr_item_ = items.quest1;
      } else {
        curr_item_ = items.quest2;
      }
    } else if (act == Commands_quest::REJECT) {}
}

void Player::action(Npc* npc) {
  interface->print_choice();
  Commands_act act = interface->get_command_act();
  if (act == Commands_act::TALK) {
    npc->talk();
    if (npc->is_good() == Condition::GOOD) {
      exp_ += npc->get_exp();
    } else if (npc->is_good() == Condition::EVIL) {
      prepare_for_fight(npc);
    } else if (npc->is_good() == Condition::BOSS) {
      boss_game(npc);
    } else if (npc->is_good() == Condition::VIZIER) {
      get_quest(npc);
    }
  } else if (act == Commands_act::RUN) {
      curr_room->curr_npc = npc;
  }
  change_room();
}
