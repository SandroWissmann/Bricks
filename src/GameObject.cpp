#include "GameObject.h"

#include "OperatorDegree.h"

#include <cassert>

namespace bricks {

GameObject::GameObject(Point topLeft, double maxPositionX, double maxPositionY,
                       double width, double height, double velocity,
                       long double angle)
    : mTopLeft{topLeft}, mMaxPositionX(maxPositionX),
      mMaxPositionY(maxPositionY), mWidth{width}, mHeight{height},
      mVelocity{velocity}, mQuadrant{impl::calcQuadrant(angle)},
      mQuadrantAngle{impl::angleToQuadrantAngle(angle, mQuadrant)}
{
    assert(mTopLeft.x > 0);
    assert(mTopLeft.y > 0);

    assert(maxPositionX > 0);
    assert(maxPositionY > 0);

    assert(width > 0);
    assert(height > 0);
}

GameObject::~GameObject() = default;

Point GameObject::topLeft() const { return mTopLeft; }

void GameObject::setTopLeft(Point topLeft) { mTopLeft = topLeft; }

Point GameObject::bottomRight() const
{
    return Point{mTopLeft.x + mWidth, mTopLeft.y + mHeight};
}

double GameObject::maxPositionX() const { return mMaxPositionX; }

double GameObject::maxPositionY() const { return mMaxPositionY; }

double GameObject::width() const { return mWidth; }

double GameObject::height() const { return mHeight; }

double GameObject::velocity() const { return mVelocity; }

void GameObject::setVelocity(double velocity) { mVelocity = velocity; }

long double GameObject::angle() const
{
    return impl::quadrantAngleToAngle(mQuadrantAngle, mQuadrant);
}

void GameObject::setAngle(long double angle)
{
    angle = impl::calcAngleIfOver360(angle);
    mQuadrant = impl::calcQuadrant(angle);
    mQuadrantAngle = impl::angleToQuadrantAngle(angle, mQuadrant);
}

long double GameObject::quadrantAngle() const { return mQuadrantAngle; }

void GameObject::setQuadrantAngle(long double quadrantAngle)
{
    assert(quadrantAngle >= 0.0 && quadrantAngle <= 90.0);

    // if (quadrantAngle > 90.0_deg) {
    //     setAngle(quadrantAngle);
    // }
    // else {
        mQuadrantAngle = quadrantAngle;
    // }
}

Quadrant GameObject::quadrant() const { return mQuadrant; }

void GameObject::setQuadrant(Quadrant quadrant) { mQuadrant = quadrant; }

namespace impl{

Quadrant calcQuadrant(long double angle)
{
    assert(angle >=0.0 && angle <= 360.0);

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

long double calcAngleIfOver360(long double angle)
{
    assert(angle > 0);

    while (angle > 360.0_deg) {
        angle -= 360.0_deg;
    }
    return angle;
}

}

} // namespace bricks