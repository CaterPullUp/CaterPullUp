/***
 * @author @MarieClaude1234
 * @file main.ino
 * @date 22 janvier 2023
***/

// #include <Arduino.h>
#include "Caterpullup.h"

Caterpullup robot;

void setup() {
    //Serial.begin(9600);

    robot = Caterpullup(MODE_AUTO);
}


void loop() {
    robot.gererEtat();
}