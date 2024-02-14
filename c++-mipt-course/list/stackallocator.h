#pragma once
#include <vector>

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

template <size_t size_>
class StackStorage {
 public:
  char store[size_];
  size_t point_ = 0;

  StackStorage() = default;
  StackStorage(StackStorage&& other) = delete;
  StackStorage& operator=(StackStorage&& other) = delete;
  StackStorage& operator=(const StackStorage& other) = delete;
  StackStorage(const StackStorage& other) = delete;
  ~StackStorage() = default;
};

template <typename T, size_t N>
class StackAllocator {
 public:
  StackStorage<N>* store_ = nullptr;

 public:
  T* allocate(size_t count);
  void deallocate(T* ptr, size_t);
  void destroy(T* ptr);

  template <typename... Args>
  void construct(T* ptr, const Args&... args);

  template <typename U>
  struct rebind {
    using other = StackAllocator<U, N>;
  };

  using value_type = T;
  using pointer = T*;

  StackAllocator() = default;
  StackAllocator(StackStorage<N>& store)
      : store_(&store) {
  }

  template <typename U>
  StackAllocator(const StackAllocator<U, N>& other)
      : store_(other.store_) {
  }

  template <typename U>
  StackAllocator& operator=(const StackAllocator<U, N>& other);
};

template <typename T, size_t N>
T* StackAllocator<T, N>::allocate(size_t count) {
  if (store_->point_ % sizeof(T) != 0) {
    store_->point_ += (sizeof(T) - store_->point_ % sizeof(T));
  }
  char* ptr = store_->store + store_->point_;
  store_->point_ += count * sizeof(T);
  return reinterpret_cast<T*>(ptr);
}

template <typename T, size_t N>
void StackAllocator<T, N>::deallocate(T* ptr, size_t) {
  std::ignore = ptr;
}

template <typename T, size_t N>
void StackAllocator<T, N>::destroy(T* ptr) {
  ptr->~T();
}

template <typename T, size_t N>
template <typename... Args>
void StackAllocator<T, N>::construct(T* ptr, const Args&... args) {
  new (ptr) T(args...);
}

template <typename T, size_t N>
template <typename U>
StackAllocator<T, N>& StackAllocator<T, N>::operator=(
    const StackAllocator<U, N>& other) {
  store_ = other.store_;
  return *this;
}

template <typename T, typename Allocator = std::allocator<T>>
class List {
 public:
  template <bool const_>
  struct BaseIterator;

 private:
  struct BaseNode;
  struct Node;

  struct BaseNode {
    BaseNode* prev_ = nullptr;
    BaseNode* next_ = nullptr;

    BaseNode() = default;
    BaseNode(BaseNode* prev, BaseNode* next)
        : prev_(prev),
          next_(next) {
    }
    BaseNode(const BaseNode& other)
        : prev_(other.prev_),
          next_(other.next_) {
    }
    ~BaseNode() = default;
  };

  struct Node : BaseNode {
    T val_;

    T& get();
    Node() = default;
    explicit Node(const T& val)
        : val_(val) {
    }
    Node(BaseNode* prev, BaseNode* next)
        : BaseNode(prev, next) {
    }
    ~Node() = default;
  };

  using AllocTraits = std::allocator_traits<Allocator>;
  using node_type_alloc = typename AllocTraits::template rebind_alloc<Node>;

  mutable BaseNode fake_node_;
  size_t size_;
  [[no_unique_address]] typename AllocTraits::template rebind_alloc<Node>
      node_alloc_ = Allocator();

  template <bool const_>
  void insert(BaseIterator<const_> it, BaseNode* to_add) noexcept;

  void push_back();

 public:
  List() noexcept;
  explicit List(size_t count);
  List(size_t count, const T& val);
  List(const Allocator& alloc);
  List(size_t count, const Allocator& alloc);
  List(size_t count, const T& val, const Allocator& alloc);

  node_type_alloc& get_allocator() noexcept;
  List(const List& other);
  ~List() noexcept;
  void swap(List& other);
  List& operator=(const List& other);

  size_t size() const noexcept;
  void push_back(const T& val);
  void push_front(const T& val);
  void pop_back();
  void pop_front();

  template <bool const_>
  struct BaseIterator {
    BaseNode* node_;

    using value_type = T;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    BaseIterator(BaseNode* node)
        : node_(node) {
    }

    operator BaseIterator<true>() const {
      return BaseIterator<true>(node_);
    }

    template <bool oth_const_>
    BaseIterator<const_>(const BaseIterator<oth_const_>& other)
        : node_(other.node_) {
    }

    template <>
    BaseIterator<true>(const BaseIterator<false>& other)
        : node_(other.node_) {
    }

    template <>
    BaseIterator<false>(const BaseIterator<true>& other) = delete;

    BaseIterator<const_>& operator=(const BaseIterator<const_>& other);
    ~BaseIterator<const_>() = default;

    BaseIterator<const_>& operator++();
    BaseIterator<const_> operator++(int);
    BaseIterator<const_>& operator--();
    BaseIterator<const_> operator--(int);
    bool operator==(const BaseIterator<const_>& other) const;
    bool operator!=(const BaseIterator<const_>& other) const;

    is_const_t<const_, T>& operator*() const;
    is_const_t<const_, T>* operator->() const;
  };

  using iterator = BaseIterator<false>;
  using const_iterator = BaseIterator<true>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

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

  template <bool const_>
  void insert(BaseIterator<const_> it, const T& val);

  template <bool const_>
  void erase(BaseIterator<const_> it);
};

template <typename T, typename Allocator>
T& List<T, Allocator>::Node::get() {
  return *val_;
}

template <typename T, typename Allocator>
template <bool const_>
typename List<T, Allocator>::template BaseIterator<const_>&
List<T, Allocator>::BaseIterator<const_>::operator=(
    const BaseIterator<const_>& other) {
  node_ = other.node_;
  return *this;
}

template <typename T, typename Allocator>
template <bool const_>
typename List<T, Allocator>::template BaseIterator<const_>&
List<T, Allocator>::BaseIterator<const_>::operator++() {
  node_ = node_->next_;
  return *this;
}

template <typename T, typename Allocator>
template <bool const_>
typename List<T, Allocator>::template BaseIterator<const_>&
List<T, Allocator>::BaseIterator<const_>::operator--() {
  node_ = node_->prev_;
  return *this;
}

template <typename T, typename Allocator>
template <bool const_>
typename List<T, Allocator>::template BaseIterator<const_>
List<T, Allocator>::BaseIterator<const_>::operator++(int) {
  BaseIterator copy(*this);
  node_ = node_->next_;
  return copy;
}

template <typename T, typename Allocator>
template <bool const_>
typename List<T, Allocator>::template BaseIterator<const_>
List<T, Allocator>::BaseIterator<const_>::operator--(int) {
  BaseIterator copy(*this);
  node_ = node_->prev_;
  return copy;
}

template <typename T, typename Allocator>
template <bool const_>
bool List<T, Allocator>::BaseIterator<const_>::operator==(
    const BaseIterator& other) const {
  return node_ == other.node_;
}

template <typename T, typename Allocator>
template <bool const_>
bool List<T, Allocator>::BaseIterator<const_>::operator!=(
    const BaseIterator& other) const {
  return node_ != other.node_;
}

template <typename T, typename Allocator>
template <bool const_>
is_const_t<const_, T>& List<T, Allocator>::BaseIterator<const_>::operator*()
    const {
  return static_cast<Node*>(node_)->val_;
}

template <typename T, typename Allocator>
template <bool const_>
is_const_t<const_, T>* List<T, Allocator>::BaseIterator<const_>::operator->()
    const {
  return &(static_cast<Node*>(node_)->val_);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator List<T, Allocator>::begin() {
  return iterator(fake_node_.next_);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::iterator List<T, Allocator>::end() {
  return iterator(&fake_node_);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator List<T, Allocator>::cbegin() const {
  return const_iterator(fake_node_.next_);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator List<T, Allocator>::cend() const {
  return const_iterator(&fake_node_);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator List<T, Allocator>::begin() const {
  return const_iterator(fake_node_.next_);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_iterator List<T, Allocator>::end() const {
  return const_iterator(&fake_node_);
}

template <typename T, typename Allocator>
typename List<T, Allocator>::reverse_iterator List<T, Allocator>::rbegin() {
  return std::make_reverse_iterator(end());
}

template <typename T, typename Allocator>
typename List<T, Allocator>::reverse_iterator List<T, Allocator>::rend() {
  return std::make_reverse_iterator(begin());
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator
List<T, Allocator>::crbegin() const {
  return std::make_reverse_iterator(cend());
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator List<T, Allocator>::crend()
    const {
  return std::make_reverse_iterator(cbegin());
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator List<T, Allocator>::rbegin()
    const {
  return std::make_reverse_iterator(cend());
}

template <typename T, typename Allocator>
typename List<T, Allocator>::const_reverse_iterator List<T, Allocator>::rend()
    const {
  return std::make_reverse_iterator(cbegin());
}

template <typename T, typename Allocator>
template <bool const_>
void List<T, Allocator>::insert(BaseIterator<const_> it, const T& val) {
  Node* to_add =
      std::allocator_traits<node_type_alloc>::allocate(node_alloc_, 1);
  try {
    std::allocator_traits<node_type_alloc>::construct(node_alloc_, to_add, val);
  } catch (...) {
    std::allocator_traits<node_type_alloc>::deallocate(node_alloc_, to_add, 1);
    throw;
  }
  insert(it, to_add);
}

template <typename T, typename Allocator>
template <bool const_>
void List<T, Allocator>::erase(BaseIterator<const_> it) {
  it.node_->prev_->next_ = it.node_->next_;
  it.node_->next_->prev_ = it.node_->prev_;
  std::allocator_traits<node_type_alloc>::destroy(node_alloc_,
                                                  static_cast<Node*>(it.node_));
  std::allocator_traits<node_type_alloc>::deallocate(
      node_alloc_, static_cast<Node*>(it.node_), 1);
  --size_;
}

template <typename T, typename Allocator>
template <bool const_>
void List<T, Allocator>::insert(BaseIterator<const_> it,
                                BaseNode* to_add) noexcept {
  it.node_->prev_->next_ = to_add;
  to_add->prev_ = it.node_->prev_;
  it.node_->prev_ = to_add;
  to_add->next_ = it.node_;
  ++size_;
}

template <typename T, typename Allocator>
List<T, Allocator>::List() noexcept
    : fake_node_(&fake_node_, &fake_node_),
      size_(0) {
}

template <typename T, typename Allocator>
List<T, Allocator>::List(size_t count)
    : fake_node_(&fake_node_, &fake_node_),
      size_(0) {
  size_t cnt = 0;
  try {
    for (; cnt < count; ++cnt) {
      push_back();
    }
  } catch (...) {
    for (size_t del = 0; del < cnt; ++del) {
      pop_back();
    }
  }
}

template <typename T, typename Allocator>
List<T, Allocator>::List(size_t count, const T& val)
    : fake_node_(&fake_node_, &fake_node_),
      size_(0) {
  size_t cnt = 0;
  try {
    for (; cnt < count; ++cnt) {
      push_back(val);
    }
  } catch (...) {
    for (size_t del = 0; del < cnt; ++del) {
      pop_back();
    }
  }
}

template <typename T, typename Allocator>
List<T, Allocator>::List(const Allocator& alloc)
    : fake_node_(&fake_node_, &fake_node_),
      size_(0),
      node_alloc_(alloc) {
}

template <typename T, typename Allocator>
List<T, Allocator>::List(size_t count, const Allocator& alloc)
    : fake_node_(&fake_node_, &fake_node_),
      size_(0),
      node_alloc_(alloc) {
  size_t cnt = 0;
  try {
    for (; cnt < count; ++cnt) {
      push_back();
    }
  } catch (...) {
    for (size_t del = 0; del < cnt; ++del) {
      pop_back();
    }
  }
}

template <typename T, typename Allocator>
List<T, Allocator>::List(size_t count, const T& val, const Allocator& alloc)
    : fake_node_(&fake_node_, &fake_node_),
      size_(0),
      node_alloc_(alloc) {
  size_t cnt = 0;
  try {
    for (; cnt < count; ++cnt) {
      push_back(val);
    }
  } catch (...) {
    for (size_t del = 0; del < cnt; ++del) {
      pop_back();
    }
  }
}

template <typename T, typename Allocator>
void List<T, Allocator>::push_back(const T& val) {
  Node* to_add =
      std::allocator_traits<node_type_alloc>::allocate(node_alloc_, 1);
  try {
    std::allocator_traits<node_type_alloc>::construct(node_alloc_, to_add, val);
  } catch (...) {
    std::allocator_traits<node_type_alloc>::deallocate(node_alloc_, to_add, 1);
    throw;
  }
  insert(this->end(), to_add);
}

template <typename T, typename Allocator>
void List<T, Allocator>::push_back() {
  Node* to_add =
      std::allocator_traits<node_type_alloc>::allocate(node_alloc_, 1);
  try {
    std::allocator_traits<node_type_alloc>::construct(
        node_alloc_, to_add, fake_node_.prev_, &fake_node_);
  } catch (...) {
    std::allocator_traits<node_type_alloc>::deallocate(node_alloc_, to_add, 1);
    throw;
  }
  to_add->prev_->next_ = to_add;
  fake_node_.prev_ = to_add;
  ++size_;
}

template <typename T, typename Allocator>
void List<T, Allocator>::push_front(const T& val) {
  Node* to_add =
      std::allocator_traits<node_type_alloc>::allocate(node_alloc_, 1);
  try {
    std::allocator_traits<node_type_alloc>::construct(node_alloc_, to_add, val);
  } catch (...) {
    std::allocator_traits<node_type_alloc>::deallocate(node_alloc_, to_add, 1);
    throw;
  }
  insert(this->begin(), to_add);
}

template <typename T, typename Allocator>
void List<T, Allocator>::pop_back() {
  erase(--(this->end()));
}

template <typename T, typename Allocator>
void List<T, Allocator>::pop_front() {
  erase(this->begin());
}

template <typename T, typename Allocator>
size_t List<T, Allocator>::size() const noexcept {
  return size_;
}

template <typename T, typename Allocator>
typename List<T, Allocator>::node_type_alloc&
List<T, Allocator>::get_allocator() noexcept {
  return node_alloc_;
}

template <typename T, typename Allocator>
List<T, Allocator>::~List() noexcept {
  size_t save = size_;
  for (size_t cnt = 0; cnt < save; ++cnt) {
    pop_back();
  }
}

template <typename T, typename Allocator>
List<T, Allocator>::List(const List& other)
    : fake_node_(&fake_node_, &fake_node_),
      size_(0),
      node_alloc_(
          std::allocator_traits<Allocator>::
              select_on_container_copy_construction(other.node_alloc_)) {
  try {
    for (auto it = other.begin(); it != other.end(); ++it) {
      push_back(*it);
    }
  } catch (...) {
    size_t save = size_;
    for (size_t cnt = 0; cnt < save; ++cnt) {
      pop_back();
    }
    throw;
  }
}

template <typename T, typename Allocator>
void List<T, Allocator>::swap(List<T, Allocator>& other) {
  std::swap(fake_node_, other.fake_node_);
  std::swap(node_alloc_, other.node_alloc_);
  std::swap(size_, other.size_);
  fake_node_.next_->prev_ = fake_node_.prev_->next_ = &fake_node_;
  other.fake_node_.next_->prev_ = other.fake_node_.prev_->next_ =
      &other.fake_node_;
}

template <typename T, typename Allocator>
List<T, Allocator>& List<T, Allocator>::operator=(
    const List<T, Allocator>& other) {
  List copy(std::allocator_traits<
                Allocator>::propagate_on_container_copy_assignment::value
                ? other.node_alloc_
                : node_alloc_);

  if (other.size_ == 0) {
    size_t save = size_;
    for (size_t cnt = 0; cnt < save; ++cnt) {
      pop_back();
    }
  }

  try {
    for (auto it = other.cbegin(); it != other.cend(); ++it) {
      copy.push_back(*it);
    }
  } catch (...) {
    size_t save = copy.size_;
    for (size_t cnt = 0; cnt < save; ++cnt) {
      copy.pop_back();
    }
    throw;
  }
  swap(copy);
  return *this;
}
