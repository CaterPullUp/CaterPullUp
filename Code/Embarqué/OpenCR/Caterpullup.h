/***
 * @author @MarieClaude1234
 * @file Caterpullup.h
 * @date 29 janvier 2023
***/

#ifndef CATERPULLUP_H
#define CATERPULLUP_H

#include "Patte.h"
#include "Corps.h"
#include "lib\Gabarits\Electroaimant.h"
#include "lib\Gabarits\Moteur.h"
#include "lib\Peripheriques\PeripheriqueCom.h"
#include "Dynamixel.h"
#include "timer.h"

#define MODE_MANUEL 0
#define MODE_AUTO 1

#define AUCUNE 0
#define REPLIER 1
#define ETIRER 2
#define MONTER 3
#define BAISSER 4
#define TERMINER 5
#define FIN_ETAPE -2

enum commande_GUI_enum
{
    INACTIF,
    ETIRER_PATTE_AV,
    REPLIER_PATTE_AV,
    ETIRER_PATTE_AR,
    REPLIER_PATTE_AR,
    CORPS_BAISSER,
    CORPS_MONTER,
    ACTIVER_ELECTRO_AV,
    DESACTIVER_ELECTRO_AV,
    ACTIVER_ELECTRO_CORPS,
    DESACTIVER_ELECTRO_CORPS,
    ACTIVER_ELECTRO_AR,
    DESACTIVER_ELECTRO_AR,
    ETAPE_PAR_ETAPE,
    COMMANDE_AUTO
    // SEQUENCE_COMPLETE,
    // ARRET_COMPLET,
    // AVANCER_DIST,
    // AVANCER_AUTO,
    
};

enum etat_sequence
{
    INIT,
    PREP_AVANCER_PATTE_AV,
    AVANCER_PATTE_AVANT,
    PREP_MONTER_CORPS,
    MONTER_CORPS,
    AVANCER_CORPS,
    PREP_AVANCER_PATTE_ARR,
    AVANCER_PATTE_ARRIERE,
    RETOUR_DEPART,
    REDRESSER,
    INCONNU
};

const float DISTANCE_SEQUENCE = 80;

class Caterpullup
{
    private:

        Dynamixel2Arduino* dxl;
        Corps* corps;
        Patte* patteAvant;
        Patte* patteArriere;

        etat_sequence sequence_robot;
        int commande_GUI;
        
        // PeripheriqueCom i2c;

        int mode;
        int nbSequences;

        bool first;
        bool firstInactif;
        bool arretComplet = false;

        bool moteursArretes;
        int action;
        Timer* timer;
        //Timer* timer2;

    public:
        /**
         * @brief Constructeur de l'objet Caterpullup
         * 
         * @param _mode 
         */
        Caterpullup(int _mode);

        /**
         * @brief Destructeur de l'objet Caterpullup
         */
        ~Caterpullup();

        void init();

        /**
         * @brief Set the Mode object
         * 
         * @param _mode 
         */
        void setMode(int _mode);

        /**
         * @brief Get the Mode object
         * 
         * @return int _mode (automatique ou manuel)
         */
        int getMode();

        void set_sequence_robot(enum etat_sequence _etat);
        int get_sequence_robot();

        void set_commande_GUI(int _etat);
        int get_commande_GUI();

        void gererEtat();

        void gererGUI();

        void sequence();

        void calculerNbSequences(float distance);

        void envoyerMessage();

        void recevoirMessage();

        void trouverEtatSequence();

        void setNbSequences(int _nbSequences);

        void setArretComplet(bool _arretComplet);

        void faireEtape(enum etat_sequence etat);

        void gererMoteurs();
};


#endif
