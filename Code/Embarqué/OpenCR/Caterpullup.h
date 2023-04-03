/***
 * @author @MarieClaude1234
 * @file Caterpullup.h
 * @date 29 janvier 2023
***/

#ifndef CATERPULLUP_H
#define CATERPPULLUP_H

#include "Patte.h"
#include "Corps.h"
#include "lib\Gabarits\Electroaimant.h"
#include "lib\Gabarits\Moteur.h"
#include "lib\Peripheriques\PeripheriqueCom.h"
#include "Dynamixel.h"

#define MODE_MANUEL 1
#define MODE_AUTO 2

#define AUCUNE 0
#define REPLIER 1
#define ETIRER 2
#define MONTER 3
#define BAISSER 4
#define TERMINER 5

enum commande_GUI_enum
{
    INACTIF,
    ELECTRO_AVANT,
    ELECTRO_CORPS,
    ELECTRO_ARRIERE,
    PATTE_AVANT,
    PIGNON_CREMAILLERE,
    PATTE_ARRIERE,
    SEQUENCE_COMPLETE,
    ETAPE_PAR_ETAPE,
    AVANCER_AUTO,
    AVANCER_DISTANCE,
    ARRET_URGENCE
};

enum etat_sequence
{
    INIT,
    PREP_AVANCER_PATTE_AV,
    AVANCER_PATTE_AVANT,
    MONTER_CORPS,
    AVANCER_CORPS,
    PREP_AVANCER_PATTE_ARR,
    AVANCER_PATTE_ARRIERE,
    RETOUR_DEPART,
    REDRESSER,
    INCONNU
};

const float DISTANCE_SEQUENCE = 100;  // !!! A CALCULER EXPÉRIMENTALEMENT

class Caterpullup
{
    private:

        Dynamixel2Arduino* dxl;
        Corps* corps;
        Patte* patteAvant;
        Patte* patteArriere;

        etat_sequence sequence_robot;
        commande_GUI_enum commande_GUI;
        
        // PeripheriqueCom i2c;

        int mode;
        int nbSequences;

        bool first;
        bool firstInactif;

        bool moteursArretes;
        int action;

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

        void set_commande_GUI(enum commande_GUI_enum _etat);
        int get_commande_GUI();

        void gererEtat();

        void gererGUI();

        void sequence();

        void calculerNbSequences(float distance);

        void envoyerMessage();

        void recevoirMessage();

        void trouverEtatSequence();

        void faireEtape(enum etat_sequence etat);

        void gererMoteurs();
};


#endif
