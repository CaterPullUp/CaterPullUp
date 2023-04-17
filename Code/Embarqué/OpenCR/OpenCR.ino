/***
 * @author @MarieClaude1234
 * @file main.ino
 * @date 22 janvier 2023
***/

#include "Arduino_function.h"
#include "Caterpullup.h"
#include "Uart.h"

#include "timer.h"

#define DEBUG_BAUD_RATE 115200

Caterpullup* robot;

Timer tx_data_timer;

void setup()
{
    Serial.begin(9600);
    UART_SERIAL.begin(9600);
    DEBUG_SERIAL.begin(DEBUG_BAUD_RATE);

    DEBUG_SERIAL.println("start");
    robot = new Caterpullup(MODE_MANUEL);
    robot->init();

    tx_data_timer.init(TX_PERIOD, INFINITE_REPETITION);
    tx_data_timer.start();
}

void loop() 
{
    robot->gererEtat();
    robot->gererMoteurs();
    if(tx_data_timer.update()){
      send_data(robot);
      tx_data_timer.start();
    }
}

/**
 * @brief Detecte et gere la reception de messages UART
 * 
 */
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
                Serial.println("arret complet true");
                robot->setArretComplet(true);
            }
        }
        Serial.println(msg.commande);
        Serial.println(msg.mode);
        Serial.println(msg.parite);
    }
}
