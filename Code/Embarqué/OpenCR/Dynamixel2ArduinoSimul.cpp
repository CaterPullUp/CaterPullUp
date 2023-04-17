/***
 * @author @couj0902 @trudelle200902
 * @file Dynamixel2ArduinoSimul.cpp
 * @date 22 mars 2023
 * 
 * @brief Simule la librairie Dynamixel2Arduino.h permettant de controller des moteurs Dynamixel
***/

#ifndef ARDUINO_OpenCR
#include "Dynamixel2ArduinoSimul.h"

/**
 * @brief Initialise les positions de trois moteurs dynamixel a utiliser
 * 
 * @param serial n'affecte pas le comportement du moteur simuler
 * @param pin n'affecte pas le comportement du moteur simuler
 */
Dynamixel2Arduino::Dynamixel2Arduino(SerialSimul serial, int pin){
    current_pos[0] = 0;
    current_pos[1] = 0;
    current_pos[2] = 0;
}

/**
 * @brief change la valeur de goal position et determine la direction a tourner pour atteindre le goal
 * 
 * @param id id du moteur affecter
 * @param angle angle viser du moteur en degree
 * @param mode n'affecte pas le moteur simuler
 */
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

/**
 * @brief incremente le moteur de position et retourne cette position
 * 
 * @param id id du moteur a mettre a jour
 * @param mode n'affecte pas le moteur simuler
 * @return float 
 */
float Dynamixel2Arduino::getPresentPosition(int id,int mode){
    current_pos[id-1] += direction[id-1]*INCREMENT;
    return current_pos[id-1];
}

/**
 * @brief determine la direction du mouvement du moteur selon le signe de vitesse
 * 
 * @param id id du moteur affecter
 * @param vitesse vitesse du moteur (seulement le signe est pris en compte lors de la simulation)
 * @param mode n'affecte pas le moteur simuler
 */
void Dynamixel2Arduino::setGoalVelocity(int id, float vitesse, int mode){
    direction[id-1] = vitesse/abs(vitesse);
}

void Dynamixel2Arduino::begin(int baud_rate){}
void Dynamixel2Arduino::connectDXL(){}
void Dynamixel2Arduino::ping(int id){}
void Dynamixel2Arduino::torqueOff(int id){}
void Dynamixel2Arduino::setPortProtocolVersion(float protocol){}
void Dynamixel2Arduino::setOperatingMode(int id, int mode){}
void Dynamixel2Arduino::torqueOn(int id){}
void Dynamixel2Arduino::writeControlTableItem(int mode,int id, float vitesse){}

#endif