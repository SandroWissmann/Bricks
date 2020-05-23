#ifndef BALL_H
#define BALL_H

#include "MoveableGameObject.h"
#include "types/Angle.h"
#include "types/Gravity.h"

namespace bricks {

class Ball : public MoveableGameObject {
public:
    Ball(types::Point topLeft, types::Width width, types::Height height,
         types::MaxPositionX maxPositionX, types::MaxPositionY maxPositionY,
         types::Velocity velocity, types::Angle angle, types::Gravity gravity);

    ~Ball() override = default;

    Ball(const Ball &) = default;
    Ball(Ball &&) = default;
    Ball &operator=(const Ball &other) = default;
    Ball &operator=(Ball &&other) = default;

    types::Angle angle() const;
    void setAngle(types::Angle angle);

    double gravity() const;
    void setGravity(double Gravity);

    bool isActive() const;
    void activate();

    void move(double elapsedTimeInMS) override;

private:
    types::Angle mAngle;
    double mGravity;
    bool mIsActive;
};

types::Point calcNewPosition(const types::Point &p, double velocity,
                             types::Angle angle, double elapsedTimeInMS);

double calcTraveldWay(double deltaTimeMS, double velocityInS);

types::Point calcDelta(types::Angle angle, double sideC);
} // namespace bricks
#endif