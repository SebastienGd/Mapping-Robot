/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-03-27

* Name of file : Timer.h
* Description : This template class allows the use of any of the 3 available
                timers on the ATmega324PA (Timer0/1/2). The Waveform mode,
                prescaler, output compare mode(for OCnA/B) can be configured.
                This class also makes it easy to toggle a few timer interupts
                but implementing an external ISR function will be needed to make
                use of it. It is also possible to convert a time(ms,us) to clock
                cycles to minimize unintuitive calculations. More information
                about the waveform modes, prescalers, output compare modes and
                timer interupt modes can be found in TimerConfigurations.h and
                TimerSpecificConfigurations.h
* Material components used : none
* Pins in input : none
* Pins in output : OC0A/B (PB3/PB4), OC1A/B (PD5/PD4), OC2A/B (PD7/PD6)
*/

#ifndef TIMER_H
#define TIMER_H

#include "TimerConfiguration.h"
#include "TimerRegisters.h"
#include "TimerSpecificConfiguration.h"

#include <avr/interrupt.h>
#include <avr/io.h>

enum TimeUnit {
    SECONDS = 1,
    MILLISECONDS = 1000,
    MICROSECONDS = 1000000,
};

template<TimerNumber timerNumber>
class Timer {
public:
    Timer();
    void setWaveformMode(const WaveformMode& mode);
    void
    setPrescaler(const typename SpecificConfiguration<timerNumber>::Prescaler&
                     prescaler);
    void setOutputCompareMode(const OutputCompareMode& mode,
                              const OutputCompareChannel& channel);
    void toggleTimerInterrupt(const InterruptMode& mode,
                              const bool toggleOn = true);
    void setOCRnX(const OutputCompareChannel& channel, const uint16_t value);
    register16_t& accessCounter();

    uint16_t frequencyToClockCycles(const double& frequency);
    uint16_t timeToClockCycles(const double& millis, const TimeUnit& timeUnit);
    uint16_t clockCyclesToTime(const uint16_t& clockCycles,
                               const TimeUnit& timeUnit);

private:
    void configureRegister(register8_t* timerRegister,
                           uint8_t bitField,
                           uint8_t value);
    uint16_t prescalerValue_;
    TimerRegisters<timerNumber> timerRegisters_;
};

#include "Timer.tpp"
#endif // TIMER_H
