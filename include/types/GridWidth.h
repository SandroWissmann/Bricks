#ifndef TYPES_GRIDWIDTH_H
#define TYPES_GRIDWIDTH_H

#include <iosfwd>

namespace bricks::types {

class GridWidth {
public:
    GridWidth() = default;
    explicit GridWidth(int value);

    int operator()() const;

private:
    int mValue{0};
};

std::istream &operator>>(std::istream &is, GridWidth &obj);

} // namespace bricks::types
#endif