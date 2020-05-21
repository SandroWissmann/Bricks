#include "GameObject.h"

#include "OperatorDegree.h"

#include <algorithm>
#include <cassert>

namespace bricks {

GameObject::GameObject(Point topLeft, MaxPositionX maxPositionX,
                       MaxPositionY maxPositionY, Width width, Height height,
                       Velocity velocity, Angle angle)
    : mTopLeft{topLeft}, mMaxPositionX(maxPositionX()),
      mMaxPositionY(maxPositionY()), mWidth{width()}, mHeight{height()},
      mVelocity{velocity()}, mAngle{angle}
{
    assert(mTopLeft.x > 0);
    assert(mTopLeft.y > 0);

    assert(mMaxPositionX > 0);
    assert(mMaxPositionY > 0);

    assert(mWidth > 0);
    assert(mHeight > 0);
}

GameObject::~GameObject() = default;

Point GameObject::topLeft() const { return mTopLeft; }

void GameObject::setTopLeft(Point topLeft)
{
    topLeft.x = std::clamp(topLeft.x, 0.0, mMaxPositionX - mWidth);
    topLeft.y = std::clamp(topLeft.y, 0.0, mMaxPositionY - mHeight);

    mTopLeft = topLeft;
}

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

Angle GameObject::angle() const
{
    return mAngle;
}

void GameObject::setAngle(Angle angle)
{
    mAngle = angle;
}

} // namespace bricks