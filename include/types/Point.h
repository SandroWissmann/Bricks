#ifndef TYPES_POINT_H
#define TYPES_POINT_H

#include <iosfwd>

namespace bricks::types {

struct Point {
    double x{0.0};
    double y{0.0};
};

std::istream &operator>>(std::istream &is, Point &obj);

} // namespace bricks::types
#endif