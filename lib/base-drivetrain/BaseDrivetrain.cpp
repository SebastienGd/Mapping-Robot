/* Author: Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-10-1
*
* Name of file : BaseDrivetrain.cpp
* Description : This file defines the foundational logic for a drivetrain.      
* Material components used : None
* Pins in input : None.
* Pins in output : None.
*/

#include "BaseDrivetrain.h"

BaseDrivetrain::BaseDrivetrain(Engine<ENGINE_TIMER>* rEngine,
                       Engine<ENGINE_TIMER>* lEngine):
    rightEngine_(rEngine),
    leftEngine_(lEngine){}

void BaseDrivetrain::stopEngines() {
    leftEngine_->setDirection(Direction::NEUTRAL);
    rightEngine_->setDirection(Direction::NEUTRAL);
}

void BaseDrivetrain::moveForward(uint8_t dutyCycle) {
    move(Direction::FORWARD, dutyCycle);
}

void BaseDrivetrain::moveBackward(uint8_t dutyCycle) {
    move(Direction::BACKWARD, dutyCycle);
}

void BaseDrivetrain::turnRight(uint16_t turnTime) {
    turn(Direction::FORWARD, Direction::BACKWARD, turnTime);
}

void BaseDrivetrain::turnLeft(uint16_t turnTime) {
    turn(Direction::BACKWARD, Direction::FORWARD, turnTime);
}

void BaseDrivetrain::turn(Direction leftDirection,
                      Direction rightDirection,
                      uint16_t turnDelay) {
    // Store initial engine states
    uint8_t leftEngineDutyCycle = leftEngine_->getDutyCycle();
    uint8_t rightEngineDutyCycle = rightEngine_->getDutyCycle();
    Direction leftEngineDirection = leftEngine_->getDirection();
    Direction rightEngineDirection = rightEngine_->getDirection();

    // Set engines to turn
    leftEngine_->setDirection(leftDirection);
    rightEngine_->setDirection(rightDirection);
    kickStartEngines();
    leftEngine_->setDutyCycle(PWM_DUTY_CYCLE_HALF);
    rightEngine_->setDutyCycle(PWM_DUTY_CYCLE_HALF);

    wait(turnDelay);

    // Restore initial engine states
    leftEngine_->setDirection(leftEngineDirection);
    rightEngine_->setDirection(rightEngineDirection);
    leftEngine_->setDutyCycle(leftEngineDutyCycle);
    rightEngine_->setDutyCycle(rightEngineDutyCycle);
}

void BaseDrivetrain::wait(uint8_t delay) {
    for(int i = 0; i < delay; i++)
        _delay_ms(WAIT_DELAY_MULTIPLIER);
}

void BaseDrivetrain::move(Direction direction, uint8_t dutyCycle) {
    leftEngine_->setDirection(direction);
    rightEngine_->setDirection(direction);
    kickStartEngines();
    leftEngine_->setDutyCycle(dutyCycle);
    rightEngine_->setDutyCycle(dutyCycle);
}

void BaseDrivetrain::kickStartEngines() {
    leftEngine_->setDutyCycle(KICK_START_DUTY_CYCLE);
    rightEngine_->setDutyCycle(KICK_START_DUTY_CYCLE);
    _delay_ms(KICK_START_DELAY_MS);
}