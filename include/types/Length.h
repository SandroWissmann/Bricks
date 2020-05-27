#ifndef TYPES_LENGTH_H
#define TYPES_LENGTH_H

#include <iosfwd>

namespace bricks::types {

class Length {
public:
    Length() = default;
    explicit Length(double value);

    double operator()() const;

private:
    double mValue{0.0};
};

std::istream& operator>>(std::istream& is, Length& obj);

} // namespace bricks::types
#endif