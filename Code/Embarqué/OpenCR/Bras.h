/***
 * @author @MarieClaude1234
 * @file Bras.h
 * @date 29 janvier 2023
***/

#ifndef BRAS_H
#define BRAS_H

#include "lib\Gabarits\Moteur.h"
#include "lib\Gabarits\Electroaimant.h"

class Bras
{
    private:
        Moteur* moteur;
        Electroaimant* electroaimant1;
        Electroaimant* electroaimant2;
        void init();

    public:
        Bras(Moteur* _moteur, Electroaimant* _electroaimants[]);
        ~Bras();

        void etirer();
        void replier();


};

#endif