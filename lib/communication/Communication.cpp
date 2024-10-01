/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-03-08
*
* Name of file : Communication.cpp
* Description : Enables the robot to transmit and receive data to and from the
*               computer.
* Material components used : Peripheral UART0 and Jumper DbgEn.
* Pins in input : None.
* Pins in output : PD1 (TXD0/transmitter 0 pin)
*/

#include "Communication.h"
#include <util/delay.h>
#include <avr/io.h>

#ifndef F_CPU
# define F_CPU 8000000
#endif

Communication Communication::instance_;

Communication::Communication() {
    // 2400 baud rate
    UBRR0H = 0;
    UBRR0L = 0xCF;

    // Set the number of data bits to 8-bit
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
    UCSR0B &= ~(1 << UCSZ02);
    // 1 stop bit
    UCSR0C &= ~(1 << USBS0);
    // Parity mode disabled
    UCSR0C &= ~((1 << UPM01) | (1 << UPM00));
    // Asynchronous mode
    UCSR0C &= ~((1 << UMSEL01) | (1 << UMSEL00));
    // Enable transmitter and reciever
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
}

void Communication::transmitByte(uint8_t data) {
    // Wait for empty transmit buffer
    while(!(UCSR0A & (1 << UDRE0))) {}

    // Put data into buffer, sends the data
    UDR0 = data;
    _delay_ms(TRANSMIT_BYTE_DELAY_MS);
}

Communication& Communication::getInstance() {
    return instance_;
}

void Communication::transmit(const char* message) {
    for(uint16_t i = 0; message[i] != '\0'; i++)
        Communication::transmitByte(message[i]);
}

void Communication::transmit(const unsigned char* message) {
    for(uint16_t i = 0; message[i] != '\0'; i++)
        Communication::transmitByte(message[i]);
}

void Communication::transmit(uint16_t number) {
    char message[MAX_DIGITS_16_BIT] = {};
    transmit(itoa(number, message, RADIX));
}

uint8_t Communication::receive(void) {
    /* Wait for data to be received */
    while(!(UCSR0A & (1 << RXC0)))
        ;

    /* Get and return received data from buffer */
    return UDR0;
}

void Communication::transmitBytes(const uint8_t data[], uint8_t taille) {
    for(uint16_t i = 0; i < taille; i++)
        Communication::transmitByte(data[i]);
}
