/***
 * @author @MarieClaude1234 @JustinCoulombe6  @etiger314
 * @file Caterpullup.cpp
 * @date 29 janvier 2023
***/

#include "Caterpullup.h"

/*void connectDXL()
{
    //dxl = new Dynamixel2Arduino(DXL_SERIAL, DXL_DIR_PIN);
    Dynamixel2Arduino dynamix(DXL_SERIAL, DXL_DIR_PIN);
    dxl = &dynamix;
    dxl->begin(DXL_BAUD_RATE);
    dxl->setPortProtocolVersion(DXL_PROTOCOL_VERSION);
}*/

Caterpullup::Caterpullup(int _mode)
{
    dxl = new Dynamixel2Arduino(DXL_SERIAL, DXL_DIR_PIN);
    //Dynamixel2Arduino* dxl = new Dynamixel2Arduino(DXL_SERIAL, DXL_DIR_PIN);
    dxl->begin(DXL_BAUD_RATE);
    dxl->setPortProtocolVersion(DXL_PROTOCOL_VERSION);
    //Dynamixel2Arduino* dxl = connectDXL();
    //connectDXL();
    /*dxl = new Dynamixel2Arduino(DXL_SERIAL, DXL_DIR_PIN);
    dxl->begin(DXL_BAUD_RATE);
    dxl->setPortProtocolVersion(DXL_PROTOCOL_VERSION);*/
    patteAvant = new Patte(dxl, 12, 1, 105, 1);
   // patteAvant = new Patte(dxl, 12, 1, 185, 1);
   // patteArriere = new Patte(dxl, 13, 2, 95, -1);
    patteArriere = new Patte(dxl, 13, 2, 15, -1);
    corps = new Corps(dxl, 14, 3);

    nbSequences = 0;
    mode = _mode;
    commande_GUI = INACTIF;
    sequence_robot = INIT;
    first = true;
    firstInactif = true;
    moteursArretes = true;
    action = AUCUNE;

    timer = new Timer();

    timer->init(2000,1);
}

Caterpullup::~Caterpullup()
{
    delete patteAvant;
    delete patteArriere;
    delete corps;

    // delete i2c;
}

void Caterpullup::init()
{
    patteAvant->init();
    patteArriere->init();
    corps->init();
    moteursArretes = false;
    DEBUG_SERIAL.println("moteurs bougent");
}

void Caterpullup::setMode(int _mode)
{
    mode = _mode;
}

int Caterpullup::getMode()
{
    return mode;
}

void Caterpullup::set_sequence_robot(enum etat_sequence _etat)
{
    sequence_robot = _etat;
}

int Caterpullup::get_sequence_robot()
{
    return sequence_robot;
}

void Caterpullup::set_commande_GUI(enum commande_GUI_enum _etat)
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

        //delay(2000);

        //commande_GUI = ETAPE_PAR_ETAPE;

        break;

    case ELECTRO_AVANT:

        if(patteAvant->electroActive())
        {
            //corps->baisser();
            //corps->activerElectro();
            //patteArriere->activerElectro();

            patteAvant->desactiverElectro();
        }

        else if(!patteAvant->electroActive())
        {
            patteAvant->activerElectro();
        }

        commande_GUI = ELECTRO_AVANT;   ///INACTIF
        sequence_robot = INCONNU;

        delay(2000);

        break;

    case ELECTRO_CORPS:

        if(corps->electroActive())
        {
            //patteAvant->activerElectro();
            //patteArriere->activerElectro();

            corps->desactiverElectro();

            DEBUG_SERIAL.println("electro corps desactive");
        }

        else if(!corps->electroActive())
        {
            //corps->baisser();

            corps->activerElectro();

            DEBUG_SERIAL.println("electro corps active");
        }

        commande_GUI = ELECTRO_CORPS;     ///INACTIF
        sequence_robot = INCONNU;

        delay(2000);

        break;

    case ELECTRO_ARRIERE:

        if(patteArriere->electroActive())
        {
            //corps->baisser();
            //corps->activerElectro();
            //patteAvant->activerElectro();

            patteArriere->desactiverElectro();

            DEBUG_SERIAL.println("electro arriere desactive");
        }

        else if(!patteArriere->electroActive())
        {
            patteArriere->activerElectro();

            DEBUG_SERIAL.println("electro arriere active");
        }

        commande_GUI = ELECTRO_ARRIERE;     ///INACTIF
        sequence_robot = INCONNU;

        delay(2000);

        break;
    
    case PATTE_AVANT:

        //corps->baisser();
        //corps->activerElectro();
        //patteArriere->activerElectro();
        //patteAvant->desactiverElectro();

        if(patteAvant->estEtire() && action == AUCUNE)
        {
            action = REPLIER;
        }

        else if(patteAvant->estReplie() && action == AUCUNE)
        {
          action = ETIRER;
        }

        if(action == REPLIER)
        {
            if(patteAvant->replier())
            {
                action = TERMINER;
            } 
        }

        else if(action == ETIRER)
        {
            if(patteAvant->etirer())
            {
                action = TERMINER;
            }
        }

        if(action == TERMINER)
        {
            commande_GUI = PATTE_AVANT; ////INACTIF
            sequence_robot = INCONNU;
            action = AUCUNE;
            delay(750);
        }

        break;

    case PIGNON_CREMAILLERE:

        //patteArriere->activerElectro();
        //patteAvant->activerElectro();
        //corps->desactiverElectro();

        if(corps->estBaisse() && action == AUCUNE)
        {
            action = MONTER;
        }

        else if(corps->estMonte() && action == AUCUNE)
        {
          action = BAISSER;
        }

        if(action == MONTER)
        {
            if(corps->monter())
            {
                action = TERMINER;
            } 
        }

        else if(action == BAISSER)
        {
            if(corps->baisser())
            {
                action = TERMINER;
            }
        }

        if(action == TERMINER)
        {
            commande_GUI = ELECTRO_CORPS;  ///INACTIF
            sequence_robot = INCONNU;
            action = AUCUNE;

            delay(750);
        }

        break;

    case PATTE_ARRIERE:

        //corps->baisser();
        //corps->activerElectro();
        //patteAvant->activerElectro();
        //patteArriere->desactiverElectro();

        if(patteArriere->estEtire() && action == AUCUNE)
        {
            action = REPLIER;
        }

        else if(patteArriere->estReplie() && action == AUCUNE)
        {
          action = ETIRER;
        }

        if(action == REPLIER)
        {
            if(patteArriere->replier())
            {
                action = TERMINER;
            } 
        }

        else if(action == ETIRER)
        {
            if(patteArriere->etirer())
            {
                action = TERMINER;
            }
        }

        if(action == TERMINER)
        {
            commande_GUI = PATTE_ARRIERE;   ///INACTIF
            sequence_robot = INCONNU;
            action = AUCUNE;
            delay(750);
        }

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
        nbSequences = 3;            ///
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
    if (sequence_robot == INIT)
    {
        DEBUG_SERIAL.println("gererEtat");
        if(moteursArretes)
        {
            patteAvant->activerElectro();
            patteArriere->activerElectro();
            sequence_robot = PREP_AVANCER_PATTE_AV;
            DEBUG_SERIAL.println("moteur stop");

            commande_GUI = AVANCER_AUTO;      ////////ENLEVER HABITUELLEMENT
        }
    }

    else if (mode == MODE_MANUEL)
    {
           // DEBUG_SERIAL.println("Manuel");
        gererGUI();
    }

    else if (mode == MODE_AUTO)
    {
        DEBUG_SERIAL.println("Auto");
        bool patteAvantRepliee;
        bool patteArriereEtiree;
        switch (sequence_robot)
        {            
            case INCONNU:

                trouverEtatSequence();

                break;

            case PREP_AVANCER_PATTE_AV:
                if (corps->baisser())
                {
                    corps->activerElectro();
                    sequence_robot = AVANCER_PATTE_AVANT;
                    DEBUG_SERIAL.println("fin_baisser");
                    if(nbSequences == -2) //etape par etape
                    {
                        mode = MODE_MANUEL;
                        commande_GUI = INACTIF;
                    }
                }

                break;

            case AVANCER_PATTE_AVANT:
                
                patteAvant->desactiverElectro();
                timer->start();
                DEBUG_SERIAL.println("case avancer patte av");

                if (timer->update() && patteAvant->etirer())
                {
                    patteAvant->activerElectro();
                    sequence_robot = MONTER_CORPS;
                    
                    if(nbSequences == -2) //etape par etape
                    {
                        DEBUG_SERIAL.println("-seq 2");
                        mode = MODE_MANUEL;
                        commande_GUI = INACTIF;
                    }
                }

                break;

            case MONTER_CORPS:

                corps->desactiverElectro();
                timer->start();

                if (timer->update() && corps->monter())
                {
                    sequence_robot = AVANCER_CORPS;

                    if(nbSequences == -2) //etape par etape
                    {
                        mode = MODE_MANUEL;
                        commande_GUI = INACTIF;
                    }
                }

                break;

            case AVANCER_CORPS:

                DEBUG_SERIAL.println(dxl->getPresentPosition(2, UNIT_DEGREE));
                patteAvantRepliee = patteAvant->replier();
                patteArriereEtiree = patteArriere->etirer();

                if (patteAvantRepliee && patteArriereEtiree)
                {
                    sequence_robot = PREP_AVANCER_PATTE_ARR;
                    //sequence_robot = AVANCER_PATTE_ARRIERE;
                    
                    if(nbSequences == -2) //etape par etape
                    {
                        mode = MODE_MANUEL;
                        commande_GUI = INACTIF;
                    }
                }

                break;

            case PREP_AVANCER_PATTE_ARR:

                if (corps->baisser())
                {
                    corps->activerElectro();
                    sequence_robot = AVANCER_PATTE_ARRIERE;

                    if(nbSequences == -2) //etape par etape
                    {
                        mode = MODE_MANUEL;
                        commande_GUI = INACTIF;
                    }
                }

                break;

            case AVANCER_PATTE_ARRIERE:

                patteArriere->desactiverElectro();
                timer->start();

                if (timer->update() && patteArriere->replier())
                {
                    patteArriere->activerElectro();

                    if(nbSequences == -2) //etape par etape
                    {
                        sequence_robot = RETOUR_DEPART;
                        mode = MODE_MANUEL;
                        commande_GUI = INACTIF;
                    }

                    else if (nbSequences == 1)
                    {
                        nbSequences -=1;
                        sequence_robot = RETOUR_DEPART;
                    }

                    else if(nbSequences == -1)
                    {
                        sequence_robot = AVANCER_PATTE_AVANT;
                    }

                    else
                    {
                        nbSequences -= 1;
                        sequence_robot = AVANCER_PATTE_AVANT;
                    }
                }

                break;

            case RETOUR_DEPART:

                corps->desactiverElectro();

                timer->start();

                if (timer->update() && corps->monter())
                {
                    sequence_robot = PREP_AVANCER_PATTE_AV;
                    mode = MODE_MANUEL;
                    commande_GUI = INACTIF;
                }

                break;

            case REDRESSER:

                patteArriere->desactiverElectro();

                timer->start();

                if(timer->update() && patteArriere->replier())
                {
                    patteArriere->activerElectro();
                    sequence_robot = MONTER_CORPS;

                    if(nbSequences == -2) //etape par etape
                    {
                        mode = MODE_MANUEL;
                        commande_GUI = INACTIF;
                    }
                }

                break;

            default:
    
                break;
        }

        if (commande_GUI == ARRET_URGENCE)
        {
          
            DEBUG_SERIAL.println("URGENCE");
            mode = MODE_MANUEL;
            commande_GUI = INACTIF;
        }
    }
}

void Caterpullup::gererMoteurs()
{
    bool moteurAvantArrete = patteAvant->estArrete();
    bool moteurArriereArrete = patteArriere->estArrete();
    bool corpsArrete = corps->estArrete();
    moteursArretes = moteurAvantArrete && moteurArriereArrete && corpsArrete;
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
                sequence_robot = AVANCER_PATTE_AVANT;
            }

            else if(patteAvant->estEtire())
            {
                patteArriere->activerElectro();
                sequence_robot = MONTER_CORPS;
            }
        }

        else if(patteArriere->estEtire())
        {
            if(patteAvant->estReplie())
            {
                sequence_robot = AVANCER_PATTE_ARRIERE;
            }

            else if(patteAvant->estEtire())
            {
                sequence_robot = REDRESSER;
            }
        }
    }

    else if(!patteAvant->electroActive())
    {
        if(patteArriere->estReplie())
        {
            if(patteAvant->estReplie())
            {
                sequence_robot = AVANCER_PATTE_AVANT;
            }

            else if(patteAvant->estEtire())
            {
                patteAvant->activerElectro();
                sequence_robot = MONTER_CORPS;
            }
        }

        else if(patteArriere->estEtire())
        {
            if(patteAvant->estReplie())
            {
                patteAvant->activerElectro();
                sequence_robot = AVANCER_PATTE_ARRIERE;
            }

            else if(patteAvant->estEtire())
            {
                patteAvant->activerElectro();
                sequence_robot = REDRESSER;
            }
        }
    }

    else if(corps->electroActive())
    {
        if(patteArriere->estReplie())
        {
            if(patteAvant->estReplie())
            {
                sequence_robot = AVANCER_PATTE_AVANT;
            }

            else if(patteAvant->estEtire())
            {
                sequence_robot = MONTER_CORPS;
            }
        }

        else if(patteArriere->estEtire())
        {
            if(patteAvant->estReplie())
            {
                sequence_robot = AVANCER_PATTE_ARRIERE;
            }

            else if(patteAvant->estEtire())
            {
                sequence_robot = REDRESSER;
            }
        }
    }

    else if(corps->estMonte())
    {
        if(patteArriere->estReplie())
        {
            if(patteAvant->estReplie())
            {
                sequence_robot = PREP_AVANCER_PATTE_AV;
            }

            else if(patteAvant->estEtire())
            {
                sequence_robot = AVANCER_CORPS;
            }
        }

        else if(patteArriere->estEtire())
        {
            if(patteAvant->estReplie())
            {
                sequence_robot = PREP_AVANCER_PATTE_ARR;
            }

            else if(patteAvant->estEtire())
            {
                if(corps->baisser())
                {
                    corps->activerElectro();
                    sequence_robot = REDRESSER;
                }
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
                sequence_robot = AVANCER_PATTE_AVANT;
            }

            else if(patteAvant->estEtire())
            {
                sequence_robot = MONTER_CORPS;
            }
        }

        else if(patteArriere->estEtire())
        {
            if(patteAvant->estReplie())
            {
                corps->activerElectro();
                sequence_robot = AVANCER_PATTE_ARRIERE;
            }

            else if(patteAvant->estEtire())
            {
                corps->activerElectro();
                sequence_robot = REDRESSER;
            }
        }
    }
}
