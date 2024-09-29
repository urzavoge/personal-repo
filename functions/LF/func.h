#pragma once

#include "object.h"

namespace LF {

    struct Tag {};

    template <typename T>
    class TFunction {
      public:

        TFunction(IFunctionBase<T>&& func) : Func_(std::move(func)) {}

        TFunction(Tag) : Func_(BIND( arg )) {}

        TFunction(const T& val) : Func_(BIND( val )) {}

        T operator()(T x) const {
            return Func_(x);
        }

      private:
        IFunctionBase<T> Func_;
    };
}
