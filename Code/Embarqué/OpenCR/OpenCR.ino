/***
 * @author @MarieClaude1234
 * @file main.ino
 * @date 22 janvier 2023
***/

#include "Arduino_function.h"
#include "Caterpullup.h"
#include "Uart.h"

#include "timer.h"

// #define UART_SERIAL Serial1
#define DEBUG_BAUD_RATE 115200
// #define RX_BUFF_LENGTH 256
// #define TX_PERIOD 2000

// void read_uart(byte *rx_data, int buff_size);
// void send_data();


Caterpullup* robot;

Timer tx_data_timer;

void setup()
{
    Serial.begin(9600);
    UART_SERIAL.begin(9600);
    DEBUG_SERIAL.begin(DEBUG_BAUD_RATE);
    // while(!DEBUG_SERIAL);
    //while(!Serial);

    //robot = Caterpullup(MODE_MANUEL);
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
      send_data();
      tx_data_timer.start();
    }
}

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


// void read_uart(byte *rx_data, int buff_size){
//   //size_t msg_length = 0;
//   if(UART_SERIAL.available()){
//     *rx_data = UART_SERIAL.read();
//   }
// }

// void send_data(){
//   while(!UART_SERIAL.availableForWrite()){}
//   UART_SERIAL.write(2);
// }
