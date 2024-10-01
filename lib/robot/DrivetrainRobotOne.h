/* Authors: Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-10-01
*
* Name of file : DriveTrainRobotOne.h
* Description : This header file defines a specialized 
*               drivetrain controller for robot one.
* Material components used : Two engines.
* Pins in input : None.
* Pins in output : Any PWM pin.
*/

#pragma once 
#include "BaseDrivetrain.h"

class DrivetrainRobotOne : public BaseDrivetrain {
    public:
        DrivetrainRobotOne(Engine<ENGINE_TIMER>* rightEngine, Engine<ENGINE_TIMER>* leftEngine) : BaseDrivetrain(rightEngine, leftEngine){};

        void turnRight(uint16_t turnTime) {
            turn(Direction::FORWARD, Direction::BACKWARD, turnTime);
        };

        void turnLeft(uint16_t turnTime) {
            turn(Direction::BACKWARD, Direction::FORWARD, turnTime);
        };
};