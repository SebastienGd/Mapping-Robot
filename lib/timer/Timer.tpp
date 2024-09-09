
#include "Timer.h"

template<TimerNumber timerNumber>
Timer<timerNumber>::Timer() {
    setPrescaler(SpecificConfiguration<timerNumber>::Prescaler::NO_CLK);
}

template<TimerNumber timerNumber>
void Timer<timerNumber>::setWaveformMode(const WaveformMode& mode) {
    *timerRegisters_.TCNTn = 0;
    uint8_t is16BitsTimer = sizeof(*timerRegisters_.TCNTn) == sizeof(uint16_t);

    if(is16BitsTimer)
        *timerRegisters_.TCCRnC = 0;

    // configure WGM1:0, in TCCRnA
    configureRegister(
        timerRegisters_.TCCRnA,
        WGM_A_BIT_FIELD,
        SpecificConfiguration<timerNumber>::getWgmConfigurationA(mode));

    // configure WGM3:2, in TCCRnB
    configureRegister(
        timerRegisters_.TCCRnB,
        WGM_B_BIT_FIELD(is16BitsTimer),
        SpecificConfiguration<timerNumber>::getWgmConfigurationB(mode));
}

template<TimerNumber timerNumber>
void Timer<timerNumber>::setPrescaler(
    const typename SpecificConfiguration<timerNumber>::Prescaler& prescaler) {
    prescalerValue_ =
        SpecificConfiguration<timerNumber>::getPrescalerValue(prescaler);
    configureRegister(timerRegisters_.TCCRnB, PRESCALER_BIT_FIELD, prescaler);
}

template<TimerNumber timerNumber>
void Timer<timerNumber>::setOutputCompareMode(
    const OutputCompareMode& mode, const OutputCompareChannel& channel) {
    configureRegister(timerRegisters_.TCCRnA, channel, mode & channel);
}

template<TimerNumber timerNumber>
void Timer<timerNumber>::toggleTimerInterrupt(
    const InterruptMode& mode,
    const bool toggleOn) {
    configureRegister(timerRegisters_.TIMSKn, mode, (toggleOn ? mode : 0));
}

template<TimerNumber timerNumber>
void Timer<timerNumber>::setOCRnX(const OutputCompareChannel& channel,
                                  const uint16_t value) {
    if(channel == OutputCompareChannel::A)
        *timerRegisters_.OCRnA = value;
    else
        *timerRegisters_.OCRnB = value;
}

template<TimerNumber timerNumber>
register16_t& Timer<timerNumber>::accessCounter() {
    return *timerRegisters_.TCNTn;
}

template<TimerNumber timerNumber>
void Timer<timerNumber>::configureRegister(register8_t* timerRegister,
                                           uint8_t bitField,
                                           uint8_t value) {
    // clear the bitfield before assigning the value
    *timerRegister &= ~bitField;
    *timerRegister |= value;
}

template<TimerNumber timerNumber>
uint16_t Timer<timerNumber>::frequencyToClockCycles(const double& frequency) {
    if(prescalerValue_ == 0) // preventing a division by 0
        return 0;
    return 1 / frequency * F_CPU / prescalerValue_;
}

template<TimerNumber timerNumber>
uint16_t Timer<timerNumber>::timeToClockCycles(const double& time,
                                               const TimeUnit& timeUnit) {
    if(prescalerValue_ == 0) // preventing a division by 0
        return 0;
    return time / timeUnit * F_CPU / prescalerValue_;
}

template<TimerNumber timerNumber>
uint16_t Timer<timerNumber>::clockCyclesToTime(const uint16_t& clockCycles,
                                               const TimeUnit& timeUnit) {
    return static_cast<const double>(clockCycles) * prescalerValue_ / F_CPU *
           timeUnit;
}
