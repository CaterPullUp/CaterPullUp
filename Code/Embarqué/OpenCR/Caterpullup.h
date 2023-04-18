/***
 * @author @MarieClaude1234
 * @file Caterpullup.h
 * @date 29 janvier 2023
***/

#ifndef CATERPULLUP_H
#define CATERPULLUP_H

#include "Patte.h"
#include "Corps.h"
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
#define FIN_ETAPE -2

#define PIN_ELECTRO_AVANT 13
#define PIN_ELECTRO_ARRIERE 12
#define PIN_ELECTRO_CORPS 14

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
        void set_commande_GUI(int _etat);

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

        /**
         * @brief Fixe la variable arretComplet
         * 
         * @param _arretComplet 
         */
        void setArretComplet(bool _arretComplet);

        /**
         * @brief Fixe la variable nbSequences
         * 
         * @param _nbSequences 
         */
        void setNbSequences(int _nbSequences);


        // Fonctions pas utilisees

        void faireEtape(enum etat_sequence etat);

        void sequence();

        void calculerNbSequences(float distance);

        void envoyerMessage();

        void recevoirMessage();
};


#endif
