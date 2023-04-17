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

    /**
     * @brief Constructeur de l'objet Timer
     * 
     */
    Timer();

    /**
     * @brief Initialise le timer
     * 
     */
    void init(/*void (*callback)(), */unsigned long delay_millis, int nb_rep);

    /**
     * @brief Demarre le timer
     * 
     */
    void start();

    /**
     * @brief Verifie si le timer est termine
     * 
     * @return true : si le timer est termine
     * @return false : si le timer n'est pas termine
     */
    bool update();

    /**
     * @brief Arrete le timer
     * 
     */
    void stop();
};

#endif
