/***
 * @author @trudelle200902
 * @file test.cpp
 * @date 12 avril 2023
***/

#include "Arduino_function.h"
#include "Caterpullup.h"
#include "SerialSimul.h"

#define DEBUG_BAUD_RATE 115200

Caterpullup* robot;

int main(){

    DEBUG_SERIAL.begin(DEBUG_BAUD_RATE);
    //while(!DEBUG_SERIAL);

    //robot = Caterpullup(MODE_MANUEL);
    DEBUG_SERIAL.println("start");
    robot = new Caterpullup(MODE_AUTO);
    robot->init();

    while(true){
        robot->gererEtat();
        robot->gererMoteurs();
    }
}