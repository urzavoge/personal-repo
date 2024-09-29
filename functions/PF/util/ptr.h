#pragma once

#include "common.h"
#include "../fwd.h"

template <typename Domain>
class SharedPtr {
  public:

    using TObj = PF::IPFunctionBase<Domain>;

    SharedPtr(Domain constant) : Ptr_(std::make_shared<PF::TPFunctionConst<Domain>>(constant)) {}

    TObj& operator*() const {
        return *Ptr_;
    }

    TObj* operator->() const {
        return &(*Ptr_);
    }

    Domain operator()(Domain arg) const {
        return Ptr_->Eval(arg);
    }

    Domain Eval(Domain arg) const {
        return Ptr_->Eval(arg);
    }

    template <typename U, typename ...Args>
    friend SharedPtr<typename U::Domain> MakeShared(Args&& ...args);

    template <typename OthDomain>
    friend class SharedPtr;

    template <typename OthDomain>
    SharedPtr(const SharedPtr<OthDomain>& other) {
        std::shared_ptr<TObj> copy(other.Ptr_);
        std::swap(copy, Ptr_);
    }

    template <typename OthDomain>
    SharedPtr(SharedPtr<OthDomain>&& other) : Ptr_(static_cast<const std::shared_ptr<PF::IPFunctionBase<double>>>(std::move(other.Ptr_))) {}

    template <typename OthDomain>
    SharedPtr& operator=(const SharedPtr<OthDomain>& other) {
        std::shared_ptr<TObj> copy(other.Ptr_);
        std::swap(copy, Ptr_);
        return *this;
    }

    template <typename OthDomain>
    SharedPtr& operator=(SharedPtr<OthDomain>&& other) {
        Ptr_ = std::move(other.Ptr_);
        return *this;
    }


  private:

    template <typename T>
    SharedPtr(std::shared_ptr<T> ptr) : Ptr_(ptr) {}

  private:
    mutable std::shared_ptr<TObj> Ptr_;
};

template <typename T, typename ...Args>
SharedPtr<typename T::Domain> MakeShared(Args&& ...args) {
    return SharedPtr<typename T::Domain>(std::make_shared<T>(std::forward<Args>(args)...));
}