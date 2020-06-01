#ifndef UTILITY_NEARLYEQUAL_H
#define UTILITY_NEARLYEQUAL_H

namespace bricks::utility {

template <typename FloatingPointType>
bool nearlyEqual(FloatingPointType a, FloatingPointType b);

template <typename FloatingPointType>
bool nearlyEqual(FloatingPointType a, FloatingPointType b, int factor);

template <typename FloatingPointType>
FloatingPointType nextLow(FloatingPointType a);

template <typename FloatingPointType>
FloatingPointType nextHight(FloatingPointType a);
} // namespace bricks::utility
#endif