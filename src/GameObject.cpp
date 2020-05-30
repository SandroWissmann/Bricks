#include "GameObject.h"

#include <cassert>

namespace bricks {

using Point = types::Point;

GameObject::GameObject() : mTopLeft{Point{}}, mWidth{0.0}, mHeight{0.0}
{
}

GameObject::GameObject(Point topLeft, types::Width width, types::Height height)
    : mTopLeft{topLeft}, mWidth{width()}, mHeight{height()}
{
    assert(mTopLeft.x >= 0);
    assert(mTopLeft.y >= 0);

    assert(mWidth > 0);
    assert(mHeight > 0);
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
} // namespace bricks