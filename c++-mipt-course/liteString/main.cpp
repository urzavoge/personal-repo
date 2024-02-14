#include <iostream>

#include <algorithm>

#include <cstring>

class String {
 private:
  char* str = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;

  void resize(size_t increase) {
    if (increase == 0) {
      increase += 1;
    }
    capacity_ = increase;
    char* inc_str = new char[increase + 1];
    std::copy(str, str + size_ + 1, inc_str);
    delete[] str;
    str = inc_str;
  }

 public:
  String() {
    size_ = 0;
    capacity_ = 0;
    str = new char[1];
    str[0] = '\0';
  }

  String(size_t n, const char& val) {
    size_ = n;
    capacity_ = n;
    str = new char[capacity_ + 1];
    std::fill(str, str + size_, val);
    str[size_] = '\0';
  }

  String(const char* cstr) {
    size_ = capacity_ = strlen(cstr);
    str = new char[capacity_ + 1];
    std::copy(cstr, cstr + size_, str);
    str[size_] = '\0';
  }

  String(const String& mum) {
    size_ = mum.size_;
    capacity_ = mum.capacity_;
    str = new char[capacity_ + 1];
    std::copy(mum.str, mum.str + size_, str);
    str[size_] = '\0';
  }

  String(const char& val) {
    size_ = capacity_ = 1;
    str = new char[2];
    str[0] = val;
    str[1] = '\0';
  }

  ~String() {
    delete[] str;
  }

  String& operator=(const String& mum) {
    if (&mum == this) { return *this; }
    if (capacity_ >= mum.capacity_) {
      size_ = mum.size_;
      std::copy(mum.str, mum.str + size_ + 1, str);
      return *this;
    }
    resize(mum.capacity_);
    size_ = mum.size_;
    std::copy(mum.str, mum.str + size_, str);
    str[size_] = '\0';
    return *this;
  }

  size_t length() const {
    return size_;
  }

  size_t size() const {
    return size_;
  }

  size_t capacity() const {
    return capacity_;
  }

  char* data() {
    return str;
  }

  const char* data() const {
    return str;
  }

  void push_back(const char& val) {
    if (size_ < capacity_) {
      str[size_] = val;
      ++size_;
      str[size_] = '\0';
    } else {
      resize(2 * capacity_);
      str[size_] = val;
      ++size_;
      str[size_] = '\0';
    }
  }

  void pop_back() {
    --size_;
    str[size_] = '\0';
  }

  char& operator[](size_t index) {
    return str[index];
  }

  const char& operator[](size_t index) const {
    return str[index];
  }

  char& front() {
    return str[0];
  }

  char& back() {
    return str[size_ - 1];
  }

  const char& front() const {
    return str[0];
  }

  const char& back() const {
    return str[size_ - 1];
  }

  bool empty() const {
    return size_ == 0;
  }

  void clear() {
    size_ = 0;
    str[size_] = '\0';
  }

  void shrink_to_fit() {
    resize(size_);
    str[size_] = '\0';
  }

  String& operator+=(const String& uvel) {
    if (capacity_ >= size_ + uvel.size_) {
      std::copy(uvel.str, uvel.str + uvel.size_, str + size_);
      size_ += uvel.size_;
      str[size_] = '\0';
    } else {
      resize(capacity_ + uvel.capacity_);
      std::copy(uvel.str, uvel.str + uvel.size_, str + size_);
      size_ += uvel.size_;
      str[size_] = '\0';
    }
    return *this;
  }

  bool is_smaller(const String& mum) const {
    size_t i = 0;
    for (; i < size_ && i < mum.size_; ++i) {
      if (str[i] < mum.str[i]) { return true; }
      if (str[i] > mum.str[i]) { return false; }
    }
    if (i == size_ && i != mum.size_) { return true; }
    return false;
  }

  String substr(size_t start, size_t count) const {
    String ans(count, '\0');
    std::copy(str + start, str + start + count, ans.str);
    return ans;
  }

  size_t find(const String& sub) const {
    size_t len = sub.size();
    std::cerr << str;
    for (size_t i = 0; i + len < size_ + 1; ++i) {
      size_t flag = 0;
      for (size_t j = 0; j < len; ++j) {
        if (sub.str[j] == str[i + j]) {
          ++flag;
        }
      }
      if (flag == len) { return i; }
    }
    return size_;
  }

  size_t rfind(const String& sub) const {
    size_t len = sub.size_;
    if (len > size_) {
      return size_;
    }
    size_t ans = size_;
    for (size_t i = 0; i + len < size_ + 1; ++i) {
      size_t flag = 0;
      for (size_t j = 0; j < len; ++j) {
        if (sub.str[j] == str[i + j]) {
          ++flag;
        }
      }
      if (flag == len) { ans = i; }
    }
    return ans;
  }
};

std::ostream& operator<<(std::ostream& out, const String& mum) {
  for (size_t i = 0; i < mum.size(); ++i) {
    out << mum[i];
  }
  return out;
}

std::istream& operator>>(std::istream& in, String& mum) {
  mum.clear();
  char val;
  while (true) {
    if (!in.get(val)) { break; }
    if (val == '\0' || val == EOF || val == '\n') { break; }
    if (val != ' ') { mum.push_back(val); }
  }
  return in;
}

String operator+(String slag1, const String& slag2) {
  slag1 += slag2;
  return slag1;
}

bool operator<(const String& left, const String& right) {
  return left.is_smaller(right);
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
  return (left >= right) && (left <= right);
}

bool operator!=(const String& left, const String& right) {
  return !(left == right);
}

using namespace std;

signed main() {
  String s{};
  for (int i = 0; i < 1000; ++i) {
    s.push_back('a');
  }
  return 0;
}