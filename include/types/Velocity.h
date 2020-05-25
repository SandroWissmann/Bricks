#ifndef TYPES_VELOCITY_H
#define TYPES_VELOCITY_H

namespace bricks::types {

class Velocity {
public:
    Velocity() = default;
    Velocity(double value);

    double operator()() const;

private:
    double mValue{0};
};

} // namespace bricks::types
#endif