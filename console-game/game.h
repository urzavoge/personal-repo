#pragma once
#include "player.h"

class Game {
  Interface* interface;
  mobs npcs = mobs(interface);

  Npc* npc;

 public:
  int level_;
  Player* user;

  explicit Game(Interface* inter);
  void start_game();
  void make_npc();
  void play();
  void download(string&& path = "info.txt");

  void end_game(string&& path = "info.txt");
  ~Game() {
    delete user;
  }
};