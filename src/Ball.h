#ifndef BALL_H
#define BALL_H

#include "Angle.h"
#include "MoveableGameObject.h"

namespace bricks {

struct Gravity {
    double value;

    double operator()() const
    {
        return value;
    }
};

class Ball : public MoveableGameObject {
public:
    Ball(Point topLeft, Width width, Height height, MaxPositionX maxPositionX,
         MaxPositionY maxPositionY, Velocity velocity, Angle angle,
         Gravity gravity);

    ~Ball() override = default;

    Ball(const Ball &) = default;
    Ball(Ball &&) = default;
    Ball &operator=(const Ball &other) = default;
    Ball &operator=(Ball &&other) = default;

    Angle angle() const;
    void setAngle(Angle angle);

    double gravity() const;
    void setGravity(double Gravity);

    bool isActive() const;
    void activate();

    void move(double elapsedTimeInMS) override;

private:
    Angle mAngle;
    double mGravity;
    bool mIsActive;
};

Point calcNewPosition(const Point &p, double velocity, Angle angle,
                      double elapsedTimeInMS);

double calcTraveldWay(double deltaTimeMS, double velocityInS);

Point calcDelta(Angle angle, double sideC);
} // namespace bricks
#endif