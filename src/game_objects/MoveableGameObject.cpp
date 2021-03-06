#include "MoveableGameObject.h"

namespace bricks::game_objects {

using Point = types::Point;
using Width = types::Width;
using Height = types::Height;
using Velocity = types::Velocity;

MoveableGameObject::MoveableGameObject() : mVelocity{0.0}
{
}

MoveableGameObject::MoveableGameObject(Point topLeft, types::Width width,
                                       Height height, Velocity velocity)
    : GameObject{topLeft, width, height}, mVelocity{velocity()}
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

} // namespace bricks::game_objects