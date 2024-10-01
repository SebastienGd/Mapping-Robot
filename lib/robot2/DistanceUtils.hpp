/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17
*
* Name of file : DistanceUtils.h
* Description : Diverse functions to manipulate lines and compute them, before sending them to the Display class.
* Material components used : None.
* Pins in input : None.
* Pins in output : Depends on Timer used (PWM pins), Ground PIN.
*/

#pragma once

#include "DisplayConstants.h"
#include <avr/io.h>

#define TICKS_TO_INCHE 11
#define GCOUNTER_LOWER_THRESHOLD 10
#define GCOUNTER_UPPER_THRESHOLD 70

namespace distanceUtils {
    Line initiliazeLine(uint16_t distance, bool isVertical);
    void storeDistance(Line* distanceDataArray,
                       Line& distanceData,
                       uint16_t& distanceDataArrayIndex);
    void computeLine(Line* lineArray,
                     Line& line,
                     uint16_t& lineArrayIndex,
                     bool isVertical);
    uint16_t convertCounterToDistance(uint16_t counter);
    Lenght computeLineType(uint16_t distance);
}
