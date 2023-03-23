/***
 * @author @etiger314
 * @file Dynamixel.h
 * @date 22 mars 2023
***/

#ifndef DYNAMIXEL_H
#define DYNAMIXEL_H

#include "Arduino_function.h"

#define DXL_SERIAL   Serial3
#define DXL_BAUD_RATE 57600
#define DEBUG_BAUD_RATE 115200
#define DXL_DIR_PIN 84
#define DXL_PROTOCOL_VERSION 2.0

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

static void connectDXL()
{
    //dxl.begin(DXL_BAUD_RATE);
    //dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
}

#endif
