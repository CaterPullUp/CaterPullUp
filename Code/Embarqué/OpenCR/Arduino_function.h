/***
 * @author @etiger314
 * @file Arduino_function.h
 * @date 22 mars 2023
***/

#ifndef ARDUINO_FUNCTION_H
#define ARDUINO_FUNCTION_H

#if defined(ARDUINO_OpenCR)
#include <Arduino.h>
#define DEBUG_SERIAL Serial
#else
#define digitalWrite(A,B)
#define digitalRead(A)
#define pinMode(A,B)
#define Dynamixel2Arduino
#define dxl(A,B)
#define DEBUG_SERIAL
#endif

#endif