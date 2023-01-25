/***
 * @author @etiger314
 * @file Moteur.h
 * @date 17 janvier 2023
***/
#ifndef MOTEUR_H_
#define MOTEUR_H_

class Moteur
{
private:

    float vitesse;
    int pin;

public:

    Moteur(int pint);

    float getVitesse();
    int getPin();
    void setVitesse(float v);
};

#endif