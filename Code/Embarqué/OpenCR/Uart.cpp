#include "Uart.h"

struct uart_recu read_uart(int buff_size){
  uint8_t rx_data;
  if(UART_SERIAL.available() >= 1){
    UART_SERIAL.readBytes(&rx_data, 1);
    Serial.println((int) rx_data, BIN);
    return traiter_msg(rx_data);

  }
  struct uart_recu retour = {0,0,0};
  return retour;
}

void send_data(){
  while(!UART_SERIAL.availableForWrite()){}
  UART_SERIAL.write(2);
}

struct uart_recu traiter_msg(uint8_t data){
    struct uart_recu msg;
    msg.mode = (data & 0b10000000) >> 7;
    msg.commande = (data & 0b01111110) >> 1;
    msg.parite = (data & 0b00000001);
    return msg;
}
