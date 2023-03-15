/***
 * @author @LoganCadorette
 * @file ElectroCPU.cpp
 * @date 29 janvier 2023
***/

#include "ElectroCPU.h"


// Constructeur de la classe ElectroCPU
ElectroCPU::ElectroCPU(int pin_) : Electroaimant(pin_)
{
    pin = pin_;
    etat = false; // initialement desactive
    pinMode(pin_, OUTPUT);
    digitalWrite(pin_, LOW);
}


void ElectroCPU::activer()
{
    setEtat(true);
    digitalWrite(pin, HIGH);
}

void ElectroCPU::desactiver()
{
    setEtat(false);
    digitalWrite(pin, LOW);
}

bool ElectroCPU::getEtat()      
{
    return etat;
}

void ElectroCPU::setEtat(bool etat_)
{
    etat = etat_;
}

int ElectroCPU::getPin()
{
    return pin;
}
