#pragma once

#include <iostream>
#include <sstream>
#include <vector>

using std::cin, std::cout, std::vector, std::ostream, std::istream, std::string, std::stringstream, std::max;

class BigInteger {
private:
  static const int mod = 1e7;
  bool isNotNegative;
  vector<int64_t> chanks;
public:
  void Norm();
  BigInteger& operator=(const BigInteger& other);
  BigInteger();
  BigInteger(int64_t x);
  BigInteger(bool znak, vector<int64_t> copy);
  BigInteger(const string& str);
  BigInteger(const BigInteger& other) : isNotNegative(other.isNotNegative), chanks(other.chanks) {}
  string toString() const;
  bool isLess(const BigInteger& other) const;
  bool isEqual(const BigInteger& other) const;
  bool isNull() const;
  BigInteger abs() const;
  BigInteger& operator+=(const BigInteger& other);
  BigInteger& operator++();
  BigInteger operator++(int);
  BigInteger& operator--();
  BigInteger operator--(int);
  BigInteger& operator-();
  BigInteger& operator-=(const BigInteger& other);
  BigInteger simpleMult(int64_t x) const;
  void newChanks();
  BigInteger& operator*=(const BigInteger& other);
  BigInteger& operator/=(const BigInteger& other);
  BigInteger& operator%=(const BigInteger& other);
  explicit operator bool() const {
    return !(this->isNull());
  }
};

BigInteger& BigInteger::operator=(const BigInteger& other) {
  if (&other == this) { return *this; }
  isNotNegative = other.isNotNegative;
  chanks = other.chanks;
  return *this;
}

BigInteger::BigInteger() {
  chanks.push_back(0);
  isNotNegative = true;
}

BigInteger::BigInteger(int64_t x) {
  if (x == 0) {
    chanks.push_back(0);
    isNotNegative = true;
  } else {
    isNotNegative = (x > 0);
    x *= (x > 0) ? 1 : -1;
    while (x) {
      chanks.push_back(x % mod);
      x /= mod;
    }
  }
}

BigInteger::BigInteger(bool znak, vector<int64_t> copy) :  isNotNegative(znak), chanks(copy) {}

BigInteger::BigInteger(const string& str) {
  isNotNegative = (str[0] != '-');
  int i = static_cast<int>(str.size()) - 1;
  int64_t base = 1, num = 0;
  while ((str[i] != '-') && i >= 0) {
    num += base * (str[i] - '0');
    base *= 10;
    if (base == mod) {
      base = 1;
      chanks.push_back(num);
      num = 0;
    }
    --i;
  }
  chanks.push_back(num);
  Norm();
}

string BigInteger::toString() const {
  stringstream ans;
  if (!isNotNegative) {
    ans << '-';
  }
  ans << chanks.back();
  for (int i = static_cast<int>(chanks.size()) - 2; i >= 0; --i) {
    int64_t num = chanks[i];
    int64_t j = 1e6;
    while (j) {
      ans << num / j;
      num %= j;
      j /= 10;
    }
  }
  return ans.str();
}

ostream& operator<<(ostream& out, const BigInteger& x) {
  out << x.toString();
  return out;
}

BigInteger BigInteger::abs() const {
  return BigInteger(true, this->chanks);
}

bool BigInteger::isLess(const BigInteger& other) const {
  if (isNotNegative != other.isNotNegative) {
    return (!isNotNegative);
  }
  if (chanks.size() < other.chanks.size()) {
    return (isNotNegative);
  }
  if (chanks.size() > other.chanks.size()) {
    return !(isNotNegative);
  }
  int index = static_cast<int>(chanks.size()) - 1;
  while (index + 1) {
    if (chanks[index] < other.chanks[index]) {
      return (isNotNegative);
    }
    if (chanks[index] > other.chanks[index]) {
      return !(isNotNegative);
    }
    --index;
  }
  return false;
}

bool BigInteger::isEqual(const BigInteger &other) const {
  if (isNotNegative != other.isNotNegative) {
    return false;
  }
  if (chanks.size() != other.chanks.size()) {
    return false;
  }
  int index = static_cast<int>(chanks.size()) - 1;
  while (index + 1) {
    if (chanks[index] != other.chanks[index]) {
      return false;
    }
    --index;
  }
  return true;
}

bool BigInteger::isNull() const {
  return (chanks.size() == 1 && chanks[0] == 0);
}

bool operator<(const BigInteger& one, const BigInteger& second) {
  return one.isLess(second);
}

bool operator>(const BigInteger& one, const BigInteger& second) {
  return second.isLess(one);
}

bool operator<=(const BigInteger& one, const BigInteger& second) {
  return !(second.isLess(one));
}

bool operator>=(const BigInteger& one, const BigInteger& second) {
  return !(one.isLess(second));
}

bool operator==(const BigInteger& one, const BigInteger& second) {
  return one.isEqual(second);
}

bool operator!=(const BigInteger& one, const BigInteger& second) {
  return !(one.isEqual(second));
}

void BigInteger::Norm() {
  int64_t ostatok = 0;
  for (size_t i = 0; i < chanks.size(); ++i) {
    if (chanks[i] + ostatok < 0) {
      int64_t temp = mod + chanks[i] + ostatok;
      chanks[i] = temp % mod;
      ostatok = -1;
    } else {
      int64_t temp = chanks[i] + ostatok;
      ostatok = temp / mod;
      chanks[i] = temp % mod;
    }
  }
  if (ostatok > 0) { chanks.push_back(ostatok); }
  if (ostatok < 0) {
    chanks.push_back(-ostatok);
    isNotNegative = !isNotNegative;
  }
  while (chanks.size() > 1 && chanks.back() == 0) {
    chanks.pop_back();
  }
  if (chanks.back() == 0) {
    isNotNegative = true;
  }
}

BigInteger& BigInteger::operator+=(const BigInteger& other) {
  if ((isNotNegative && other.isNotNegative) || (!isNotNegative && !other.isNotNegative)) {
    for (size_t i = 0; i < other.chanks.size(); ++i) {
      if (i >= chanks.size()) {
        chanks.push_back(other.chanks[i]);
      } else {
        chanks[i] += other.chanks[i];
      }
    }
    Norm();
    return *this;
  }
  if (other.abs() == this->abs()) {
    isNotNegative = true;
    chanks = vector<int64_t> {0};
    return *this;
  }
  if (other.abs().isLess(this->abs())) {
    for (size_t i = 0; i < other.chanks.size(); ++i) {
      chanks[i] -= other.chanks[i];
    }
    Norm();
    return *this;
  }
  vector<int64_t> copy = chanks;
  chanks = other.chanks;
  for (size_t i = 0; i < copy.size(); ++i) {
    chanks[i] -= copy[i];
  }
  Norm();
  isNotNegative = !isNotNegative;
  return *this;
}

BigInteger& BigInteger::operator++() {
  return (*this) += 1;
}

BigInteger BigInteger::operator++(int) {
  BigInteger copy = *this;
  (*this) += 1;
  return copy;
}

BigInteger& BigInteger::operator--() {
  return (*this) -= 1;
}

BigInteger BigInteger::operator--(int) {
  BigInteger copy = *this;
  (*this) -= 1;
  return copy;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
  BigInteger copy(!other.isNotNegative, other.chanks);
  (*this) += copy;
  return *this;
}

void BigInteger::newChanks() {
  chanks.insert(chanks.begin(), 0);
}

BigInteger BigInteger::simpleMult(int64_t x) const {
  BigInteger temp = *this;
  if (x == mod) {
    temp.newChanks();
    return temp;
  }
  for (size_t i = 0; i < chanks.size(); ++i) {
    temp.chanks[i] *= x;
  }
  temp.Norm();
  return temp;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
  isNotNegative = (isNotNegative == other.isNotNegative);
  vector<int64_t> ostatok(0);
  ostatok.resize(chanks.size() + other.chanks.size() + 1);
  for (size_t i = 0; i < chanks.size(); ++i) {
    for (size_t j = 0; j < other.chanks.size(); ++j) {
      ostatok[i + j] += chanks[i] * other.chanks[j];
    }
  }
  chanks = ostatok;
  Norm();
  return *this;
}

BigInteger operator*(const BigInteger& first, const BigInteger& second) {
  BigInteger new_first = first;
  new_first *= second;
  return new_first;
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
  isNotNegative = (isNotNegative == other.isNotNegative);
  BigInteger ostatok;
  for (int64_t i = static_cast<int64_t>(chanks.size()) - 1; i >= 0; --i) {
    ostatok.newChanks();
    ostatok.chanks[0] = chanks[i];
    ostatok.Norm();
    int64_t num = 0, left = 0, right = mod;
    while (left <= right) {
      int64_t mid = (right + left) / 2;
      if (other.abs() * mid <= ostatok) {
        num = mid;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    chanks[i] = num;
    ostatok -= other.abs() * num;
  }
  Norm();
  return *this;
}

BigInteger& BigInteger::operator-() {
  isNotNegative = !isNotNegative;
  Norm();
  return *this;
}

BigInteger operator+(const BigInteger& first, const BigInteger& second) {
  BigInteger new_first = first;
  new_first += second;
  return new_first;
}

BigInteger operator-(const BigInteger& first, const BigInteger& second) {
  BigInteger new_first = first;
  new_first -= second;
  return new_first;
}

BigInteger operator/(const BigInteger& first, const BigInteger& second) {
  BigInteger new_first = first;
  new_first /= second;
  return new_first;
}

BigInteger& BigInteger::operator%=(const BigInteger& other) {
  *this -= ((*this / other) * other);
  return *this;
}

BigInteger operator%(const BigInteger& first, const BigInteger& second) {
  BigInteger new_first = first;
  new_first %= second;
  return new_first;
}

istream& operator>>(istream& in, BigInteger& x) {
  string str;
  in >> str;
  x = BigInteger(str);
  return in;
}

BigInteger operator""_bi(const char* str, size_t) {
  return BigInteger(str);
}

static BigInteger nod(BigInteger first, BigInteger second) {
  if (first == 0 || second == 0) { return first + second; }
  if (first == second) { return first; }
  if (first == 1 || second == 1) { return 1; }
  if (first > second) { return nod(first % second, second); }
  return nod(first, second % first);
}

BigInteger stepen(BigInteger osn, int64_t step) {
  BigInteger res = 1;
  while (step) {
    if (step & 1) {
      res *= osn;
      --step;
    } else {
      osn *= osn;
      step >>= 1;
    }
  }
  return res;
}

class Rational {
private:
  BigInteger numerator;
  BigInteger denominator;
public:
  void norm_sign();
  Rational& operator=(const Rational& other);
  Rational();
  Rational(const BigInteger& x);
  Rational(int64_t x);
  Rational(const Rational& other) : numerator(other.numerator), denominator(other.denominator) {}
  bool isEqual(const Rational& other) const;
  bool isLess(const Rational& other) const;
  Rational& operator+=(const Rational& other);
  Rational& operator-=(const Rational& other);
  Rational& operator*=(const Rational& other);
  Rational& operator/=(const Rational& other);
  Rational& operator-();
  string toString() const;
  string asDecimal(size_t precision = 0) const;
  explicit operator double() const {
    stringstream temp(asDecimal(37));
    double ans;
    temp >> ans;
    return ans;
  }
};

void Rational::norm_sign() {
  if (denominator < 0) {
    numerator *= -1;
    denominator *= -1;
  }
}

Rational& Rational::operator=(const Rational& other) {
  numerator = other.numerator;
  denominator = other.denominator;
  return *this;
}

Rational::Rational() {
  numerator = BigInteger(0);
  denominator = BigInteger(1);
}

Rational::Rational(int64_t x) {
  numerator = BigInteger(x);
  denominator = BigInteger(1);
}

Rational::Rational(const BigInteger& x) {
  numerator = x;
  denominator = BigInteger(1);
}

bool Rational::isEqual(const Rational &other) const {
  return (numerator * other.denominator).isEqual(denominator * other.numerator);
}

bool Rational::isLess(const Rational &other) const {
  return (numerator * other.denominator).isLess(denominator * other.numerator);
}

bool operator<(const Rational& one, const Rational& second) {
  return one.isLess(second);
}

bool operator>(const Rational& one, const Rational& second) {
  return second.isLess(one);
}

bool operator<=(const Rational& one, const Rational& second) {
  return !(second.isLess(one));
}

bool operator>=(const Rational& one, const Rational& second) {
  return !(one.isLess(second));
}

bool operator==(const Rational& one, const Rational& second) {
  return one.isEqual(second);
}

bool operator!=(const Rational& one, const Rational& second) {
  return !(one.isEqual(second));
}

Rational& Rational::operator+=(const Rational& other) {
  numerator = numerator * other.denominator + other.numerator * denominator;
  denominator = denominator * other.denominator;
  norm_sign();
  return *this;
}

Rational& Rational::operator-=(const Rational& other) {
  numerator = numerator * other.denominator - other.numerator * denominator;
  denominator = denominator * other.denominator;
  norm_sign();
  return *this;
}

Rational& Rational::operator*=(const Rational& other) {
  numerator = numerator * other.numerator;
  denominator = denominator * other.denominator;
  norm_sign();
  return *this;
}

Rational& Rational::operator/=(const Rational& other) {
  numerator = numerator * other.denominator;
  denominator = denominator * other.numerator;
  norm_sign();
  return *this;
}

Rational& Rational::operator-() {
  numerator = -numerator;
  return *this;
}

Rational operator+(const Rational& first, const Rational& second) {
  Rational new_first = first;
  new_first += second;
  return new_first;
}

Rational operator-(const Rational& first, const Rational& second) {
  Rational new_first = first;
  new_first -= second;
  return new_first;
}

Rational operator*(const Rational& first, const Rational& second) {
  Rational new_first = first;
  new_first *= second;
  return new_first;
}

Rational operator/(const Rational& first, const Rational& second) {
  Rational new_first = first;
  new_first /= second;
  return new_first;
}

string Rational::toString() const {
  BigInteger gcd = nod(numerator.abs(), denominator.abs());
  string str = (numerator / gcd).toString();
  if ((denominator / gcd) != 1) {
    str += '/';
    str += (denominator / gcd).toString();
  }
  return str;
}

string Rational::asDecimal(size_t precision) const {
  BigInteger exp = stepen(10, static_cast<int64_t>(precision));
  string str = ((numerator * exp) / denominator).toString();
  if (!precision) { return str; }
  str[0] = (numerator >= 0) ? str[0] : '0';
  while (str.size() <= precision) {
    str = '0' + str;
  }
  if (numerator < 0) {
    str = '-' + str;
  }
  str.insert(static_cast<int64_t>(str.size()) - precision, 1, '.');
  return str;
}

ostream& operator<<(ostream& out, const Rational& x) {
  out << x.toString();
  return out;
}