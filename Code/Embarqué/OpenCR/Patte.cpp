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
    //moteur = new Dynamixel();
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

}

bool Patte::replier()
{

}

void Patte::activerElectro()
{
    electroaimant->activer();
}

void Patte::desactiverElectro()
{
    electroaimant->desactiver();
}