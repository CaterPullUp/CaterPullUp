/***
 * @author @etiger314
 * @file Moteur.cpp
 * @date 17 janvier 2023
***/

#include "Moteur.h"

Moteur::Moteur(int pint)
{

    pin = pint;
    //Mettre la vitesse a 0.
    vitesse = 0;
}

void Moteur::setVitesse(float v)
{
    //changer la vitesse
    vitesse = v;
}

float Moteur::getVitesse()
{
    return vitesse;
}

int Moteur::getPin()
{
    return pin;
}