#ifndef WALL_H
#define WALL_H

#include "GameObject.h"

namespace bricks {

class Wall : public GameObject {
public:
    using GameObject::GameObject;
    ~Wall() override = default;

    Wall(const Wall&) = default;
    Wall(Wall&&) = default;
    Wall& operator=(const Wall& other) = default;
    Wall& operator=(Wall&& other) = default;
};
} // namespace bricks
#endif