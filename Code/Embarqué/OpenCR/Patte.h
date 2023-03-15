/***
 * @author @MarieClaude1234
 * @file Patte.h
 * @date 29 janvier 2023
***/

#ifndef PATTE_H
#define PATTE_H

#include "lib\Gabarits\Moteur.h"
#include "lib\Gabarits\Electroaimant.h"
#include "ElectroCPU.h"

class Patte
{
    private:
        Moteur* moteur;
        Electroaimant* electroaimant;
        void init();

    public:
        //Patte(Moteur* _moteur, Electroaimant* _electroaimant);
        Patte();
        ~Patte();

        bool etirer();
        bool replier();
        void activerElectro();
        void desactiverElectro();
};

#endif