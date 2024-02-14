#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>


using std::to_string, std::ifstream, std::ofstream, std::fstream, std::pair,
      std::exception, std::cin, std::vector, std::cout, std::string, std::min, std::max;

class end_process : public exception {};

class wrong_data : public exception {};

enum class Side {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
    NONE
};

enum class Commands_menu {
    ENTER_GOD_MODE,
    PLAY,
    READ,
    LOAD,
    SHOW
};

enum class Commands_act {
    RUN,
    TALK
};

enum class Commands_fight {
    FIGHT,
    RUN,
    USE
};

enum class Commands_quest {
    ACCEPT,
    REJECT
};

struct Interface {
  virtual Commands_menu get_command_menu() = 0;
  virtual Side get_command_room() = 0;
  virtual Commands_act get_command_act() = 0;
  virtual Commands_fight get_command_fight() = 0;
  virtual Commands_quest get_command_quest() = 0;
  virtual string get_string() = 0;
  virtual int get_int() = 0;


  virtual void show(string&& path) = 0;
  virtual void print_info() = 0;
  virtual void print_head_command() = 0;
  virtual void print_exit_game() = 0;
  virtual void print_good_load() = 0;
  virtual void print_bad_load() = 0;
  virtual void print_god_mode() = 0;
  virtual void print_start_process() = 0;
  virtual void print_end_process() = 0;

  virtual void print_start_game1() = 0;
  virtual void print_start_game2() = 0;
  virtual void print_end_game(int exp) = 0;
  virtual void print_base_iteration() = 0;
  virtual void print_get_name() = 0;
  virtual void print_get_room() = 0;
  virtual void print_new_room(Side side) = 0;

  virtual void print_get_item_base() = 0;
  virtual void print_get_item_run() = 0;
  virtual void print_get_sword() = 0;
  virtual void print_get_stick() = 0;
  virtual void print_death() = 0;
  virtual void print_draw() = 0;
  virtual void print_win(string name, int exp) = 0;
  virtual void print_use_sword() = 0;
  virtual void print_use_stick_true(int exp) = 0;
  virtual void print_use_stick_false() = 0;
  virtual void print_use_quest(int exp) = 0;
  virtual void print_pass_quest(int exp) = 0;

  virtual void print_boss_1() = 0;
  virtual void print_boss_2() = 0;
  virtual void print_boss_3() = 0;
  virtual void print_boss_weak(int exp) = 0;
  virtual void print_boss_strong(int exp) = 0;
  virtual void print_boss_wrong_1() = 0;
  virtual void print_boss_wrong_2() = 0;
  virtual void print_boss_wrong_3() = 0;

  virtual void print_fight() = 0;
  virtual void print_fight_use() = 0;
  virtual void print_run() = 0;
  virtual void print_choice() = 0;

  virtual void print_goblin(string& name, int dam) = 0;
  virtual void print_citizen(string& name, int exp) = 0;
  virtual void print_prisoner(string& name, int dam, int exp) = 0;
  virtual void print_boss() = 0;
  virtual void print_vizier(string& name) = 0;
  virtual void print_field(string map) = 0;
};

struct ConsoleInterface : virtual Interface{
  Commands_menu get_command_menu() final;
  Side get_command_room() final;
  Commands_act get_command_act() final;
  Commands_fight get_command_fight() final;
  Commands_quest get_command_quest() final;
  string get_string() final;
  int get_int() final;


  void show(string&& path) final;
  void print_info() final;
  void print_head_command() final;
  void print_exit_game() final;
  void print_good_load() final;
  void print_bad_load() final;
  void print_god_mode() final;
  void print_start_process() final;
  void print_end_process() final;

  void print_start_game1() final;
  void print_start_game2() final;
  void print_end_game(int exp) final;
  void print_base_iteration() final;
  void print_get_name() final;
  void print_get_room() final;
  void print_new_room(Side side) final;

  void print_get_item_base() final;
  void print_get_item_run() final;
  void print_get_sword() final;
  void print_get_stick() final;
  void print_death() final;
  void print_draw() final;
  void print_win(string name, int exp) final;
  void print_use_sword() final;
  void print_use_stick_true(int exp) final;
  void print_use_stick_false() final;
  void print_use_quest(int exp) final;
  void print_pass_quest(int exp) final;

  void print_boss_1() final;
  void print_boss_2() final;
  void print_boss_3() final;
  void print_boss_weak(int exp) final;
  void print_boss_strong(int exp) final;
  void print_boss_wrong_1() final;
  void print_boss_wrong_2() final;
  void print_boss_wrong_3() final;

  void print_fight() final;
  void print_fight_use() final;
  void print_run() final;
  void print_choice() final;

  void print_goblin(string& name, int dam) final;
  void print_citizen(string& name, int exp) final;
  void print_prisoner(string& name, int dam, int exp) final;
  void print_boss() final;
  void print_vizier(string& name) final;
  void print_field(string map) final;
};