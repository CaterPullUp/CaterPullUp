/***
 * @author @trudelle200902
 * @file SerialSimul.h
 * @date 22 mars 2023
***/

#ifndef SERIAL_SIMUL_H
#define SERIAL_SIMUL_H
#ifndef ARDUINO_OpenCR

#include <stdio.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <ctime>
#include <chrono>
#include <stdarg.h>
#include <cstdarg>

#define BIN 0

class SerialSimul{
    private:
        char file_name[64];
    public:
        SerialSimul(std::string name);
        void begin(int baud_rate);
        void print(std::string str);
        void println(std::string str);
        void print(float val);
        void println(float val);
        void print(int val);
        void println(int val);
        void print(int val, int mode);
        void println(int val, int mode);
        bool availableForWrite();
        int available();
        void readBytes(uint8_t* buff, int nb_byte);
        void write(int i);
};

extern SerialSimul Serial;
extern SerialSimul Serial1;
extern SerialSimul Serial3;

#endif
#endif
