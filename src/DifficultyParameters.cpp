#include "DifficultyParameters.h"

namespace bricks {

using Velocity = types::Velocity;
using Width = types::Width;
using Gravity = types::Gravity;

DifficultyParameters::DifficultyParameters(const Velocity& platformVelocity,
                                           const Width& platformWidth,
                                           const Velocity& ballVelocity,
                                           const Gravity& ballGravity)
    : mPlatformVelocity{platformVelocity}, mPlatformWidth{platformWidth},
      mBallVelocity{ballVelocity}, mBallGravity{ballGravity}
{
}

void DifficultyParameters::setPlatformVelocity(const Velocity& velocity)
{
    mPlatformVelocity = velocity;
}

void DifficultyParameters::setPlatformWidth(const Width& width)
{
    mPlatformWidth = width;
}

void DifficultyParameters::setBallVelocity(const Velocity& velocity)
{
    mPlatformVelocity = velocity;
}

void DifficultyParameters::setBallGravity(const Gravity& gravity)
{
    mBallGravity = gravity;
}

Velocity DifficultyParameters::getPlatformVelocity() const
{
    return mPlatformVelocity;
}

Width DifficultyParameters::getPlatformWidth() const
{
    return mPlatformWidth;
}

Velocity DifficultyParameters::getBallVelocity() const
{
    return mBallVelocity;
}

Gravity DifficultyParameters::getBallGravity() const
{
    return mBallGravity;
}
} // namespace bricks