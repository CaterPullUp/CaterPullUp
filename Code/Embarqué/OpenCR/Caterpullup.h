/***
 * @author @MarieClaude1234
 * @file Caterpullup.h
 * @date 29 janvier 2023
***/

#ifndef CATERPULLUP_H
#define CATERPPULLUP_H

#include "Bras.h"
#include "Corps.h"
#include "lib\Gabarits\Electroaimant.h"
#include "lib\Gabarits\Moteur.h"
#include "lib\Peripheriques\PeripheriqueCom.h"


#define MODE_MANUEL 1
#define MODE_AUTO 2

<<<<<<< Updated upstream
<<<<<<< Updated upstream
enum
=======
enum Commande
>>>>>>> Stashed changes
=======
enum Commande
>>>>>>> Stashed changes
{
    INIT,
    ARRET_URGENCE,
    RECEVOIR_COMMANDE,
    EXECUTER_COMMANDE,
    ACTIVER_ELECTRO,
    ACTIVER_MOTEUR
};

<<<<<<< Updated upstream
<<<<<<< Updated upstream
class Caterpullup
{
    private:
        Moteur* moteurs[3];
        Electroaimant* electroaimants[6];
        Bras* bras[2];
        // Corps corps;
        // PeripheriqueCom i2c;

        int mode;
        int etat;
=======
=======
>>>>>>> Stashed changes
enum Sequence
{
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

const float DISTANCE_SEQUENCE = 13;  // !!! A CALCULER EXPÉRIMENTALEMENT

class Caterpullup
{
    private:

        Corps* corps;
        Patte* patteAvant;
        Patte* patteArriere;

        Sequence etat_sequence;
        Commande commande_GUI;
        
        // PeripheriqueCom i2c;

        int mode;
        int nbSequences;

        bool first;
        bool firstInactif;
>>>>>>> Stashed changes

        bool moteursArretes;

        bool moteursArretes;

    public:
        Caterpullup(int _mode);
        ~Caterpullup();

        void setMode(int _mode);
        int getMode();

<<<<<<< Updated upstream
<<<<<<< Updated upstream
        void setEtat(int _etat);
        int getEtat();

        void gererEtat();
=======
=======
>>>>>>> Stashed changes
        void set_etat_sequence(enum Sequence _etat);
        int get_etat_sequence();

        void set_commande_GUI(enum Commande _etat);
        int get_commande_GUI();

        void gererEtat();

        void gererGUI();

        void sequence();

        void calculerNbSequences(float distance);

        void envoyerMessage();

        void recevoirMessage();

        void trouverEtatSequence();

        void faireEtape(enum Sequence etat);

        void gererMoteurs();
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
};


#endif