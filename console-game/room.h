#pragma once
#include "npc.h"


class Field {
  vector<string> field_;
 public:
  Interface* interface;


  void change(int x, int y, char sym);
  char get(int x, int y);

  Field(Interface* inter, int size);
  void print();
};

class Room {

  int num_;
  Room* left_;
  Room* right_;
  Room* top_;
  Room* bottom_;

 public:
  Npc* curr_npc = nullptr;
  Room(int num, Room* prev, Side side);

  Room* make_room(Side side);
  Room* change_room(Side side);
  void clear(Side side);

  void generate(Field& field, int x, int y);
};