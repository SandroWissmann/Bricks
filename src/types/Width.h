#ifndef TYPES_WIDTH_H
#define TYPES_WIDTH_H

namespace bricks::types {

struct Width {
    double operator()() const;

    double value;
};

}
#endif