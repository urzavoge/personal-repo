#pragma once

#include "../util/defines.h"
#include "../func.h"

DECLARE_DOUBLE_ARG_FUNCTION(Sum, operator+, First_->Eval(arg) + Second_->Eval(arg))
DECLARE_DOUBLE_ARG_FUNCTION(Multiply,operator*, First_->Eval(arg) * Second_->Eval(arg))
DECLARE_DOUBLE_ARG_FUNCTION(Minus, operator-, First_->Eval(arg) - Second_->Eval(arg))
DECLARE_DOUBLE_ARG_FUNCTION(Divide, operator/, First_->Eval(arg) / Second_->Eval(arg))
DECLARE_SINGLE_ARG_FUNCTION(UnMinus, operator-, -Func_->Eval(arg))
DECLARE_DOUBLE_ARG_FUNCTION(Power, operator^, std::pow(First_->Eval(arg), Second_->Eval(arg)))

/* user declared functions!
 * to declare your function
 * call this macro with a tedious number of arguments (SINGLE or DOUBLE)
 * pass custom name (you will write it in expression) and c++ name of your function
 */

SINGLE_ARG_FUNCTION(ln, std::log)
SINGLE_ARG_FUNCTION(sin, std::sin)
SINGLE_ARG_FUNCTION(cos, std::cos)
SINGLE_ARG_FUNCTION(tan, std::tan)
SINGLE_ARG_FUNCTION(abs, std::abs)
