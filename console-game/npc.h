#include "interface.h"

enum class Condition {
  GOOD,
  EVIL,
  BOSS,
  VIZIER
};
class Npc {
 protected:

  int damage_;
  int health_;
  int exp_;

 public:
  Interface* interface;

  Npc() = default;
  Npc(int dam, int hea, int exp, Interface* inter) : damage_(dam), health_(hea), exp_(exp), interface(inter) {}

  virtual void talk();
  virtual Condition is_good();
  virtual string name();

  [[nodiscard]] bool is_get_death(int dam) const;
  [[nodiscard]] bool is_kill(int hea) const;
  [[nodiscard]] int get_exp() const;
};

class Goblin : virtual public Npc {
  string name_;
 public:

  Goblin(int dam, int hea, int exp, Interface* inter, string&& nam) : Npc(dam, hea, exp, inter), name_(std::move(nam)) {}

  void talk() final;
  string name() final;
  Condition is_good() final;
};

class Citizen : virtual public Npc {
  string name_;
 public:

  Citizen(int dam, int hea, int exp, Interface* inter, string&& nam) : Npc(dam, hea, exp, inter), name_(std::move(nam)) {}

  void talk() final;
  string name() final;
  Condition is_good() final;
};

class Prisoner : virtual public Npc {
  string name_;
 public:
  Prisoner(int dam, int hea, int exp, Interface* inter, string&& nam) : Npc(dam, hea, exp, inter), name_(std::move(nam)) {}

  string name() final;
  void talk() final;
  Condition is_good() final;
};

class Vizier : virtual public Npc {
  string name_;
 public:
  Vizier(int exp, Interface* inter, string&& nam) : Npc(0, 0, exp, inter), name_(std::move(nam)) {}

  string name() final;
  void talk() final;
  Condition is_good() final;
};

class Boss: virtual public Npc {
 public:
  explicit Boss(Interface* inter) : Npc(0, 0, 10, inter) {}

  void talk() final;
  Condition is_good() final;
};

struct mobs {
  Interface* interface;
  Goblin* ura1;
  Goblin* ura2;
  Citizen* egor1;
  Citizen* egor2;
  Prisoner* ars1;
  Prisoner* ars2;
  Vizier* lola1;

  Boss* boss1;

  Goblin* pasha1;
  Goblin* pasha2;
  Citizen* null1;
  Citizen* null2;
  Prisoner* tan1;
  Prisoner* tan2;
  Vizier* lola2;

  explicit mobs(Interface* inter) : interface(inter) {
    ura1 = new Goblin(1, 2, 2, interface, "Юра");
    ura2 = new Goblin(3, 4, 4, interface, "Супер Юра");
    egor1 = new Citizen(1, 2, 2, interface, "Егор");
    egor2 = new Citizen(1, 2, 3, interface, "Егор");
    ars1 = new Prisoner(1, 2, 2, interface, "Арслан");
    ars2 = new Prisoner(5, 4, 5, interface, "Супер Арслан");
    lola1 = new Vizier(2, interface, "Лола");
    boss1 = new Boss(interface);
    pasha1 = new Goblin(3, 2, 3, interface, "Паша");
    pasha2 = new Goblin(3, 10, 5, interface, "Супер Паша");
    null1 = new Citizen(1, 2, 1, interface, "Жадина");
    null2 = new Citizen(1, 2, 1, interface, "Жадина");
    tan1 = new Prisoner(11, 2, 2, interface, "Злой Таша");
    tan2 = new Prisoner(5, 20, 10, interface, "Мирный Таша");
    lola2 = new Vizier(4, interface, "Лола");
  }

  ~mobs() {
    delete ura1;
    delete ura2;
    delete egor1;
    delete egor2;
    delete ars1;
    delete ars2;
    delete lola1;
    delete boss1;
    delete pasha1;
    delete pasha2;
    delete null1;
    delete null2;
    delete tan1;
    delete tan2;
    delete lola2;
  }
};