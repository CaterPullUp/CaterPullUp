/***
 * @author Étienne Germain
 * @file Corps.cpp
 * @date 17 janvier 2023
***/

#include "Corps.h"
        
//Corps::Corps(Moteur* _moteur, Electroaimant* _electroaimant)
//{
    //moteur = _moteur;
    //electroaimant = _electroaimant;
//}

Corps::Corps()
{
    //moteur = new Dynamixel();
    electroaimant = new ElectroCPU(12);
}

Corps::~Corps()
{
    delete moteur;
    delete electroaimant;
}

void Corps::init()
{
    
}

bool Corps::monter()
{

}

bool Corps::baisser()
{

}

void Corps::activerElectro()
{
    electroaimant->activer();
}

void Corps::desactiverElectro()
{
    electroaimant->desactiver();
}