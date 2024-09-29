#pragma once

#include "util/base_operators.h"

namespace LF {

    template <typename T>
    using IFunctionBase = const std::function<T(T)>;

}