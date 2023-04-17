/***
 * @author @couj0902
 * @file Dynamixel2ArduinoSimul.cpp
 * @date 22 mars 2023
***/

#ifndef ARDUINO_OpenCR
#include "Dynamixel2ArduinoSimul.h"

//using namespace ControlTableItem;

Dynamixel2Arduino::Dynamixel2Arduino(SerialSimul serial, int pin){
    //float goal_pos;
    //float goal_vel;
    //current_pos = 0.0;
    current_pos[0] = 0;
    current_pos[1] = 0;
    current_pos[2] = 0;
    //float direction;
}

void Dynamixel2Arduino::begin(int baud_rate){}
void Dynamixel2Arduino::connectDXL(){}
void Dynamixel2Arduino::ping(int id){}
void Dynamixel2Arduino::torqueOff(int id){}
void Dynamixel2Arduino::setPortProtocolVersion(float protocol){}
void Dynamixel2Arduino::setOperatingMode(int id, int mode){}
void Dynamixel2Arduino::torqueOn(int id){}
void Dynamixel2Arduino::writeControlTableItem(int mode,int id, float vitesse){}

void Dynamixel2Arduino::setGoalPosition(int id, float angle,int mode){

    goal_pos[id-1] = angle;
    if (current_pos[id-1] > goal_pos[id-1]){
        direction [id-1]= -1.0;
    }
    else if (current_pos[id-1] < goal_pos[id-1]){
        direction[id-1] = 1.0;
    }
    else{
        direction[id-1] = 0.0;
    } 

}

float Dynamixel2Arduino::getPresentPosition(int id,int mode){
    current_pos[id-1] += direction[id-1]*INCREMENT;
    return current_pos[id-1];
}

void Dynamixel2Arduino::setGoalVelocity(int id, float vitesse, int mode){
    direction[id-1] = vitesse/abs(vitesse);
}
#endif
