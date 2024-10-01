/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : RobotTwo.h
* Description : This header file defines a class for utilizing all components required to do the second robot's routine,
* from its movement, down to sending all the data to the first robot.
* Material components used : Piezoelectric buzzer, both engines, the robot's makerline, the robot's button, a second white button, 
* the robot's led, an infrared transmitter led.
* Pins in input : None.
* Pins in output : Depends on Timer used (PWM pins), Ground PIN.
*/

#pragma once

#include "DistanceUtils.hpp"
#include "DrivetrainRobotTwo.h"
#include "Engine.h"
#include "IrTransmitter.h"
#include "Maker-line.h"
#include "TimerUtils.h"
#include "Led.h"
#include "Piezo.h"
#include "Button.h"
#include "Display.h"
#include "Debug.h"

#define OVER_TURN_MARGIN_DELAY 110
#define MOVE_FORWARD_PWM 100
#define DEBOUNCE_DELAY 50
#define FULL_STOP_DELAY_MS 1000
#define N_TURNS_BOTTOM_SECTION 3
#define FRAME_LENGTH 40
#define DELAY_MS_BEFORE_TURN 1500
#define FULL_STOP_180_TURN_DELAY_MS 2000
#define DELAY_MS_BEFORE_TRANSMIT 2000
#define HIGH_NOTE 95
#define HALF_SECOND_DELAY 500
#define MAX_ARRAY_SIZE 8

enum class RobotCourse {
    LINE,
    TURNRIGHT,
    TURNLEFT,
    TURN180,
    TURN180FRAME,
    DECISION,
    TRANSMIT, 
    RS232
};

class RobotTwo {
public:
    RobotTwo(DrivetrainRobotTwo* driveTrain,
             MakerLine* makerLine,
             Timer<DELAY_TIMER>* timer,
             Led* led,
             Button* buttonInterrupt,
             Button* buttonWhite);
    RobotCourse center();
    RobotCourse turnRight(uint16_t& nTurns, uint16_t& gCounter);
    RobotCourse turnLeft();
    RobotCourse turn180(uint16_t& nTurns, uint16_t& gCounter);
    RobotCourse turn180Frame(uint16_t& nTurns, uint16_t& gCounter);
    RobotCourse decision();
    RobotCourse transmit();
    RobotCourse rs232();

    Timer<DELAY_TIMER>* getTimer();

private:
    DrivetrainRobotTwo* driveTrain_;
    MakerLine* makerLine_;
    Timer<DELAY_TIMER>* timer_;

    Line lineArray_[MAX_ARRAY_SIZE];
    uint16_t lineArrayIndex_ = 0;
    bool isVertical_ = true, canTurnLeft_ = false;

    Led* led_;
    Button* buttonInterrupt_;
    Button* buttonWhite_;
};
