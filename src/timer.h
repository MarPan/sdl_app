#ifndef TIMER_H
#define TIMER_H


class Timer
{
public:
    Timer();

    void start();
    void stop();
    void pause();
    void resume();

    unsigned int getTicks();

    bool isStarted();
    bool isPaused();

private:
    unsigned int mPausedTicks;
    unsigned int mStartTicks;

    bool mPaused;
    bool mStarted;

    void clearTimer();
};

#endif // TIMER_H
