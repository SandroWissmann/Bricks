#ifndef TYPES_WIDTH_H
#define TYPES_WIDTH_H

#include <iosfwd>

namespace bricks::types {

class Width {
public:
    Width() = default;
    explicit Width(double value);

    double operator()() const;

private:
    static double checkArgs(double value) ;

    double mValue{0.0};
};

std::istream& operator>>(std::istream& is, Width& obj);

} // namespace bricks::types
#endif