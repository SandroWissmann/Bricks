#include "Brick.h"

#include <stdexcept>

namespace bricks::game_objects {

using Point = types::Point;
using Width = types::Width;
using Height = types::Height;
using Hitpoints = types::Hitpoints;

Brick::Brick() : mStartHitpoints{1}, mHitpoints{mStartHitpoints}
{
}

Brick::Brick(Point topLeft, Width width, Height height, Hitpoints hitpoints)
    : GameObject(topLeft, width, height),
      mStartHitpoints{checkArgs(hitpoints())}, mHitpoints{mStartHitpoints}
{
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

int Brick::checkArgs(int hitpoints)
{
    if (hitpoints < 1 || hitpoints > 9) {
        throw std::invalid_argument("int Brick::checkArgs(int hitpoints)\n"
                                    "hitpoints must be > 0 and < 10\n"
                                    "hitpoints: " +
                                    std::to_string(hitpoints));
    }
    return hitpoints;
}

} // namespace bricks::game_objects
