/***
 * @author @MarieClaude1234 @JustinCoulombe6  @etiger314
 * @file Caterpullup.cpp
 * @date 29 janvier 2023
***/

#include "Caterpullup.h"

Caterpullup::Caterpullup(int _mode)
{
    connectDXL();

    corps = new Corps();
    patteAvant = new Patte();
    patteArriere = new Patte();

    nbSequences = 0;
    mode = _mode;
    commande_GUI = INACTIF;
    etat_sequence = PREP_AVANCER_PATTE_AV;
    firstInactif = true;

    init();
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

void Caterpullup::init()
{
    corps->monter();
    patteAvant->replier();
    patteArriere->replier();
    corps->desactiverElectro();
    patteAvant->activerElectro();
    patteArriere->activerElectro();
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

        if(firstInactif)
        {
            envoyerMessage();
        }

        //if(//le GUI envoie un message)
        //{
            //recevoirMessage();
        //}

        break;

    case ELECTRO_AVANT:

        if(patteAvant->electroActive())
        {
            corps->baisser();
            corps->activerElectro();
            patteArriere->activerElectro();

            patteAvant->desactiverElectro();
        }

        else if(!patteAvant->electroActive())
        {
            patteAvant->activerElectro();
        }

        commande_GUI = INACTIF;
        etat_sequence = INCONNU;

        break;

    case ELECTRO_CORPS:

        if(corps->electroActive())
        {
            patteAvant->activerElectro();
            patteArriere->activerElectro();

            corps->desactiverElectro();
        }

        else if(!corps->electroActive())
        {
            corps->baisser();

            corps->activerElectro();
        }

        commande_GUI = INACTIF;
        etat_sequence = INCONNU;

        break;

    case ELECTRO_ARRIERE:

        if(patteArriere->electroActive())
        {
            corps->baisser();
            corps->activerElectro();
            patteAvant->activerElectro();

            patteArriere->desactiverElectro();
        }

        else if(!patteArriere->electroActive())
        {
            patteArriere->activerElectro();
        }

        commande_GUI = INACTIF;
        etat_sequence = INCONNU;

        break;
    
    case PATTE_AVANT:

        corps->baisser();
        corps->activerElectro();
        patteArriere->activerElectro();
        patteAvant->desactiverElectro();

        if(patteAvant->estEtire())
        {
            patteAvant->replier();
        }

        else if(patteAvant->estReplie())
        {
            patteAvant->etirer();
        }

        commande_GUI = INACTIF;
        etat_sequence = INCONNU;

        break;

    case PIGNON_CREMAILLERE:

        patteArriere->activerElectro();
        patteAvant->activerElectro();
        corps->desactiverElectro();

        if(corps->estMonte())
        {
            corps->baisser();
        }

        else if(corps->estBaisse())
        {
            corps->monter();
        }

        commande_GUI = INACTIF;
        etat_sequence = INCONNU;

        break;

    case PATTE_ARRIERE:

        corps->baisser();
        corps->activerElectro();
        patteAvant->activerElectro();
        patteArriere->desactiverElectro();

        if(patteArriere->estEtire() )
        {
            patteArriere->replier();
        }

        else if(patteArriere->estReplie())
        {
            patteArriere->etirer();
        }

        commande_GUI = INACTIF;
        etat_sequence = INCONNU;
        break;

    case SEQUENCE_COMPLETE:

        nbSequences = 1;
        mode = MODE_AUTO;
        break;

    case ETAPE_PAR_ETAPE:

        nbSequences = -2;
        mode = MODE_AUTO;
        break;

    case AVANCER_AUTO:

        nbSequences = -1;
        mode = MODE_AUTO;
        break;

    case AVANCER_DISTANCE:
        //float distance = //valeur dans le GUI
        //calculerNbSequences(distance);
        mode = MODE_AUTO;
        break;

    case ARRET_URGENCE:

        commande_GUI = INACTIF;
        break;
    
    default:

        break;
    }
}

void Caterpullup::gererEtat()
{
    if (mode == MODE_MANUEL)
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