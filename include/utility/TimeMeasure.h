#ifndef UTILITY_TIME_H
#define UTILITY_TIME_H

#include <chrono>

namespace bricks::utility {
std::chrono::time_point<std::chrono::high_resolution_clock> getCurrentTime();

double getElapsedTime(
    const std::chrono::time_point<std::chrono::high_resolution_clock>& first,
    const std::chrono::time_point<std::chrono::high_resolution_clock>& last);

void wait(const std::chrono::milliseconds& milliseconds);
} // namespace bricks::utility
#endif