#ifndef TYPES_MAXPOSITIONY_H
#define TYPES_MAXPOSITIONY_H

namespace bricks::types {

struct MaxPositionY {
    double operator()() const;

    double value;
};

} // namespace bricks::types
#endif