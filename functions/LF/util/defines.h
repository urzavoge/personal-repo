#pragma once

#include "common.h"

#define BIND(action) [=](T arg){ return action; }

#define DEFINE_BASE_OPERATION(name, operation) namespace LF {\
    template <typename T, typename U> \
    T name(const T& first, const U& second) { return first operation second; } }

#define DEFINE_DOUBLE_ARG_FUNCTION(operation, action) namespace LF { \
    template <typename T> \
    TFunction<T> operation(const TFunction<T>& first, const TFunction<T>& second) { \
        return TFunction<T>(BIND( action(first(arg), second(arg)) )); } \
    template <typename T, typename U> \
    TFunction<T> operation(const TFunction<T>& first, const U& second) { \
        return TFunction<T>(BIND( action(first(arg), second) )); }\
    template <typename T, typename U> \
    TFunction<T> operation(const U& first, const TFunction<T>& second) { \
        return TFunction<T>(BIND( action(first, second(arg)) )); }}

#define DEFINE_SINGLE_ARG_FUNCTION(operation, action) namespace LF { \
    template <typename T> \
    TFunction<T> operation(const TFunction<T>& func) { \
        return TFunction<T>(BIND( action(func(arg)) )); } \
    template <typename T, typename U> \
    TFunction<T> operation(const U& val) { \
         return TFunction<T>(BIND( action(val) )); }}

#define FUNCTION_WITH_TYPE(func, type) namespace LF { static auto inner_##func = func; \
    template <typename ...Args> \
    TFunction<type> func(Args... args) { \
        return TFunction<type>(     \
                    [=](type arg){ return inner_##func(Argument<type, Args>(arg, args)...); } \
 ); }}

#define FUNCTION(func) FUNCTION_WITH_TYPE(func, double)
