#ifndef POINT_H
#define POINT_H

#include <iosfwd>

namespace bricks {

struct Point {
    double x{0.0};
    double y{0.0};
};

std::istream& operator>>(std::istream& is, Point& obj);

} // namespace bricks
#endif