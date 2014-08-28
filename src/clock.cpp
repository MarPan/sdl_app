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
}

void Clock::stop()
{
    SDL_RemoveTimer(mTimer_id);
    mTimer.stop();
}

//funkcja wołana co sekundę, ładuje czcionkę z czasem, a następnie ją rysuje\
//zamiast rysowania może lepiej zwracać to jakoś może wysyłając event? i dopiero odbierający by rysował
///*static*/ Uint32 Clock::setTime(Uint32 interval, void* p)
//{
//    std::stringstream timeText; //it could be passed as parameter, same with textColor?
//    Timer *myTimer = reinterpret_cast<Timer *>(p);
//    //Set text to be rendered
//    timeText.str( "" );
//    timeText << "Seconds since start time " << ( myTimer->getTicks() / 1000.f ) ;
//    SDL_Color textColor = { 0, 0, 255 };
//    //Render text
////    if(!theTextureManager.loadTextWithFont( "Action-Man/Action_Man.ttf", "action_man.ttf",
////                                            timeText.str().c_str(), textColor, 56))
////    {
////        printf( "Unable to render time texture!\n" );
////    }
////    delete myTimer;
////    myTimer = NULL;
////    theTextureManager.draw("action_man.ttf", 90, 200, theTextureManager.getSize("action_man.ttf").first, theTextureManager.getSize("action_man.ttf").second);
//    std::cout<< "inside setTime " << ( myTimer->getTicks() / 1000.f );
//    return interval;
//}

/*static*/ Uint32 Clock::updateTimeCallback(Uint32 interval, void* p)
{
    SDL_Event event;

    Timer *myTimer = reinterpret_cast<Timer *>(p);
    std::stringstream timeText;
    timeText.str( "" );
    timeText << ( myTimer->getTicks() / 1000.f ) ;
    myTimer = NULL;

    event.type = SDL_USEREVENT;
    event.user.code = 0;
    event.user.data1 = (void *)timeText.str().c_str(); //current time
    event.user.data2 = NULL;

    SDL_PushEvent(&event);
    return(interval);
}
