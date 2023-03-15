/***
 * @author @LoganCadorette
 * @file ElectroCPU.h
 * @date 29 janvier 2023
***/

#ifndef ELECTROCPU_H
#define ELECTROCPU_H

#if defined(ARDUINO_OpenCR)
#include <Arduino.h>
#else
#define digitalWrite(A,B)
#define digitalRead(A)
#define pinMode(A,B)
#endif

#include "Electroaimant.h"

class ElectroCPU : public Electroaimant
{
private:

public:

    // Constructeur de la classe ElectroCPU qui appelle le constructeur de la classe Electroaimant
    ElectroCPU(int pin_);

    // Fonctions virtuelles de la classe Electroaimant
    void activer();
    void desactiver();
    bool getEtat();
    int getPin();
    void setEtat(bool etat_);
};

#endif
