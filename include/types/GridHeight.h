#ifndef TYPES_GRIDHEIGHT_H
#define TYPES_GRIDHEIGHT_H

#include <iosfwd>

namespace bricks::types {

class GridHeight {
public:
    GridHeight() = default;
    explicit GridHeight(int value);

    int operator()() const;

private:
    int checkArgs(int value) const;

    int mValue{0};
};

std::istream& operator>>(std::istream& is, GridHeight& obj);

} // namespace bricks::types
#endif