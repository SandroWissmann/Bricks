#include "MoveableGameObject.h"

#include <algorithm>
#include <cassert>

namespace bricks {

    MoveableGameObject::MoveableGameObject(
        Point topLeft, Width width, Height height, 
        MaxPositionX maxPositionX, MaxPositionY maxPositionY, 
        Velocity velocity)
    :GameObject{topLeft, width, height},
     mMaxPositionX(maxPositionX()), mMaxPositionY(maxPositionY()),
      mVelocity{velocity()}
{
    assert(mMaxPositionX > 0);
    assert(mMaxPositionY > 0);
}

void MoveableGameObject::setTopLeft(Point topLeft) 
{
    topLeft.x = std::clamp(topLeft.x, 0.0, mMaxPositionX - width());
    topLeft.y = std::clamp(topLeft.y, 0.0, mMaxPositionY - height());

    GameObject::setTopLeft(topLeft);
}

double MoveableGameObject::velocity() const { return mVelocity; }

void MoveableGameObject::setVelocity(double velocity) { mVelocity = velocity; }

} // namespace bricks