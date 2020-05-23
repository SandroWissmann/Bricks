#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Point.h"

namespace bricks {

struct Width {
    double value;

    double operator()() const
    {
        return value;
    }
};

struct Height {
    double value;

    double operator()() const
    {
        return value;
    }
};

class GameObject {
public:
    GameObject(Point topLeft, Width width, Height height);

    virtual ~GameObject() = 0;

    GameObject(const GameObject &) = default;
    GameObject(GameObject &&) = default;
    GameObject &operator=(const GameObject &other) = default;
    GameObject &operator=(GameObject &&other) = default;

    Point topLeft() const;
    virtual void setTopLeft(Point topLeft);
    Point bottomRight() const;

    double width() const;
    double height() const;

private:
    Point mTopLeft;

    const double mWidth;
    const double mHeight;
};

} // namespace bricks

#endif