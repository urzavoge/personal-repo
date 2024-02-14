#include "room.h"
#include "items.h"

class Player {
 protected:

  string name_;
  int exp_ = 0;
  Items items = Items();
  Item* curr_item_ = nullptr;

 public:
  Interface* interface;
  Room* curr_room = nullptr;

  explicit Player(Interface* inter);
  ~Player();

  void make_player();
  void change_room();
  [[nodiscard]] int get_exp() const;
  [[nodiscard]] string get_name() const;
  void action(Npc* npc);
  void prepare_for_fight(Npc* npc);
  void get_quest(Npc* npc);
  void fight(Npc* opponent);
  void change_exp(int exp);
  void change_name(string&& name);
  void boss_game(Npc* opponent);
  void use_and_fight(Npc* opponent);
  void get_item();
  void get_item_while_running();
};