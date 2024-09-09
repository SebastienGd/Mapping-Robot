/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : RobotOne.h
* Description : This header file defines a class for utilizing all components required to do the first robot's routine,
* from its movement, down to receiving all the data from the second robot.
* Material components used : Piezoelectric buzzer, both engines, the robot's ADC, the robot's button, the robot's led, 
* an infrared receiver.
* Pins in input : None.
* Pins in output : Depends on Timer used (PWM pins), Ground PIN.
*/

#pragma once

#include "Button.h"
#include "Drivetrain.h"
#include "Timer.h"
#include "Led.h"
#include "Can.h"
#include "IrReceiver.h"
#include "Piezo.h"
#include "Display.h"
#include <util/delay.h>

#define ENGINE_LEFT_STRENGTH_INDEX_R1 1.0f
#define ENGINE_RIGHT_STRENGTH_INDEX_R1 0.93f
#define ONE_SECOND_IN_MS 1000

enum class Mode {
    WAIT, 
    RECEIVE, 
    RS232
    };

class RobotOne {
public:
    RobotOne(Timer<TimerNumber::TIMER_2>* timerPiezo, Timer<TimerNumber::TIMER_0>* engineTimer, Timer<TimerNumber::TIMER_1>* receiverTimer, MakerLine* makerLine);

    void robotModeSwitch();
    uint8_t readDistance();
    void runWithDistance();
    void spinToOpening();

    uint8_t getDirection(){ return direction_; }
    uint8_t getQuadrant(){ return distance_; }
    uint8_t getInverted() { return inverted_; }
    void setDirection(uint8_t direction) { direction_ = direction; } // 0 -> Fait face au mur ; 1 -> Fait face au centre
    void setDistance(uint8_t distance) { distance_ = distance; }     // Distance de depart entre le robot et le mur
    void setInverted(uint8_t inverted) { inverted_ = inverted; }

private:

    Piezo<TimerNumber::TIMER_2> piezo_;

    Engine<TimerNumber::TIMER_0> rightEngine_;
    Engine<TimerNumber::TIMER_0> leftEngine_;
    Drivetrain drivetrain_;

    Led led_;
    can converter_;
    IrReceiver<TimerNumber::TIMER_1> receiver_;
    Button button_;
    
    uint8_t direction_;
    uint8_t distance_;
    uint8_t inverted_ = 0;

    static constexpr uint8_t DEAD_CENTER = 42;
    static constexpr uint8_t OPENING_DISTANCE = 0b00001111;
};
