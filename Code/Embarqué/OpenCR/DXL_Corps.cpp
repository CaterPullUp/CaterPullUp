/***
 * @author @etiger314
 * @file DXL_Patte.cpp
 * @date 22 mars 2023
***/

#include "DXL_Corps.h"

DXL_Corps::DXL_Corps(Dynamixel2Arduino* dxl_, int id, float zero_position)// : Moteur(pin)
{
    dxl=dxl_;
}

int DXL_Corps::getPins()
{
    return DXL_DIR_PIN;
}

float DXL_Corps::getVitesse()
{
    return dxl->getPresentVelocity(id, UNIT_PERCENT);
}

void DXL_Corps::setVitesse(float vitesse)
{
    dxl->setGoalVelocity(id, vitesse, UNIT_PERCENT);
}
