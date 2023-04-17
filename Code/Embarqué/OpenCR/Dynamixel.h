/***
 * @author @etiger314 @trudelle200902
 * @file Dynamixel.h
 * @date 22 mars 2023
***/

#ifndef DYNAMIXEL_H
#define DYNAMIXEL_H

#include "Arduino_function.h"

#if defined(ARDUINO_OpenCR)
#include <Dynamixel2Arduino.h>
#else
#include "Dynamixel2ArduinoSimul.h"
#endif

#define DXL_SERIAL Serial3
#define DXL_BAUD_RATE 57600
#define DEBUG_BAUD_RATE 115200
#define DXL_DIR_PIN 84
#define DXL_PROTOCOL_VERSION 2.0

#endif
