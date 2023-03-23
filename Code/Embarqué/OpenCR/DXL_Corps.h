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

class DXL_Corps : public Moteur
{
private:

    float zero_position;
    bool down;
    int id;

public:

    DXL_Corps(int id, float zero_position);

    int getPin();
    float getVitesse();
    void setVitesse(float v);

    void setZeroPosition(float angle);
    float getZeroPosition();

    void stopMotor();
    void stopTorque();
    void startTorque();

};

#endif
