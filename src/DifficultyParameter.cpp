#include "DifficultyParameter.h"

namespace bricks {

using Velocity = types::Velocity;
using Width = types::Width;
using Gravity = types::Gravity;

DifficultyParameter::DifficultyParameter(const Velocity& platformVelocity,
                                         const Width& platformWidth,
                                         const Velocity& ballVelocity,
                                         const Gravity& ballGravity)
    : mPlatformVelocity{platformVelocity}, mPlatformWidth{platformWidth},
      mBallVelocity{ballVelocity}, mBallGravity{ballGravity}
{
}

void DifficultyParameter::setPlatformVelocity(const Velocity& velocity)
{
    mPlatformVelocity = velocity;
}

void DifficultyParameter::setPlatformWidth(const Width& width)
{
    mPlatformWidth = width;
}

void DifficultyParameter::setBallVelocity(const Velocity& velocity)
{
    mPlatformVelocity = velocity;
}

void DifficultyParameter::setBallGravity(const Gravity& gravity)
{
    mBallGravity = gravity;
}

Velocity DifficultyParameter::getPlatformVelocity() const
{
    return mPlatformVelocity;
}

Width DifficultyParameter::getPlatformWidth() const
{
    return mPlatformWidth;
}

Velocity DifficultyParameter::getBallVelocity() const
{
    return mBallVelocity;
}

Gravity DifficultyParameter::getBallGravity() const
{
    return mBallGravity;
}
} // namespace bricks