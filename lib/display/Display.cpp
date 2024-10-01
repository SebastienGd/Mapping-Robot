/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17
*
* Name of file : Display.cpp
* Description : This file defines all functions of the Display class, allowing for 
*               the robot to edit and print the map.
*               This class uses the RS232 protocol to send all informations to a PC.
* Material components used : None.
* Pins in input : None.
* Pins in output : None.
*/

#include "Display.h"
#include "Communication.h"
#include "DisplayConstants.h"
#include "Memoire_24.h"
#include <avr/io.h>

using namespace DisplayConstants;

Display Display::instance_;

Display::Display() {}

Display& Display::getInstance() {
    return instance_;
}

void Display::insertBot(uint8_t input, uint8_t isInverted) {
    if(input > CLOSEST_ROBOT_ONE_INPUT)
        input = CLOSEST_ROBOT_ONE_INPUT;
    else if(input < FARTHEST_ROBOT_ONE_INPUT)
        input = FARTHEST_ROBOT_ONE_INPUT;

    Coordinates destination = {
        BOT_ZONE.UP_LEFT.X,
        uint8_t(BOT_ZONE.UP_LEFT.Y + getRobotYOffset(input))};

    if(isInverted) {
        revertBot();
        destination.Y = uint8_t(BOT_ZONE.DOWN_RIGHT.Y - getRobotYOffset(input) -
                                BOT.HEIGHT + 1);
    }

    insertToMap(botMap, BOT, destination);
}

void Display::insertLine(Line line) {
    if(nbrOfLines < 6) {
        lines[nbrOfLines++] = line;

        uint8_t yOrigin = LINES_ZONE.UP_LEFT.Y;
        if(line.vertical == Vertical::UP) {
            setTableChar(
                getCoordinates(LINES_ZONE.UP_LEFT.X + line.inchesToLeftBorder,
                               uint8_t(line.vertical)),
                'A');

        } else if(line.vertical == Vertical::DOWN) {
            setTableChar(
                getCoordinates(LINES_ZONE.UP_LEFT.X + line.inchesToLeftBorder,
                               uint8_t(line.vertical)),
                'B');

            yOrigin = LINES_ZONE.DOWN_RIGHT.Y + 1 - uint8_t(line.lenght);
        }
        for(int i = 0; i < uint8_t(line.lenght); i++) {
            setTableChar(
                getCoordinates(LINES_ZONE.UP_LEFT.X + line.inchesToLeftBorder,
                               yOrigin + i),
                'm');
        }
    }
}

void Display::printMap() {
    for(int i = 0; i < (MAP.HEIGHT * MAP.WIDTH); i++) {
        if(i % (MAP.WIDTH) == 0 && i != 0)
            Communication::getInstance().transmit("\n");
        Communication::getInstance().transmit(getUnicode(getTableChar(i)));
    }
    Communication::getInstance().transmit("\n");
}

const char* Display::getUnicode(char letter) {
    if('a' <= letter && letter <= 'z') {
        return KEY[uint8_t(letter) - uint8_t('a')];
    } else if('A' <= letter && letter <= 'Z') {
        return KEY[uint8_t(letter) - uint8_t('A') +
                   26]; // 26 being the number of letters in the alphabet
    } else
        return "Error";
}

uint16_t Display::getCoordinates(uint8_t x, uint8_t y, Dimensions size) {
    return uint16_t((size.WIDTH * y) + x);
}

void Display::insertToMap(const char origin[],
                          Dimensions originSize,
                          Coordinates destination) {
    for(int y = 0; y < originSize.HEIGHT; y++) {
        for(int x = 0; x < originSize.WIDTH; x++) {
            setTableChar(getCoordinates(destination.X + x, destination.Y + y),
                         origin[uint8_t(getCoordinates(x, y, BOT))]);
        }
    }
}

void Display::revertBot() {
    // These next four lines switch the "tires" with the lines just above them
    // to "flip" the robot.
    botMap[getCoordinates(0, 2, BOT)] = 'z';
    botMap[getCoordinates(BOT.WIDTH - 1, 2, BOT)] = 'z';

    botMap[getCoordinates(0, 3, BOT)] = 'x';
    botMap[getCoordinates(BOT.WIDTH - 1, 3, BOT)] = 'y';
}

uint8_t Display::getRobotYOffset(uint8_t value) {
    uint8_t inputRange = (CLOSEST_ROBOT_ONE_INPUT - FARTHEST_ROBOT_ONE_INPUT);
    uint8_t deltaRange =
        (BOT_ZONE.dimensions.HEIGHT - BOT.HEIGHT - SIX_INCH_OFFSET);
    uint8_t levelledInput = (CLOSEST_ROBOT_ONE_INPUT - value);
    uint16_t bigNumber = (levelledInput * deltaRange);
    uint8_t backToSmallNumber = (bigNumber / inputRange);
    return uint8_t(backToSmallNumber + SIX_INCH_OFFSET);
}

char Display::getTableChar(uint16_t index) {
    unsigned char letter;
    Memoire24CXXX::getInstance().lecture(TABLE_MAP_MEM_LOCATION + index,
                                         &letter);
    return letter;
}

void Display::setTableChar(uint16_t index, char letter) {
    Memoire24CXXX::getInstance().ecriture(TABLE_MAP_MEM_LOCATION + index,
                                          letter);
}

void Display::displaySteve() {
    printMap();
    Communication::getInstance().transmit(signatureMap);
}

void Display::displayNotSteve() {
    printMap();
    Communication::getInstance().transmit("\n");
}

void Display::failSafeLines() {
    insertLine({Lenght::EIGHT_POINT_FIVE, Vertical::UP, 10});
    insertLine({Lenght::EIGHT_POINT_FIVE, Vertical::UP, 22});
    insertLine({Lenght::FOUR_POINT_FIVE, Vertical::UP, 36});

    insertLine({Lenght::FOUR_POINT_FIVE, Vertical::DOWN, 32});
    insertLine({Lenght::SIX_POINT_FIVE, Vertical::DOWN, 12});
}

void Display::failSafeRobot() {
    insertBot(FARTHEST_ROBOT_ONE_INPUT + 5, 0);
}

Line* Display::getLines(){
    return lines;
}