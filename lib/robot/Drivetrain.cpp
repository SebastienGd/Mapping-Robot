/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17
*
* Name of file : Drivetrain.cpp
* Description : This file defines all functions of the Drivetrain class, that
*               takes two engines and a line-maker in parameters to allow a robot
*               to move whilst following black lines.
* Material components used : Line-maker, both engines.
* Pins in input : None.
* Pins in output : Depends on Timer used (PWM pins), Ground PIN.
*/

#include "Drivetrain.h"

Drivetrain::Drivetrain(Engine<ENGINE_TIMER>* rEngine,
                       Engine<ENGINE_TIMER>* lEngine,
                       MakerLine* makerLine):
    rightEngine_(rEngine),
    leftEngine_(lEngine),
    makerLine_(makerLine) {}

void Drivetrain::move(Direction direction, uint8_t dutyCycle) {
    leftEngine_->setDirection(direction);
    rightEngine_->setDirection(direction);
    kickStartEngines();
    leftEngine_->setDutyCycle(dutyCycle);
    rightEngine_->setDutyCycle(dutyCycle);
}

void Drivetrain::moveSingleEngine(Engine<ENGINE_TIMER>* engine,
                                  Direction direction,
                                  uint8_t dutyCycle) {
    engine->setDirection(direction);
    engine->setDutyCycle(dutyCycle);
}

void Drivetrain::turn(Direction leftDirection,
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

    // Delay for turning 90 degrees at 50% PWM
    for(uint16_t i = 0; i < turnDelay; i++)
        _delay_ms(10);

    // Restore initial engine states
    leftEngine_->setDirection(leftEngineDirection);
    rightEngine_->setDirection(rightEngineDirection);
    leftEngine_->setDutyCycle(leftEngineDutyCycle);
    rightEngine_->setDutyCycle(rightEngineDutyCycle);
}

void Drivetrain::turnMakerLine(Direction leftDirection,
                               Direction rightDirection) {
    // Store initial engine states
    uint8_t leftEngineDutyCycle = leftEngine_->getDutyCycle();
    uint8_t rightEngineDutyCycle = rightEngine_->getDutyCycle();
    Direction leftEngineDirection = leftEngine_->getDirection();
    Direction rightEngineDirection = rightEngine_->getDirection();

    // Set engines to turn
    leftEngine_->setDirection(leftDirection);
    rightEngine_->setDirection(rightDirection);
    leftEngine_->setDutyCycle(PWM_DUTY_CYCLE_HALF);
    rightEngine_->setDutyCycle(PWM_DUTY_CYCLE_HALF);

    if(leftDirection == Direction::FORWARD &&
       rightDirection == Direction::BACKWARD) {
        while(!makerLine_->isFarRightSensorHigh()) {}
    }
    if(leftDirection == Direction::BACKWARD &&
       rightDirection == Direction::FORWARD) {
        while(!makerLine_->isFarLeftSensorHigh()) {}
    }

    if (leftDirection == Direction::FORWARD &&
       rightDirection == Direction::BACKWARD){
        while (!makerLine_->isCloseRightSensorHigh()){}
            leftEngine_->setDirection(rightDirection);
            rightEngine_->setDirection(leftDirection);
            leftEngine_->setDutyCycle(BRAKE_PWM);
            rightEngine_->setDutyCycle(BRAKE_PWM);
            _delay_ms(BRAKE_DELAY_MS);
    }

    if (leftDirection == Direction::BACKWARD &&
       rightDirection == Direction::FORWARD){
        while (!makerLine_->isCloseLeftSensorHigh()){}
            leftEngine_->setDirection(rightDirection);
            rightEngine_->setDirection(leftDirection);
            leftEngine_->setDutyCycle(BRAKE_PWM);
            rightEngine_->setDutyCycle(BRAKE_PWM);
            _delay_ms(BRAKE_DELAY_MS);
    }

    // Restore initial engine states
    leftEngine_->setDirection(leftEngineDirection);
    rightEngine_->setDirection(rightEngineDirection);
    leftEngine_->setDutyCycle(leftEngineDutyCycle);
    rightEngine_->setDutyCycle(rightEngineDutyCycle);
}

void Drivetrain::wait(uint8_t delay) {
    for(int i = 0; i < delay; i++)
        _delay_ms(WAIT_DELAY_MULTIPLIER);
}

void Drivetrain::kickStartEngines() {
    leftEngine_->setDutyCycle(250);
    rightEngine_->setDutyCycle(250);
    _delay_ms(50);
}

void Drivetrain::stopEngines() {
    leftEngine_->setDirection(Direction::NEUTRAL);
    rightEngine_->setDirection(Direction::NEUTRAL);
}

void Drivetrain::moveForward(uint8_t dutyCycle) {
    move(Direction::FORWARD, dutyCycle);
}

void Drivetrain::moveBackward(uint8_t dutyCycle) {
    move(Direction::BACKWARD, dutyCycle);
}

void Drivetrain::turnRightMakerLine() {
    turnMakerLine(Direction::FORWARD, Direction::BACKWARD);
}

void Drivetrain::turnLeftMakerLine() {
    turnMakerLine(Direction::BACKWARD, Direction::FORWARD);
}

void Drivetrain::turnRight(uint16_t turnTime) {
    turn(Direction::FORWARD, Direction::BACKWARD, turnTime);
}

void Drivetrain::turnLeft(uint16_t turnTime) {
    turn(Direction::BACKWARD, Direction::FORWARD, turnTime);
}

void Drivetrain::turn180(uint16_t turnTime) {
    turn(Direction::FORWARD, Direction::BACKWARD, turnTime);
}

void Drivetrain::center() {
    uint8_t leftEngineDutyCycle = leftEngine_->getDutyCycle();
    uint8_t rightEngineDutyCycle = rightEngine_->getDutyCycle();

    if(makerLine_->isCloseLeftSensorHigh() ||
       makerLine_->isFarLeftSensorHigh()) {
        leftEngine_->setDutyCycle(CENTER_CORRECTION_PWM);
        while(makerLine_->isCloseLeftSensorHigh() ||
              makerLine_->isFarLeftSensorHigh()) {
            if(makerLine_->is2LeftSensorsHigh() ||
               makerLine_->is2RightSensorsHigh()) {
                break;
            }
        }
        leftEngine_->setDutyCycle(leftEngineDutyCycle);
    } else if(makerLine_->isCloseRightSensorHigh() ||
              makerLine_->isFarRightSensorHigh()) {
        rightEngine_->setDutyCycle(CENTER_CORRECTION_PWM);
        while(makerLine_->isCloseRightSensorHigh() ||
              makerLine_->isFarRightSensorHigh()) {
            if(makerLine_->is2RightSensorsHigh() ||
               makerLine_->is2LeftSensorsHigh()) {
                break;
            }
        }
        rightEngine_->setDutyCycle(rightEngineDutyCycle);
    }
}
