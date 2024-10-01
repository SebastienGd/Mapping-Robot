/* Authors: Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-10-01
*
* Name of file : DriveTrainRobotTwo.h
* Description : This header file defines a specialized 
*               drivetrain controller for robot two.
* Material components used : Two engines.
* Pins in input : None.
* Pins in output : Any PWM pin.
*/

#pragma once

#include "BaseDrivetrain.h"
#include "Maker-line.h"

#define BRAKE_PWM 200
#define BRAKE_DELAY_MS 50
#define CENTER_CORRECTION_PWM 50

class DrivetrainRobotTwo : public BaseDrivetrain {
    public:
        DrivetrainRobotTwo(Engine<ENGINE_TIMER>* rightEngine, Engine<ENGINE_TIMER>* leftEngine, MakerLine* makerLine);

        void turnRight(uint16_t turnTime);
        void turnLeft(uint16_t turnTime);
        void center();

        ~DrivetrainRobotTwo(){};

    private:
        void turnMakerLine(Direction leftDirection, Direction rightDirection);

        MakerLine* makerLine_;
};
