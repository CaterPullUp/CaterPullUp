/***
 * @author @MarieClaude1234
 * @file Caterpullup.cpp
 * @date 29 janvier 2023
***/

#include "Caterpullup.h"

Caterpullup::Caterpullup(int _mode)
{
    mode = _mode;
    etat = INIT;
}

Caterpullup::~Caterpullup()
{
    for(int i = 0; i < 3; i++)
        delete moteurs[i];
    
    for(int i = 0; i < 6; i++)
        delete electroaimants[i];

    for(int i = 0; i < 2; i++)
        delete bras[i];

    // delete corps;
    // delete i2c;
}

void Caterpullup::setMode(int _mode)
{
    mode = _mode;
}

int Caterpullup::getMode()
{
    return mode;
}

void Caterpullup::setEtat(int _etat)
{
    etat = _etat;
}

int Caterpullup::getEtat()
{
    return etat;
}

void Caterpullup::gererEtat()
{
    switch (etat)
    {
    case INIT:
        /* code */
        break;
    case ARRET_URGENCE:

        break;
    case RECEVOIR_COMMANDE:

        break;
    case EXECUTER_COMMANDE:

        break;
    case ACTIVER_ELECTRO:

        break;
    case ACTIVER_MOTEUR:

        break;
    default:
        break;
    }
}