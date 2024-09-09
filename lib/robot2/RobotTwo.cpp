/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : RobotTwo.cpp
* Description : This header file defines a class for utilizing all components required to do the second robot's routine,
* from its movement, down to sending all the data to the first robot.
* Material components used : Piezoelectric buzzer, both engines, the robot's makerline, the robot's button, a second white button, 
* the robot's led, an infrared transmitter led.
* Pins in input : None.
* Pins in output : Depends on Timer used (PWM pins), Ground PIN.
*/

#include "RobotTwo.h"

RobotTwo::RobotTwo(Drivetrain* driveTrain,
                   MakerLine* makerLine,
                   Timer<DELAY_TIMER>* timer,
                   Led* led,
                   Button* buttonInterrupt,
                   Button* buttonWhite):
    driveTrain_(driveTrain),
    makerLine_(makerLine),
    timer_(timer),
    led_(led),
    buttonInterrupt_(buttonInterrupt),
    buttonWhite_(buttonWhite){};

RobotCourse RobotTwo::center() {
    driveTrain_->moveForward(MOVE_FORWARD_PWM);
    while(!(makerLine_->isAllSensorsLow() && canTurnLeft_) &&
          !(canTurnLeft_ && makerLine_->is2LeftSensorsHigh() &&
            isVertical_ == false) &&
          !makerLine_->is2RightSensorsHigh()) {
        driveTrain_->center();
    }
    if(makerLine_->isAllSensorsHigh())
        return RobotCourse::TURNRIGHT;
    else if(makerLine_->is2RightSensorsHigh())
        return RobotCourse::TURNRIGHT;
    else if(makerLine_->is2LeftSensorsHigh())
        return RobotCourse::TURNLEFT;
    else if(makerLine_->isAllSensorsLow())
        return RobotCourse::TURN180;
    return RobotCourse::LINE;
}

RobotCourse RobotTwo::turnRight(uint16_t& nTurns, uint16_t& gCounter) {
    canTurnLeft_ = true;
    if(nTurns != 0) {
        if(nTurns == N_TURNS_BOTTOM_SECTION) { 
            isVertical_ = false;
            lineArray_[lineArrayIndex_ - 1].inchesToLeftBorder =
                FRAME_LENGTH - distanceUtils::convertCounterToDistance(gCounter);
            lineArray_[lineArrayIndex_ - 1].vertical = Vertical::DOWN;
        } else if(nTurns == 1) {
            Line line = distanceUtils::initiliazeLine(gCounter, isVertical_);
            distanceUtils::computeLine(lineArray_, line, lineArrayIndex_,isVertical_);
        }
    }
    ++nTurns;
    _delay_ms(FULL_STOP_DELAY_MS);
    driveTrain_->stopEngines();
    _delay_ms(DELAY_MS_BEFORE_TURN);
    timerUtils::resetTimer(timer_, gCounter);
    driveTrain_->turnRight(); 
    driveTrain_->turnRightMakerLine();
    if(gCounter > OVER_TURN_MARGIN_DELAY) { 
        timerUtils::resetTimer(timer_, gCounter);
        return RobotCourse::TURN180FRAME;
    } else {
        _delay_ms(FULL_STOP_DELAY_MS);
        timerUtils::resetTimer(timer_, gCounter);
        return RobotCourse::LINE;
    }
}

RobotCourse RobotTwo::turnLeft() {
    timerUtils::stopTimer(timer_);
    _delay_ms(FULL_STOP_DELAY_MS);
    driveTrain_->stopEngines();
    _delay_ms(DELAY_MS_BEFORE_TURN);
    driveTrain_->turnLeft();        
    driveTrain_->turnLeftMakerLine(); 
    _delay_ms(FULL_STOP_DELAY_MS);
    for(uint16_t i = 1; i < (lineArrayIndex_ - 1); ++i)
        if(lineArray_[i].vertical == Vertical::UP)
            lineArray_[i].inchesToLeftBorder += 4;
    return RobotCourse::DECISION;
}

RobotCourse RobotTwo::turn180(uint16_t& nTurns, uint16_t& gCounter) {
    canTurnLeft_ = false;
    lineArray_[lineArrayIndex_ - 1].lenght =
        distanceUtils::computeLineType(gCounter);
    nTurns = 0;
    _delay_ms(FULL_STOP_180_TURN_DELAY_MS);
    driveTrain_->stopEngines();
    _delay_ms(1100);
    driveTrain_->turnLeft(); 
    driveTrain_->turnLeftMakerLine();
    _delay_ms(FULL_STOP_DELAY_MS);
    timerUtils::resetTimer(timer_, gCounter);
    return RobotCourse::LINE;
}

RobotCourse RobotTwo::turn180Frame(uint16_t& nTurns, uint16_t& gCounter) {
    canTurnLeft_ = false;
    lineArray_[lineArrayIndex_ - 1].lenght = Lenght::FOUR_POINT_FIVE;
    _delay_ms(HALF_SECOND_DELAY);
    driveTrain_->turnLeft();
    driveTrain_->turnLeftMakerLine();
    _delay_ms(FULL_STOP_DELAY_MS);
    nTurns = 1;
    timerUtils::resetTimer(timer_, gCounter);
    return RobotCourse::LINE;
}

RobotCourse RobotTwo::decision() {
    Timer<TimerNumber::TIMER_2> timerPiezo;
    Piezo<TimerNumber::TIMER_2> piezo(&timerPiezo, &PORTD, &DDRD, PD5);
    led_->turnOnRed();
    while(true) {
        if(buttonInterrupt_->isPressed()) {
            piezo.playSuccessiveNotes(HIGH_NOTE, 3);
            return RobotCourse::TRANSMIT;
        } else if(buttonWhite_->isPressed()) {
            return RobotCourse::RS232;
        }
    }
    return RobotCourse::DECISION;
}

RobotCourse RobotTwo::transmit() {
    led_->turnOff();
    _delay_ms(DELAY_MS_BEFORE_TRANSMIT);
    Timer<TimerNumber::TIMER_2> transmitterTimer;
    IrTransmitter<TimerNumber::TIMER_2> transmitter(&transmitterTimer);
    transmitter.sendData(lineArray_[1], (lineArrayIndex_ - 2) * sizeof(Line));
    return RobotCourse::DECISION;
}

RobotCourse RobotTwo::rs232() {
    led_->startFlash();

    for(uint16_t i = 1; i < (lineArrayIndex_ - 1); ++i){
        Display::getInstance().insertLine(lineArray_[i]);
    }
    Display::getInstance().displayNotSteve();
    led_->stopFlash();
    return RobotCourse::DECISION;
}

Timer<DELAY_TIMER>* RobotTwo::getTimer() {
    return timer_;
}
