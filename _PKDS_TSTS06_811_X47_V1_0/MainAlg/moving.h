/*
 * moving.h
 *
 *  Created on: Feb 8, 2022
 *      Author: kendor
 */

#ifndef MAINALG_MOVING_H_
#define MAINALG_MOVING_H_

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "xmc_common.h"

//
//extern int32_t Velocity ;
//extern int32_t Current;
////extern int32_t ACurrent;
////extern int32_t ICurrent;
//
//
//extern int32_t Max_Close_current;
//extern int32_t Max_Open_current;
//extern int32_t Max_Velocity;
//extern int32_t Min_Velocity;
//


int32_t Homing(int32_t cmd);
int32_t CloseDoor(int32_t cmd);
int32_t OpenDoor(int32_t cmd);
int32_t OpenAfterBlockage (int32_t cmd);

//void MotorWrite(int32_t cmd, int32_t direction, int32_t ramp, int32_t start_value, int32_t end_value);
//void MotorStop(void);

//void MotorStepProc(void *args);




#endif /* MAINALG_MOVING_H_ */
