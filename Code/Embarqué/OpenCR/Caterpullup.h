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

#define MODE_MANUEL 1
#define MODE_AUTO 2

enum commande_GUI
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
    POSITION_DEPART, // pattes avant et arriere retractees, electroaiamnts avant et arriere actives, pignon cremaillere remonte
    PREP_AVANCER_PATTE_AV, //
    AVANCER_PATTE_AV,
    MONTER_CORPS,
    AVANCER_CORPS,
    PREP_AVANCER_PATTE_AR,
    AVANCER_PATTE_AR
};

const float DISTANCE_SEQUENCE = 13;  // !!! A CALCULER EXPÉRIMENTALEMENT

class Caterpullup
{
    private:
        //Moteur* moteurs[3];
        //Electroaimant* electroaimants[6];

        Corps* corps;
        Patte* patteAvant;
        Patte* patteArriere;

        etat_sequence etat_sequence;
        commande_GUI commande_GUI;
        
        // PeripheriqueCom i2c;

        int mode;
        int nbSequences;

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

        void set_etat_sequence(enum etat_sequence _etat);
        int get_etat_sequence();

        void set_commande_GUI(enum commande_GUI _etat);
        int get_commande_GUI();



        /**
         * @brief 
         * 
         */
        void gererEtat();

        void gererGUI();

        void sequence();

        void calculerNbSequences(float distance);
};

#endif