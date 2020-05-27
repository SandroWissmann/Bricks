#ifndef RGBCOLOR_H
#define RGBCOLOR_H

#include <cassert>

namespace bricks {
class RGBColor {
public:
    constexpr RGBColor(int r, int g, int b, int a = 0xFF)
        : mR{r}, mG{g}, mB{b}, mA{a}
    {
        assert(mR >= 0 && mR <= 0xFF);
        assert(mG >= 0 && mG <= 0xFF);
        assert(mB >= 0 && mB <= 0xFF);
        assert(mA >= 0 && mA <= 0xFF);
    }

    constexpr int r() const
    {
        return mR;
    }

    constexpr int g() const
    {
        return mG;
    }

    constexpr int b() const
    {
        return mB;
    }

    constexpr int a() const
    {
        return mA;
    }

private:
    const int mR;
    const int mG;
    const int mB;
    const int mA;
};
} // namespace bricks
#endif