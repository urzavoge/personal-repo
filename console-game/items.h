#pragma once
#include <random>
#include <ctime>

struct PRNG {
  std::mt19937 engine;
};

static void initGenerator(PRNG& generator) {
  auto seed = unsigned(std::time(nullptr));
  generator.engine.seed(seed);
}

static size_t getRandomIndex(PRNG& generator, size_t size) {
  std::uniform_int_distribution<size_t> distribution(0, size - 1);
  return distribution(generator.engine);
}

static size_t get_rnd() {
  PRNG gen;
  initGenerator(gen);
  return getRandomIndex(gen, 60);
}

enum class Name {
  NO,
  RED_SWORD,
  FROST_STICK,
  QUEST
};

class Item {
 public:
  Name name = Name::NO;
  explicit Item(Name nam) : name(nam) {}
  virtual int change_exp();
  virtual bool skip();
  virtual int get_level();
};

class Red_sword : virtual public Item {
 public:
  Red_sword() : Item(Name::RED_SWORD) {}
  int change_exp() final;
};

class Frost_stick : virtual public Item {
 public:
  Frost_stick() : Item(Name::FROST_STICK) {}
  bool skip() final;
};

class Quest : virtual public Item {
  int difficult;
 public:
  explicit Quest(int x) : Item(Name::QUEST), difficult(x) {}
  int get_level() final;
};

struct Items {
  Red_sword* sword;
  Frost_stick* stick;
  Quest* quest1;
  Quest* quest2;

  Items() {
    sword = new Red_sword();
    stick = new Frost_stick();
    quest1 = new Quest(2);
    quest2 = new Quest(4);
  }

  ~Items() {
    delete sword;
    delete stick;
    delete quest1;
    delete quest2;
  }
};


