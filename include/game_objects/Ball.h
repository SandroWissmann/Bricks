#ifndef GAME_OBJECTS_BALL_H
#define GAME_OBJECTS_BALL_H

#include "../types/Angle.h"
#include "../types/Gravity.h"
#include "MoveableGameObject.h"

namespace bricks::game_objects {

class Ball : public MoveableGameObject {
public:
    Ball();

    Ball(types::Point topLeft, types::Width width, types::Height height,
         types::Velocity velocity, types::Angle angle, types::Gravity gravity);

    ~Ball() override = default;

    Ball(const Ball&) = default;
    Ball(Ball&&) = default;
    Ball& operator=(const Ball& other) = default;
    Ball& operator=(Ball&& other) = default;

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

types::Point calcNewPosition(const types::Point& p, double velocity,
                             types::Angle angle, double elapsedTimeInMS);

double calcTraveldWay(double deltaTimeMS, double velocityInS);

types::Point calcDelta(types::Angle angle, double sideC);
} // namespace bricks::game_objects
#endif