#ifndef UART_H
#define UART_H

#include "Arduino_function.h"
#include "Caterpullup.h"

#define RX_BUFF_LENGTH 1
#define TX_PERIOD 2000
#define UART_SERIAL Serial1

struct uart_recu{
    bool mode : 1;
    uint8_t commande : 6;
    bool parite : 1;
};

struct uart_recu read_uart(int buff_size);
void send_data();
struct uart_recu traiter_msg(uint8_t data);


#endif