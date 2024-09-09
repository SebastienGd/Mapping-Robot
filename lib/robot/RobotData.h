/* Authors: Simon Asmar, Alexandre Brassard, Maya Forest and Sébastien Girard
* Group : 03
* Team : 6076
* Date : 2024-03-18
*
* Name of file : RobotData.h
* Description : This file defines the different constants used to 
*               manipulate the following classes located inside
*               the RobotData struct : Engine, Piezo and Led.
* Material components used : See includes. (None other). 
* Pins in input : None.
* Pins in output : PA0, PA1, PB2, PB3, PD4, PD5, PD6, PD7
*/

#pragma once

#include "Engine.h"
#include "Led.h"
#include "Memoire_24.h"
#include "Piezo.h"


//engines
#define ENGINE_TIMER TimerNumber::TIMER_0
#define ENGINE_PORT PORTB
#define ENGINE_DDRX DDRB

//left engine
#define ENGINE_LEFT_PWM_CHANNEL OutputCompareChannel::A
#define ENGINE_LEFT_PWM_PIN PB3
#define ENGINE_LEFT_DIRECTION_PIN PB5
#define ENGINE_LEFT_STRENGTH_INDEX 1.0f

//right engine
#define ENGINE_RIGHT_PWM_CHANNEL OutputCompareChannel::B
#define ENGINE_RIGHT_PWM_PIN PB4
#define ENGINE_RIGHT_DIRECTION_PIN PB2
#define ENGINE_RIGHT_STRENGTH_INDEX 1.0f



