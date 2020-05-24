#ifndef TYPES_HEIGHT_H
#define TYPES_HEIGHT_H

#include <iosfwd>

namespace bricks::types {

class Height {
public:
    Height() = default;
    Height(double value);

    double operator()() const;

private:
    double mValue{0.0};
};

std::istream &operator>>(std::istream &is, Height &obj);

} // namespace bricks::types
#endif