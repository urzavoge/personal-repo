#pragma once

#include "../func.h"
#include "../util/type_traits.h"

DEFINE_DOUBLE_ARG_FUNCTION(operator+, sum)
DEFINE_DOUBLE_ARG_FUNCTION(operator-, minus)
DEFINE_DOUBLE_ARG_FUNCTION(operator*, multiply)
DEFINE_DOUBLE_ARG_FUNCTION(operator/, divide)
DEFINE_DOUBLE_ARG_FUNCTION(operator^, std::pow)

DEFINE_SINGLE_ARG_FUNCTION(operator-, -)
DEFINE_SINGLE_ARG_FUNCTION(sin, std::sin)
DEFINE_SINGLE_ARG_FUNCTION(cos, std::cos)
DEFINE_SINGLE_ARG_FUNCTION(tan, std::tan)
DEFINE_SINGLE_ARG_FUNCTION(abs, std::abs)
DEFINE_SINGLE_ARG_FUNCTION(ln, std::log)
