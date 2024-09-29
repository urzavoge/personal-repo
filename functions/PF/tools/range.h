#pragma once

#include "objects.h"

namespace PF {

    template<typename T>
    class TRange {
      public:
        TRange(T range) : Start_(0), End_([=](T arg) { return arg < range; }), Next_(x + 1) {}
        TRange(T start, T end) : Start_(start), End_([=](T arg) { return arg < end; }), Next_(x + 1) {}
        TRange(T start, T end, T step) : Start_(start), End_([=](T arg) { return arg < end; }), Next_(x + step) {}

        template <typename U>
        TRange(U start, U end, TFunctionPtr<T> step) : Start_(start), End_([=](T arg) { return arg < end; }), Next_(step) {}

        class TIterator {
          public:
            TIterator(const TRange *base) : Node_(base), Value_(Node_->Start_) {}

            TIterator &operator++() {
                Value_ = Node_->Next_(Value_);
                return *this;
            }

            TIterator operator++(int) {
                TIterator copy(*this);
                return ++copy;
            }

            bool operator!=(const TIterator &) {
                return Node_->End_(Value_);
            }

            bool operator==(const TIterator &other) {
                return other.Node_ == Node_ && other.Value_ == Value_;
            }

            T &operator*() {
                return Value_;
            }


          private:
            const TRange *Node_;

            T Value_;
        };

        TIterator begin() const {
            return TIterator(this);
        }

        TIterator end() const {
            return TIterator(this);
        }

      private:
        T Start_;

        std::function<bool(T)> End_;

        TFunctionPtr<T> Next_;
    };

}