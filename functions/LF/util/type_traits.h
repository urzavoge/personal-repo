#pragma once

#include "common.h"

namespace LF {

    template <typename T, typename F>
    auto Argument(T arg, F f) -> T {
        if constexpr (std::invocable<F, T>) {
            return f(arg);
        } else {
            return T(f);
        }
    }

}