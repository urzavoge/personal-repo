#include <iostream>

template <typename T>
class EnableSharedFromThis;

template <typename T>
class WeakPtr;

template <typename T>
class SharedPtr {
  // NOLINTBEGIN
  template <typename S, typename... Args>
  friend SharedPtr<S> makeShared(Args&&... args);

  template <typename S, typename Alloc, typename... Args>
  friend SharedPtr<S> allocateShared(const Alloc& alloc, Args&&... args);
  // NOLINTEND
  template <typename Y>
  friend class WeakPtr;

  template <typename Y>
  friend class SharedPtr;

  struct BaseControlBlock {
    int count_shared = 1;
    int count_weak = 0;

    BaseControlBlock() = default;

    virtual void delete_obj(T* ptr) = 0;
    virtual void destroy_self() = 0;
    virtual ~BaseControlBlock() = default;
  };

  template <typename Deleter, typename Alloc>
  struct ControlBlock : BaseControlBlock {
    Deleter deleter;

    using Allocator = typename std::allocator_traits<
        Alloc>::template rebind_alloc<ControlBlock<Deleter, Alloc>>;

    Allocator alloc;

    ControlBlock()
        : BaseControlBlock() {
    }
    ControlBlock(Deleter deleter, Alloc alloc)
        : BaseControlBlock(),
          deleter(deleter),
          alloc(alloc) {
    }

    void delete_obj(T* ptr) override {
      if (ptr != nullptr) {
        deleter(ptr);
      }
    }

    void destroy_self() override {
      std::allocator_traits<Allocator>::deallocate(alloc, this, 1);
    }
  };

  template <typename Alloc>
  struct ControlBlockFromMake : BaseControlBlock {
    T obj_;
    Alloc alloc;

    using AllocatorSelf = typename std::allocator_traits<
        Alloc>::template rebind_alloc<ControlBlockFromMake<Alloc>>;
    using Allocatorobj_ =
        typename std::allocator_traits<Alloc>::template rebind_alloc<T>;

    AllocatorSelf alloc_self;
    Allocatorobj_ alloc_obj_;

    template <typename... Args>
    ControlBlockFromMake(Alloc alloc, Args&&... args)
        : BaseControlBlock(),
          obj_(std::forward<Args>(args)...),
          alloc(alloc),
          alloc_self(alloc),
          alloc_obj_(alloc) {
    }

    void delete_obj(T* ptr) override {
      if (ptr) {
        std::allocator_traits<Allocatorobj_>::destroy(alloc, ptr);
      }
    }

    void destroy_self() override {
      std::allocator_traits<AllocatorSelf>::deallocate(alloc_self, this, 1);
    }
  };

  T* obj_ = nullptr;
  BaseControlBlock* control_ = nullptr;

  template <typename Y>
  SharedPtr(bool a, Y* ptr, typename SharedPtr<Y>::BaseControlBlock* cb)
      : obj_(ptr),
        control_(
            reinterpret_cast<typename SharedPtr<T>::BaseControlBlock*>(cb)) {
    std::ignore = a;
  }

 public:
  template <typename Y>
  SharedPtr(const WeakPtr<Y>& weak)
      : obj_(weak.obj_),
        control_(reinterpret_cast<typename SharedPtr<T>::BaseControlBlock*>(
            weak.control_)) {
    ++(control_->count_shared);
  }

  SharedPtr() = default;

  template <typename Y>
  SharedPtr(Y* ptr)
      : SharedPtr(ptr, std::default_delete<T>(), std::allocator<T>()) {
  }

  template <typename Y, typename Deleter, typename Alloc>
  SharedPtr(Y* ptr, const Deleter& deleter, const Alloc& alloc)
      : obj_(ptr) {
    using AllocatorSelf = typename std::allocator_traits<
        Alloc>::template rebind_alloc<ControlBlock<Deleter, Alloc>>;
    AllocatorSelf self_alloc = alloc;

    ControlBlock<Deleter, Alloc>* new_control =
        std::allocator_traits<AllocatorSelf>::allocate(self_alloc, 1);
    try {
      new (new_control) ControlBlock<Deleter, Alloc>(deleter, alloc);
      control_ = new_control;
    } catch (...) {
      std::allocator_traits<AllocatorSelf>::deallocate(self_alloc, new_control,
                                                       1);
      throw;
    }
  }

  template <typename Deleter>
  SharedPtr(T* ptr, const Deleter& deleter)
      : SharedPtr<T>(ptr, deleter, std::allocator<T>()) {
  }

  template <typename Y>
  SharedPtr(const SharedPtr<Y>& other) noexcept
      : SharedPtr<T>(false, other.obj_, other.control_) {
    ++(control_->count_shared);
  }

  SharedPtr(const SharedPtr& other) noexcept
      : SharedPtr<T>(false, other.obj_, other.control_) {
    if (control_) {
      ++(control_->count_shared);
    }
  }

  template <typename Y>
  SharedPtr(SharedPtr<Y>&& other) noexcept
      : SharedPtr<T>(false, other.obj_, other.control_) {
    other.obj_ = nullptr;
    other.control_ = nullptr;
  }

  void swap(SharedPtr& argument) {
    std::swap(obj_, argument.obj_);
    std::swap(control_, argument.control_);
  }

  template <typename Y>
  SharedPtr& operator=(const SharedPtr<Y>& other) {
    SharedPtr<T> new_s(other);
    swap(new_s);
    return *this;
  }

  SharedPtr& operator=(const SharedPtr<T>& other) {
    SharedPtr<T> new_s(other);
    swap(new_s);
    return *this;
  }

  template <typename Y>
  SharedPtr& operator=(SharedPtr<Y>&& other) noexcept {
    SharedPtr<T> new_s(std::move(other));
    swap(new_s);
    return *this;
  }

  SharedPtr& operator=(SharedPtr<T>&& other) noexcept {
    SharedPtr<T> new_s(std::move(other));
    swap(new_s);
    return *this;
  }

  int use_count() const {
    return control_->count_shared;
  }

  T& operator*() const {
    return *obj_;
  }

  T* operator->() const {
    return obj_;
  }

  template <typename Y>
  void reset(Y* pointer) {
    SharedPtr<T> new_s(pointer);
    swap(new_s);
  }

  void reset() {
    SharedPtr new_s{};
    swap(new_s);
  }

  T* get() const {
    return obj_;
  }

  ~SharedPtr() {
    if (control_ == nullptr) {
      return;
    }
    --(control_->count_shared);
    if (control_->count_shared == 0) {
      control_->delete_obj(obj_);
      if (control_->count_weak == 0) {
        control_->destroy_self();
      }
    }
  }
};

template <typename T, typename Alloc, typename... Args>
SharedPtr<T> allocateShared(const Alloc& alloc, Args&&... args) {  // NOLINT
  using AllocatorSelf =
      typename std::allocator_traits<Alloc>::template rebind_alloc<
          typename SharedPtr<T>::template ControlBlockFromMake<Alloc>>;
  AllocatorSelf self_alloc = alloc;
  typename SharedPtr<T>::template ControlBlockFromMake<Alloc>* control =
      std::allocator_traits<AllocatorSelf>::allocate(self_alloc, 1);
  try {
    std::allocator_traits<AllocatorSelf>::construct(
        self_alloc, control, alloc, std::forward<Args>(args)...);
    return SharedPtr<T>(false, &(control->obj_), control);
  } catch (...) {
    std::allocator_traits<AllocatorSelf>::deallocate(self_alloc, control, 1);
    throw;
  }
}

template <typename T, typename... Args>
SharedPtr<T> makeShared(Args&&... args) {  // NOLINT
  return allocateShared<T>(std::allocator<T>(), std::forward<Args>(args)...);
}

template <typename T>
class WeakPtr {
  T* obj_;
  typename SharedPtr<T>::BaseControlBlock* control_ = nullptr;

  template <typename Y>
  WeakPtr(Y* ptr, typename SharedPtr<Y>::BaseControlBlock* control)
      : obj_(ptr),
        control_(reinterpret_cast<typename SharedPtr<T>::BaseControlBlock*>(
            control)) {
  }

 public:
  template <typename Y>
  friend class SharedPtr;

  template <typename Y>
  friend class WeakPtr;

  WeakPtr() = default;

  template <typename Y>
  WeakPtr(const SharedPtr<Y>& other)
      : WeakPtr(other.obj_, other.control_) {
    ++(control_->count_weak);
  }

  WeakPtr(const SharedPtr<T>& other)
      : WeakPtr(other.obj_, other.control_) {
    ++(control_->count_weak);
  }

  template <typename Y>
  WeakPtr(const WeakPtr<Y>& other)
      : WeakPtr(other.obj_, other.control_) {
    ++(control_->count_weak);
  }

  WeakPtr(const WeakPtr<T>& other)
      : WeakPtr(other.obj_, other.control_) {
    ++(control_->count_weak);
  }

  template <typename Y>
  WeakPtr(SharedPtr<Y>&& other) noexcept
      : WeakPtr(std::move(other.obj_), std::move(other.control_)) {
    obj_ = nullptr;
    other.control_ = nullptr;
  }

  WeakPtr(SharedPtr<T>&& other) noexcept
      : WeakPtr(std::move(other.obj_), std::move(other.control_)) {
    obj_ = nullptr;
    other.control_ = nullptr;
  }

  void swap(WeakPtr& other) {
    std::swap(obj_, other.obj_);
    std::swap(control_, other.control_);
  }

  template <typename Y>
  WeakPtr& operator=(const WeakPtr<Y>& other) {
    WeakPtr<T> new_w(other);
    swap(new_w);
    return *this;
  }

  template <typename Y>
  WeakPtr& operator=(const SharedPtr<Y>& other) {
    WeakPtr<T> new_w(other);
    swap(new_w);
    return *this;
  }

  template <typename Y>
  WeakPtr& operator=(WeakPtr<Y>&& other) {
    swap(WeakPtr<T>(std::move(other)));
    return *this;
  }

  template <typename Y>
  WeakPtr& operator=(SharedPtr<Y>&& other) {
    swap(WeakPtr<T>(std::move(other)));
    return *this;
  }

  bool expired() const noexcept {
    return control_->count_shared == 0;
  }

  SharedPtr<T> lock() const {
    return expired() ? SharedPtr<T>() : SharedPtr<T>(*this);
  }

  int use_count() const {
    return control_->count_shared;
  }

  ~WeakPtr() {
    if (control_ == nullptr) {
      return;
    }
    --(control_->count_weak);
    if (control_->count_weak == 0 && control_->count_shared == 0) {
      control_->destroy_self();
    }
  }
};

template <typename T>
class EnableSharedFromThis {
 private:
  WeakPtr<T> weak_;

 public:
  SharedPtr<T> shared_from_this() {
    return SharedPtr<T>(weak_.lock());
  }
};

template <typename T, typename... Args>
SharedPtr<T> makeShared(Args&&... args);  // NOLINT

template <typename T, typename Alloc, typename... Args>
SharedPtr<T> allocateShared(const Alloc& alloc, Args&&... args);  // NOLINT
