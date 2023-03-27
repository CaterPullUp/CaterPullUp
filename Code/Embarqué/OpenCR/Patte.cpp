/***
 * @author @MarieClaude1234
 * @file Patte.cpp
 * @date 29 janvier 2023
***/

#include "Patte.h"

Patte::Patte(Dynamixel2Arduino* dxl, int pin_electro, int id_moteur, float zero_position, int direction)
{
    moteur = new DXL_Patte(dxl, id_moteur, zero_position, direction);

    electroaimant = new ElectroCPU(pin_electro);
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
    //compléter le code

    etire = true;
    replie = false;
}

bool Patte::replier()
{
    //compléter le code

    etire = false;
    replie = true;
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
