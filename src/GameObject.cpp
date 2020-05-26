#include "GameObject.h"

#include <cassert>

namespace bricks {

using Point = types::Point;

GameObject::GameObject()
    :mTopLeft{Point{}}, mLength{0.0}, mWidth{0.0}
{
}

GameObject::GameObject(Point topLeft, types::Length length, types::Width width)
    : mTopLeft{topLeft}, mLength{length()}, mWidth{width()}
{
    assert(mTopLeft.x >= 0);
    assert(mTopLeft.y >= 0);

    assert(mLength > 0);
    assert(mWidth > 0);
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
    return Point{mTopLeft.x + mLength, mTopLeft.y + mWidth};
}

double GameObject::length() const
{
    return mLength;
}

double GameObject::width() const
{
    return mWidth;
}
} // namespace bricks