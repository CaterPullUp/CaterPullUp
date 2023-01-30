/***
 * @author @MarieClaude1234
 * @file Bras.cpp
 * @date 29 janvier 2023
***/

#include "Bras.h"
        
Bras::Bras(Moteur* _moteur, Electroaimant* _electroaimants[])
{
    moteur = _moteur;
    electroaimant1 = _electroaimants[0];
    electroaimant2 = _electroaimants[1];
}

Bras::~Bras()
{

}

void Bras::init()
{
    
}

void Bras::etirer()
{

}

void Bras::replier()
{

}