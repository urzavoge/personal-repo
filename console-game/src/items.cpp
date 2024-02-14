#include "../items.h"

int Item::change_exp() { return 0; }
bool Item::skip() { return false; }
int Item::get_level() { return 9999; }


int Red_sword::change_exp() {
  return 5;
}

bool Frost_stick::skip() {
  return get_rnd() % 3 != 0;
}

int Quest::get_level() {
  return difficult;
}