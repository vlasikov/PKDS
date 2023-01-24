/*
 * motor.h
 *
 *  Created on: May 23, 2022
 *      Author: kendor
 */

#ifndef MOTORLIB_MOTOR_H_
#define MOTORLIB_MOTOR_H_

#include <DAVE.h>




void MotorInit(void);

void MotorStart(void);
void MotorStop(void);
void MotorRead(void);

//void MotorGetCurrent(int32_t *current);
//void MotorGetSpeed(int32_t *speed);

void MotorSetSpeed(int32_t speed);
void MotorSetProportionalGain(uint16_t kp);
void MotorSetIntegralGain(uint16_t ki);
void MotorSetPILimit(uint8_t percent_limit);

void MotorClearError(void);



typedef struct __ElectricDriveTypeDef
{

	uint16_t Position;
	uint16_t Current;
	uint16_t Velocity;

	int32_t RAWPosition;
	int32_t RAWVelocity;
	int32_t RAWCurrent;

	uint8_t Referenced;

}ElectricTypeDef;


extern ElectricTypeDef drive;


#endif /* MOTORLIB_MOTOR_H_ */
