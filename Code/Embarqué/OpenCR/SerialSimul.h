/***
 * @author @trudelle200902
 * @file Dynamixel2ArduinoSimul.h
 * @date 22 mars 2023
***/

#ifndef SERIAL_SIMUL_H
#define SERIAL_SIMUL_H

#include <stdio.h>
#include <string>
#include <cstring>
#include <ctime>
#include <chrono>

class SerialSimul{
    private:
        FILE *fptr;
    public:
        //Serial();
        void begin(int baud_rate);
        void print(std::string str);
        void println(std::string str);
        void print(float val);
        void println(float val);
};

//extern SerialSimul* Serial;
//extern SerialSimul* Serial3;
extern SerialSimul Serial;
extern SerialSimul Serial3;

#endif