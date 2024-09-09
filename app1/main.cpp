/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : main.cpp
* Description : Main file for the first robot, initializing all timers and the robot itself.
* The functions allowing the robot to execute its task are also called.
* Pins in output : Depends on Timer used (PWM pins), Ground PIN.
*/

#include "RobotOne.h"

int main() {
    Timer<TimerNumber::TIMER_2> timerPiezo;
    Timer<TimerNumber::TIMER_0> engineTimer;
    Timer<TimerNumber::TIMER_1> receiverTimer;

    MakerLineData makerlinedata {&DDRA, &PINA, PA0, PA1, PA2, PA3, PA4};
    MakerLine makerLine (makerlinedata);

    RobotOne Steve(&timerPiezo, &engineTimer, &receiverTimer, &makerLine);

    Steve.runWithDistance();
    _delay_ms(ONE_SECOND_IN_MS);
    Steve.spinToOpening();
    Steve.robotModeSwitch();
    
    while(true) {}

    return 0;
}