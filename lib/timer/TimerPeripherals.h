#include "Timer.h"

#ifndef TIMER_PERIPHERALS_H
# define TIMER_PERIPHERALS_H

template<TimerNumber timerNumber>
struct TimerPeripherals {
    static void setPinToOutput(const OutputCompareChannel& channel) {
        switch(timerNumber) {
            case TimerNumber::TIMER_0:
                DDRB |= 1 << ((channel == OutputCompareChannel::A) ? PB3 : PB4);
                break;
            case TimerNumber::TIMER_1:
                DDRD |= 1 << ((channel == OutputCompareChannel::A) ? PD5 : PD4);
                break;
            case TimerNumber::TIMER_2:
                DDRD |= 1 << ((channel == OutputCompareChannel::A) ? PD7 : PD6);
                break;
        }
    }
};
#endif
