/* Author: Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-10-1
*
* Name of file : BaseDrivetrain.h
* Description : This file defines the foundational logic for a drivetrain.      
* Material components used : None
* Pins in input : None.
* Pins in output : None.
*/

#pragma once

#include "Engine.h"
#include "RobotData.h"
#include <util/delay.h>

#define PWM_DUTY_CYCLE_HALF 90
#define WAIT_DELAY_MULTIPLIER 10
#define KICK_START_DUTY_CYCLE 250
#define KICK_START_DELAY_MS 50

class BaseDrivetrain {
    public:
        BaseDrivetrain(Engine<ENGINE_TIMER>* rightEngine, Engine<ENGINE_TIMER>* leftEngine);

        void stopEngines();
        void moveForward(uint8_t dutyCycle);
        void moveBackward(uint8_t dutyCycle);
        virtual void turnRight(uint16_t turnTime) = 0;
        virtual void turnLeft(uint16_t turnTime) = 0;

    protected:
        void wait(uint8_t delay);
        void turn(Direction leftDirection, Direction rightDirection, uint16_t turnDelay);
        void move(Direction direction, uint8_t dutyCycle);
        void kickStartEngines();
        
        Engine<ENGINE_TIMER>* rightEngine_; 
        Engine<ENGINE_TIMER>* leftEngine_;
};