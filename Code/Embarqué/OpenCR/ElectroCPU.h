/***
 * @author @LoganCadorette
 * @file ElectroCPU.h
 * @date 29 janvier 2023
***/


#ifndef ELECTROCPU_H
#define ELECTROCPU_H
#include <Arduino.h>
#include "Electroaimant.h"

class ElectroCPU : public Electroaimant
{
private:


public:

    // Constructeur de la classe ElectroCPU qui appelle le constructeur de la classe Electroaimant
    ElectroCPU(int pin_);

    // Fonctions virtuelles de la classe Electroaimant
    virtual void activer();
    virtual void desactiver();
    virtual bool getEtat();
    virtual int getPin();
    virtual void setEtat(bool etat_);
};

#endif
