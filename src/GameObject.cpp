#include "GameObject.h"

#include "OperatorDegree.h"

namespace bricks {

	GameObject::GameObject(Point topLeft,
		double maxPositioX, double maxPositionY,
		double width, double height,
        double velocity, long double angle)
		:mTopLeft{ topLeft },
		mMaxPositionX(maxPositioX),
		mMaxPositionY(maxPositionY),
		mWidth{ width },
		mHeight{ height },
		mVelocity{ velocity },
		mQuadrant{ calcQuadrant(angle) },
		mQuadrantAngle{ angleToQuadrantAngle(angle, mQuadrant) }
	{
	}

	GameObject::~GameObject() = default;

	Point GameObject::topLeft() const
	{
		return mTopLeft;
	}

	void GameObject::setTopLeft(Point topLeft)
	{
		mTopLeft = topLeft;
	}

	Point GameObject::bottomRight() const
	{
		return Point{ mTopLeft.x + mWidth , mTopLeft.y + mHeight };
	}

	double GameObject::velocity() const
	{
		return mVelocity;
	}

	void GameObject::setVelocity(double velocity)
	{
		mVelocity = velocity;
	}

    long double GameObject::angle() const
	{
		return qudrantAngleToAngle(mQuadrantAngle, mQuadrant);
	}

    void GameObject::setAngle(long double angle)
	{
        angle = calcAngleIfOver360(angle);
		mQuadrant = calcQuadrant(angle);
		mQuadrantAngle = angleToQuadrantAngle(angle, mQuadrant);
	}

    long double GameObject::quadrantAngle() const
	{
		return mQuadrantAngle;
	}

    void GameObject::setQuadrantAngle(long double quadrantAngle)
    {
        if(quadrantAngle > 90.0_deg) {
            setAngle(quadrantAngle);
        }
        else{
            mQuadrantAngle = quadrantAngle;
        }
    }

	Quadrant GameObject::quadrant() const
	{
		return mQuadrant;
	}

    void GameObject::setQuadrant(Quadrant quadrant)
    {
        mQuadrant = quadrant;
    }

	double GameObject::width() const
	{
		return mWidth;
	}

	double GameObject::height() const
	{
		return mHeight;
	}

    double GameObject::maxPositionX() const
    {
        return mMaxPositionX;
    }

    double GameObject::maxPositionY() const
    {
        return mMaxPositionY;
    }

    bool isInQuadrantI(long double angle)
    {
        return angle >= 0.0_deg && angle <= 90.0_deg;
    }

    bool isInQuadrantII(long double angle)
    {
        return angle > 90.0_deg && angle <= 180.0_deg;
    }

    bool isInQuadrantIII(long double angle)
    {
        return angle > 180.0_deg && angle <= 270.0_deg;
    }

    bool isInQuadrantIV(long double angle)
    {
        return angle > 270.0_deg && angle <= 360.0_deg;
    }

    Quadrant calcQuadrant(long double angle)
    {
        if (isInQuadrantI(angle)) {
            return Quadrant::I;
        }
        if (isInQuadrantII(angle)) {
            return Quadrant::II;
        }
        if (isInQuadrantIII(angle)) {
            return Quadrant::III;
        }
        return Quadrant::IV;
    }

    long double angleToQuadrantAngle(long double angle, Quadrant quadrant)
    {
        return angle - 90.0_deg * static_cast<int>(quadrant);
    }

    long double qudrantAngleToAngle(long double quadrantAngle, Quadrant quadrant)
    {
        return quadrantAngle + 90.0_deg * static_cast<int>(quadrant);
    }

    long double calcAngleIfOver360(long double angle)
    {
        while (angle > 360.0_deg) {
            angle -= 360.0_deg;
        }
        return angle;
    }

}  // namespace bricks