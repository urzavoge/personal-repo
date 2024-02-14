#include "../room.h"

Field::Field(Interface* inter, int size) {
  interface = inter;
  field_.resize(size, "");
  for (auto& str : field_) {
    for (int count = 0; count < size; ++count) {
      str += ' ';
    }
  }
}

void Field::change(int x, int y, char sym) {
  field_[y][x] = sym;
}

char Field::get(int x, int y) {
  return field_[y][x];
}

void Field::print() {
  int min_left = std::numeric_limits<int>::max();
  int min_right = std::numeric_limits<int>::max();
  for (auto& str : field_) {
    int local_min_left = 0;
    int local_min_right = 0;
    for (auto& ch : str) {
      if (ch == '+') break;
      ++local_min_left;
    }
    min_left = min(min_left, local_min_left);
    std::reverse(str.begin(), str.end());
    for (auto& ch : str) {
      if (ch == '+') break;
      ++local_min_right;
    }
    min_right = min(min_right, local_min_right);
  }
  for (auto& str : field_) {
    str.erase(str.size() - min_left, min_left);
    str.erase(0, min_right);
  }
  vector<string> copy(field_);
  for (int i = 0; i < field_.size(); ++i) {
    field_[i] = copy[field_.size() - i - 1];
  }
  for (auto& str : field_) {
    bool flag = true;
    for (auto& ch : str) {
      if (ch == '+' or ch == '|') flag = false;
    }
    if (flag) continue;
    interface->print_field(str);
  }
}

void Room::clear(Side side) {
  if (side != Side::LEFT) {
    if (right_ != nullptr) right_->clear(Side::RIGHT);
  }
  if (side != Side::BOTTOM) {
    if (top_ != nullptr) top_->clear(Side::TOP);
  }
  if (side != Side::RIGHT) {
    if (left_ != nullptr) left_->clear(Side::LEFT);
  }
  if (side != Side::TOP) {
    if (bottom_ != nullptr) bottom_->clear(Side::BOTTOM);
  }
  delete this;
}

Room::Room(int num, Room* prev, Side side) : num_(num), left_(nullptr),
                                             right_(nullptr),
                                             top_(nullptr),
                                             bottom_(nullptr) {
  if (side == Side::LEFT) {
    right_ = prev;
  }
  if (side == Side::RIGHT) {
    left_ = prev;
  }
  if (side == Side::TOP) {
    bottom_ = prev;
  }
  if (side == Side::BOTTOM) {
    top_ = prev;
  }
}

Room* Room::make_room(Side side) {
  Room* new_room = new Room(num_ + 1, this, side);
  if (side == Side::LEFT) {
    left_ = new_room;
  }
  if (side == Side::RIGHT) {
    right_ = new_room;
  }
  if (side == Side::TOP) {
    top_ = new_room;
  }
  if (side == Side::BOTTOM) {
    bottom_ = new_room;
  }
  return new_room;
}

Room* Room::change_room(Side side) {
  if (side == Side::LEFT) {
    if (this->left_ != nullptr) return this->left_;
  }
  if (side == Side::RIGHT) {
    if (this->right_ != nullptr) return this->right_;
  }
  if (side == Side::TOP) {
    if (this->top_ != nullptr) return this->top_;
  }
  if (side == Side::BOTTOM) {
    if (this->bottom_ != nullptr) return this->bottom_;
  }
  return make_room(side);
}

void Room::generate(Field& field, int x, int y) {
  if (field.get(x, y) == '+') {
    return;
  }
  field.change(x, y, '+');
  if (left_ != nullptr) {
    field.change(x + 1, y, '-');
    left_->generate(field, x + 2, y);
  }
  if (right_ != nullptr) {
    field.change(x - 1, y, '-');
    right_->generate(field, x - 2, y);
  }
  if (top_ != nullptr) {
    field.change(x, y + 1, '|');
    top_->generate(field, x, y  + 2);
  }
  if (bottom_ != nullptr) {
    field.change(x, y - 1, '|');
    bottom_->generate(field, x, y - 2);
  }
}