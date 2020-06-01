#include "TimeMeasure.h"

#include <thread>

namespace bricks::utility {
std::chrono::time_point<std::chrono::high_resolution_clock> getCurrentTime()
{
    return std::chrono::high_resolution_clock::now();
}

double getElapsedTime(
    const std::chrono::time_point<std::chrono::high_resolution_clock>& first,
    const std::chrono::time_point<std::chrono::high_resolution_clock>& last)
{
    return static_cast<int>(
        std::chrono::duration<double, std::milli>(last - first).count());
}

void wait(const std::chrono::milliseconds& milliseconds)
{
    std::this_thread::sleep_for(milliseconds);
}
} // namespace bricks::utility