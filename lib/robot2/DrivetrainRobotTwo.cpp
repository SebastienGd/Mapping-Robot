/* Authors: Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-10-01
*
* Name of file : DriveTrainRobotTwo.cpp
* Description : This header file defines a specialized 
*               drivetrain controller for robot two.
* Material components used : Two engines.
* Pins in input : None.
* Pins in output : Any PWM pin.
*/

#include "DrivetrainRobotTwo.h"

DrivetrainRobotTwo::DrivetrainRobotTwo(Engine<ENGINE_TIMER>* rightEngine, Engine<ENGINE_TIMER>* leftEngine, MakerLine* makerLine)
    : BaseDrivetrain(rightEngine, leftEngine), makerLine_(makerLine) {}

void DrivetrainRobotTwo::turnRight(uint16_t turnTime) {
    turn(Direction::FORWARD, Direction::BACKWARD, turnTime);
    turnMakerLine(Direction::FORWARD, Direction::BACKWARD);
}

void DrivetrainRobotTwo::turnLeft(uint16_t turnTime) {
    turn(Direction::BACKWARD, Direction::FORWARD, turnTime);
    turnMakerLine(Direction::BACKWARD, Direction::FORWARD);
}

void DrivetrainRobotTwo::center() {
    uint8_t leftEngineDutyCycle = leftEngine_->getDutyCycle();
    uint8_t rightEngineDutyCycle = rightEngine_->getDutyCycle();

    if (makerLine_->isCloseLeftSensorHigh() || makerLine_->isFarLeftSensorHigh()) {
        leftEngine_->setDutyCycle(CENTER_CORRECTION_PWM);
        while (makerLine_->isCloseLeftSensorHigh() || makerLine_->isFarLeftSensorHigh()) {
            if (makerLine_->is2LeftSensorsHigh() || makerLine_->is2RightSensorsHigh()) {
                break;
            }
        }
        leftEngine_->setDutyCycle(leftEngineDutyCycle);
    } else if (makerLine_->isCloseRightSensorHigh() || makerLine_->isFarRightSensorHigh()) {
        rightEngine_->setDutyCycle(CENTER_CORRECTION_PWM);
        while (makerLine_->isCloseRightSensorHigh() || makerLine_->isFarRightSensorHigh()) {
            if (makerLine_->is2RightSensorsHigh() || makerLine_->is2LeftSensorsHigh()) {
                break;
            }
        }
        rightEngine_->setDutyCycle(rightEngineDutyCycle);
    }
}

void DrivetrainRobotTwo::turnMakerLine(Direction leftDirection, Direction rightDirection) {
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

    if (leftDirection == Direction::FORWARD && rightDirection == Direction::BACKWARD) {
        while (!makerLine_->isFarRightSensorHigh()) {}
    }
    if (leftDirection == Direction::BACKWARD && rightDirection == Direction::FORWARD) {
        while (!makerLine_->isFarLeftSensorHigh()) {}
    }

    if (leftDirection == Direction::FORWARD && rightDirection == Direction::BACKWARD) {
        while (!makerLine_->isCloseRightSensorHigh()) {
            leftEngine_->setDirection(rightDirection);
            rightEngine_->setDirection(leftDirection);
            leftEngine_->setDutyCycle(BRAKE_PWM);
            rightEngine_->setDutyCycle(BRAKE_PWM);
            _delay_ms(BRAKE_DELAY_MS);
        }
    }

    if (leftDirection == Direction::BACKWARD && rightDirection == Direction::FORWARD) {
        while (!makerLine_->isCloseLeftSensorHigh()) {
            leftEngine_->setDirection(rightDirection);
            rightEngine_->setDirection(leftDirection);
            leftEngine_->setDutyCycle(BRAKE_PWM);
            rightEngine_->setDutyCycle(BRAKE_PWM);
            _delay_ms(BRAKE_DELAY_MS);
        }
    }

    // Restore initial engine states
    leftEngine_->setDirection(leftEngineDirection);
    rightEngine_->setDirection(rightEngineDirection);
    leftEngine_->setDutyCycle(leftEngineDutyCycle);
    rightEngine_->setDutyCycle(rightEngineDutyCycle);
}
