/***
 * @author @etiger314
 * @file DXL_Patte.h
 * @date 22 mars 2023
***/

#ifndef DXL_PATTE_H
#define DXL_PATTE_H

#define VITESSE_PATTE 9

#include "Arduino_function.h"

#include "Dynamixel.h"
#include "Moteur.h"

#define EXTEND_MOVEMENT_ANGLE 235
#define RETRACT_MOVEMENT_ANGLE 125

class DXL_Patte : public Moteur
{
private:

    bool finished_movement;
    float current_angle;
    float goal_angle;
    Dynamixel2Arduino* dxl;

    float zero_position;
    int id;
    int direction;
    void init();

public:

    /**
     * @brief Constructeur de l'objet DXL_Patte
     * 
     * @param dxl 
     * @param id_ 
     * @param zero_position_ : position de depart
     * @param direction_ : 1 ou -1
     */
    DXL_Patte(Dynamixel2Arduino* dxl, int id_, float zero_position_, int direction_);

    /**
     * @brief Met le moteur a sa positon initiale
     * 
     */
    void positionInitiale();

    /**
     * @brief Obtention de la variable vitesse
     * 
     * @return float vitesse
     */
    float getVitesse();

    /**
     * @brief Fixe la variable vitesse et le moteur à la vitesse passee en parametre
     * 
     * @param v : vitesse du moteur (%)
     */
    void setVitesse(float v);

    /**
     * @brief Obtention de la variable pin
     * 
     * @return int pin
     */
    int getPins();

    /**
     * @brief Arrete le moteur s'il a atteint son objectif d'angle
     * 
     * @return true : si le mouvement est fini
     * @return false : si le mouvement n'est pas fini
     */
    bool is_movement_finished();

    /**
     * @brief Trouve l'angle actuel et le renvoie
     * 
     * @return float current_angle
     */
    float currentAngle();

    /**
     * @brief Change l'objectif d'angle de la valeur passee en parametre
     * 
     * @param angle : angle a incrementer ou decrementer
     */
    void incrementGoalAngle(float angle);

    /**
     * @brief Obtention de la variable goal_angle
     * 
     * @return float goal_angle
     */
    float getGoalAngle();

    /**
     * @brief Obtention de la variable zero_position
     * 
     * @return float zero_position
     */
    float getZeroPosition();

    /**
     * @brief Obtention de la variable id
     * 
     * @return uint8_t : id
     */
    uint8_t getID();

    /**
     * @brief Obtention de la variable direction
     * 
     * @return int direction
     */
    int getDirection();

    /**
     * @brief Fixe la variable vitesse et le moteur à la vitesse par défaut
     * 
     */
    void setVitesse();

    //void stopMotor();
    //void stopTorque();
    //void startTorque();
    //bool getTorque();
    
};

#endif
