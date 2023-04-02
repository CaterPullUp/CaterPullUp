/***
 * @author @etiger314
 * @file DXL_Patte.cpp
 * @date 22 mars 2023
***/

#include "DXL_Corps.h"

using namespace ControlTableItem;

DXL_Corps::DXL_Corps(Dynamixel2Arduino* dxl_, int id_)// : Moteur(pin)
{
    dxl=dxl_;
    id = id_;
    finished_movement = true;
    vitesse = VITESSE_CORPS;
    pin = DXL_DIR_PIN;

    init();
}

void DXL_Corps::init()
{
    dxl->ping(id);
    dxl->torqueOff(id);
    dxl->setOperatingMode(id, OP_POSITION);
    dxl->torqueOn(id);
    dxl->writeControlTableItem(PROFILE_VELOCITY, id, VITESSE_CORPS);
}

int DXL_Corps::getPins()
{
    return pin;
}

float DXL_Corps::getVitesse()
{
    return vitesse;
}

void DXL_Corps::setVitesse(float vitesse_)
{
    dxl->writeControlTableItem(PROFILE_VELOCITY, id, vitesse_);
    vitesse = vitesse_;
}

uint8_t DXL_Corps::getID()
{
    return id;
}

bool DXL_Corps::is_movement_finished()
{
    if(finished_movement)
    {
        return true;
    }
    
    if(abs(currentAngle() - goal_angle) < 3)
    {
        finished_movement = true;

        return true;
    }

    return false;
}

void DXL_Corps::go_to_position(float angle)
{
    dxl->setGoalPosition(id, angle, UNIT_DEGREE);
    finished_movement = false;
    goal_angle = angle;
}

float DXL_Corps::getGoalAngle()
{
    return goal_angle;
}

float DXL_Corps::currentAngle()
{
    current_angle = dxl->getPresentPosition(id, UNIT_DEGREE);
    return current_angle;
}

void DXL_Corps::positionInitiale()
{
    goal_angle = ANGLE_MONTER;
    dxl->setGoalPosition(id, goal_angle, UNIT_DEGREE);
    finished_movement = false;
}