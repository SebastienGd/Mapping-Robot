/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : IrReceiver.cpp
* Description : This header file defines all functions for the IrReceiver class
used for receiving informations from the second robot,
* using an infrared receiver.
* Material components used : Infrared Receiver.
* Pins in input : None.
* Pins in output : Depends on Timer used (PWM pins), Ground PIN.
*/

#include "IrReceiver.h"

template<TimerNumber timerNumber>
IrReceiver<timerNumber>::IrReceiver(Timer<timerNumber>& timer,
                                    register8_t& inputPort,
                                    register8_t& ddrX,
                                    uint8_t pinNumber,
                                    const uint8_t address):
    timer_(&timer),
    inputPort_(&inputPort),
    pinNumber_(pinNumber),
    address_(address),
    edgeChangeCounter_(0),
    signalIsHigh_(true) {
    timer_->setWaveformMode(WaveformMode::NORMAL_OPERATION);
    timer_->setPrescaler(
        SpecificConfiguration<TimerNumber::TIMER_1>::Prescaler::DIVISOR_256);
    ddrX &= ~(1 << pinNumber);
}

template<TimerNumber timerNumber>
template<typename T>
bool IrReceiver<timerNumber>::tryReceiveData(T* dataBuffer,
                                             uint8_t* bufferSize) {
    uint8_t index = 0;
    uint8_t transmittedDataSize = 0;
    uint8_t crc = __UINT8_MAX__;

    // receive then compare the transmitted size
    while(!tryReceiveNextByte(&transmittedDataSize)) {}
    if(transmittedDataSize > *bufferSize)
        return false;
    *bufferSize = transmittedDataSize;

    // receive data and calculate crc
    crc = _crc16_update(crc, transmittedDataSize);
    index = 0;
    while(index < transmittedDataSize) {
        if(tryReceiveNextByte(&reinterpret_cast<uint8_t*>(dataBuffer)[index])) {
            crc = _crc16_update(crc,
                                reinterpret_cast<uint8_t*>(dataBuffer)[index]);
            ++index;
        }
    }

    // receive the transmitted crc and compare it with what we calculated
    uint8_t transmittedCrc;
    while(!tryReceiveNextByte(&transmittedCrc)) {}
    return transmittedCrc == crc;
}

template<TimerNumber timerNumber>
bool IrReceiver<timerNumber>::tryReceiveNextByte(uint8_t* buffer) {
    uint8_t signalCounter = 0;
    uint16_t rawMessageBuffer = 0;
    edgeChangeCounter_ = 0;
    signalIsHigh_ = true;

    // receive full 14 bit message (start bit + 8 bit command + 5 bit address)
    while(signalCounter <= TRANSMISSION_SIZE) {
        if(hasEdgeChanged())
            processSignal(signalCounter, rawMessageBuffer);
        _delay_us(3);
    }
    // process data if it corresponds to the address of the receiver
    if((rawMessageBuffer >> BITS_IN_BYTE) == address_) {
        *buffer = rawMessageBuffer & __UINT8_MAX__;
        return true;
    }
    return false;
}

template<TimerNumber timerNumber>
bool IrReceiver<timerNumber>::hasEdgeChanged() {
    if((signalIsHigh_ << pinNumber_) ^ ((*inputPort_) & (1 << pinNumber_)))
        ++edgeChangeCounter_;
    else
        edgeChangeCounter_ = 0;

    return edgeChangeCounter_ > NBR_OF_EDGE_SAMPLES;
}

template<TimerNumber timerNumber>
void IrReceiver<timerNumber>::confirmEdgeChanged() {
    edgeChangeCounter_ = 0;
    signalIsHigh_ = !signalIsHigh_;
    timer_->accessCounter() = 0;
}

template<TimerNumber timerNumber>
void IrReceiver<timerNumber>::processSignal(uint8_t& signalCounter,
                                            uint16_t& dataBuffer) {
    SignalType signal = getSignalType(signalCounter);
    switch(signal) {
        case SignalType::START_BIT:
            signalCounter = 1;
            confirmEdgeChanged();
            break;

        case SignalType::LOGICAL_1:
            if(signalCounter != 0) {
                dataBuffer |= 1 << (signalCounter++ - 1);
                confirmEdgeChanged();
            }
            break;

        case SignalType::LOGICAL_0:
            if(signalCounter != 0) {
                dataBuffer &= ~(1 << (signalCounter++ - 1));
                confirmEdgeChanged();
            }
            break;

        case SignalType::OFF_PULSE:
            confirmEdgeChanged();
            break;

        case SignalType::IGNORABLE_NOISE:
            break;

        case SignalType::SIGNIFICANT_NOISE:
            // we assume that we were reading invalid signals, so we omit what
            // we read about the byte by reseting the signalCounter
            signalCounter = 0;
            break;
    }
}

template<TimerNumber timerNumber>
SignalType IrReceiver<timerNumber>::getSignalType(uint8_t& signalCounter) {
    uint16_t signalDuration = timer_->clockCyclesToTime(
        reinterpret_cast<uint16_t>(timer_->accessCounter()),
        TimeUnit::MICROSECONDS);

    if(signalIsHigh_) {
        if(signalCounter == 0 ||
           areSignalsEquivalent(signalDuration, PULSE_OFF_DURATION_US))
            return SignalType::OFF_PULSE;
    } else if(areSignalsEquivalent(signalDuration, LOGICAL_0_ON_DURATION_US))
        return SignalType::LOGICAL_0;
    else if(areSignalsEquivalent(signalDuration, LOGICAL_1_ON_DURATION_US))
        return SignalType::LOGICAL_1;
    else if(areSignalsEquivalent(signalDuration, START_BIT_ON_DURATION_US))
        return SignalType::START_BIT;

    return (signalDuration > START_BIT_ON_DURATION_US) ?
               SignalType::SIGNIFICANT_NOISE :
               SignalType::IGNORABLE_NOISE;
}

template<TimerNumber timerNumber>
bool IrReceiver<timerNumber>::areSignalsEquivalent(const int16_t& signalA,
                                                   const int16_t& signalB) {
    return abs(signalA - signalB) < SIGNAL_DURATION_US_TOLERANCE;
}
