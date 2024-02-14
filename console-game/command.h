#include "game.h"

struct Command {

  explicit Command(Interface* inter) : interface(inter) {}
  void play(string&& path_save = "save.txt", string&& path_info = "info.txt");
  void show(string&& path = "save.txt");
  void read();
  void load(string&& path = "info.txt");
  void god_mode(string&& path_save = "save.txt", string&& path_info = "info.txt");

  void execute();

 private:
  Interface* interface;
};