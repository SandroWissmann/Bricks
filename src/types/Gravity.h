#ifndef TYPES_GRAVITY_H
#define TYPES_GRAVITY_H

namespace bricks::types {

class Gravity {
public:
    Gravity() = default;
    Gravity(double value);

    double operator()() const;
private:
    double mValue{0};
};

} // namespace bricks::types
#endif