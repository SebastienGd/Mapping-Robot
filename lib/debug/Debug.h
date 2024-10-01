/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-03-08
*
* Name of file : Debug.h
* Description : Replaces the Debug command by the method to transmit from the
*               robot (see Communication.h).
* Material components used : None.
* Pins in input : None.
* Pins in output : None.
*/

#pragma once

#include "Communication.h"

#ifdef DEBUG
# define DEBUG_PRINT(x) Communication::getInstance().transmit(x)
#else
# define DEBUG_PRINT(x) \
     do { \
     } while(false)
#endif
