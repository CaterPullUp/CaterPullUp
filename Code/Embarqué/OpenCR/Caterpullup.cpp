/***
 * @author @MarieClaude1234
 * @file Caterpullup.cpp
 * @date 29 janvier 2023
***/

#include "Caterpullup.h"

Caterpullup::Caterpullup(int _mode)
{
    Dynamixel2Arduino* dxl = connectDXL();
    patteAvant = new Patte(dxl, 12, 1, 110, 1);
    patteArriere = new Patte(dxl, 13, 2, 305, -1);
    corps = new Corps(dxl, 14, 3);

    nbSequences = 0;
    mode = _mode;
    commande_GUI = INACTIF;
    etat_sequence = PREP_AVANCER_PATTE_AV;
    first = true;
    firstInactif = true;

    init();
}

Caterpullup::~Caterpullup()
{
    delete patteAvant;
    delete patteArriere;
    delete corps;

    // delete corps;
    // delete i2c;
}

void Caterpullup::init()
{

}

void Caterpullup::setMode(int _mode)
{
    mode = _mode;
}

int Caterpullup::getMode()
{
    return mode;
}

void Caterpullup::set_etat_sequence(enum Sequence _etat)
{
    etat = _etat;
}

int Caterpullup::getEtat()
{
    return etat;
}

void Caterpullup::set_commande_GUI(enum Commande _etat)
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

void Caterpullup::gererEtat()
{
    if(first)
    {
        DEBUG_SERIAL.println("first");
        patteAvant->init();
        patteArriere->init();
        corps->init();

        if(moteursArretes)
        {
            DEBUG_SERIAL.println("moteurs arretes");
            patteAvant->activerElectro();
            patteArriere->activerElectro();
            first = false;
        }
    }

    else if (mode == MODE_MANUEL)
    {
        gererGUI();
    }

    else if (mode == MODE_AUTO)
    {
        switch (etat_sequence)
        {
            case INCONNU:

                trouverEtatSequence();

                break;

            case PREP_AVANCER_PATTE_AV:
                if (corps->baisser())
                {
                    corps->activerElectro();
                    etat_sequence = AVANCER_PATTE_AVANT;
                }

                if(nbSequences == -2) //etape par etape
                {
                    mode = MODE_MANUEL;
                    commande_GUI = INACTIF;
                }

                break;

            case AVANCER_PATTE_AVANT:

                patteAvant->desactiverElectro();

                if (patteAvant->etirer())
                {
                    patteAvant->activerElectro();
                    etat_sequence = MONTER_CORPS;
                }

                if(nbSequences == -2) //etape par etape
                {
                    mode = MODE_MANUEL;
                    commande_GUI = INACTIF;
                }

                break;

            case MONTER_CORPS:

                corps->desactiverElectro();

                if (corps->monter())
                {
                    etat_sequence = AVANCER_CORPS;
                }

                if(nbSequences == -2) //etape par etape
                {
                    mode = MODE_MANUEL;
                    commande_GUI = INACTIF;
                }

                break;

            case AVANCER_CORPS:

                if (patteAvant->replier() && patteArriere->etirer())
                {
                    etat_sequence = PREP_AVANCER_PATTE_ARR;
                }

                if(nbSequences == -2) //etape par etape
                {
                    mode = MODE_MANUEL;
                    commande_GUI = INACTIF;
                }

                break;

            case PREP_AVANCER_PATTE_ARR:

                if (corps->baisser())
                {
                    corps->activerElectro();
                    etat_sequence = AVANCER_PATTE_ARRIERE;
                }

                if(nbSequences == -2) //etape par etape
                {
                    mode = MODE_MANUEL;
                    commande_GUI = INACTIF;
                }

                break;

            case AVANCER_PATTE_ARRIERE:

                patteArriere->desactiverElectro();

                if (patteArriere->replier())
                {
                    patteArriere->activerElectro();

                    if(nbSequences == -2) //etape par etape
                    {
                        etat_sequence = RETOUR_DEPART;
                        mode = MODE_MANUEL;
                        commande_GUI = INACTIF;
                    }

                    else if (nbSequences > 0)
                    {
                        nbSequences -=1;
                        etat_sequence = AVANCER_PATTE_AVANT;
                    }

                    else if(nbSequences == -1)
                    {
                        etat_sequence = AVANCER_PATTE_AVANT;
                    }

                    else
                    {
                        etat_sequence = RETOUR_DEPART;
                    }
                }

                break;

            case RETOUR_DEPART:

                corps->desactiverElectro();

                if (corps->monter())
                {
                    etat_sequence = PREP_AVANCER_PATTE_AV;
                    mode = MODE_MANUEL;
                    commande_GUI = INACTIF;
                }

                break;

            case REDRESSER:

                patteArriere->desactiverElectro();

                if(patteArriere->replier())
                {
                    patteArriere->activerElectro();
                    etat_sequence = MONTER_CORPS;
                }

                if(nbSequences == -2) //etape par etape
                {
                    mode = MODE_MANUEL;
                    commande_GUI = INACTIF;
                }

                break;

            default:
    
                break;
        }

        if (commande_GUI = ARRET_URGENCE)
        {
            mode = MODE_MANUEL;
            commande_GUI = INACTIF;
        }
    }
}

void Caterpullup::gererMoteurs()
{
    moteursArretes = patteAvant->estArrete() && patteArriere->estArrete();// && corps->estArrete();
}

void Caterpullup::calculerNbSequences(float distance)
{
    nbSequences = distance / DISTANCE_SEQUENCE;
}

void Caterpullup::envoyerMessage()
{
    //dire au GUI que le robot est prêt à recevoir une commande

    firstInactif = false;
}

void Caterpullup::recevoirMessage()
{
    //commande_GUI = //la commande associée au bouton appuyé;
    firstInactif = true;
}

void Caterpullup::trouverEtatSequence()
{
    if(!patteArriere->electroActive())
    {
        if(patteArriere->estReplie())
        {
            if(patteAvant->estReplie())
            {
                patteArriere->activerElectro();
                etat_sequence = AVANCER_PATTE_AVANT;
            }

            else if(patteAvant->estEtire())
            {
                patteArriere->activerElectro();
                etat_sequence = MONTER_CORPS;
            }
        }

        else if(patteArriere->estEtire())
        {
            if(patteAvant->estReplie())
            {
                etat_sequence = AVANCER_PATTE_ARRIERE;
            }

            else if(patteAvant->estEtire())
            {
                etat_sequence = REDRESSER;
            }
        }
    }

    else if(!patteAvant->electroActive())
    {
        if(patteArriere->estReplie())
        {
            if(patteAvant->estReplie())
            {
                etat_sequence = AVANCER_PATTE_AVANT;
            }

            else if(patteAvant->estEtire())
            {
                patteAvant->activerElectro();
                etat_sequence = MONTER_CORPS;
            }
        }

        else if(patteArriere->estEtire())
        {
            if(patteAvant->estReplie())
            {
                patteAvant->activerElectro();
                etat_sequence = AVANCER_PATTE_ARRIERE;
            }

            else if(patteAvant->estEtire())
            {
                patteAvant->activerElectro();
                etat_sequence = REDRESSER;
            }
        }
    }

    else if(corps->electroActive())
    {
        if(patteArriere->estReplie())
        {
            if(patteAvant->estReplie())
            {
                etat_sequence = AVANCER_PATTE_AVANT;
            }

            else if(patteAvant->estEtire())
            {
                etat_sequence = MONTER_CORPS;
            }
        }

        else if(patteArriere->estEtire())
        {
            if(patteAvant->estReplie())
            {
                etat_sequence = AVANCER_PATTE_ARRIERE;
            }

            else if(patteAvant->estEtire())
            {
                etat_sequence = REDRESSER;
            }
        }
    }

    else if(corps->estMonte())
    {
        if(patteArriere->estReplie())
        {
            if(patteAvant->estReplie())
            {
                etat_sequence = PREP_AVANCER_PATTE_AV;
            }

            else if(patteAvant->estEtire())
            {
                etat_sequence = AVANCER_CORPS;
            }
        }

        else if(patteArriere->estEtire())
        {
            if(patteAvant->estReplie())
            {
                etat_sequence = PREP_AVANCER_PATTE_ARR;
            }

            else if(patteAvant->estEtire())
            {
                corps->baisser();
                corps->activerElectro();
                etat_sequence = REDRESSER;
            }
        }
    }

    else if(corps->estBaisse())
    {
        if(patteArriere->estReplie())
        {
            if(patteAvant->estReplie())
            {
                corps->activerElectro();
                etat_sequence = AVANCER_PATTE_AVANT;
            }

            else if(patteAvant->estEtire())
            {
                etat_sequence = MONTER_CORPS;
            }
        }

        else if(patteArriere->estEtire())
        {
            if(patteAvant->estReplie())
            {
                corps->activerElectro();
                etat_sequence = AVANCER_PATTE_ARRIERE;
            }

            else if(patteAvant->estEtire())
            {
                corps->activerElectro();
                etat_sequence = REDRESSER;
            }
        }
    }
}