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
#include "DXL_Corps.h"

class Corps
{
    private:
        Moteur* moteur;
        Electroaimant* electroaimant;
        bool monte;
        bool baisse;

    public:
        //Corps(Moteur* _moteur, Electroaimant* _electroaimant);
        Corps(Dynamixel2Arduino* dxl, int pin_electro, int id_moteur);
        ~Corps();

        void init();

        bool monter();
        bool baisser();
        void activerElectro();
        void desactiverElectro();

        bool estMonte();
        bool estBaisse();
        bool electroActive();
};

#endif
