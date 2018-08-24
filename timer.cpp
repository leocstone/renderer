#include "timer.h"

void Timer::start()
{
    m_start = currentTime();
}

double Timer::msElapsed()
{
    return secondsElapsed() * 1000.0;
}

double Timer::secondsElapsed()
{
    duration<double> elapsed = duration_cast<duration<double>>(currentTime() - m_start);
    return elapsed.count();
}

timepoint Timer::currentTime()
{
    return high_resolution_clock::now();
}
