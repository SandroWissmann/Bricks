#ifndef NEARLYEQUAL_H
#define NEARLYEQUAL_H

namespace bricks {

template <typename FloatingPointType>
bool nearlyEqual(FloatingPointType a, FloatingPointType b);

template <typename FloatingPointType>
bool nearlyEqual(FloatingPointType a, FloatingPointType b, int factor);

template <typename FloatingPointType>
FloatingPointType nextLow(FloatingPointType a);

template <typename FloatingPointType>
FloatingPointType nextHight(FloatingPointType a);
} // namespace bricks
#endif