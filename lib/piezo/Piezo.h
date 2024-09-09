/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-03-19

* Name of file : piezo.h
* Description : This header file defines a class for utilizing any of the 3
                available timers on the ATmega324PA microcontroller as an
                Engine. It employs the phase-correct PWM mode and integrates
                several methods implemented in the timer file. Additionally,
                this class facilitates the configuration of the engine's duty
                cycle and direction.
* Material components used :
* Pins in input :
* Pins in output :
*/

#pragma once

#include "Timer.h"
#include "TimerPeripherals.h"

#include <avr/io.h>
#include <math.h>

template<TimerNumber timerNumber>
class Piezo {
public:
    Piezo(Timer<timerNumber>* timer,
          register8_t* portX,
          register8_t* ddrX,
          uint8_t gndPin):
        timer_(timer) {
        TimerPeripherals<timerNumber>::setPinToOutput(OutputCompareChannel::A);
        *ddrX |= (1 << gndPin);
        *portX &= ~(1 << gndPin);
        cli();
        timer_->setWaveformMode(WaveformMode::CTC);
        timer_->setPrescaler(
            SpecificConfiguration<timerNumber>::Prescaler::DIVISOR_1024);
        stopMusic();
        sei();
    }

    double noteToFrequency(uint8_t note) {
        return (440 * pow(2, ((note - 69) / 12.0)));
    }

    void playNote(uint8_t note) {
        timer_->setOutputCompareMode(OutputCompareMode::TOGGLE, OutputCompareChannel::A);
        timer_->setOCRnX(OutputCompareChannel::A,
                         timer_->frequencyToClockCycles(noteToFrequency(note)) / 2);
    }

    void playSuccessiveNotes(uint8_t note, uint8_t times) {
        for (int i = 0; i < times; i++) {
        playNote(note);
        _delay_ms(DELAY_BLINK_SOUND);
        stopMusic();
        _delay_ms(DELAY_BLINK_SOUND);
    }
    }

    void stopMusic() {
        timer_->setOutputCompareMode(OutputCompareMode::NORMAL, OutputCompareChannel::A);
    }

private:
    Timer<timerNumber>* timer_;
    static constexpr uint8_t DELAY_BLINK_SOUND = 50;
};
