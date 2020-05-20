#ifndef NEARLYEQUAL_H
#define NEARLYEQUAL_H

namespace bricks {

    template <typename FloatingPointType>
	bool nearlyEqual(FloatingPointType a, FloatingPointType b);

    template <typename FloatingPointType>
	bool nearlyEqual(FloatingPointType a, FloatingPointType b, int factor);

    template <typename FloatingPointType>
    double nextLow(FloatingPointType a);

    template <typename FloatingPointType>
    double nextHight(FloatingPointType a);
}
#endif