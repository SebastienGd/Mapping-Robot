#pragma once

#include <avr/io.h>

struct Dimensions {
    uint8_t WIDTH;
    uint8_t HEIGHT;
};

struct Coordinates {
    uint8_t X;
    uint8_t Y;
};

struct Zone {
    constexpr Zone(Coordinates upLeft, Coordinates downRight):UP_LEFT(upLeft),DOWN_RIGHT(downRight){}
    Coordinates UP_LEFT, DOWN_RIGHT;
    Dimensions dimensions = {(uint8_t) (DOWN_RIGHT.X - UP_LEFT.X + 1),
                             (uint8_t) (DOWN_RIGHT.Y - UP_LEFT.Y + 1)};
};

namespace displayConstants {

    static constexpr Dimensions MAP = {(uint8_t) 101, (uint8_t) 25};
    static constexpr Dimensions BOT = {(uint8_t) 5, (uint8_t) 5};

    static constexpr Zone BOT_ZONE = {
        {(uint8_t) 17,  (uint8_t) 4},
        {(uint8_t) 21, (uint8_t) 20}
    }; // excludes exterior

    static constexpr Zone LINES_ZONE = {
        {(uint8_t) 43,  (uint8_t) 6},
        {(uint8_t) 90, (uint8_t) 18}
    }; // also excludes exterior

    const uint8_t FARTHEST_ROBOT_ONE_INPUT = 0b0001'1001;
    const uint8_t CLOSEST_ROBOT_ONE_INPUT = 0b0101'0100;
    const uint8_t SIX_INCH_OFFSET = 2;

    static constexpr Dimensions ZONE_LINES_INCHES = {(uint8_t) 48,
                                                     (uint8_t) 30};

    static const uint8_t MAX_NBR_LINES = 6;

    static const uint8_t TABLE_MAP_MEM_LOCATION = 0x0000;

} // namespace displayConstants

enum Lenght {
    NONE = 0,
    FOUR_POINT_FIVE = 2,
    SIX_POINT_FIVE = 3,
    EIGHT_POINT_FIVE = 4
}; // numbers obtained through : lenght of line divided by height of zone on
   // table times height of zone in code

enum Vertical {
    NOWHERE = 0,
    UP = displayConstants::LINES_ZONE.UP_LEFT.Y - 1,
    DOWN = displayConstants::LINES_ZONE.DOWN_RIGHT.Y + 1
};

struct Line {
    Lenght lenght = Lenght::NONE;
    Vertical vertical = Vertical::NOWHERE;
    uint8_t inchesToLeftBorder = 0;
};
