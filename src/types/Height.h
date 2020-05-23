#ifndef TYPES_HEIGHT_H
#define TYPES_HEIGHT_H

namespace bricks::types {

struct Height {
    double operator()() const;

    double value;
};

} // namespace bricks::types
#endif