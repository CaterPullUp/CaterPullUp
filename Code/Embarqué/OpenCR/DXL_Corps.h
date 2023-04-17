/***
 * @author @etiger314
 * @file DXL_Corps.h
 * @date 22 mars 2023
***/

#ifndef DXL_CORPS_H
#define DXL_CORPS_H

#include "Arduino_function.h"

#include "Dynamixel.h"
#include "Moteur.h"

using namespace ControlTableItem;

#define VITESSE_CORPS 50

#define ANGLE_MONTER 360
#define ANGLE_BAISSER 220
#define ANGLE_RAPPROCHE 250

class DXL_Corps : public Moteur
{
private:

    Dynamixel2Arduino* dxl;
    int id;
    bool finished_movement;

    float current_angle;
    float goal_angle;

    void init();

public:

    /**
     * @brief Constructeur de l'objet DXL_Corps
     * 
     * @param dxl 
     * @param id 
     */
    DXL_Corps(Dynamixel2Arduino* dxl, int id);

    /**
     * @brief Obtention de la variable pin
     * 
     * @return int pin
     */
    int getPins();

    /**
     * @brief Obtention de la variable vitesse
     * 
     * @return float vitesse
     */
    float getVitesse();

    /**
     * @brief Fixe la variable vitesse
     * 
     * @param v : vitesse du moteur (%)
     */
    void setVitesse(float v);

    /**
     * @brief Obtention de la variable id
     * 
     * @return uint8_t id
     */
    uint8_t getID();

    /**
     * @brief Dit si le moteur a atteint son objectif d'angle
     * 
     * @return true : si le moteur a termine son mouvement
     * @return false : si le moteur n'a pas termine son mouvement
     */
    bool is_movement_finished();

    /**
     * @brief Active le moteur pour qu'il se rende jusqu'a une position
     * 
     * @param angle : position a atteindre
     */
    void go_to_position(float angle);

    /**
     * @brief Obtention de la variable goal_angle
     * 
     * @return float goal_angle
     */
    float getGoalAngle();

    /**
     * @brief Trouve l'angle actuel et le renvoie
     * 
     * @return float current_angle
     */
    float currentAngle();

    /**
     * @brief Met le moteur a sa position initiale
     * 
     */
    void positionInitiale();

    //void stopMotor();
    //void stopTorque();
    //void startTorque();

};

#endif
