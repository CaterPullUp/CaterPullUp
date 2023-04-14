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

#if defined(ARDUINO_OpenCR)
using namespace ControlTableItem;
#endif

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

    DXL_Corps(Dynamixel2Arduino* dxl, int id);

    int getPins();
    float getVitesse();
    void setVitesse(float v);

    uint8_t getID();
    bool is_movement_finished();

    void go_to_position(float angle);

    float getGoalAngle();

    float currentAngle();

    void positionInitiale();

    //void stopMotor();
    //void stopTorque();
    //void startTorque();

};

#endif
