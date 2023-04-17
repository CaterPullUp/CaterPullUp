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
#include "timer.h"

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
    PREP_MONTER_CORPS,
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
        Timer* timer;
        //Timer* timer2;

    public:

        /**
         * @brief Constructeur de l'objet Caterpullup
         * 
         * @param _mode : MODE_MANUEL ou MODE_AUTO
         */
        Caterpullup(int _mode);

        /**
         * @brief Destructeur de l'objet Caterpullup
         */
        ~Caterpullup();

        /**
         * @brief Initialise les pattes et le corps du robot
         * 
         */
        void init();

        /**
         * @brief Fixe la variable mode
         * 
         * @param _mode : MODE_MANUEL ou MODE_AUTO
         */
        void setMode(int _mode);

        /**
         * @brief Obtention de la variable mode
         * 
         * @return int _mode : MODE_MANUEL ou MODE_AUTO
         */
        int getMode();

        /**
         * @brief Fixe la variable sequence_robot
         * 
         * @param _etat : etat de la sequence
         */
        void set_sequence_robot(enum etat_sequence _etat);

        /**
         * @brief Obtention de la variable etat_sequence
         * 
         * @return int etat_sequence : etat de la sequence
         */
        int get_sequence_robot();

        /**
         * @brief Fixe la variable commande_GUI
         * 
         * @param _etat : etat de la commande GUI
         */
        void set_commande_GUI(enum commande_GUI_enum _etat);

        /**
         * @brief Obtention de la variable commande_GUI
         * 
         * @return int commande_GUI : etat de la commande GUI
         */
        int get_commande_GUI();

        /**
         * @brief Gere la sequence
         * 
         */
        void gererEtat();

        /**
         * @brief Gere les commandes GUI
         * 
         */
        void gererGUI();

        /**
         * @brief Trouve l'etat actuel et replace le robot dans la sequence
         * 
         */
        void trouverEtatSequence();

        /**
         * @brief Verifie si les moteurs sont arretes
         * 
         */
        void gererMoteurs();


        //Fonctions pas utilisées

        void sequence();

        void calculerNbSequences(float distance);

        void envoyerMessage();

        void recevoirMessage();

        void faireEtape(enum etat_sequence etat);

};


#endif
