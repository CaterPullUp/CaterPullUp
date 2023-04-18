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

        /**
         * @brief Constructeur de l'objet Patte
         * 
         * @param dxl 
         * @param pin_electro 
         * @param id_moteur 
         * @param zero_position : angle de depart
         * @param direction : 1 ou -1
         */
        Patte(Dynamixel2Arduino* dxl, int pin_electro, int id_moteur, float zero_position, int direction);

        /**
         * @brief Destructeur de l'objet Patte
         * 
         */
        ~Patte();

        /**
         * @brief Désactive l'électroaimant et place le moteur a sa position initiale
         * 
         */
        void init();

        /**
         * @brief Etire la patte
         * 
         * @return true : si la patte est etiree
         * @return false : si la patte n'est pas etiree
         */
        bool etirer();

        /**
         * @brief Replie la patte
         * 
         * @return true : si la patte est repliee
         * @return false : si la patte n'est pas repliee
         */
        bool replier();

        /**
         * @brief Active l'electroaimant
         * 
         */
        void activerElectro();

        /**
         * @brief Desactive l'electroaimant
         * 
         */
        void desactiverElectro();

        /**
         * @brief Dit si la patte est etiree ou non
         * 
         * @return true : si la patte est etiree
         * @return false : si la patte n'est pas etiree
         */
        bool estEtire();

        /**
         * @brief Dit si la patte est repliee ou non
         * 
         * @return true : si la patte est repliee
         * @return false : si la patte n'est pas repliee
         */
        bool estReplie();

        /**
         * @brief Dit si l'electroaimant est active
         * 
         * @return true : si l'electroaimant est active
         * @return false : si l'electroaimant n'est pas active
         */
        bool electroActive();

        /**
         * @brief Arrete le moteur s'il a atteint son objectif d'angle
         * 
         * @return true : si le moteur est arrete
         * @return false : si le moteur n'est pas arrete
         */
        bool estArrete();
};

#endif
