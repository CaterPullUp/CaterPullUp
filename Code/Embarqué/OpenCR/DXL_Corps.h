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

#define VITESSE_CORPS 5  ///////////

class DXL_Corps : public Moteur
{
private:

    float zero_position;
    Dynamixel2Arduino* dxl;
    bool down;
    int id;

public:

    DXL_Corps(Dynamixel2Arduino* dxl, int id, float zero_position);

    int getPins();
    float getVitesse();
    void setVitesse(float v);

    void setZeroPosition(float angle);
    float getZeroPosition();

    void stopMotor();
    void stopTorque();
    void startTorque();

};

#endif
