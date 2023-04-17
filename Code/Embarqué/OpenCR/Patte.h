/***
 * @author @MarieClaude1234
 * @file Patte.h
 * @date 29 janvier 2023
***/

#ifndef PATTE_H
#define PATTE_H

#include "ElectroCPU.h"
#include "DXL_Patte.h"

class Patte
{
    private:
        Moteur* moteur;
        Electroaimant* electroaimant;

        int direction_;
        
        bool etire;
        bool replie;

    public:
        Patte(Dynamixel2Arduino* dxl, int pin_electro, int id_moteur, float zero_position, int direction);
        ~Patte();

        void init();

        bool etirer();
        bool replier();
        void activerElectro();
        void desactiverElectro();

        bool estEtire();
        bool estReplie();
        bool electroActive();

        bool estArrete();
};

#endif

#endif