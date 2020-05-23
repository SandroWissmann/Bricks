#ifndef TYPES_GRAVITY_H
#define TYPES_GRAVITY_H

namespace bricks::types {

struct Gravity {
    double operator()() const;

    double value;
};

} // namespace bricks::types
#endif