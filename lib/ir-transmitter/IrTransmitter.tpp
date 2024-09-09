#include "IrTransmitter.h"

template<TimerNumber timerNumber>
IrTransmitter<timerNumber>::IrTransmitter(Timer<timerNumber>* timer,
                                          const uint8_t address):
    timer_(timer),
    address_(address) {
    cli();
    TimerPeripherals<timerNumber>::setPinToOutput(OutputCompareChannel::B);
    timer_->setPrescaler(
        SpecificConfiguration<timerNumber>::Prescaler::DIVISOR_1);
    timer_->setOutputCompareMode(OutputCompareMode::CLEAR,
                                 OutputCompareChannel::B);
    uint16_t OCCRnAValue =
        timer_->frequencyToClockCycles(CARRIER_FREQUENCY) / 2;
    timer_->setOCRnX(OutputCompareChannel::B, OCCRnAValue * CARRIER_DUTY_CYCLE);
    timer_->setOCRnX(OutputCompareChannel::A, OCCRnAValue);
    timer_->setOutputCompareMode(OutputCompareMode::NORMAL,
                                 OutputCompareChannel::B);
    timer_->setWaveformMode(WaveformMode::PHASE_CORRECT_PWM_OCRNA_TOP);
    sei();
}

template<TimerNumber timerNumber>
template<typename T>
void IrTransmitter<timerNumber>::sendData(T& data, const uint8_t size) {
    // send unusable data to make the receiver get out of its idle mode then
    // send the size of the data, the data and then the calculated crc
    uint8_t* bytes = reinterpret_cast<uint8_t*>(&data);
    uint8_t crc = __UINT8_MAX__;

    sendUnusableData();
    sendByte(size, crc);
    
    for(uint8_t i = 0; i < size; ++i)
        sendByte(bytes[i], crc);
    sendByte(crc);
}

template<TimerNumber timerNumber>
void IrTransmitter<timerNumber>::sendByte(uint8_t data) {
    sendSignal<START_BIT_ON_DURATION_US>();
    sendRawBits(data, BITS_IN_BYTE);
    sendRawBits(address_, ADDRESS_LENGHT);
}

template<TimerNumber timerNumber>
void IrTransmitter<timerNumber>::sendByte(uint8_t data, uint8_t& crc) {
    crc = _crc16_update(crc, data);
    sendByte(data);
}

template<TimerNumber timerNumber>
void IrTransmitter<timerNumber>::sendUnusableData() {
    // this function sends unusable data to the receiver with an invalid address
    // in order to make it get out of its idle mode where noise is heavy, this
    // behavior was observed using the single trigger mode of the oscilloscope,
    // and the receiver is less reliable without doing that
    uint8_t oldAddress = address_;
    address_ ^= __UINT8_MAX__;
    uint8_t bytes[UNUSED_DATA_BYTE_LENGTH] = {};
    for(uint8_t i = 0; i < UNUSED_DATA_BYTE_LENGTH; ++i)
        sendByte(bytes[i]);
    address_ = oldAddress;
}

template<TimerNumber timerNumber>
void IrTransmitter<timerNumber>::sendRawBits(const uint8_t bits,
                                             const uint8_t length) {
    for(uint8_t i = 0; i < length; ++i)
        if(bits & (1 << i))
            sendSignal<LOGICAL_1_ON_DURATION_US>();
        else
            sendSignal<LOGICAL_0_ON_DURATION_US>();
}

template<TimerNumber timerNumber>
template<uint16_t onTime>
void IrTransmitter<timerNumber>::sendSignal() {
    timer_->setOutputCompareMode(OutputCompareMode::CLEAR,
                                 OutputCompareChannel::B);
    _delay_us(onTime);
    timer_->setOutputCompareMode(OutputCompareMode::NORMAL,
                                 OutputCompareChannel::B);
    _delay_us(PULSE_OFF_DURATION_US);
}
