/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-03-08

* Name of file : Communication.h
* Description : Enables the robot to transmit and receive data to and from the
computer.
* Material components used : Peripheral UART0. Jumper DbgEn.
* Pins in input : None.
* Pins in output : PD1 (TXD0/transmitter 0 pin)
*/

#pragma once

#include <avr/io.h>
#include <stdlib.h>

class Communication {
public:
    Communication();

    static Communication& getInstance();

    void transmit(const char* message);
    void transmit(const unsigned char* message);
    void transmit(uint16_t number);
    void transmitBytes(const uint8_t data[], uint8_t taille);

    uint8_t receive(void);

private:
    void transmitByte(uint8_t data);

    static Communication instance_;
    static constexpr uint8_t MAX_DIGITS_16_BIT = 6; // 5 digits + '\0'
    static constexpr uint8_t RADIX = 10;
};
