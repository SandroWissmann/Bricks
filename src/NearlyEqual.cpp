#include "NearlyEqual.h"

#include <cmath>
#include <limits>

namespace bricks {

template <typename FloatingPointType>
bool nearlyEqual(FloatingPointType a, FloatingPointType b)
{
    return nextLow(a) <= b && nextHight(a) >= b;
}

template <> bool nearlyEqual<float>(float a, float b);
template <> bool nearlyEqual<double>(double a, double b);
template <> bool nearlyEqual<long double>(long double a, long double b);

template <typename FloatingPointType>
bool nearlyEqual(FloatingPointType a, FloatingPointType b, int factor)
{
    auto minA = a - (a - nextLow(a)) * factor;
    auto maxA = a + (nextHight(a) - a) * factor;

    return minA <= b && maxA >= b;
}

template <> bool nearlyEqual<float>(float a, float b, int factor);
template <> bool nearlyEqual<double>(double a, double b, int factor);
template <>
bool nearlyEqual<long double>(long double a, long double b, int factor);

template <typename FloatingPointType>
FloatingPointType nextLow(FloatingPointType a)
{
    return std::nextafter(a, std::numeric_limits<FloatingPointType>::lowest());
}

template <> float nextLow<float>(float a);
template <> double nextLow<double>(double a);
template <> long double nextLow<long double>(long double a);

template <typename FloatingPointType>
FloatingPointType nextHight(FloatingPointType a)
{
    return std::nextafter(a, std::numeric_limits<FloatingPointType>::max());
}

template <> float nextHight<float>(float a);
template <> double nextHight<double>(double a);
template <> long double nextHight<long double>(long double a);
} // namespace bricks