#ifndef TIMER_H_
#define TIMER_H_

#include <Arduino.h>

#define INFINITE_REPETITION -1

class Timer
{
private:
    void (*callback_)();
    unsigned long delay_;
    unsigned long deadline_;
    bool enable_;
    int nb_rep_;
    int remaining_rep_;

public:
    Timer();
    void init(/*void (*callback)(), */unsigned long delay_millis, int nb_rep);
    void start();
    bool update();
    void stop();
};

#endif
