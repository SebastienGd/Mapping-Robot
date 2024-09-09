/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : IrReceiver.h
* Description : IrReceiver is a class that is used to receive data of any type
                using the SIRC protocol. The receiver requires a carrier
                frequency of 38kHz. Error checking is implemented. An invalid
                address or a message that could not be processed will be ignored.
ignored.
* Material components used : Infrared Receiver (PNA4601M).
* Pins in input : Any pin can be used.
* Pins in output : None.
*/

#pragma once
#include "Timer.h"

#include <avr/io.h>
#include <stdlib.h>
#include <util/crc16.h>
#include <util/delay.h>

#define BITS_IN_BYTE 8
#define ADDRESS_LENGHT 5
#define TRANSMISSION_SIZE ADDRESS_LENGHT + BITS_IN_BYTE
#define DEFAULT_ADDRESS 0b1'0100

#define PULSE_OFF_DURATION_US 600
#define LOGICAL_0_ON_DURATION_US 600
#define LOGICAL_1_ON_DURATION_US 1200
#define START_BIT_ON_DURATION_US 2400

enum class SignalType {
    START_BIT,
    LOGICAL_1,
    LOGICAL_0,
    IGNORABLE_NOISE,
    SIGNIFICANT_NOISE,
    OFF_PULSE,
};

template<TimerNumber timerNumber>
class IrReceiver {
public:
    IrReceiver(Timer<timerNumber>& timer,
               register8_t& inputPort,
               register8_t& ddrX,
               uint8_t pinNumber,
               const uint8_t address = DEFAULT_ADDRESS);

    template<typename T>
    bool tryReceiveData(T* dataBuffer, uint8_t* bufferSize);

private:
    bool hasEdgeChanged();
    void confirmEdgeChanged();

    bool tryReceiveNextByte(uint8_t* buffer);
    void processSignal(uint8_t& signalCounter, uint16_t& rawMessageBuffer);
    SignalType getSignalType(uint8_t& signalCounter);
    bool areSignalsEquivalent(const int16_t& signalA, const int16_t& signalB);

    Timer<TimerNumber::TIMER_1>* timer_;
    register8_t* inputPort_;
    const uint8_t pinNumber_, address_;
    uint8_t edgeChangeCounter_;
    bool signalIsHigh_;

    // the biggest deviation that was caught on the oscilloscope was 230us on a
    // start bit, so we put 300us to be safe
    static constexpr uint16_t SIGNAL_DURATION_US_TOLERANCE = 300;
    static constexpr uint8_t NBR_OF_EDGE_SAMPLES =
        20; // found by trials and errors
    static constexpr uint8_t DELAY_US_BETWEEN_SAMPLES =
        2; // found by trials and errors
};

#include "IrReceiver.tpp"
