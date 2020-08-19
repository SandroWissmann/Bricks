#ifndef UTILITY_OPERATORDEGREE_H
#define UTILITY_OPERATORDEGREE_H

#define _USE_MATH_DEFINES
#include <cmath>

namespace bricks::utility {

constexpr long double operator"" _deg(long double radAngle)
{
    return rad2deg(radAngle);
}

constexpr long double rad2deg(long double radAngle)
{
    return radAngle * M_PI / 180.0L;
}

} // namespace bricks::utility
#endif
