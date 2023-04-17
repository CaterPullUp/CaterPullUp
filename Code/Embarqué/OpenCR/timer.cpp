/***
 * @author @trudelle200902
 * @file timer.cpp
 * @date 12 avril 2023
***/

#include "timer.h"

/**
 * @brief Construit un nouveau Timer et met à initialise toute les valeurs de départ
 * 
 */
Timer::Timer(){
    delay_ = 0;
    deadline_ = 0;
    enable_ = false;
    nb_rep_ = INFINITE_REPETITION;
    remaining_rep_ = INFINITE_REPETITION;
    callback_ = NULL;
}

/**
 * @brief Initialise le Timer avec une fonction de retour, un delai et un bombre de repetition
 * 
 * @param callback une fonction void sans argument qui sera appelée à chaque fois que le delay s'écoule
 * @param delay_millis unsigned long qui représente le temps en milliseconde tu timer
 * @param nb_rep nombre de fois que le délais s'exécute -1 pour répeter à l'infini
 */
void Timer::init(unsigned long delay_millis, int nb_rep){
    this->delay_ = delay_millis;
    this->nb_rep_ = nb_rep;
}

/**
 * @brief démarre le timer et initialise le temps de départ et la temps d'arrêt
 * 
 */
void Timer::start(){
    if (!enable_){
        enable_ = true;
        deadline_ = millis() + delay_;
        remaining_rep_ = nb_rep_;
    }
}

/**
 * @brief doit être appeler à chaque repetition permet de vérifier si le temps est écouler
 * 
 */
bool Timer::update(){
    if(enable_ && millis() > deadline_){
        if(nb_rep_ != -1){
            remaining_rep_--;
        }

        if(remaining_rep_ == 0){
                stop();
        }
        else{
            deadline_ = millis() + delay_;
        }
        return true;
    }
    return false;
}

void Timer::stop(){
    enable_ = false;
}