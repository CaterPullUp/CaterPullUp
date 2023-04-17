/***
 * @author @MarieClaude1234
 * @file Uart.cpp
 * @date 12 avril 2023
***/

#include "Uart.h"

struct uart_recu read_uart(int buff_size){
  //size_t msg_length = 0;
  uint8_t rx_data;
  if(UART_SERIAL.available() >= buff_size){
    Serial.println("SerialEvent");
    UART_SERIAL.readBytes(&rx_data, 1);
    Serial.println((int) rx_data, BIN);
    return traiter_msg(rx_data);

  }
  struct uart_recu retour = {0,0,0};
  return retour;
}

void send_data(Caterpullup* robot){
    Serial.println("in send data");
    while(!UART_SERIAL.availableForWrite()){}
    struct uart_envoi msg = robot->prepMessage();

    uint8_t data[2];
    data[0] = (msg.SOF << 7) + (msg.mode << 6) + (msg.commande);
    data[1] = (msg.etape << 5) + (msg.electro1 << 4) + (msg.electro2 << 3) + (msg.electro3 << 2) + (msg.parite) + (msg.END);
        
    UART_SERIAL.write(data, 2);
    Serial.println("message sent");
}

struct uart_recu traiter_msg(uint8_t data){
    struct uart_recu msg;
    msg.mode = (data & 0b10000000) >> 7;
    msg.commande = (data & 0b01111110) >> 1;
    msg.parite = (data & 0b00000001);
    return msg;
}
