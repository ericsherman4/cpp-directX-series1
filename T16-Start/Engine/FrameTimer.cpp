#include "FrameTimer.h"

using namespace std::chrono; //promote std::chrono to the scope of this cpp file.

FrameTimer::FrameTimer()
{
    last = steady_clock::now();
}

float FrameTimer::Mark()
{
    // see T-17 start for what this is doing. just a simplified version of that.
    const auto old = last;
    last = steady_clock::now();
    const duration<float> frameTime = last - old;
    return frameTime.count();
}