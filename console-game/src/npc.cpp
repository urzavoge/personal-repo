#include "../npc.h"

string Npc::name() {
  return "";
}

void Npc::talk() {}

int Npc::get_exp() const {
  return exp_;
}

bool Npc::is_get_death(int dam) const {
  return dam >= health_;
}

bool Npc::is_kill(int hea) const {
  return hea <= damage_;
}

Condition Npc::is_good() {
  return Condition::GOOD;
}

Condition Goblin::is_good() {
  return Condition::EVIL;
}

string Goblin::name() {
  return name_;
}

void Goblin::talk() {
  interface->print_goblin(name_, damage_);
}

Condition Citizen::is_good() {
  return Condition::GOOD;
}

string Citizen::name() {
  return name_;
}

void Citizen::talk() {
  interface->print_citizen(name_, exp_);
}

string Prisoner::name() {
  return name_;
}

void Prisoner::talk() {
  interface->print_prisoner(name_, damage_, exp_);
}

Condition Prisoner::is_good() {
  return Condition::EVIL;
}

void Boss::talk() {
  interface->print_boss();
}

Condition Boss::is_good() {
  return Condition::BOSS;
}

string Vizier::name() {
  return name_;
}

void Vizier::talk() {
  interface->print_vizier(name_);
}

Condition Vizier::is_good() {
  return Condition::VIZIER;
}