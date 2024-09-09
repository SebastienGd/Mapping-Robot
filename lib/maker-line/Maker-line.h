/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : Maker-line.h
* Description : This header file defines a class that initializes a line-maker to be used on the second robot.
* Material components used : Line-maker
* Pins in input : None.
* Pins in output : D1, D2, D3 , D4, D5.
*/

#pragma once

struct MakerLineData{
    volatile uint8_t* ddrX;
    volatile uint8_t* pinX;
    uint8_t pinDI1;
    uint8_t pinDI2;
    uint8_t pinDI3;
    uint8_t pinDI4;
    uint8_t pinDI5;
};

class MakerLine{
public:
    MakerLine(MakerLineData& makerLineData) :
                pinX_(makerLineData.pinX), 
                pinDI1_(makerLineData.pinDI1), 
                pinDI2_(makerLineData.pinDI2), 
                pinDI3_(makerLineData.pinDI3), 
                pinDI4_(makerLineData.pinDI4), 
                pinDI5_(makerLineData.pinDI5) {
        *makerLineData.ddrX &= ~((1 << pinDI1_) | (1 << pinDI2_) | (1 << pinDI3_) | (1 << pinDI4_) | (1 << pinDI5_));
    }
    
    bool isFarLeftSensorHigh() const {
        return (*pinX_ & (1 << pinDI1_));
    }

    bool isCloseLeftSensorHigh() const {
        return (*pinX_ & (1 << pinDI2_));
    }

    bool isMiddleSensorHigh() const {
        return (*pinX_ & (1 << pinDI3_));
    }

    bool isCloseRightSensorHigh() const {
        return (*pinX_ & (1 << pinDI4_));
    }

    bool isFarRightSensorHigh() const {
        return (*pinX_ & (1 << pinDI5_));
    }

    bool isAllSensorsHigh() const {
        return (isFarLeftSensorHigh() && isCloseLeftSensorHigh() && isMiddleSensorHigh() 
        && isCloseRightSensorHigh() && isFarRightSensorHigh());
    }

    bool isAllSensorsLow() const {
        return !(isFarLeftSensorHigh() || isCloseLeftSensorHigh() || isMiddleSensorHigh() 
        || isCloseRightSensorHigh() || isFarRightSensorHigh());
    }

    bool is2LeftSensorsHigh() const {
        return (isFarLeftSensorHigh() && isMiddleSensorHigh());
    }

    bool is2RightSensorsHigh() const {
        return (isFarRightSensorHigh() && isMiddleSensorHigh());
    }
private:
    volatile uint8_t* pinX_;
    uint8_t pinDI1_;
    uint8_t pinDI2_;
    uint8_t pinDI3_;
    uint8_t pinDI4_;
    uint8_t pinDI5_;
};