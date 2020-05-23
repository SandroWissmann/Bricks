#include "Ball.h"

#include "NearlyEqual.h"
#include "OperatorDegree.h"

namespace bricks {

    Ball::Ball(Point topLeft, Width width, Height height, 
    MaxPositionX maxPositionX, MaxPositionY maxPositionY, 
    Velocity velocity, Angle angle, Gravity gravity)
        :MoveableGameObject{topLeft, width, height, maxPositionX, maxPositionY,
        velocity}, mAngle{angle}, mGravity{gravity()}, mIsActive{false}
    {
    }

    Angle Ball::angle() const
    {
        return mAngle;
    }

    void Ball::setAngle(Angle angle)
    {
        mAngle = angle;
    }

    double Ball::gravity() const
    {
        return mGravity;
    }

    void Ball::setGravity(double Gravity)
    {
        mGravity = Gravity;
    }

    bool Ball::isActive() const
    {
        return mIsActive;
    }

    void Ball::activate() 
    {
        mIsActive = true;
    }

    void Ball::move(double elapsedTimeInMS) 
    {
        if(!isActive()) {
            return;
        }

        auto newPos = topLeft();

        if(velocity() != 0.0) {
            newPos = calcNewPosition(newPos, velocity(), angle(), 
            elapsedTimeInMS);
        }

        if (gravity() != 0.0) {
             newPos = calcNewPosition(newPos, gravity(), Angle{90.0_deg}, 
             elapsedTimeInMS);
        }

        setTopLeft(newPos);
    }

    Point calcNewPosition(const Point &p, double velocity, Angle angle, 
    double elapsedTimeInMS)
{
    auto distance = calcTraveldWay(elapsedTimeInMS, velocity);
    auto traveldWay = calcDelta(angle, distance);

    return Point{p.x + traveldWay.x, p.y + traveldWay.y};
}

double calcTraveldWay(double deltaTimeMS, double velocityInS)
{
    return deltaTimeMS / 1000.0 * velocityInS;
}

Point calcDelta(Angle angle, double sideC)
{
    if (nearlyEqual(sideC, 0.0)) {
        return Point{0, 0};
    }

    auto sideA = sin(angle.quadrantAngle()) * sideC;
    auto sideB = cos(angle.quadrantAngle()) * sideC;

    Point ret;
    switch (angle.quadrant()) {
    case Quadrant::I:
        ret.x = sideB;
        ret.y = sideA;
        break;
    case Quadrant::II:
        ret.x = -sideA;
        ret.y = sideB;
        break;
    case Quadrant::III:
        ret.x = -sideB;
        ret.y = -sideA;
        break;
    case Quadrant::IV:
        ret.x = sideA;
        ret.y = -sideB;
        break;
    }
    return ret;
}


}