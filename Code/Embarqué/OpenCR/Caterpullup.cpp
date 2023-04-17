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
    //patteAvant = new Patte(dxl, 12, 1, 105, 1);
    patteAvant = new Patte(dxl, 13, 2, 15, 1);
    patteArriere = new Patte(dxl, 12, 1, 200, -1);
    //patteArriere = new Patte(dxl, 13, 2, 15, -1);
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
    //timer2 = new Timer();

    timer->init(750,1);
    //timer2->init(2000,1);
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

void Caterpullup::setNbSequences(int _nbSequences){
    nbSequences = _nbSequences;
}

void Caterpullup::setArretComplet(bool _arretComplet){
    arretComplet = _arretComplet;
}

void Caterpullup::set_commande_GUI(int _etat)
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

    case ETIRER_PATTE_AV:

        if(patteAvant->etirer()){
            commande_GUI = INACTIF;
            sequence_robot = INCONNU;
        }
        break;

    case REPLIER_PATTE_AV:
        if(patteAvant->replier()){
            commande_GUI = INACTIF;
            sequence_robot = INCONNU;
        }
        break;

    case ETIRER_PATTE_AR:
        if(patteArriere->etirer()){
            commande_GUI = INACTIF;
            sequence_robot = INCONNU;
        }
        break;

    case REPLIER_PATTE_AR:
        if(patteArriere->replier()){
            commande_GUI = INACTIF;
            sequence_robot = INCONNU;
        }
        break;

    case CORPS_BAISSER:
        if(corps->baisser()){
            commande_GUI = INACTIF;
            sequence_robot = INCONNU;
        }
        break;

    case CORPS_MONTER:
        if(corps->monter()){
            commande_GUI = INACTIF;
            sequence_robot = INCONNU;
        }
        break;

    case ACTIVER_ELECTRO_AV:
        patteAvant->activerElectro();
        commande_GUI = INACTIF;
        sequence_robot = INCONNU;
        break;

    case DESACTIVER_ELECTRO_AV:
        patteAvant->desactiverElectro();
        commande_GUI = INACTIF;
        sequence_robot = INCONNU;
        break;

    case ACTIVER_ELECTRO_CORPS:
        corps->activerElectro();
        commande_GUI = INACTIF;
        sequence_robot = INCONNU;
        break;

    case DESACTIVER_ELECTRO_CORPS:
        corps->desactiverElectro();
        commande_GUI = INACTIF;
        sequence_robot = INCONNU;
        break;

    case ACTIVER_ELECTRO_AR:
        patteArriere->activerElectro();
        commande_GUI = INACTIF;
        sequence_robot = INCONNU;
        break;

    case DESACTIVER_ELECTRO_AR:
        patteArriere->desactiverElectro();
        commande_GUI = INACTIF;
        sequence_robot = INCONNU;
        break;

    case ETAPE_PAR_ETAPE:
        nbSequences = FIN_ETAPE;
        mode = MODE_AUTO;
        break;

    case COMMANDE_AUTO:
        
        if (nbSequences == 0){//Avancer sans arret
            nbSequences = -1;           
        }
        mode = MODE_AUTO;
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
            
            DEBUG_SERIAL.println("moteur stop");

            timer->start();
            DEBUG_SERIAL.println("started");
            if (timer->update())
            {
                DEBUG_SERIAL.println("timer done");
                //commande_GUI = SEQUENCE_COMPLETE;
                //commande_GUI = PIGNON_CREMAILLERE;
                // commande_GUI = AVANCER_AUTO;
                sequence_robot = PREP_AVANCER_PATTE_AV;
                //commande_GUI = PATTE_AVANT;
                commande_GUI = INACTIF;
                mode = MODE_MANUEL;
            }
            
            
        }
    }

    else if (mode == MODE_MANUEL)
    {
           // DEBUG_SERIAL.println("Manuel");
        gererGUI();
    }

    else if (mode == MODE_AUTO)
    {
        //DEBUG_SERIAL.println("Auto");
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
                    timer->start();
                    if (timer->update()){
                      if(corps->rapprocher()){
                        
                        sequence_robot = AVANCER_PATTE_AVANT;
                        DEBUG_SERIAL.println("fin_baisser");
                        if(nbSequences == -2) //etape par etape
                        {
                            mode = MODE_MANUEL;
                            commande_GUI = INACTIF;
                        }
                      }
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
                    sequence_robot = PREP_MONTER_CORPS;
                    
                    if(nbSequences == -2) //etape par etape
                    {
                        DEBUG_SERIAL.println("-seq 2");
                        mode = MODE_MANUEL;
                        commande_GUI = INACTIF;
                    }
                }

                break;

            case PREP_MONTER_CORPS:

            timer->start();
            if(timer->update()){

              corps->desactiverElectro();
              sequence_robot = MONTER_CORPS;
              
            }

            case MONTER_CORPS:

                //corps->desactiverElectro();
                timer->start();

                //if (timer->update() && corps->monter())
                if (timer->update())
                {
                  if(corps->monter())
                  {
                    sequence_robot = AVANCER_CORPS;

                    if(nbSequences == -2) //etape par etape
                    {
                        mode = MODE_MANUEL;
                        commande_GUI = INACTIF;
                    }
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

                    timer->start();

                    if(timer->update())
                    {
                        sequence_robot = AVANCER_PATTE_ARRIERE;
    
                        if(nbSequences == -2) //etape par etape
                        {
                            mode = MODE_MANUEL;
                            commande_GUI = INACTIF;
                        }
                    }
                }

                break;

            case AVANCER_PATTE_ARRIERE:

                patteArriere->desactiverElectro();
                timer->start();

                if (timer->update() && patteArriere->replier())
                {
                    patteArriere->activerElectro();
                    if(corps->rapprocher()){
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

        if (arretComplet)
        {
            arretComplet=false;
            Serial.print("ArretComplet case");
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
