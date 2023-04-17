/***
 * @author @MarieClaude1234
 * @file Patte.cpp
 * @date 29 janvier 2023
***/

#include "Patte.h"

Patte::Patte(Dynamixel2Arduino* dxl, int pin_electro, int id_moteur, float zero_position, int direction)
{
    moteur = new DXL_Patte(dxl, id_moteur, zero_position, direction);
    direction_ = direction;
    electroaimant = new ElectroCPU(pin_electro);
    replie = false;
    etire = false;
}

Patte::~Patte()
{
    delete moteur;
    delete electroaimant;
}

void Patte::init()
{
    desactiverElectro();
    ((DXL_Patte*)moteur)->positionInitiale();

    replie = true;
    etire = false;
}

bool Patte::etirer()
{
    if(etire)
    {
        return true;
    }

    if(replie)
    { 
        DEBUG_SERIAL.print("Patte ");
        DEBUG_SERIAL.print(((DXL_Patte*)moteur)->getID());
        DEBUG_SERIAL.println(" etirer");
        ((DXL_Patte *)moteur)->incrementGoalAngle(direction_ == 1 ? EXTEND_MOVEMENT_ANGLE : RETRACT_MOVEMENT_ANGLE);
        ((DXL_Patte *)moteur)->setVitesse();

        replie = false;

        return false;
    }
    
    if(estArrete())
    {
        DEBUG_SERIAL.print("Patte ");
        DEBUG_SERIAL.print(((DXL_Patte*)moteur)->getID());
        DEBUG_SERIAL.println(" terminer");   
        etire = true;
        return true;
    }
    return false;
}

bool Patte::replier()
{
    if(replie)
    {
        return true;
    }

    if(etire)
    {
        DEBUG_SERIAL.print("Patte ");
        DEBUG_SERIAL.print(((DXL_Patte*)moteur)->getID());
        DEBUG_SERIAL.println(" replier");
        ((DXL_Patte *)moteur)->incrementGoalAngle(direction_ == 1 ? RETRACT_MOVEMENT_ANGLE : EXTEND_MOVEMENT_ANGLE);
        ((DXL_Patte *)moteur)->setVitesse();

        etire = false;

        return false;
    }
    
    if(estArrete())
    {
        DEBUG_SERIAL.print("Patte ");
        DEBUG_SERIAL.print(((DXL_Patte*)moteur)->getID());
        DEBUG_SERIAL.println(" terminer");
        replie = true;
        return true;
    }

    return false;
}

void Patte::activerElectro()
{
    electroaimant->activer();
}

void Patte::desactiverElectro()
{
    electroaimant->desactiver();
}

bool Patte::estEtire()
{
    return etire;
}

bool Patte::estReplie()
{
    return replie;
}

bool Patte::electroActive()
{
    return electroaimant->getEtat();
}

bool Patte::estArrete()
{
    return ((DXL_Patte *)moteur)->is_movement_finished();
}
