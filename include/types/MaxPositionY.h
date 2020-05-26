#ifndef TYPES_MAXPOSITIONY_H
#define TYPES_MAXPOSITIONY_H

namespace bricks::types {

class MaxPositionY {
public:
    MaxPositionY() = default;
    explicit MaxPositionY(double value);

    double operator()() const;

private:
    double mValue{0.0};
};

} // namespace bricks::types
#endif