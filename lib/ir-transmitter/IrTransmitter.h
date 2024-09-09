/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : IrTransmitter.h
* Description : IrTransmitter is a class that uses the SIRC protocol to transmit
                infrared data to a receiver that requires a carrier frequency of
                38kHz. A duty cycle of 25% is used in order to extend the range
                although the 220ohm resistor is limiting performance according
                to the datasheet. The SIRC protocol has been used to transmit a
                13 bit messages excluding the start bit (8 data bits, 5 address
                bits). Any data type (smaller than 255bytes) can be transmitted.
                An initial header message will be sent to give the length of the
                incoming data and when the data will be transmitted, the
                calculated crc byte will be transmitted for error detection.
* Material components used : Infrared led (Lite-On LTE 4208) and a 220ohm
                            resistor.
* Pins in input : None.
* Pins in output : OCnB pin of the specified timer.
*/

#pragma once

#include "IrReceiver.h"
#include "Timer.h"
#include "TimerPeripherals.h"

#include <avr/io.h>
#include <util/crc16.h>
#include <util/delay.h>

#define CARRIER_FREQUENCY 38000
#define CARRIER_DUTY_CYCLE 0.25f

template<TimerNumber timerNumber>
class IrTransmitter {
public:
    IrTransmitter(Timer<timerNumber>* timer,
                  const uint8_t address = DEFAULT_ADDRESS);

    template<typename T>
    void sendData(T& data, const uint8_t size = sizeof(T));
    void sendByte(uint8_t data);
    void sendByte(uint8_t data, uint8_t& crc);

private:
    void sendUnusableData();
    void sendRawBits(const uint8_t bits, const uint8_t length);
    template<uint16_t onTime>
    void sendSignal();

    Timer<timerNumber>* timer_;
    uint8_t address_;
    static constexpr uint8_t UNUSED_DATA_BYTE_LENGTH = 5;
};

#include "IrTransmitter.tpp"
