/***
 * @author @couj0902
 * @file Dynamixel2ArduinoSimul.h
 * @date 22 mars 2023
***/

#ifndef DYNAMIXEL_SIMUL_H
#define DYNAMIXEL_SIMUL_H
#ifndef ARDUINO_OpenCR

#include "Arduino_function.h"
#include <cstdlib>

#define DXL_SERIAL   Serial3
#define DXL_BAUD_RATE 57600
#define DEBUG_BAUD_RATE 115200
#define DXL_DIR_PIN 84
#define DXL_PROTOCOL_VERSION 2.0
#define OP_POSITION 0
#define OP_VELOCITY 0
#define PROFILE_VELOCITY 0
#define UNIT_DEGREE 0
#define UNIT_PERCENT 0
#define NB_MOTEUR 3
#define INCREMENT 1.0



    class Dynamixel2Arduino{
        private:

            float goal_pos[NB_MOTEUR];
            float goal_vel[NB_MOTEUR];
            float current_pos[NB_MOTEUR];
            float direction[NB_MOTEUR];
            //float position[NB_MOTEUR];
        public:
            Dynamixel2Arduino(SerialSimul serial, int pin);
            void begin(int baud_rate);
            void connectDXL();
            void ping(int id);
            void torqueOff(int id);
            void setOperatingMode(int id, int mode);
            void setPortProtocolVersion(float);
            void torqueOn(int id);
            void writeControlTableItem(int mode,int id, float vitesse);
            void setGoalPosition(int id, float angle,int mode);
            float getPresentPosition(int id,int mode);
            void setGoalVelocity(int id, float vitesse, int mode);
    };

    #endif
    #endif