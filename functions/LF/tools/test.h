#pragma once

#include "objects.h"
#include "range.h"

double loh(double x, double y, double z) {
    return x * z - y;
}

FUNCTION(loh)

namespace LF {
    void Test() {
        auto func = loh((x ^ 6) + 5, 8, x);

        assert( (x + 4)(20) == 24 );

        assert( func(1) == -2);

        int u = 0;
        for (auto i : TRange(0, 10, 2 * x + 2)) {
            assert( i == u );
            u = 2 * u + 2;
        }
        assert(u == 14);
    }
}