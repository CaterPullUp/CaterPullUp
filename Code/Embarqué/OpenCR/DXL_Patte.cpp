/***
 * @author @etiger314
 * @file DXL_Patte.cpp
 * @date 22 mars 2023
***/

#include "DXL_Patte.h"

DXL_Patte::DXL_Patte(Dynamixel2Arduino* dxl_, int id_, float zero_position_, int direction_)// : Moteur(pin)
{
    id = id_;
    zero_position = zero_position_;
    direction = direction_;
    finished_movement = true;
    dxl = dxl_;

    init();
}

void DXL_Patte::init()
{
    dxl->ping(id);
    dxl->torqueOff(id);
    dxl->setOperatingMode(id, OP_VELOCITY);
    dxl->torqueOn(id);
}

void DXL_Patte::positionInitiale()
{
    goal_angle = zero_position;

    if(dxl->getPresentPosition(id, UNIT_DEGREE) < zero_position)
    {
        dxl->setGoalVelocity(id, VITESSE_PATTE, UNIT_PERCENT);
    }

    else
    {
        dxl->setGoalVelocity(id, -1 * VITESSE_PATTE, UNIT_PERCENT);
    }

    finished_movement = false;
}

bool DXL_Patte::is_movement_finished()
{
    if(finished_movement)
    {
        return true;
    }

    if(abs(dxl->getPresentPosition(id, UNIT_DEGREE) - goal_angle) < 3)
    {
        dxl->setGoalVelocity(id, 0, UNIT_PERCENT);

        finished_movement = true;

        return true;
    }

    return false;
}

int DXL_Patte::getPins()
{
    return DXL_DIR_PIN;
}

float DXL_Patte::getVitesse()
{
    return dxl->getPresentVelocity(id, UNIT_PERCENT);
}

void DXL_Patte::setVitesse(float vitesse)
{
    dxl->setGoalVelocity(id, vitesse, UNIT_PERCENT);
}
