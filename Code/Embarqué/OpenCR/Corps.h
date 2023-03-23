/***
 * @author Étienne Germain
 * @file Corps.h
 * @date 17 janvier 2023
***/

#ifndef CORPS_H
#define CORPS_H

#include "lib\Gabarits\Moteur.h"
#include "lib\Gabarits\Electroaimant.h"
#include "ElectroCPU.h"

class Corps
{
    private:
        Moteur* moteur;
        Electroaimant* electroaimant;
        void init();
        bool monte;
        bool baisse;

    public:
        //Corps(Moteur* _moteur, Electroaimant* _electroaimant);
        Corps();
        ~Corps();

        bool monter();
        bool baisser();
        void activerElectro();
        void desactiverElectro();

        bool estMonte();
        bool estBaisse();
        bool electroActive();
};

#endif