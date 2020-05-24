#ifndef TYPES_HITPOINTS_H
#define TYPES_HITPOINTS_H

#include <iosfwd>

namespace bricks::types {

class Hitpoints {
public:
    Hitpoints() = default;
    Hitpoints(int value);

    int operator()() const;

private:
    int mValue{0};
};

std::istream &operator>>(std::istream &is, Hitpoints &obj);

} // namespace bricks::types
#endif