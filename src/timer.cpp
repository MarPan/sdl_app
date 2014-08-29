#include "timer.h"
#include <SDL.h>

Timer::Timer()
{
  clearTimer();
}

void Timer::start()
{
  mPaused = false;
  mStarted = true;

  mPausedTicks = 0;
  mStartTicks = SDL_GetTicks();
}

void Timer::stop()
{
  clearTimer();
}

void Timer::pause()
{
  if (mStarted && !mPaused) {
    mPausedTicks = SDL_GetTicks() - mStartTicks;
    mPaused = true;
    mStartTicks = 0;
  }
}

void Timer::resume()
{
  if (mPaused && mStarted) {
    mStartTicks = SDL_GetTicks() - mPausedTicks;
    mPausedTicks = 0;
    mPaused = false;
  }
}

//in case timer is stopped we return time 0;
unsigned int Timer::getTicks()
{
  unsigned int time = 0;
  if (mStarted) {
    if (mPaused) {
      time = mPausedTicks;
    } else {
      time = SDL_GetTicks() - mStartTicks;
    }
  }

  return time;
}

bool Timer::isPaused()
{
  return mPaused;
}


bool Timer::isStarted()
{
  return mStarted;
}

void Timer::clearTimer()
{
  mPaused = false;
  mStarted = false;

  mPausedTicks = 0;
  mStartTicks = 0;
}
