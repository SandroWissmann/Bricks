#ifndef TYPES_HITPOINTS_H
#define TYPES_HITPOINTS_H

namespace bricks::types {

struct Hitpoints {
    int operator()() const;

    int value;
};

} // namespace bricks::types
#endif