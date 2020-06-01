#include "RGBColor.h"

#include <cassert>

#include <algorithm>

namespace bricks::types {

RGBColor::RGBColor(int r, int g, int b, int a) : mR{r}, mG{g}, mB{b}, mA{a}
{
    assert(mR >= 0 && mR <= 0xFF);
    assert(mG >= 0 && mG <= 0xFF);
    assert(mB >= 0 && mB <= 0xFF);
    assert(mA >= 0 && mA <= 0xFF);
}

int RGBColor::r() const
{
    return mR;
}

int RGBColor::g() const
{
    return mG;
}

int RGBColor::b() const
{
    return mB;
}

int RGBColor::a() const
{
    return mA;
}

RGBColor RGBColor::lighter(double factor) const
{
    return RGBColor{
        calcLighterPart(mR, factor),
        calcLighterPart(mG, factor),
        calcLighterPart(mB, factor),
    };
}

RGBColor RGBColor::darker(double factor) const
{
    return RGBColor{
        calcDarkerPart(mR, factor),
        calcDarkerPart(mG, factor),
        calcDarkerPart(mB, factor),
    };
}

RGBColor RGBColor::grayscale() const
{
    return RGBColor{
        static_cast<int>(double(mR) * 0.2126),
        static_cast<int>(double(mG) * 0.7152),
        static_cast<int>(double(mB) * 0.0722),
    };
}

int RGBColor::calcLighterPart(int part, double factor) const
{
    return std::clamp(static_cast<int>(part + (0xFF - part) * factor), 0x00,
                      0xFF);
}

int RGBColor::calcDarkerPart(int part, double factor) const
{
    return std::clamp(static_cast<int>(part * (1.0 - factor)), 0x00, 0xFF);
}
} // namespace bricks