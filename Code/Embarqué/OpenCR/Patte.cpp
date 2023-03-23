/***
 * @author @MarieClaude1234
 * @file Patte.cpp
 * @date 29 janvier 2023
***/

#include "Patte.h"
        
//Patte::Patte(Moteur* _moteur, Electroaimant* _electroaimant)
//{
    //moteur = _moteur;
    //electroaimant = _electroaimant;
//}

Patte::Patte()
{
    //moteur = new DXL_Patte();
    electroaimant = new ElectroCPU(11);
}

Patte::~Patte()
{
    delete moteur;
    delete electroaimant;
}

void Patte::init()
{
    
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
