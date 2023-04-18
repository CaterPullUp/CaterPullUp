/***
 * @author @LoganCadorette
 * @file ElectroCPU.h
 * @date 29 janvier 2023
***/

#ifndef ELECTROCPU_H
#define ELECTROCPU_H

#include "Arduino_function.h"

#include "Electroaimant.h"

class ElectroCPU : public Electroaimant
{
public:

    /**
     * @brief Constructeur de l'objet ElectroCPU
     * 
     * @param pin_ 
     */
    ElectroCPU(int pin_);

    /**
     * @brief Active l'electroaimant
     * 
     */
    void activer();

    /**
     * @brief Desactive l'electroaimant
     * 
     */
    void desactiver();

    /**
     * @brief Obtention de la variable etat
     * 
     * @return true : si l'electroaimant est active
     * @return false : si l'electroaimant est desactive
     */
    bool getEtat();

    /**
     * @brief Obtention de la variable pin
     * 
     * @return int pin
     */
    int getPins();

    /**
     * @brief Fixe la variable etat
     * 
     * @param etat_ 
     */
    void setEtat(bool etat_);
};

#endif
