#ifndef TYPES_VELOCITY_H
#define TYPES_VELOCITY_H

namespace bricks::types {

struct Velocity {
    double operator()() const;

    double value;
};

}
#endif