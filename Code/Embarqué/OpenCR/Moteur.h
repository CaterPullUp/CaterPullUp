/***
 * @author @etiger314
 * @file Moteur.h
 * @date 17 janvier 2023
***/
#ifndef MOTEUR_H_
#define MOTEUR_H_

class Moteur
{
protected:

    float vitesse;
    int pin;

public:

    //Moteur(int pin);

    virtual float getVitesse() = 0;
    virtual int getPins() = 0;
    virtual void setVitesse(float v) = 0;
};

#endif