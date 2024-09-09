/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : TimerUtils.h
* Description : Diverse functions to manipulate timers by starting, resetting and stopping them.
* Pins in input : None.
* Pins in output : Depends on Timer used (PWM pins), Ground PIN.
*/

#pragma once

#include <avr/io.h>
#include <Timer.h>
#define DELAY_TIMER TimerNumber::TIMER_1
#define TIMER_TICKS_LOST_WHEN_TURNING 20

namespace timerUtils {
    void startTimer(Timer<DELAY_TIMER>* timer);
    void resetTimer(Timer<DELAY_TIMER>* timer, uint16_t& gCounter);
    void stopTimer(Timer<DELAY_TIMER>* timer);
}
