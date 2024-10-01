/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : RobotOne.cpp
* Description : This file defines all functions related to its class for
*               utilizing all components required to do the first robot's routine,
*               from its movement, down to receiving all the data from the second robot.
* Material components used : Piezoelectric buzzer, both engines, the robot's
*                            ADC, the robot's button, the robot's led, an infrared receiver.
* Pins in input : None.
* Pins in output : Depends on Timer used (PWM pins), Ground PIN.
*/

#include "RobotOne.h"

#define SMALL_TURN 30
#define ENGINE_SPEED 120
#define LOW_NOTE 40
#define HIGH_NOTE 95
#define NINETY_DEGREES_TURN 15
#define TURN_DELAY_IN_MS 700

RobotOne::RobotOne(Timer<TimerNumber::TIMER_2>* timerPiezo,
                   Timer<TimerNumber::TIMER_0>* engineTimer,
                   Timer<TimerNumber::TIMER_1>* receiverTimer):
    piezo_(timerPiezo, &PORTD, &DDRD, PD6),
    rightEngine_(engineTimer,
                 ENGINE_RIGHT_PWM_CHANNEL,
                 &ENGINE_PORT,
                 &ENGINE_DDRX,
                 ENGINE_RIGHT_DIRECTION_PIN,
                 ENGINE_RIGHT_STRENGTH_INDEX_R1),
    leftEngine_(engineTimer,
                ENGINE_LEFT_PWM_CHANNEL,
                &ENGINE_PORT,
                &ENGINE_DDRX,
                ENGINE_LEFT_DIRECTION_PIN,
                ENGINE_LEFT_STRENGTH_INDEX_R1),
    drivetrain_(&rightEngine_, &leftEngine_),
    led_(&PORTD, &DDRD, PD4, PD5),
    converter_(),
    receiver_(*receiverTimer,
               PINC,
               DDRC,
               PC6),
    button_(ExternalInterruptNumber::INTERUPT_0) {
    }

void RobotOne::robotModeSwitch() {
    Mode mode = Mode::WAIT;

    Line lineArray[6];
    uint8_t lineArraySize = 6 * sizeof(Line);

    while(true) {
        switch(mode) {
            case Mode::WAIT:
                led_.turnOnRed();
                while(button_.isPressed() == false) {}
                piezo_.playSuccessiveNotes(HIGH_NOTE, 3);
                mode = Mode::RECEIVE;
                break;
            case Mode::RECEIVE:
                led_.turnOff();
                if(receiver_.tryReceiveData(&lineArray, &lineArraySize)){
                    mode = Mode::RS232;
                }
                else {
                    piezo_.playNote(LOW_NOTE);
                    _delay_ms(1000);
                    piezo_.stopMusic();
                    mode = Mode::WAIT;
                }
                break;
            case Mode::RS232:
                led_.turnOnGreen();
                while(button_.isPressed() == false) {}
                led_.startFlash();
                for(uint16_t i = 0; i < lineArraySize / sizeof(Line); ++i) {
                    Display::getInstance().insertLine(lineArray[i]);  
                }
                Display::getInstance().insertBot(getQuadrant(), getInverted());
                Display::getInstance().displaySteve();
                led_.stopFlash();
                break;
        }
    }
}

uint8_t RobotOne::readDistance() {
    uint8_t distanceAverage = 0;
    uint16_t sum = 0;
    uint8_t measure = 0;
    for(int i = 0; i < 10; i++) { // moyenne de 10 mesures pour precision
        measure = converter_.lecture(0) >> 2;
        sum += measure;
    }
    distanceAverage = sum / 10;
    return distanceAverage;
}

void RobotOne::runWithDistance() {
    uint8_t distance = readDistance();
    setDistance(distance);

    if(distance > DEAD_CENTER) {
        drivetrain_.moveBackward(ENGINE_SPEED);  
        while(distance > DEAD_CENTER)
            distance = readDistance();
        setDirection(0);
    } else {
        drivetrain_.moveForward(ENGINE_SPEED);
        while(distance < DEAD_CENTER)
            distance = readDistance();
        setDirection(1);
    }
    drivetrain_.stopEngines();
}

void RobotOne::spinToOpening() {
    uint8_t distance = 0;
    uint8_t nTurns = 0;

    distance = readDistance();
    _delay_ms(ONE_SECOND_IN_MS);
    while(distance >= OPENING_DISTANCE) { 
        drivetrain_.turnRight(SMALL_TURN);  
        distance = readDistance();
        ++nTurns;
        _delay_ms(TURN_DELAY_IN_MS);
    }

    if (getDirection()) {
        if (nTurns < NINETY_DEGREES_TURN)
            setInverted(1);
    }
    else {
        if (nTurns < NINETY_DEGREES_TURN)
            setInverted(1); 
    }
}
