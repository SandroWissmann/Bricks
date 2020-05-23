#ifndef OPERATORDEGREE_H
#define OPERATORDEGREE_H

#define _USE_MATH_DEFINES
#include <cmath>

namespace bricks {

constexpr long double operator"" _deg(long double deg)
{
    return deg * M_PI / 180.0L;
}
} // namespace bricks
#endif
