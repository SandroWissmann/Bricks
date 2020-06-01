#include "Angle.h"

#include "../utility/OperatorDegree.h"

#include <cassert>

#include <algorithm>
#include <iostream>

namespace bricks::types {

using namespace utility;

Angle::Angle()
    : mQuadrant{impl::calcQuadrant(0.0)},
      mQuadrantAngle{impl::angleToQuadrantAngle(0.0, mQuadrant)}
{
}

Angle::Angle(long double angle)
    : mQuadrant{impl::calcQuadrant(angle)},
      mQuadrantAngle{impl::angleToQuadrantAngle(angle, mQuadrant)}
{
}

long double Angle::Angle::get() const
{
    return impl::quadrantAngleToAngle(mQuadrantAngle, mQuadrant);
}

void Angle::set(long double angle)
{
    angle = impl::calcAngleIfOutOfRange(angle);
    mQuadrant = impl::calcQuadrant(angle);
    mQuadrantAngle = impl::angleToQuadrantAngle(angle, mQuadrant);
}

long double Angle::quadrantAngle() const
{
    return mQuadrantAngle;
}

void Angle::setQuadrantAngle(long double quadrantAngle)
{
    if(quadrantAngle <0.0_deg || quadrantAngle > 90.0_deg) {
        std::cerr << "void Angle::setQuadrantAngle(long double quadrantAngle)\n" 
        "Out of Range 0.0_deg to 90.0_deg\n"
        "supllied angle: " << quadrantAngle << '\n';
        quadrantAngle = std::clamp(quadrantAngle, 0.0_deg, 90.0_deg);
    }
    mQuadrantAngle = quadrantAngle;
}

Quadrant Angle::quadrant() const
{
    return mQuadrant;
}

void Angle::setQuadrant(Quadrant quadrant)
{
    mQuadrant = quadrant;
}

void Angle::mirrorHorizontal()
{
    switch (mQuadrant) {
    case Quadrant::I:
        mQuadrant = Quadrant::IV;
        break;
    case Quadrant::II:
        mQuadrant = Quadrant::III;
        break;
    case Quadrant::III:
        mQuadrant = Quadrant::II;
        break;
    case Quadrant::IV:
        mQuadrant = Quadrant::I;
        break;
    }
    mQuadrantAngle = impl::mirrorQuadrantAngle(mQuadrantAngle);
}

void Angle::mirrorVertical()
{
    switch (mQuadrant) {
    case Quadrant::I:
        mQuadrant = Quadrant::II;
        break;
    case Quadrant::II:
        mQuadrant = Quadrant::I;
        break;
    case Quadrant::III:
        mQuadrant = Quadrant::IV;
        break;
    case Quadrant::IV:
        mQuadrant = Quadrant::III;
        break;
    }
    mQuadrantAngle = impl::mirrorQuadrantAngle(mQuadrantAngle);
}

namespace impl {

long double mirrorQuadrantAngle(long double quadrantAngle)
{
    return 90.0_deg - quadrantAngle;
}

Quadrant calcQuadrant(long double angle)
{
    assert(angle >= 0.0 && angle <= 360.0);

    if (isInQuadrantI(angle)) {
        return Quadrant::I;
    }
    if (isInQuadrantII(angle)) {
        return Quadrant::II;
    }
    if (isInQuadrantIII(angle)) {
        return Quadrant::III;
    }
    return Quadrant::IV;
}

bool isInQuadrantI(long double angle)
{
    return angle >= 0.0_deg && angle <= 90.0_deg;
}

bool isInQuadrantII(long double angle)
{
    return angle > 90.0_deg && angle <= 180.0_deg;
}

bool isInQuadrantIII(long double angle)
{
    return angle > 180.0_deg && angle <= 270.0_deg;
}

bool isInQuadrantIV(long double angle)
{
    return angle > 270.0_deg && angle <= 360.0_deg;
}

long double angleToQuadrantAngle(long double angle, Quadrant quadrant)
{
    return angle - 90.0_deg * static_cast<int>(quadrant);
}

long double quadrantAngleToAngle(long double quadrantAngle, Quadrant quadrant)
{
    return quadrantAngle + 90.0_deg * static_cast<int>(quadrant);
}

long double calcAngleIfOutOfRange(long double angle)
{
    while (angle < 0.0_deg) {
        angle += 360.0_deg;
    }
    while (angle > 360.0_deg) {
        angle -= 360.0_deg;
    }
    return angle;
}

} // namespace impl
} // namespace bricks::types