#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>

template <bool const_, typename T>
struct is_const {
  using type = T;
};

template <typename T>
struct is_const<true, T> {
  using type = const T;
};

template <bool const_, typename T>
using is_const_t = typename is_const<const_, T>::type;

template <typename T>
class Deque {
  static const size_t array_size = 32;

  T** arrays_;
  size_t num_arr_;
  size_t size_;
  size_t index_first_;
  size_t array_first_;

  size_t new_num_arr(size_t prev_num_arrays, size_t num_elements = array_size);
  T* get_ptr(size_t ind) const;

 public:
  Deque();
  Deque(const Deque<T>& other);
  Deque(size_t num);
  Deque(size_t num, const T& val);
  ~Deque() noexcept;

  Deque& operator=(const Deque<T>& other);
  void swap(Deque<T>& first, Deque<T>& second) noexcept;
  size_t size() const;
  T& operator[](size_t index);
  const T& operator[](size_t index) const;
  T& at(size_t index);
  const T& at(size_t index) const;

  T** resize();
  void push_back(const T& val);
  void pop_back();
  void push_front(const T& val);
  void pop_front();

  template <bool const_, bool reverse_>
  struct base_iterator {
   private:
    T** what_data_;
    const static size_t array_sizet = 32;
    size_t index_;

   public:
    using value_type = T;
    using iterator_category = std::random_access_iterator_tag;

    base_iterator(const Deque<T>& curr, size_t ind);

    template <bool oth_const_>
    base_iterator<const_, reverse_>(
        const base_iterator<oth_const_, reverse_>& other)
        : what_data_(other.what_data_),
          index_(other.index_) {
    }

    template <>
    base_iterator<true, reverse_>(const base_iterator<false, reverse_>& other)
        : what_data_(other.what_data_),
          index_(other.index_) {
    }

    template <>
    base_iterator<false, reverse_>(const base_iterator<true, reverse_>& other) =
        delete;

    base_iterator<const_, reverse_>& operator=(
        const base_iterator<const_, reverse_>& other);
    ~base_iterator<const_, reverse_>() = default;

    size_t get_ind() const;
    base_iterator<const_, reverse_>& operator++();
    base_iterator<const_, reverse_> operator++(int);
    base_iterator<const_, reverse_>& operator--();
    base_iterator<const_, reverse_> operator--(int);
    base_iterator<const_, reverse_>& operator+=(int num);
    int operator-=(const base_iterator<const_, reverse_>& other) const;
    base_iterator<const_, reverse_>& operator-=(int num);

    base_iterator<const_, reverse_> operator+(int num) const;
    base_iterator<const_, reverse_> operator-(int num) const;
    int operator-(const base_iterator<const_, reverse_>& other) const;

    bool operator<(const base_iterator<const_, reverse_>& other) const;
    bool operator>(const base_iterator<const_, reverse_>& other) const;
    bool operator<=(const base_iterator<const_, reverse_>& other) const;
    bool operator>=(const base_iterator<const_, reverse_>& other) const;
    bool operator==(const base_iterator<const_, reverse_>& other) const;
    bool operator!=(const base_iterator<const_, reverse_>& other) const;

    is_const_t<const_, T>& operator*() const;
    is_const_t<const_, T>* operator->() const;
  };

  using iterator = base_iterator<false, false>;
  using const_iterator = base_iterator<true, false>;
  using reverse_iterator = base_iterator<false, true>;
  using const_reverse_iterator = base_iterator<true, true>;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator begin() const;
  const_iterator cend() const;
  const_iterator end() const;
  reverse_iterator rbegin();
  reverse_iterator rend();
  const_reverse_iterator crbegin() const;
  const_reverse_iterator rbegin() const;
  const_reverse_iterator crend() const;
  const_reverse_iterator rend() const;

  void insert(iterator it, const T& val);
  void erase(iterator it);
};

template <typename T>
size_t Deque<T>::new_num_arr(size_t prev_num_arrays, size_t num_elements) {
  if (num_elements <= (prev_num_arrays / 2 + 1) * array_size) {
    return prev_num_arrays * 2;
  }
  return (num_elements / array_size + 1) * 4;
}

template <typename T>
T* Deque<T>::get_ptr(size_t ind) const {
  return arrays_[ind / array_size + array_first_] + ind % array_size;
}

template <typename T>
Deque<T>::~Deque() noexcept {
  for (size_t ind = 0; ind < size_; ++ind) {
    ((*this)[ind]).~T();
  }
  for (size_t i = 0; i < num_arr_; ++i) {
    delete[] reinterpret_cast<char*>(arrays_[i]);
  }
  delete[] arrays_;
}

template <typename T>
T& Deque<T>::operator[](size_t index) {
  return *(this->get_ptr(index + index_first_));
}

template <typename T>
const T& Deque<T>::operator[](size_t index) const {
  return *(this->get_ptr(index + index_first_));
}

template <typename T>
T& Deque<T>::at(size_t index) {
  if (index >= size_) {
    throw std::out_of_range("out_of_range");
  }
  return (*this)[index];
}

template <typename T>
const T& Deque<T>::at(size_t index) const {
  if (index >= size_) {
    throw std::out_of_range("out_of_range");
  }
  return (*this)[index];
}

template <typename T>
size_t Deque<T>::size() const {
  return size_;
}

template <typename T>
Deque<T>::Deque()
    : arrays_(new T*[new_num_arr(1)]),
      num_arr_(new_num_arr(1)),
      size_(0),
      index_first_(0),
      array_first_(num_arr_ / 2) {
  size_t i = 0;
  try {
    for (; i < num_arr_; ++i) {
      arrays_[i] = reinterpret_cast<T*>(new char[array_size * sizeof(T)]);
    }
  } catch (...) {
    for (size_t tmp_i = 0; tmp_i < i; ++tmp_i) {
      delete[] reinterpret_cast<char*>(arrays_[tmp_i]);
    }
    delete[] arrays_;
    throw;
  }
}

template <typename T>
Deque<T>::Deque(size_t num)
    : arrays_(new T*[new_num_arr(1, num)]),
      num_arr_(new_num_arr(1, num)),
      size_(num),
      index_first_(0),
      array_first_(num_arr_ / 2) {
  size_t i = 0;
  try {
    for (; i < num_arr_; ++i) {
      arrays_[i] = reinterpret_cast<T*>(new char[array_size * sizeof(T)]);
    }
  } catch (...) {
    for (size_t tmp_i = 0; tmp_i < i; ++tmp_i) {
      delete[] reinterpret_cast<char*>(arrays_[tmp_i]);
    }
    delete[] arrays_;
    throw;
  }
  if (std::is_default_constructible_v<T>) {
    size_t ind = 0;
    try {
      for (; ind < num; ++ind) {
        new (this->get_ptr(ind)) T();
      }
    } catch (...) {
      for (size_t j = 0; j < ind; ++j) {
        (this->get_ptr(j))->~T();
      }
      for (size_t j = 0; j < num_arr_; ++j) {
        delete[] reinterpret_cast<char*>(arrays_[j]);
      }
      delete[] arrays_;
      throw;
    }
  }
}

template <typename T>
Deque<T>::Deque(size_t num, const T& val)
    : arrays_(new T*[new_num_arr(1, num)]),
      num_arr_(new_num_arr(1, num)),
      size_(num),
      index_first_(0),
      array_first_(num_arr_ / 2) {
  size_t i = 0;
  try {
    for (; i < num_arr_; ++i) {
      arrays_[i] = reinterpret_cast<T*>(new char[array_size * sizeof(T)]);
    }
  } catch (...) {
    for (size_t tmp_i = 0; tmp_i < i; ++tmp_i) {
      delete[] reinterpret_cast<char*>(arrays_[tmp_i]);
    }
    delete[] arrays_;
    throw;
  }
  size_t ind = 0;
  try {
    for (; ind < num; ++ind) {
      new (this->get_ptr(ind)) T(val);
    }
  } catch (...) {
    for (size_t j = 0; j < ind; ++j) {
      (this->get_ptr(j))->~T();
    }
    for (size_t j = 0; j < num_arr_; ++j) {
      delete[] reinterpret_cast<char*>(arrays_[j]);
    }
    delete[] arrays_;
    throw;
  }
}

template <typename T>
Deque<T>::Deque(const Deque<T>& other)
    : arrays_(new T*[other.num_arr_]),
      num_arr_(other.num_arr_),
      size_(other.size_),
      index_first_(other.index_first_),
      array_first_(other.array_first_) {
  size_t i = 0;
  try {
    for (; i < num_arr_; ++i) {
      arrays_[i] = reinterpret_cast<T*>(new char[array_size * sizeof(T)]);
    }
  } catch (...) {
    for (size_t tmp_i = 0; tmp_i < i; ++tmp_i) {
      delete[] reinterpret_cast<char*>(arrays_[tmp_i]);
    }
    delete[] arrays_;
    throw;
  }
  size_t ind = index_first_;
  try {
    for (; ind < index_first_ + size_; ++ind) {
      new (this->get_ptr(ind)) T(*(other.get_ptr(ind)));
    }
  } catch (...) {
    for (size_t j = index_first_; j < ind; ++j) {
      (this->get_ptr(j))->~T();
    }
    for (size_t j = 0; j < num_arr_; ++j) {
      delete[] reinterpret_cast<char*>(arrays_[j]);
    }
    delete[] arrays_;
    throw;
  }
}

template <typename T>
void Deque<T>::swap(Deque<T>& first, Deque<T>& second) noexcept {
  std::swap(first.arrays_, second.arrays_);
  std::swap(first.size_, second.size_);
  std::swap(first.num_arr_, second.num_arr_);
  std::swap(first.index_first_, second.index_first_);
  std::swap(first.array_first_, second.array_first_);
}

template <typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& other) {
  if (this == &other) {
    return *this;
  }
  Deque<T> copy(other);
  swap(copy, *this);
  return *this;
}

template <typename T>
T** Deque<T>::resize() {
  T** newarr = new T*[new_num_arr(num_arr_)];
  size_t j = 0;
  try {
    for (; j < new_num_arr(num_arr_) / 4; ++j) {
      newarr[j] = reinterpret_cast<T*>(new char[array_size * sizeof(T)]);
    }
  } catch (...) {
    for (size_t tmp_j = 0; tmp_j < j; ++tmp_j) {
      delete[] reinterpret_cast<char*>(newarr[tmp_j]);
    }
    delete[] newarr;
    throw;
  }
  for (j = new_num_arr(num_arr_) / 4; j < 3 * (new_num_arr(num_arr_) / 4);
       ++j) {
    newarr[j] = arrays_[j - new_num_arr(num_arr_) / 4];
  }
  try {
    for (j = 3 * (new_num_arr(num_arr_) / 4); j < new_num_arr(num_arr_); ++j) {
      newarr[j] = reinterpret_cast<T*>(new char[array_size * sizeof(T)]);
    }
  } catch (...) {
    for (size_t tmp_j = 3 * (new_num_arr(num_arr_) / 4); tmp_j < j; ++tmp_j) {
      delete[] reinterpret_cast<char*>(newarr[tmp_j]);
    }
    delete[] newarr;
    throw;
  }
  return newarr;
}

template <typename T>
void Deque<T>::push_back(const T& val) {
  size_t next_ind = (index_first_ + size_) % array_size;
  size_t next_arr = array_first_ + (index_first_ + size_) / array_size;
  if (next_arr < num_arr_) {
    try {
      new (arrays_[next_arr] + next_ind) T(val);
    } catch (...) {
      throw;
    }
    ++size_;
    return;
  }

  T** newarr = resize();
  try {
    new (newarr[next_arr + new_num_arr(num_arr_) / 4] + next_ind) T(val);
  } catch (...) {
    for (size_t j = 0; j < new_num_arr(num_arr_) / 4; ++j) {
      delete[] reinterpret_cast<char*>(newarr[j]);
    }
    for (size_t j = 3 * (new_num_arr(num_arr_) / 4); j < new_num_arr(num_arr_);
         ++j) {
      delete[] reinterpret_cast<char*>(newarr[j]);
    }
    delete[] newarr;
    throw;
  }
  delete[] arrays_;
  arrays_ = newarr;
  ++size_;
  array_first_ += new_num_arr(num_arr_) / 4;
  num_arr_ = new_num_arr(num_arr_);
}

template <typename T>
void Deque<T>::pop_front() {
  if (size_ == 0) {
    return;
  }
  (this->get_ptr(index_first_))->~T();
  --size_;
  array_first_ += (index_first_ != array_size - 1) ? 0 : 1;
  array_first_ = (size_ != 0) ? array_first_ : num_arr_ / 2;
  index_first_ = (size_ != 0) ? (index_first_ + 1) % array_size : 0;
}

template <typename T>
void Deque<T>::push_front(const T& val) {
  if (index_first_ + array_size * array_first_ != 0) {
    try {
      new (arrays_[array_first_ - ((index_first_ == 0) ? 1 : 0)] +
           (index_first_ + array_size - 1) % array_size) T(val);
    } catch (...) {
      throw;
    }
    ++size_;
    array_first_ -= (index_first_ == 0) ? 1 : 0;
    index_first_ = (index_first_ + array_size - 1) % array_size;
    return;
  }

  T** newarr = resize();
  try {
    new (newarr[new_num_arr(num_arr_) / 4 - 1] + array_size - 1) T(val);
  } catch (...) {
    for (size_t j = 0; j < new_num_arr(num_arr_) / 4; ++j) {
      delete[] reinterpret_cast<char*>(newarr[j]);
    }
    for (size_t j = 3 * (new_num_arr(num_arr_) / 4); j < new_num_arr(num_arr_);
         ++j) {
      delete[] reinterpret_cast<char*>(newarr[j]);
    }
    delete[] newarr;
    throw;
  }
  delete[] arrays_;
  arrays_ = newarr;
  ++size_;
  array_first_ = new_num_arr(num_arr_) / 4 - 1;
  index_first_ = array_size - 1;
  num_arr_ = new_num_arr(num_arr_);
}

template <typename T>
void Deque<T>::pop_back() {
  if (size_ == 0) {
    return;
  }
  (this->get_ptr(index_first_ + size_ - 1))->~T();
  --size_;
  array_first_ = (size_ != 0) ? array_first_ : num_arr_ / 2;
  index_first_ = (size_ != 0) ? index_first_ : 0;
}

template <typename T>
template <bool const_, bool reverse_>
Deque<T>::base_iterator<const_, reverse_>::base_iterator(const Deque<T>& curr,
                                                         size_t ind)
    : what_data_(curr.arrays_),
      index_(ind) {
}

template <typename T>
template <bool const_, bool reverse_>
typename Deque<T>::template base_iterator<const_, reverse_>&
Deque<T>::base_iterator<const_, reverse_>::operator=(
    const Deque<T>::base_iterator<const_, reverse_>& other) {
  what_data_ = other.what_data_;
  index_ = other.index_;
  return *this;
}

template <typename T>
template <bool const_, bool reverse_>
size_t Deque<T>::base_iterator<const_, reverse_>::get_ind() const {
  return index_;
}

template <typename T>
template <bool const_, bool reverse_>
typename Deque<T>::template base_iterator<const_, reverse_>&
Deque<T>::base_iterator<const_, reverse_>::operator++() {
  index_ += (reverse_) ? -1 : 1;
  return *this;
}

template <typename T>
template <bool const_, bool reverse_>
typename Deque<T>::template base_iterator<const_, reverse_>
Deque<T>::base_iterator<const_, reverse_>::operator++(int) {
  Deque<T>::base_iterator<const_, reverse_> copy(*this);
  index_ += (reverse_) ? -1 : 1;
  return copy;
}

template <typename T>
template <bool const_, bool reverse_>
typename Deque<T>::template base_iterator<const_, reverse_>&
Deque<T>::base_iterator<const_, reverse_>::operator--() {
  index_ += (reverse_) ? 1 : -1;
  return *this;
}

template <typename T>
template <bool const_, bool reverse_>
typename Deque<T>::template base_iterator<const_, reverse_>
Deque<T>::base_iterator<const_, reverse_>::operator--(int) {
  Deque<T>::base_iterator<const_, reverse_> copy(*this);
  index_ += (reverse_) ? 1 : -1;
  return copy;
}

template <typename T>
template <bool const_, bool reverse_>
typename Deque<T>::template base_iterator<const_, reverse_>&
Deque<T>::base_iterator<const_, reverse_>::operator+=(int num) {
  index_ += (reverse_) ? -num : num;
  return *this;
}

template <typename T>
template <bool const_, bool reverse_>
typename Deque<T>::template base_iterator<const_, reverse_>&
Deque<T>::base_iterator<const_, reverse_>::operator-=(int num) {
  index_ += (reverse_) ? num : -num;
  return *this;
}

template <typename T>
template <bool const_, bool reverse_>
int Deque<T>::base_iterator<const_, reverse_>::operator-=(
    const typename Deque<T>::template base_iterator<const_, reverse_>& other)
    const {
  return (reverse_) ? other.index_ - index_ : index_ - other.index_;
}

template <typename T>
template <bool const_, bool reverse_>
typename Deque<T>::template base_iterator<const_, reverse_>
Deque<T>::base_iterator<const_, reverse_>::operator+(int num) const {
  typename Deque<T>::template base_iterator<const_, reverse_> copy(*this);
  copy += num;
  return copy;
}

template <typename T>
template <bool const_, bool reverse_>
typename Deque<T>::template base_iterator<const_, reverse_>
Deque<T>::base_iterator<const_, reverse_>::operator-(int num) const {
  typename Deque<T>::template base_iterator<const_, reverse_> copy(*this);
  copy -= num;
  return copy;
}

template <typename T>
template <bool const_, bool reverse_>
int Deque<T>::base_iterator<const_, reverse_>::operator-(
    const typename Deque<T>::template base_iterator<const_, reverse_>& other)
    const {
  return *this -= other;
}

template <typename T>
template <bool const_, bool reverse_>
is_const_t<const_, T>& Deque<T>::base_iterator<const_, reverse_>::operator*()
    const {
  return what_data_[index_ / array_sizet][index_ % array_sizet];
}

template <typename T>
template <bool const_, bool reverse_>
is_const_t<const_, T>* Deque<T>::base_iterator<const_, reverse_>::operator->()
    const {
  return what_data_[index_ / array_sizet] + (index_ % array_sizet);
}

template <typename T>
template <bool const_, bool reverse_>
bool Deque<T>::base_iterator<const_, reverse_>::operator<(
    const typename Deque<T>::template base_iterator<const_, reverse_>& other)
    const {
  return (*this - other) < 0;
}

template <typename T>
template <bool const_, bool reverse_>
bool Deque<T>::base_iterator<const_, reverse_>::operator>(
    const typename Deque<T>::template base_iterator<const_, reverse_>& other)
    const {
  return (*this - other) > 0;
}

template <typename T>
template <bool const_, bool reverse_>
bool Deque<T>::base_iterator<const_, reverse_>::operator<=(
    const typename Deque<T>::template base_iterator<const_, reverse_>& other)
    const {
  return (*this - other) <= 0;
}

template <typename T>
template <bool const_, bool reverse_>
bool Deque<T>::base_iterator<const_, reverse_>::operator>=(
    const typename Deque<T>::template base_iterator<const_, reverse_>& other)
    const {
  return (*this - other) >= 0;
}

template <typename T>
template <bool const_, bool reverse_>
bool Deque<T>::base_iterator<const_, reverse_>::operator==(
    const typename Deque<T>::template base_iterator<const_, reverse_>& other)
    const {
  return (*this - other) == 0;
}

template <typename T>
template <bool const_, bool reverse_>
bool Deque<T>::base_iterator<const_, reverse_>::operator!=(
    const typename Deque<T>::template base_iterator<const_, reverse_>& other)
    const {
  return (*this - other) != 0;
}

template <typename T>
typename Deque<T>::iterator Deque<T>::begin() {
  typename Deque<T>::iterator what(*this,
                                   array_size * array_first_ + index_first_);
  return what;
}

template <typename T>
typename Deque<T>::iterator Deque<T>::end() {
  typename Deque<T>::iterator what(
      *this, array_size * array_first_ + index_first_ + size_);
  return what;
}

template <typename T>
typename Deque<T>::const_iterator Deque<T>::cbegin() const {
  typename Deque<T>::const_iterator what(
      *this, array_size * array_first_ + index_first_);
  return what;
}

template <typename T>
typename Deque<T>::const_iterator Deque<T>::cend() const {
  typename Deque<T>::const_iterator what(
      *this, array_size * array_first_ + index_first_ + size_);
  return what;
}

template <typename T>
typename Deque<T>::const_iterator Deque<T>::begin() const {
  typename Deque<T>::const_iterator what(
      *this, array_size * array_first_ + index_first_);
  return what;
}

template <typename T>
typename Deque<T>::const_iterator Deque<T>::end() const {
  typename Deque<T>::const_iterator what(
      *this, array_size * array_first_ + index_first_ + size_);
  return what;
}

template <typename T>
typename Deque<T>::reverse_iterator Deque<T>::rbegin() {
  typename Deque<T>::reverse_iterator what(
      *this, array_size * array_first_ + index_first_ + size_ - 1);
  return what;
}

template <typename T>
typename Deque<T>::reverse_iterator Deque<T>::rend() {
  typename Deque<T>::reverse_iterator what(
      *this, array_size * array_first_ + index_first_ - 1);
  return what;
}

template <typename T>
typename Deque<T>::const_reverse_iterator Deque<T>::crbegin() const {
  typename Deque<T>::const_reverse_iterator what(
      *this, array_size * array_first_ + index_first_ + size_ - 1);
  return what;
}

template <typename T>
typename Deque<T>::const_reverse_iterator Deque<T>::crend() const {
  typename Deque<T>::const_reverse_iterator what(
      *this, array_size * array_first_ + index_first_ - 1);
  return what;
}

template <typename T>
typename Deque<T>::const_reverse_iterator Deque<T>::rbegin() const {
  typename Deque<T>::const_reverse_iterator what(
      *this, array_size * array_first_ + index_first_ + size_ - 1);
  return what;
}

template <typename T>
typename Deque<T>::const_reverse_iterator Deque<T>::rend() const {
  typename Deque<T>::const_reverse_iterator what(
      *this, array_size * array_first_ + index_first_ - 1);
  return what;
}

template <typename T>
void Deque<T>::insert(iterator it, const T& val) {
  size_t ind = it.get_ind() - array_size * array_first_ - index_first_;
  T to_push(val);
  for (; ind < size_; ++ind) {
    std::swap(to_push, (*this)[ind]);
  }
  this->push_back(to_push);
}

template <typename T>
void Deque<T>::erase(iterator it) {
  size_t ind = it.get_ind() - array_size * array_first_ - index_first_;
  for (; ind < size_ - 1; ++ind) {
    std::swap((*this)[ind], (*this)[ind + 1]);
  }
  this->pop_back();
}
