#ifndef TYPES_MAXPOSITIONX_H
#define TYPES_MAXPOSITIONX_H

namespace bricks::types {

struct MaxPositionX {
    double operator()() const;

    double value;
};

} // namespace bricks::types
#endif