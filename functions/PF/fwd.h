#pragma once

#define DECLARE_FUNC(name) \
    template <typename T> \
    class TPFunction##name;

namespace PF {

    template <typename T>
    class IPFunctionBase;

    DECLARE_FUNC(Const);
    DECLARE_FUNC(Id);
    DECLARE_FUNC(Sum);
    DECLARE_FUNC(Multiply);
    DECLARE_FUNC(Minus);
    DECLARE_FUNC(Divide);
    DECLARE_FUNC(UnMinus)
}

