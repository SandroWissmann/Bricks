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
    static int checkArgs(int value) ;

    int mValue{0};
};

std::istream& operator>>(std::istream& is, GridHeight& obj);

} // namespace bricks::types
#endif