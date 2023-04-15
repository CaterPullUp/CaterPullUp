/***
 * @author @LoganCadorette
 * @file ElectroCPU.cpp
 * @date 29 janvier 2023
***/

#include "ElectroCPU.h"
//#include "Caterpullup.h"

// Constructeur de la classe ElectroCPU
ElectroCPU::ElectroCPU(int pin_) : Electroaimant(pin_)
{
    pin = pin_;
    etat = false; // initialement desactive
    pinMode(pin_, OUTPUT);
    digitalWrite(pin_, LOW);
    /*switch(pin){
        case PIN_ELECTRO_ARRIERE:
            name = "arriere";
            break;
        case PIN_ELECTRO_AVANT:
            name = "avant";
            break;
        case PIN_ELECTRO_CORPS:
            name = "corps";
            break;
    }*/
}

void ElectroCPU::activer()
{
    /*if(getEtat() == false){
        DEBUG_SERIAL.print("Activer electro ");
        DEBUG_SERIAL.println(name);
    }*/
    setEtat(true);
    digitalWrite(pin, HIGH);
}

void ElectroCPU::desactiver()
{
    /*if(getEtat() == true){
        DEBUG_SERIAL.print("Desactiver electro ");
        DEBUG_SERIAL.println(name);
    }*/
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

int ElectroCPU::getPins()
{
    return pin;
}
