/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-03-08

* Name of file : TimerConfigurations.h
* Description : This file contains all the configuration needed for the 3 timers
                of the ATmega324PA. The WaveformModes (NORMAL_OPERATION,
                CTC,PHASE_CORRECT_PWM), OutputCompareMode(NORMAL, TOGGLE, CLEAR,
                SET), OutputCompareChannel(A,B) act in the same manner for all
                timers. The Prescaler and configurations used for the waveform
                generation mode, are specific for each timers.
* Material components used : None
* Pins in input : None
* Pins in output : None
*/

#ifndef TIMER_CONFIGURATION_H
#define TIMER_CONFIGURATION_H

#include "TimerRegisters.h"

#include <avr/io.h>

#define PRESCALER_BIT_FIELD (1 << CS12) | (1 << CS11) | (1 << CS10)
#define WGM_A_BIT_FIELD (1 << WGM10) | (1 << WGM11)
#define WGM_B_BIT_FIELD(isTimer16Bits) \
    isTimer16Bits ? (1 << WGM12) | (1 << WGM13) : (1 << WGM12)

enum WaveformMode {
    NORMAL_OPERATION,
    CTC,
    PHASE_CORRECT_PWM,
    FAST_PWM,
    PHASE_CORRECT_PWM_OCRNA_TOP
};

// the values of OutputCompareMode are configured for both channels, and can be
// singled out by using the OutputCompareChannel as a mask
enum OutputCompareMode {
    NORMAL = 0,
    TOGGLE = (1 << COM1A0) | (1 << COM1B0),
    CLEAR = (1 << COM1A1) | (1 << COM1B1),
    SET = (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0)
};

enum OutputCompareChannel {
    A = (1 << COM1A1) | (1 << COM1A0),
    B = (1 << COM1B1) | (1 << COM1B0)
};

enum InterruptMode {
    OVERFLOW = (1 << TOIE0),
    MATCH_A = (1 << OCIE0A),
    MATCH_B = (1 << OCIE0B)
};

#include "TimerSpecificConfiguration.h"
#endif // TIMER_CONFIGURATION_H
