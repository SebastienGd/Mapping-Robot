/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-03-08

* Name of file : TimerRegisters.h
* Description : This file contains the registers for each timer of the
                ATmega324PA. (TIMER_0,TIMER_1,TIMER_2)
* Material components used :
* Pins in input :
* Pins in output :
*/

#ifndef TIMER_REGISTERS_H
#define TIMER_REGISTERS_H

#include <avr/io.h>

typedef volatile uint8_t register8_t;
typedef volatile uint16_t register16_t;

enum class TimerNumber {
    TIMER_0,
    TIMER_1,
    TIMER_2
};

template<TimerNumber timerNumber>
struct TimerRegisters {
    void *TCNTn, *TCCRnA, *TCCRnB, *TCCRnC, *OCRnA, *OCRnB, *TIMSKn;
};

// TIMER 0 
template<>
struct TimerRegisters<TimerNumber::TIMER_0> {
    register8_t *TCNTn = &TCNT0, *TCCRnA = &TCCR0A, *TCCRnB = &TCCR0B,
                *TCCRnC = nullptr, *OCRnA = &OCR0A, *OCRnB = &OCR0B,
                *TIMSKn = &TIMSK0;
};

// TIMER 1  
template<>
struct TimerRegisters<TimerNumber::TIMER_1> {
    register16_t *TCNTn = &TCNT1, *OCRnA = &OCR1A, *OCRnB = &OCR1B;
    register8_t *TCCRnA = &TCCR1A, *TCCRnB = &TCCR1B, *TCCRnC = &TCCR1C,
                *TIMSKn = &TIMSK1;
};

// TIMER 2 
template<>
struct TimerRegisters<TimerNumber::TIMER_2> {
    register8_t *TCNTn = &TCNT2, *TCCRnA = &TCCR2A, *TCCRnB = &TCCR2B,
                *TCCRnC = nullptr, *OCRnA = &OCR2A, *OCRnB = &OCR2B,
                *TIMSKn = &TIMSK2;
};

#endif
