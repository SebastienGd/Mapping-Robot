/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-03-27
*
* Name of file : Button.cpp
* Description : Manages the interruptions setup and/or debounce of a button.
*               Multiple interruption types are available
* Material components used : A button
* Pins in input : PD2, PD3 or PB2 depending on the selected interrupt
* Pins in output : None.
*/

#pragma once

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

enum ExternalInteruptType {
    LOW_LEVEL = 0,
    ANY_EDGE = 1 << ISC00,
    FALLING_EDGE = 1 << ISC01,
    RISING_EDGE = (1 << ISC00) | (1 << ISC01)
};

enum ExternalInterruptNumber {
    INTERUPT_0,
    INTERUPT_1,
    INTERUPT_2
};

class Button {
public:
    Button(const ExternalInterruptNumber& externalInteruptNumber);
    Button(const ExternalInterruptNumber& externalInteruptNumber,
           const ExternalInteruptType& interuptType);
    bool isPressed();

private:
    void setPinToInput();
    bool isPinHigh();

    static constexpr uint8_t DEBOUNCE_DELAY = 10;
    ExternalInterruptNumber _externalInteruptNumber;
};
