/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-03-21

* Name of file : Line.h
* Description : This header file defines a class that allows to categorizes all 4 to 6 segments added to the final exam's track.
*/

#pragma once

#include <avr/io.h>

enum Lenght {
    NONE,
    FOUR_POINT_FIVE,
    SIX_POINT_FIVE,
    EIGHT_POINT_FIVE
};

enum Vertical {
    NOWHERE,
    UP,
    DOWN
};

class Line {
public:
    Line();

private:
    //Lenght lenght = Lenght::NONE;
    //Vertical vertical = Vertical::NOWHERE;
};
