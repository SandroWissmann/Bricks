#ifndef OPERATORDEGREE_H
#define OPERATORDEGREE_H

#include <cmath>

namespace bricks {

constexpr long double pi() { return std::atan(1) * 4; }

constexpr long double operator"" _deg(long double deg)
{
    return deg * pi() / 180.0L;
}
} // namespace bricks
#endif
