#include "MoveableGameObject.h"

#include <algorithm>
#include <cassert>

namespace bricks {

using Point = types::Point;
using Length = types::Length;
using Height = types::Height;
using MaxPositionX = types::MaxPositionX;
using MaxPositionY = types::MaxPositionY;
using Velocity = types::Velocity;

MoveableGameObject::MoveableGameObject(Point topLeft, types::Length length,
                                       Height height, MaxPositionX maxPositionX,
                                       MaxPositionY maxPositionY,
                                       Velocity velocity)
    : GameObject{topLeft, length, height}, mMaxPositionX(maxPositionX()),
      mMaxPositionY(maxPositionY()), mVelocity{velocity()}
{
    assert(mMaxPositionX > 0);
    assert(mMaxPositionY > 0);
}

void MoveableGameObject::setTopLeft(Point topLeft)
{
    topLeft.x = std::clamp(topLeft.x, 0.0, mMaxPositionX - length());
    topLeft.y = std::clamp(topLeft.y, 0.0, mMaxPositionY - height());

    GameObject::setTopLeft(topLeft);
}

double MoveableGameObject::maxPositionX() const
{
    return mMaxPositionX;
}

double MoveableGameObject::maxPositionY() const
{
    return mMaxPositionY;
}

double MoveableGameObject::velocity() const
{
    return mVelocity;
}

void MoveableGameObject::setVelocity(double velocity)
{
    mVelocity = velocity;
}

} // namespace bricks