#ifndef TIMER_H
#define TIMER_H
#include <chrono>

using namespace std::chrono;

typedef high_resolution_clock::time_point timepoint;

/*

Timer

Simple timer class that uses std::high_resolution_clock to record time

*/
class Timer
{
public:

    Timer() {}
    ~Timer() {}
    void start();
    double secondsElapsed();
    double msElapsed();
    static inline timepoint currentTime();

private:

    timepoint m_start;
};

#endif // TIMER_H
