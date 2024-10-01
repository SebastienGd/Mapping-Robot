/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : main.cpp
* Description : Main file for the second robot, initializing all timers, material components, and the robot itself.
* The functions allowing the robot to execute its task are also called, and its state machine is defined above.
* Pins in output : Depends on Timer used (PWM pins), Ground PIN.
*/

#include "Debug.h"
#include "DistanceUtils.hpp"
#include "DrivetrainRobotTwo.h"
#include "Engine.h"
#include "Maker-line.h"
#include "RobotTwo.h"
#include "TimerUtils.h"

uint16_t nTurns = 0;
uint16_t gCounter = 0;

ISR(TIMER1_COMPA_vect) {
    ++gCounter;
}

void fsm(RobotTwo& robotTwo) {
    timerUtils::startTimer(robotTwo.getTimer());
    RobotCourse state = RobotCourse::LINE;
    bool exitSwitch = false;

    while(!exitSwitch) {
        switch(state) {
            case RobotCourse::LINE:
                state = robotTwo.center();
                break;

            case RobotCourse::TURNRIGHT:
                state = robotTwo.turnRight(nTurns, gCounter);
                break;

            case RobotCourse::TURNLEFT:
                state = robotTwo.turnLeft();
                break;

            case RobotCourse::TURN180:
                state = robotTwo.turn180(nTurns, gCounter);
                break;

            case RobotCourse::TURN180FRAME:
                state = robotTwo.turn180Frame(nTurns, gCounter);
                break;

            case RobotCourse::DECISION:
                state = robotTwo.decision();
                break;

            case RobotCourse::TRANSMIT:
                state = robotTwo.transmit();
                break;

            case RobotCourse::RS232:
                state = robotTwo.rs232();
                break;
        }
    }
}

int main() {
    Led led(&PORTD, &DDRD, PD4,PD5);
    Timer<ENGINE_TIMER> motorTimer;

    Engine<ENGINE_TIMER> rightEngine(&motorTimer,
                                     ENGINE_RIGHT_PWM_CHANNEL,
                                     &ENGINE_PORT,
                                     &ENGINE_DDRX,
                                     ENGINE_RIGHT_DIRECTION_PIN,
                                     ENGINE_RIGHT_STRENGTH_INDEX);

    Engine<ENGINE_TIMER> leftEngine(&motorTimer,
                                    ENGINE_LEFT_PWM_CHANNEL,
                                    &ENGINE_PORT,
                                    &ENGINE_DDRX,
                                    ENGINE_LEFT_DIRECTION_PIN,
                                    ENGINE_LEFT_STRENGTH_INDEX);

    MakerLineData makerlinedata{&DDRA, &PINA, PA0, PA1, PA2, PA3, PA4};
    MakerLine makerLine(makerlinedata);

    DrivetrainRobotTwo drivetrain(&rightEngine, &leftEngine, &makerLine);

    Timer<TimerNumber::TIMER_1> timer1;

    Button buttonInterrupt(ExternalInterruptNumber::INTERUPT_0);
    Button buttonWhite(ExternalInterruptNumber::INTERUPT_1);

    RobotTwo robotTwo(
        &drivetrain, &makerLine, &timer1, &led, &buttonInterrupt, &buttonWhite);

    fsm(robotTwo);
    while(true) {}
}
