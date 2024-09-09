/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : DistanceUtils.cpp
* Description : Diverse functions to manipulate lines and compute them, before sending them to the Display class.
* Pins in input : None.
* Pins in output : Depends on Timer used (PWM pins), Ground PIN.
*/

#include "DistanceUtils.hpp"

namespace distanceUtils {
    Line initiliazeLine(uint16_t distance, bool isVertical) {
        Line lineData;
        lineData.vertical = isVertical ? Vertical::UP : Vertical::DOWN;
        lineData.inchesToLeftBorder = convertCounterToDistance(distance);

        return lineData;
    }

    void storeDistance(Line* lineArray, Line& line, uint16_t& lineArrayIndex) {
        lineArray[lineArrayIndex] = line;
        ++lineArrayIndex;
    }

    void computeLine(Line* lineArray,
                     Line& line,
                     uint16_t& lineArrayIndex,
                     bool isVertical) {
        if(lineArrayIndex == 0)
            storeDistance(lineArray, line, lineArrayIndex);
        else if(isVertical)
            line.inchesToLeftBorder +=
                lineArray[lineArrayIndex - 1].inchesToLeftBorder;
        else line.inchesToLeftBorder =
                lineArray[lineArrayIndex - 1].inchesToLeftBorder - line.inchesToLeftBorder ;
        storeDistance(lineArray, line, lineArrayIndex);
    }

    uint16_t convertCounterToDistance(uint16_t counter) {
        return counter / TICKS_TO_INCHE;
    }

    Lenght computeLineType(uint16_t distance) {
        if(distance > GCOUNTER_LOWER_THRESHOLD && distance < GCOUNTER_UPPER_THRESHOLD) // Verifier
            return Lenght::SIX_POINT_FIVE;
        else if(distance >= GCOUNTER_UPPER_THRESHOLD)
            return Lenght::EIGHT_POINT_FIVE;
        return Lenght::FOUR_POINT_FIVE;
    }

}
