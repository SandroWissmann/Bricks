#include "GameParameter.h"

namespace bricks{

    using Velocity = types::Velocity;
    using Width = types::Width;
    using Gravity = types::Gravity;

    GameParameter::GameParameter(const Velocity& platformVelocity, 
        const Width& platformWidth, 
        const Velocity& ballVelocity,
        const Gravity& ballGravity)
    {     
    }

    void GameParameter::setPlatformVelocity(const Velocity& velocity)
    {
        mPlatformVelocity = velocity;
    }

    void GameParameter::setPlatformWidth(const Width& width)
    {
        mPlatformWidth = width;
    }

    void GameParameter::setBallVelocity(const Velocity& velocity)
    {
        mPlatformVelocity = velocity;
    }

    void GameParameter::setBallGravity(const Gravity& gravity)
    {
        mBallGravity = gravity;
    }

    Velocity GameParameter::getPlatformVelocity() const
    {
        return mPlatformVelocity;
    }

    Width GameParameter::getPlatformWidth() const
    {
        return mPlatformWidth;
    }

    Velocity GameParameter::getBallVelocity() const
    {
        return mBallVelocity;
    }

    Gravity GameParameter::getBallGravity() const
    {
        return mBallGravity;
    }
}