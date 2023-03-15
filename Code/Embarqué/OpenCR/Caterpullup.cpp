/***
 * @author @MarieClaude1234 @JustinCoulombe6  @etiger314
 * @file Caterpullup.cpp
 * @date 29 janvier 2023
***/

#include "Caterpullup.h"

Caterpullup::Caterpullup(int _mode)
{
    corps = new Corps();
    patteAvant = new Patte();
    patteArriere = new Patte();

    int nbSequences = 0;
    mode = _mode;
    commande_GUI = INACTIF;
    etat_sequence = POSITION_DEPART;

    corps->monter();
    patteAvant->activerElectro();
    patteArriere->activerElectro();
}

Caterpullup::~Caterpullup()
{
    //for(int i = 0; i < 3; i++)
        //delete moteurs[i];
    
    //for(int i = 0; i < 6; i++)
        //delete electroaimants[i];

    delete corps;
    delete patteAvant;
    delete patteArriere;

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

void Caterpullup::set_etat_sequence(enum etat_sequence _etat)
{
    etat_sequence = _etat;
}

int Caterpullup::get_etat_sequence()
{
    return etat_sequence;
}

void Caterpullup::set_commande_GUI(enum commande_GUI _etat)
{
    commande_GUI = _etat;
}

int Caterpullup::get_commande_GUI()
{
    return commande_GUI;
}

void Caterpullup::gererGUI()
{
    switch (commande_GUI)
    {

    case INACTIF:

        break;

    case ELECTRO_AVANT:

        break;

    case ELECTRO_CORPS:

        break;

    case ELECTRO_ARRIERE:

        break;
    
    case PATTE_AVANT:

        break;

    case PIGNON_CREMAILLERE:

        break;

    case PATTE_ARRIERE:

        break;

    case SEQUENCE_COMPLETE:

        break;

    case ETAPE_PAR_ETAPE:

        break;

    case AVANCER_AUTO:

        break;

    case AVANCER_DISTANCE:
        //calculerNbSequences();

        break;

    case ARRET_URGENCE:

        break;
    
    default:
        break;
    }
}

void Caterpullup::gererEtat()
{
    if (mode == MODE_MANUEL)
    {

    }

    else if (mode == MODE_AUTO)
    {
        switch (etat_sequence)
        {
            case POSITION_DEPART:

                corps->desactiverElectro();
                if (corps->monter())
                {
                    etat_sequence = PREP_AVANCER_PATTE_AV;
                }
                break;

            case PREP_AVANCER_PATTE_AV:
                if (corps->baisser())
                {
                    corps->activerElectro();
                    etat_sequence = AVANCER_PATTE_AV;
                }
                break;

            case AVANCER_PATTE_AV:
                patteAvant->desactiverElectro();
                if (patteAvant->etirer())
                {
                    patteAvant->activerElectro();
                    etat_sequence = MONTER_CORPS;
                }
                break;

            case MONTER_CORPS:
                corps->desactiverElectro();
                if (corps->monter())
                {
                    etat_sequence = AVANCER_CORPS;
                }
                break;

            case AVANCER_CORPS:
                if (patteAvant->replier() && patteArriere->etirer())
                {
                    etat_sequence = PREP_AVANCER_PATTE_AR;
                }
                break;

            case PREP_AVANCER_PATTE_AR:
                if (corps->baisser())
                {
                    corps->activerElectro();
                    etat_sequence = AVANCER_PATTE_AR;
                }
                break;

            case AVANCER_PATTE_AR:
                patteArriere->desactiverElectro();
                if (patteArriere->replier())
                {
                    patteArriere->activerElectro();
                    if (nbSequences > 0)
                    {
                        nbSequences -=1;
                        etat_sequence = AVANCER_PATTE_AV;
                    }
                    else if(nbSequences == -1)
                    {
                        etat_sequence = AVANCER_PATTE_AV;
                    }
                    else
                    {
                        etat_sequence = POSITION_DEPART;
                    }
                }
                break;
        }
    }
}

void Caterpullup::calculerNbSequences(float distance)
{
    nbSequences = distance / DISTANCE_SEQUENCE;
}