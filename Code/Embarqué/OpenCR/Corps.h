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

        /**
         * @brief Constructeur de l'objet Corps
         * 
         * @param dxl 
         * @param pin_electro 
         * @param id_moteur 
         */
        Corps(Dynamixel2Arduino* dxl, int pin_electro, int id_moteur);

        /**
         * @brief Destructeur de l'objet Corps
         * 
         */
        ~Corps();

        /**
         * @brief Désactive l'électroaimant et place le moteur a sa position initiale
         * 
         */
        void init();

        /**
         * @brief Fait monter le corps
         * 
         * @return true : si le corps est monte
         * @return false : si le corps n'est pas monte
         */
        bool monter();

        /**
         * @brief Fait baisser le corps
         * 
         * @return true : si le corps est baisse
         * @return false : si le corps n'est pas baisse
         */
        bool baisser();

        /**
         * @brief Remonte un peu la cremaillere pour rapprocher le robot de la surface
         * 
         * @return true : si le corps est dans la position rapprochee
         * @return false : si le corps n'est pas dans la position rapprochee
         */
        bool rapprocher();

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
         * @brief Dit si la cremaillere est montee ou non
         * 
         * @return true : si la cremaillere est montee
         * @return false : si la cremaillere n'est pas montee
         */
        bool estMonte();

        /**
         * @brief Dit si la cremaillere est baissee ou non
         * 
         * @return true : si la cremaillere est baissee
         * @return false : si la cremaillere n'est pas baissee
         */
        bool estBaisse();

        /**
         * @brief Dit si l'electroaimant est active
         * 
         * @return true : si l'electroaimant est active
         * @return false : si l'electroaimant est desactive
         */
        bool electroActive();

        /**
         * @brief Dit si le moteur a atteint son objectif d'angle
         * 
         * @return true : si le moteur est arrete
         * @return false : si le moteur n'est pas arrete
         */
        bool estArrete();
};

#endif
