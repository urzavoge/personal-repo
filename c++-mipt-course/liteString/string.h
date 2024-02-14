#pragma once

#include <algorithm>
#include <iostream>
#include <cstring>

class String {
 private:
  size_t size_;
  size_t capacity_;
  char* str;

  void resize(size_t increase);

 public:
  String();
  String(size_t n, char value);
  String(const char* c_string);
    String(const String& other);
  String(char value);
  ~String() {
    delete[] str;
  }

  void push_back(char value);
  void pop_back();
  String& operator=(const String& other);
  size_t length() const;
  size_t size() const;
  size_t capacity() const;
  char* data();
  const char* data() const;
  char& operator[](size_t index);
  const char& operator[](size_t index) const;
  char& front();
  char& back();
  const char& front() const;
  const char& back() const;
  bool empty() const;
  void clear();
  void shrink_to_fit();
  String& operator+=(const String& other);
  String substr(size_t start, size_t count) const;
  size_t find(const String& substring) const;
  size_t rfind(const String& substring) const;
  bool is_substr_here(size_t i, const String& substring) const;
  void swap(String& first, String& second);
};

String::String() : size_(0), capacity_(0), str(new char[1]) {
  str[0] = '\0';
}

String::String(size_t n, char value) : size_(n), capacity_(n), str(new char[capacity_ + 1]) {
  std::fill(str, str + size_, value);
  str[size_] = '\0';
}

String::String(const char* c_string) : size_(strlen(c_string)), capacity_(size_), str(new char[capacity_ + 1]) {
  std::copy(c_string, c_string + size_, str);
  str[size_] = '\0';
}

String::String(const String& other) : size_(other.size_), capacity_(other.capacity_), str(new char[capacity_ + 1]) {
  std::copy(other.str, other.str + size_, str);
  str[size_] = '\0';
}

String::String(char value) : size_(1), capacity_(1), str(new char[2]) {
  str[0] = value;
  str[1] = '\0';
}

std::ostream& operator<<(std::ostream& out, const String& other) {
  out << other.data();
  return out;
}

std::istream& operator>>(std::istream& in, String& other) {
  other.clear();
  char value;
  while (in.get(value) && !isspace(value)) {
    other.push_back(value);
  }
  return in;
}

String operator+(const String& first, const String& second) {
  String copy(first);
  copy += second;
  return copy;
}

bool operator<(const String& left, const String& right) {
  size_t stop = (left.size() < right.size()) ? left.size() : right.size();
  for (size_t i = 0; i < stop; ++i) {
    if (left[i] != right[i]) {
      return left[i] < right[i];
    }
  }
  return left.size() < right.size();
}

bool operator>(const String& left, const String& right) {
  return right < left;
}

bool operator<=(const String& left, const String& right) {
  return !(right < left);
}

bool operator>=(const String& left, const String& right) {
  return !(right > left);
}

bool operator==(const String& left, const String& right) {
  if (left.size() != right.size()) {
    return false;
  }
  for (size_t i = 0; i < left.size(); ++i) {
    if (left[i] != right[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const String& left, const String& right) {
  return !(left == right);
}

void String::push_back(char value) {
  if (size_ == capacity_) {
    resize(2 * capacity_ + 2);
  }
  str[size_] = value;
  str[++size_] = '\0';
}

void String::pop_back() {
  str[--size_] = '\0';
}

void String::clear() {
  size_ = 0;
  str[size_] = '\0';
}

void String::shrink_to_fit() {
  resize(size_);
  str[size_] = '\0';
}

String& String::operator+=(const String& other) {
  if (size_ + other.size_ > capacity_) {
    resize(size_ + other.size_);
  }
  std::copy(other.str, other.str + other.size_, str + size_);
  size_ += other.size_;
  str[size_] = '\0';
  return *this;
}

String String::substr(size_t start, size_t count) const {
  String answer(count, '\0');
  std::copy(str + start, str + start + count, answer.str);
  return answer;
}

bool String::is_substr_here(size_t i, const String& substring) const {
  for (size_t j = 0; j < substring.size(); ++j, ++i) {
    if (str[i] != substring.str[j]) {
      return false;
    }
  }
  return true;
}

size_t String::find(const String& substring) const {
  for (size_t i = 0; i + substring.size() < size_ + 1; ++i) {
    if (is_substr_here(i, substring)) {
      return i;
    }
  }
  return size_;
}

size_t String::rfind(const String& substring) const {
  if (substring.size() > size_) {
    return size_;
  }
  for (size_t i = size_; i >= substring.size(); --i) {
    if (is_substr_here(i - substring.size(), substring)) {
      return i - substring.size();
    }
  }
  return size_;
}

void String::swap(String& first, String& second) {
  std::swap(first.capacity_, second.capacity_);
  std::swap(first.size_, second.size_);
  std::swap(first.str, second.str);
}

String& String::operator=(const String& other) {
  if (&other == this) { return *this; }
  if (capacity_ < other.size_) {
    String copy(other);
    swap(copy, *this);
    return *this;
  }
  size_ = other.size_;
  std::copy(other.str, other.str + size_ + 1, str);
  return *this;
}

void String::resize(size_t increase) {
  capacity_ = increase;
  char* copy = new char[increase + 1];
  std::copy(str, str + size_ + 1, copy);
  delete[] str;
  str = copy;
}

size_t String::length() const {
  return size_;
}

size_t String::size() const {
  return size_;
}

size_t String::capacity() const {
  return capacity_;
}

char* String::data() {
  return str;
}

const char* String::data() const {
  return str;
}

char& String::operator[](size_t index) {
  return str[index];
}

const char& String::operator[](size_t index) const {
  return str[index];
}

char& String::front() {
  return str[0];
}

char& String::back() {
  return str[size_ - 1];
}

const char& String::front() const {
  return str[0];
}

const char& String::back() const {
  return str[size_ - 1];
}

bool String::empty() const {
  return size_ == 0;
}