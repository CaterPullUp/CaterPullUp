/***
 * @author @etiger314
 * @file DXL_Patte.h
 * @date 22 mars 2023
***/

#ifndef DXL_PATTE_H
#define DXL_PATTE_H

#define EXTEND_MOVEMENT_ANGLE 200
#define RETRACT_MOVEMENT_ANGLE 160
#define VITESSE_PATTE 10

#include "Arduino_function.h"

#include "Dynamixel.h"
#include "Moteur.h"

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

    DXL_Patte(Dynamixel2Arduino* dxl, int id_, float zero_position_, int direction_);

    void positionInitiale();

    float getVitesse();
    void setVitesse(float v);
    int getPins();

    bool is_movement_finished();
    float getCurrentAngle();
    bool is_extended();
    void incrementGoalAngle(float angle);
    float getGoalAngle();
    void setZeroPosition(float angle);
    float getZeroPosition();
    void stopMotor();
    void stopTorque();
    void startTorque();
    bool getTorque();
    uint8_t getID();
};

#endif
