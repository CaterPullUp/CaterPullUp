/***
 * @author @MarieClaude1234
 * @file main.ino
 * @date 22 janvier 2023
***/

#include "Arduino_function.h"
#include "Caterpullup.h"

#define DEBUG_BAUD_RATE 115200

Caterpullup* robot;

void setup()
{
    DEBUG_SERIAL.begin(DEBUG_BAUD_RATE);
    while(!DEBUG_SERIAL);

    //robot = Caterpullup(MODE_MANUEL);
    DEBUG_SERIAL.println("start");
    robot = new Caterpullup(MODE_MANUEL);
    robot->init();
}

void loop() 
{
    robot->gererEtat();
    //robot->gererMoteurs();
}
