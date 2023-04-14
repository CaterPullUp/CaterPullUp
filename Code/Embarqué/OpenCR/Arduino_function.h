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
#include "SerialSimul.h"

#define DEBUG_SERIAL (*Serial)

#include <cstdint>
#include <sys/time.h>

long inline get_time(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return (long)tp.tv_sec * 1000L + tp.tv_usec / 1000;
}

#define millis get_time
    
#endif

#define DEBUG_SERIAL Serial

#endif
