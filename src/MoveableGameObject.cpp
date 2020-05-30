#include "MoveableGameObject.h"

namespace bricks {

using Point = types::Point;
using Length = types::Length;
using Width = types::Width;
using Velocity = types::Velocity;

MoveableGameObject::MoveableGameObject()
    : GameObject{}, mVelocity{0.0}
{
}

MoveableGameObject::MoveableGameObject(Point topLeft, types::Length length,
                                       Width width, Velocity velocity)
    : GameObject{topLeft, length, width}, mVelocity{velocity()}
{
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