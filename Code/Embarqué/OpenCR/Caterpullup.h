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

enum
{
    INIT,
    ARRET_URGENCE,
    RECEVOIR_COMMANDE,
    EXECUTER_COMMANDE,
    ACTIVER_ELECTRO,
    ACTIVER_MOTEUR
};

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

    public:
        Caterpullup(int _mode);
        ~Caterpullup();

        void setMode(int _mode);
        int getMode();

        void setEtat(int _etat);
        int getEtat();

        void gererEtat();
};


#endif