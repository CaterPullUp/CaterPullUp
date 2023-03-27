/***
 * @author @etiger314
 * @file Dynamixel.h
 * @date 22 mars 2023
***/

#ifndef DYNAMIXEL_H
#define DYNAMIXEL_H

#include "Arduino_function.h"
#include <Dynamixel2Arduino.h>

#define DXL_SERIAL   Serial3
#define DXL_BAUD_RATE 57600
#define DEBUG_BAUD_RATE 115200
#define DXL_DIR_PIN 84
#define DXL_PROTOCOL_VERSION 2.0

//Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

static Dynamixel2Arduino* connectDXL()
{
    Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
    dxl.begin(DXL_BAUD_RATE);
    dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
    return &dxl;
}

#endif
