/***
 * @author @etiger314
 * @file Moteur.h
 * @date 17 janvier 2023
***/
#ifndef MOTEUR_H_
#define MOTEUR_H_

class Moteur
{
protected:

    float vitesse;
    int pin;

public:

    /**
     * @brief Obtention de la variable vitesse
     * 
     * @return float vitesse
     */
    virtual float getVitesse() = 0;

    /**
     * @brief Obtention de la variable pin
     * 
     * @return int pin
     */
    virtual int getPins() = 0;

    /**
     * @brief Fixe la variable vitesse
     * 
     * @param v 
     */
    virtual void setVitesse(float v) = 0;
};

#endif