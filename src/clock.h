#ifndef CLOCK_H
#define CLOCK_H

#include "multiplatformSDL.h"
#include "timer.h"



//counts time from start to stop
class Clock
{
public:
    Clock();
    void clearTime();
    void start(const int interval);
    void stop();
    Timer mTimer;

private:
    SDL_TimerID mTimer_id;
    int mInterval;
    //static Uint32 setTime(Uint32 seconds, void* param);
    static Uint32 updateTimeCallback(Uint32 interval, void* p);
};


#endif // CLOCK_H
