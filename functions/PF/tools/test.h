#pragma once

#include "objects.h"
#include "range.h"

double MyCoolFunc(double x, double y, double z) {
    return x;
}

double MyFoo(double x, double y, double z, double w) {
    return  x + y + z + w;
}

REGISTER_FUNCTION(double, MyCoolFunc)
REGISTER_FUNCTION(double, MyFoo)

void Test() {
    PF::TFunctionPtr<double> x = MakeShared<PF::TPFunctionId<double>>();
    assert(std::abs(sin(cos(tan((x^3) + 5) - ln(x * 7 - 8)))(20) + 0.0551659) < 0.00001);
    assert(abs(sin(cos(tan((x^3) + 5) - ln(x * 7 - 8))) + 0.0551659)(20) < 0.00001);

    assert(MyFoo(x, x, x, x)(5) == 20);

    int u = 0;
    for (auto i : PF::TRange(0, 10, x + 3)) {
        assert(i == u);
        u += 3;
    }
    assert(u == 12);
}