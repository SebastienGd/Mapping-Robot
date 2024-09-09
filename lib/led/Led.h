/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-03-08

* Name of file : Led.h
* Description : Various ways to use a LED on the motherboard.
* Material components used : A LED on the motherboard.
* Pins in input : None.
* Pins in output : Two, users choice.
*/

#pragma once

#include <avr/io.h>
#include <util/delay.h>

class Led {
public:
    Led(volatile uint8_t* portX,
        volatile uint8_t* ddrX,
        uint8_t positivePin,
        uint8_t negativePin);

    void turnOnGreen();
    void turnOnRed();
    void turnOnAmber(uint16_t timeInMilliseconds);
    void startFlash();
    void stopFlash();
    void turnOff();

private:
    volatile uint8_t* portX_;
    uint8_t positivePin_;
    uint8_t negativePin_;
    static constexpr uint8_t DELAY_MS_AMBER = 10;
    static constexpr uint8_t TIME_IN_LOOP = 20;
};
