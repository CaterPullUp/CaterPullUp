/***
 * @author @etiger314
 * @file Electroaimant.h
 * @date 17 janvier 2023
***/

#ifndef ELECTROAIMANT_H
#define ELECTROAIMANT_H

class Electroaimant
{
protected:

    bool etat;
    int pin;

public:

    /**
     * @brief Constructeur de l'objet Electroaimant
     * 
     * @param pin_ 
     */
    Electroaimant(int pin_){};

    /**
     * @brief Fixe la variable objet
     * 
     * @param etat_ 
     */
    virtual void setEtat(bool etat_)=0;

    /**
     * @brief Obtention de la variable etat
     * 
     * @return true : si l'electroaimant est active
     * @return false : si l'electroaimant est desactive
     */
    virtual bool getEtat()=0;

    /**
     * @brief Obtention de la variable pin
     * 
     * @return int pin
     */
    virtual int getPins()=0;

    /**
     * @brief Active l'electroaimant
     * 
     */
    virtual void activer()=0;

    /**
     * @brief Desactive l'electroaimant
     * 
     */
    virtual void desactiver()=0;
};

#endif
