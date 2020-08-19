#ifndef UTILITY_OPERATORDEGREE_H
#define UTILITY_OPERATORDEGREE_H

#define _USE_MATH_DEFINES
#include <cmath>

namespace bricks::utility {

constexpr long double deg2rad(long double degAngle)
{
    return degAngle * M_PI / 180.0L;
}

constexpr long double operator"" _deg(long double degAngle)
{
    return deg2rad(degAngle);
}

} // namespace bricks::utility
#endif
