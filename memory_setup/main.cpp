/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-04-17

* Name of file : main.cpp
* Description : Main file for the memory setup. Stores the map inside the external memory of the robot, without any added lines.
*/

#include "Debug.h"
#include "DisplayConstants.h"
#include "Memoire_24.h"

#include <avr/io.h>
#ifndef F_CPU
# define F_CPU 8000000
#endif
#include <avr/pgmspace.h> //used to store arrays in the flash to free up limited space in sram
#include <util/delay.h>

using namespace DisplayConstants;
// const uint8_t BINARY_INSTRUCTIONS[] PROGMEM
// clang-format off

static constexpr char TABLE_MAP[] PROGMEM =
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

static constexpr uint16_t TABLE_MAP_SIZE = sizeof(TABLE_MAP);

// clang-format on

int main() {
    uint16_t address = 0;
    // char charBuffer[2] = {}; // only useful to DEBUG_PRINT by printing a
                             // character followed by '\0'
    for(uint16_t i = 0; i < TABLE_MAP_SIZE - 1; i++) {
        // charBuffer[0] = pgm_read_byte(&TABLE_MAP[i]);
        // DEBUG_PRINT(charBuffer);
        Memoire24CXXX::getInstance().ecriture(address++, pgm_read_byte(&TABLE_MAP[i]));
        _delay_ms(5);
    }

    // DEBUG_PRINT("Terminer");
    return 0;
}
