/***
 * @author @trudelle200902
 * @file Uart.h
 * @date 27 mars  2023
***/


#ifndef UART_H
#define UART_H

#include "Arduino_function.h"
#include "Caterpullup.h"

#define RX_BUFF_LENGTH 1
#define TX_PERIOD 1000
#define UART_SERIAL Serial1

struct uart_recu{
    bool mode : 1;
    uint8_t commande : 6;
    bool parite : 1;
};

/**
 * @brief Lit les messages recus par UART
 * 
 * @param buff_size Longueur d'un message en octets
 * @return struct uart_recu Structure du message traite
 */
struct uart_recu read_uart(int buff_size);

/**
 * @brief Envoi les messages vers l'ESP32
 * 
 * @param robot pointeur de l'objet Caterpullup
 */
void send_data(Caterpullup* robot);

/**
 * @brief Interprete les messages recus
 * 
 * @param data Message recu
 * @return struct uart_recu Structure du message traite
 */
struct uart_recu traiter_msg(uint8_t data);


#endif