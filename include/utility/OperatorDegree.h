#ifndef UTILITY_OPERATORDEGREE_H
#define UTILITY_OPERATORDEGREE_H

#define _USE_MATH_DEFINES
#include <cmath>

namespace bricks::utility {

constexpr long double operator"" _deg(long double deg)
{
    return deg * M_PI / 180.0L;
}
} // namespace bricks
#endif
