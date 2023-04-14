/***
 * @author @LoganCadorette
 * @file ElectroCPU.h
 * @date 29 janvier 2023
***/

#ifndef ELECTROCPU_H
#define ELECTROCPU_H

#include "Arduino_function.h"

#include "Electroaimant.h"

class ElectroCPU : public Electroaimant
{
private:
    char* name;
public:

    // Constructeur de la classe ElectroCPU qui appelle le constructeur de la classe Electroaimant
    ElectroCPU(int pin_);

    void activer();
    void desactiver();
    bool getEtat();
    int getPins();
    void setEtat(bool etat_);
};

#endif
