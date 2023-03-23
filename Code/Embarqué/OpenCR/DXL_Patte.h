/***
 * @author @etiger314
 * @file DXL_Patte.h
 * @date 22 mars 2023
***/

#ifndef DXL_PATTE_H
#define DXL_PATTE_H

#define EXTEND_MOVEMENT_ANGLE 180
#define RETRACT_MOVEMENT_ANGLE 180

#include "Arduino_function.h"

#include "Dynamixel.h"
#include "Moteur.h"

class DXL_Patte : public Moteur
{
private:

    bool finished_movement;
    float current_angle;
    bool extended;
    float goal_angle;
    float zero_position;
    int id;

public:

    DXL_Patte(int id, float zero_position);

    float getVitesse();
    void setVitesse(float v);
    int getPin();

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
