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

#include "Button.h"

Button::Button(const ExternalInterruptNumber& externalInteruptNumber):
    _externalInteruptNumber(externalInteruptNumber) {
    setPinToInput();
}

Button::Button(const ExternalInterruptNumber& externalInteruptNumber,
               const ExternalInteruptType& interuptType):
    _externalInteruptNumber(externalInteruptNumber) {
    cli();
    setPinToInput();
    EICRA |= (interuptType << (2 * externalInteruptNumber));
    EIMSK |= (1 << externalInteruptNumber);
    sei();
}

bool Button::isPressed() {
    if( isPinHigh()) {
        _delay_ms(DEBOUNCE_DELAY);
        return  isPinHigh();
    }
    return false;
}

bool Button::isPinHigh() {
    switch(_externalInteruptNumber) {
        case INTERUPT_0:
            return PIND & (1 << PD2);
            break;
        case INTERUPT_1:
            return PIND & (1 << PD3);
            break;
        case INTERUPT_2:
            return PINB & (1 << PB2);
            break;
    }
    return false;
}

void Button::setPinToInput() {
    switch(_externalInteruptNumber) {
        case INTERUPT_0:
            DDRD &= ~(1 << PD2);
            break;
        case INTERUPT_1:
            DDRD &= ~(1 << PD3);
            break;
        case INTERUPT_2:
            DDRB &= ~(1 << PB2);
            break;
    }
}
