#include "clock.h"
#include "texturemanager.h"
#include <sstream>
#include <iostream>



Clock::Clock()
{
}

void Clock::start(const int interval)
{
    mTimer.start();
    mTimer_id = SDL_AddTimer(interval * 1000, &Clock::updateTimeCallback, &mTimer);
//    std::cout << "MY TIMER HAS A BEAUTIFUL ADDRESS " << &mTimer << std::endl;
}

void Clock::stop()
{
    SDL_RemoveTimer(mTimer_id);
    mTimer.stop();
}

/*static*/ Uint32 Clock::updateTimeCallback(Uint32 interval, void* p)
{

//    std::cout << "IS THAT MY TIMER?  " << p << std::endl;
    SDL_Event event;
    Timer *myTimer = reinterpret_cast<Timer *>(p);
    std::stringstream timeText;
    timeText.str( "" );
    timeText << ( myTimer->getTicks() / 1000.f ) ;
    event.type = SDL_USEREVENT;
    event.user.code = myTimer->getTicks() / 1000;
    event.user.data1 = NULL; //current time
    event.user.data2 = NULL;

    SDL_PushEvent(&event);
    return(interval);
}
