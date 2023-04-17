/***
 * @author @trudelle200902
 * @file test.cpp
 * @date 12 avril 2023
***/
#ifndef ARDUINO_OpenCR

#include "Arduino_function.h"
#include "Caterpullup.h"
//#include "SerialSimul.h"
#include "Uart.h"

#include "timer.h"

#define DEBUG_BAUD_RATE 115200

Caterpullup* robot;

Timer tx_data_timer;

void serialEvent1();

int main(){

    DEBUG_SERIAL.begin(DEBUG_BAUD_RATE);
    UART_SERIAL.begin(9600);
    //while(!DEBUG_SERIAL);

    //robot = Caterpullup(MODE_MANUEL);
    DEBUG_SERIAL.println("start");
    robot = new Caterpullup(MODE_AUTO);
    robot->init();

    tx_data_timer.init(TX_PERIOD, INFINITE_REPETITION);
    tx_data_timer.start();
    robot->setMode(MODE_AUTO);
    robot->setNbSequences(1);

    while(true){
        robot->gererEtat();
        robot->setMode(MODE_AUTO);
        robot->gererMoteurs();
        //if(tx_data_timer.update()){
        //    send_data();
        //    tx_data_timer.start();
        //}
        //serialEvent1();
    }
}

#endif
    
