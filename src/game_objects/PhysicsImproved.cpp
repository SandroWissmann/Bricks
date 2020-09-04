#include "PhysicsImproved.h"

#include "Ball.h"
#include "Brick.h"
#include "GameObject.h"
#include "IndestructibleBrick.h"
#include "Platform.h"
#include "Wall.h"

#include "../types/Angle.h"
#include "../types/Point.h"
#include "../utility/NearlyEqual.h"
#include "../utility/OperatorDegree.h"

#include <algorithm>
#include <random>

#include <cassert>

namespace bricks::game_objects::improved {

using namespace utility;

using Angle = types::Angle;
using Point = types::Point;
using Quadrant = types::Quadrant;

bool reflectFromPlatform(const Ball& ball, const Platform& platform)
{
    return false;
}

std::vector<std::shared_ptr<GameObject>> reflectFromGameObjects(
    const Ball& ball, const std::vector<Wall>& walls,
    const std::vector<IndestructibleBrick>& indestructibleBrick,
    std::vector<Brick>& bricks)
{
    return std::vector<std::shared_ptr<GameObject>>{};
}

double calcAngleFactor(double xBall, double xLeft, double xCenter,
                       double xRight)
{
    assert(xLeft < xCenter);
    assert(xCenter < xRight);

    xBall = std::clamp(xBall, xLeft, xRight);

    auto len = xCenter - xLeft;
    double factor = 0.0;
    if (xBall <= xCenter) {
        factor = (xCenter - xBall) / len;
    }
    else {
        factor = (xBall - xCenter) / len;
    }
    factor = std::clamp(factor, 0.0, 1.0);
    assert(factor >= 0.0 && factor <= 1.0);
    return factor;
}

types::Angle clampAngle(const types::Angle& angle)
{
    auto deltaX = 30.0_deg;
    auto deltaY = 15.0_deg;

    auto newAngle = angle;

    if (isBigger(angle.get(), 0.0_deg, deltaX)) {
        newAngle.set(0.0_deg + deltaX);
    }
    else if (isSmaller(angle.get(), 90.0_deg, deltaY)) {
        newAngle.set(90.0_deg - deltaY);
    }
    else if (isBigger(angle.get(), 90.0_deg, deltaY)) {
        newAngle.set(90.0_deg + deltaY);
    }
    else if (isSmaller(angle.get(), 180.0_deg, deltaX)) {
        newAngle.set(180.0_deg - deltaX);
    }
    else if (isBigger(angle.get(), 180.0_deg, deltaX)) {
        newAngle.set(180.0_deg + deltaX);
    }
    else if (isSmaller(angle.get(), 270.0_deg, deltaY)) {
        newAngle.set(270.0_deg - deltaY);
    }
    else if (isBigger(angle.get(), 270.0_deg, deltaY)) {
        newAngle.set(270.0_deg + deltaY);
    }
    else if (isSmaller(angle.get(), 360.0_deg, deltaX)) {
        newAngle.set(360.0_deg - deltaX);
    }

    return newAngle;
}

bool isSmaller(double angle, double targetAngle, double delta)
{
    return angle >= targetAngle - delta && angle < targetAngle;
}

bool isBigger(double angle, double targetAngle, double delta)
{
    return angle >= targetAngle && angle < targetAngle + delta;
}

} // namespace bricks::game_objects