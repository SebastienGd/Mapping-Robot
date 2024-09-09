/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : Display.h
* Description : This file defines all functions of the Display class, allowing for the robot to edit and print the map.
* This class uses the RS232 protocol to send all informations to a PC.
*/

#pragma once

#include "DisplayConstants.h"
#include "Memoire_24.h"

using namespace displayConstants;

#include <avr/io.h>

class Display {
public:
    Display();
    static Display& getInstance();

    void insertBot(uint8_t input, uint8_t isInverted = 0);
    // isInverted = 0 if it is not inverted

    void insertLine(Line line);

    void displaySteve(); // prints the map with the signature
    void displayNotSteve(); // prints the map with an empty signature

    void failSafeLines();
    void failSafeRobot();

    void printMap();
    void testing();

    Line* getLines();

private:
    static Display instance_;

    Line lines[MAX_NBR_LINES];
    uint8_t nbrOfLines = 0;

    const char* getUnicode(char letter);
    char getTableChar(uint16_t index);
    void setTableChar(uint16_t index, char letter);

    uint8_t getRobotYOffset(uint8_t value);
    uint16_t getCoordinates(uint8_t x, uint8_t y, Dimensions size = MAP);

    void insertToMap(const char origin[],
                     Dimensions originSize,
                     Coordinates destination);
    void revertBot();

    // only cryptic instanciations below this point
    // aka the key, the tableMap and the botMap

    const char* KEY[28] = {
        " ",  // 0 a
        "┌",  // 1 b
        "─",  // 2 c
        "┐",  // 3 d
        "│",  // 4 e
        "┏",  // 5 f
        "━",  // 6 g
        "┓",  // 7 h
        "┃",  // 8 i
        "╔",  // 9 j
        "═",  // 10 k
        "╗",  // 11 l
        "║",  // 12 m
        "╣",  // 13 n
        "╚",  // 14 o
        "╝",  // 15 p
        "┗",  // 16 q
        "┛",  // 17 r
        "└",  // 18 s
        "┘",  // 19 t
        "_",  // 20 u
        "/",  // 21 v
        "\\", // 22 w
        "⎸",  // 23 x
        "⎹",  // 24 y
        "▓",  // 25 z
        "╦",  // 26 A
        "╩",  // 27 B
    };

    /*
        // clang-format off

        char tableMap[(MAP.HEIGHT * MAP.WIDTH) + 1] = // the + 1 is because of
       the \0 added at the end
         "bcccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccd"
         "eaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaae"
         "eaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaae"
         "eaaaaafggggggggggggggggggggggggghaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaiaaaaaaaaajkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkklaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaiaaaaaaaaamaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaiaaaaaaaaamaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaiaaaaaaaaamaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaiaaaaaaaaamaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaiaaaaaaaaamaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaaaaakkkkkknaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaiaaaaaaaaamaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaiaaaaaaaaamaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaiaaaaaaaaamaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaiaaaaaaaaamaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaiaaaaaaaaamaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaamaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaiaaaaaaaaaokkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkpaaaaaaaae"
         "eaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaiaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaae"
         "eaaaaaqgggggggggggggggggggggggggraaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaae"
         "eaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaae"
         "eaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaae"
         "sccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccct";

        // clang-format on
    */

    const char* signatureMap = "Produit par: Steve\n";

    char botMap[BOT.HEIGHT * BOT.WIDTH + 1] = "auuua"
                                              "vaaaw"
                                              "xaaay"
                                              "zaaaz"
                                              "wuuuv";
};
