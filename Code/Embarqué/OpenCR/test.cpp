/***
 * @author @trudelle200902
 * @file test.cpp
 * @date 12 avril 2023
***/

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
/*
void serialEvent1() {
    struct uart_recu msg = read_uart(RX_BUFF_LENGTH);
    
    if(!(msg.mode == 0 && msg.commande == 0 && msg.parite == 0)){
        robot->setMode(msg.mode);
        if (msg.mode == 0){
            robot->set_commande_GUI(msg.commande);
        }
        else{
            robot->setNbSequences(msg.commande);
            robot->set_commande_GUI(14);
            if (msg.commande == 63){//Arret complet
                //Serial.println("arret complet true");
                robot->setArretComplet(true);
            }
        }
        //Serial.println(msg.commande);
        //Serial.println(msg.mode);
        //Serial.println(msg.parite);
    }
}*/