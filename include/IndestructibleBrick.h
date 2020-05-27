#ifndef INDESTRUCTIBLEBRICK_H
#define INDESTRUCTIBLEBRICK_H

#include "GameObject.h"

namespace bricks {

class IndestructibleBrick : public GameObject {
public:
    using GameObject::GameObject;
    ~IndestructibleBrick() override = default;

    IndestructibleBrick(const IndestructibleBrick&) = default;
    IndestructibleBrick(IndestructibleBrick&&) = default;
    IndestructibleBrick& operator=(const IndestructibleBrick& other) = default;
    IndestructibleBrick& operator=(IndestructibleBrick&& other) = default;
};
} // namespace bricks

#endif