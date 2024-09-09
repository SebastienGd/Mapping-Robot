/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-03-08

* Name of file : Led.cpp
* Description : Various ways to use a LED on the motherboard.
* Material components used : A LED on the motherboard.
* Pins in input : None.
* Pins in output : Two, users choice.
*/

#include "Led.h"

Led::Led(volatile uint8_t* portX,
         volatile uint8_t* ddrX,
         uint8_t positivePin,
         uint8_t negativePin):
    portX_(portX),
    positivePin_(positivePin),
    negativePin_(negativePin) {
    *ddrX |= (1 << positivePin | 1 << negativePin);
}

void Led::turnOnGreen() {
    *portX_ &= ~(1 << positivePin_);
    *portX_ |= (1 << negativePin_);
}

void Led::turnOnRed() {
    *portX_ |= (1 << positivePin_);
    *portX_ &= ~(1 << negativePin_);
}

void Led::turnOnAmber(uint16_t timeInMilliseconds) {
    for(uint16_t i = 0; i < timeInMilliseconds; i += TIME_IN_LOOP) {
        turnOnGreen();
        _delay_ms(DELAY_MS_AMBER);
        turnOnRed();
        _delay_ms(DELAY_MS_AMBER);
    }
}

void Led::startFlash() {
    TCCR1B |=  (1 << WGM12)| (1<<CS10) | (1<<CS12);
    TCCR1B &= ~((1<< WGM13) | (1<<CS11));
    TCCR1A |= (1 << COM1A0);
    TCCR1A &= ~((1 << COM1A1) | (1<<WGM11)| (1<<WGM10));
    TCNT1 = 0;
    OCR1A = 781;

}
void Led::stopFlash() {
    TCCR1A &= ~(1 << COM1A0);
    TCCR1A &= ~(1 << COM1A1);
}

void Led::turnOff() {
    *portX_ &= ~(1 << positivePin_);
    *portX_ &= ~(1 << negativePin_);
}
