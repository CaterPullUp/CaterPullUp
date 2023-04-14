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
    pin = DXL_DIR_PIN;
    vitesse = 0;

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

    if(currentAngle() < zero_position)
    {
        DEBUG_SERIAL.println("pos initial 1");
        DEBUG_SERIAL.println(dxl->getPresentPosition(id, UNIT_DEGREE));
        dxl->setGoalVelocity(id, VITESSE_PATTE, UNIT_PERCENT);
    }

    else
    {
        DEBUG_SERIAL.println("pos initial -1");
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
    
    //DEBUG_SERIAL.print(id);
    //DEBUG_SERIAL.print("present : ");
    //DEBUG_SERIAL.println(current_angle);
    //DEBUG_SERIAL.print("goal : ");
    //DEBUG_SERIAL.println(goal_angle);

    if(abs(currentAngle() - goal_angle) < 5)
    {
        dxl->setGoalVelocity(id, 0, UNIT_PERCENT);

        finished_movement = true;

        return true;
    }

    return false;
}

int DXL_Patte::getPins()
{
    return pin;
}

float DXL_Patte::getVitesse()
{
    return vitesse;
}

void DXL_Patte::setVitesse(float vitesse_)
{
    dxl->setGoalVelocity(id, vitesse_, UNIT_PERCENT);
    vitesse = vitesse_;
    finished_movement = false;
}

void DXL_Patte::setVitesse()
{
    dxl->setGoalVelocity(id, VITESSE_PATTE * direction, UNIT_PERCENT);
    vitesse = VITESSE_PATTE;
    finished_movement = false;
}

float DXL_Patte::currentAngle()
{
    current_angle = dxl->getPresentPosition(id, UNIT_DEGREE);
    return current_angle;
}

void DXL_Patte::incrementGoalAngle(float angle)
{
    goal_angle += angle * direction;
}

float DXL_Patte::getGoalAngle()
{
    return goal_angle;
}

float DXL_Patte::getZeroPosition()
{
    return zero_position;
}

uint8_t DXL_Patte::getID()
{
    return id;
}

int DXL_Patte::getDirection()
{
    return direction;
}
