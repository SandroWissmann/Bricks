#include "GameObject.h"

#include <stdexcept>
#include <string>

namespace bricks::game_objects {

using Point = types::Point;

GameObject::GameObject() : mTopLeft{Point{}}, mWidth{0.0}, mHeight{0.0}
{
}

GameObject::GameObject(Point topLeft, types::Width width, types::Height height)
    : mTopLeft{checkArgs(topLeft)}, mWidth{width()}, mHeight{height()}
{
}

GameObject::~GameObject() = default;

Point GameObject::topLeft() const
{
    return mTopLeft;
}

void GameObject::setTopLeft(Point topLeft)
{
    if (topLeft.x >= 0.0 && topLeft.y >= 0.0) {
        mTopLeft = topLeft;
    }
}

Point GameObject::bottomRight() const
{
    return Point{mTopLeft.x + mWidth, mTopLeft.y + mHeight};
}

double GameObject::width() const
{
    return mWidth;
}

double GameObject::height() const
{
    return mHeight;
}

Point GameObject::checkArgs(Point point)
{
    if(point.x < 0.0 || point.y < 0.0) {
        throw std::invalid_argument(
            "Point GameObject::checkArgs(Point point)\n"
        "Point must be >= 0\n"
        "Point x: " + std::to_string(point.x) + "\n"
        "Point y: " + std::to_string(point.y) + "\n");
    }
    return point;
}
} // namespace bricks::game_objects