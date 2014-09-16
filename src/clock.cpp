#include "clock.h"

Clock::Clock()
{
}

void Clock::start(const int interval)
{
    mTimer.start();
    mTimer_id = SDL_AddTimer(interval * 1000, &Clock::updateTimeCallback, &mTimer);
}

void Clock::stop()
{
    SDL_RemoveTimer(mTimer_id);
    mTimer.stop();
}

/*static*/ Uint32 Clock::updateTimeCallback(Uint32 interval, void* p)
{
    SDL_Event event;
    event.type = SDL_USEREVENT;

    Timer *myTimer = reinterpret_cast<Timer *>(p);
    event.user.code = myTimer->getTicks() / 1000;

    SDL_PushEvent(&event);
    return(interval);
}
