/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-03-08
*
* Name of file : Engine.h
* Description : This header file defines a class for utilizing any of the 3
                available timers on the ATmega324PA microcontroller as an
                Engine. It employs the phase-correct PWM mode and integrates
                several methods implemented in the timer file. Additionally,
                this class facilitates the configuration of the engine's duty
                cycle and direction.
* Material components used : Engine.
* Pins in input : None.
* Pins in output : Any PWM output pin can be used.
*/

#pragma once

#include "Timer.h"
#include "TimerPeripherals.h"
#include <math.h>
#include <avr/io.h>

enum class Direction {
    FORWARD,
    BACKWARD,
    NEUTRAL
};

template<TimerNumber timerNumber>
class Engine {
public:
    Engine(Timer<timerNumber>* timer,
           OutputCompareChannel channel,
           register8_t* portX,
           register8_t* ddrX,
           uint8_t pinX,
           float strengthIndex):
        timer_(timer),
        channel_(channel),
        portX_(portX),
        pinX_(pinX),
        strengthIndex_(strengthIndex) {
        TimerPeripherals<timerNumber>::setPinToOutput(channel);
        *ddrX |= 1 << pinX;
        cli();
        timer_->setWaveformMode(WaveformMode::PHASE_CORRECT_PWM);
        timer_->setPrescaler(
            SpecificConfiguration<timerNumber>::Prescaler::DIVISOR_8);
        timer_->setOutputCompareMode(OutputCompareMode::CLEAR, channel_);
        sei();
    }

    uint8_t getDutyCycle() const {
        return dutyCycle_;
    }

    Direction getDirection() const {
        return direction_;
    }

    void setDutyCycle(uint8_t dutyCycle) {
        dutyCycle_ = round(strengthIndex_ * dutyCycle);
        timer_->setOCRnX(channel_, dutyCycle_);
    }

     void setDirection(Direction direction) {
        if(direction == Direction::FORWARD)
            *portX_ &= ~(1 << pinX_);
        else if (direction == Direction::BACKWARD)
            *portX_ |= (1 << pinX_);
        else 
            setDutyCycle(0);
        direction_ = direction;
    }

    void setStrengthIndex(float strengthIndex) {
        strengthIndex_ = strengthIndex;
    }

private:
    Timer<timerNumber>* timer_;
    OutputCompareChannel channel_;
    volatile uint8_t* portX_;
    uint8_t pinX_;

    float strengthIndex_;
    uint8_t dutyCycle_;
    Direction direction_;
};
