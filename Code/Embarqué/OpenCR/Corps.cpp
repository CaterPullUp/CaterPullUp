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
    //moteur = new DXL_Corps();
    electroaimant = new ElectroCPU(12);

    init();
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
    //completer le code

    monte = true;
    baisse = false;
}

bool Corps::baisser()
{
    //compléter le code

    monte = false;
    baisse = true;
}

void Corps::activerElectro()
{
    electroaimant->activer();
}

void Corps::desactiverElectro()
{
    electroaimant->desactiver();
}

bool Corps::estMonte()
{
    return monte;
}

bool Corps::estBaisse()
{
    return baisse;
}

bool Corps::electroActive()
{
    return electroaimant->getEtat();
}