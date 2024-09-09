/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : TimerUtils.cpp
* Description : Diverse functions to manipulate timers by starting, resetting and stopping them.
* Pins in input : None.
* Pins in output : Depends on Timer used (PWM pins), Ground PIN.
*/

#include "TimerUtils.h"

namespace timerUtils {
    void startTimer(Timer<DELAY_TIMER>* timer) {
        cli();
        timer->setWaveformMode(WaveformMode::CTC);
        timer->setPrescaler(
            SpecificConfiguration<DELAY_TIMER>::Prescaler::DIVISOR_1024);
        timer->setOCRnX(OutputCompareChannel::A,
                        timer->timeToClockCycles(25, TimeUnit::MILLISECONDS));
        timer->toggleTimerInterrupt(InterruptMode::MATCH_A, true);
        sei();
    }

    void resetTimer(Timer<DELAY_TIMER>* timer, uint16_t& gCounter) {
        gCounter = TIMER_TICKS_LOST_WHEN_TURNING;
        timer->accessCounter() = 0;
    }
    void stopTimer(Timer<DELAY_TIMER>* timer) {
        cli();
        timer->toggleTimerInterrupt(InterruptMode::MATCH_A, false);
        sei();
    }
}
