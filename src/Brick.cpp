#include "Brick.h"

#include <cassert>

namespace bricks {

using Point = types::Point;
using Length = types::Length;
using Width = types::Width;
using Hitpoints = types::Hitpoints;

Brick::Brick(Point topLeft, Length length, Width width, Hitpoints hitpoints)
    : GameObject(topLeft, length, width), mStartHitpoints{hitpoints()},
      mHitpoints{mStartHitpoints}
{
    assert(mHitpoints > 0);
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
} // namespace bricks
