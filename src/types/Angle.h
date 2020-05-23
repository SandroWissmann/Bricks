#ifndef TYPES_ANGLE_H
#define TYPES_ANGLE_H

namespace bricks::types {

enum class Quadrant { I, II, III, IV };

class Angle {
public:
    Angle(long double angle);

    long double angle() const;
    void setAngle(long double angle);

    long double quadrantAngle() const;
    void setQuadrantAngle(long double quadrantAngle);

    Quadrant quadrant() const;
    void setQuadrant(Quadrant quadrant);

    void mirrorHorizontal();
    void mirrorVertical();

private:
    Quadrant mQuadrant;
    long double mQuadrantAngle;
};

namespace impl {

long double mirrorQuadrantAngle(long double angle);

Quadrant calcQuadrant(long double angle);

bool isInQuadrantI(long double angle);
bool isInQuadrantII(long double angle);
bool isInQuadrantIII(long double angle);
bool isInQuadrantIV(long double angle);

long double angleToQuadrantAngle(long double angle, Quadrant quadrant);

long double quadrantAngleToAngle(long double quadrantAngle, Quadrant quadrant);

long double calcAngleIfOver360(long double angle);

} // namespace impl
} // namespace bricks

#endif