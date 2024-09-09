/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : Drivetrain.h
* Description : This header file defines a class that takes two engines and a line-maker in parameters to allow a robot to move whilst
* following black lines.
* Material components used : Line-maker, both engines.
* Pins in input : None.
* Pins in output : Depends on Timer used (PWM pins), Ground PIN.
*/

#pragma once

#include "RobotData.h"
#include "Maker-line.h"
#include <util/delay.h>


#define PWM_DUTY_CYCLE_HALF 90
#define KICKSTART_TURN_DELAY 100 
#define ONE_EIGHTY_DEGREE_TURN_DELAY 120
#define WAIT_DELAY_MULTIPLIER 25
#define BRAKE_PWM 200
#define BRAKE_DELAY_MS 50
#define CENTER_CORRECTION_PWM 50


class Drivetrain{
public:
    Drivetrain(Engine<ENGINE_TIMER>* rightEngine, Engine<ENGINE_TIMER>* leftEngine, MakerLine* makerLine);
    void move(Direction direction, uint8_t dutyCycle);
    void moveSingleEngine(Engine<ENGINE_TIMER>* engine, Direction direction, uint8_t dutyCycle);
    void turn(Direction leftDirection, Direction rightDirection, uint16_t turnDelay);
    void turnMakerLine(Direction leftDirection, Direction rightDirection);
    void wait(uint8_t delay);
    void stopEngines();
    void kickStartEngines();
    void moveForward(uint8_t dutyCycle);
    void moveBackward(uint8_t dutyCycle);
    void turnRightMakerLine();
    void turnLeftMakerLine();
    void turnRight(uint16_t turnTime = KICKSTART_TURN_DELAY);
    void turnLeft(uint16_t turnTime = KICKSTART_TURN_DELAY);
    void turn180(uint16_t turnTime = ONE_EIGHTY_DEGREE_TURN_DELAY);
    void center();
private:
    Engine<ENGINE_TIMER>* rightEngine_; 
    Engine<ENGINE_TIMER>* leftEngine_;
    MakerLine* makerLine_;
};