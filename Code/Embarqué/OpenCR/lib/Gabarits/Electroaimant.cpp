/***
 * @author @etiger314
 * @file Electroaimant.cpp
 * @date 17 janvier 2023
***/

#include "Electroaimant.h"

Electroaimant::Electroaimant(int pint)
{

    pin = pint;
    //pinMode(pin, OUTPUT);
    etat = false;
}

void Electroaimant::activer()
{
    //digitalWrite(pin, HIGH);
    etat = true;
}

void Electroaimant::desactiver()
{
    //digitalWrite(pin, LOW);
    etat = false;
}

bool Electroaimant::getEtat()
{
    return etat;
}

int Electroaimant::getPin()
{
    return pin;
}