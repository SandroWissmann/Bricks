#ifndef TYPES_MAXPOSITIONX_H
#define TYPES_MAXPOSITIONX_H

namespace bricks::types {

class MaxPositionX {
public:
    MaxPositionX() = default;
    MaxPositionX(double value);

    double operator()() const;

private:
    double mValue{0.0};
};

} // namespace bricks::types
#endif