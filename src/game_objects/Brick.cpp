#include "Brick.h"

#include <cassert>

namespace bricks::game_objects {

using Point = types::Point;
using Width = types::Width;
using Height = types::Height;
using Hitpoints = types::Hitpoints;

Brick::Brick() : GameObject{}, mStartHitpoints{0}, mHitpoints{mStartHitpoints}
{
}

Brick::Brick(Point topLeft, Width width, Height height, Hitpoints hitpoints)
    : GameObject(topLeft, width, height), mStartHitpoints{hitpoints()},
      mHitpoints{mStartHitpoints}
{
    assert(mHitpoints > 0 && mHitpoints < 10);
}

int Brick::startHitpoints() const
{
    return mStartHitpoints;
}

int Brick::hitpoints() const
{
    return mHitpoints;
}

void Brick::decreaseHitpoints()
{
    if (mHitpoints > 0) {
        --mHitpoints;
    }
}

bool Brick::isDestroyed() const
{
    return mHitpoints == 0;
}
} // namespace bricks::game_objects
