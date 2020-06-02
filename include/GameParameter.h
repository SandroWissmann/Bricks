#ifndef GAMEPARAMETER_H
#define GAMEPARAMETER_H

#include "types/Gravity.h"
#include "types/Velocity.h"
#include "types/Width.h"

namespace bricks {

class GameParameter {
public:
    GameParameter(
        const types::Velocity& platformVelocity = types::Velocity{16.0},
        const types::Width& platformWidth = types::Width{4.0},
        const types::Velocity& ballVelocity = types::Velocity{16.0},
        const types::Gravity& ballGravity = types::Gravity{1.5});

    void setPlatformVelocity(const types::Velocity& velocity);
    void setPlatformWidth(const types::Width& width);
    void setBallVelocity(const types::Velocity& velocity);
    void setBallGravity(const types::Gravity& gravity);

    types::Velocity getPlatformVelocity() const;
    types::Width getPlatformWidth() const;
    types::Velocity getBallVelocity() const;
    types::Gravity getBallGravity() const;

private:
    types::Velocity mPlatformVelocity;
    types::Width mPlatformWidth;
    types::Velocity mBallVelocity;
    types::Gravity mBallGravity;
};

} // namespace bricks

#endif