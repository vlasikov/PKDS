/*
 * motor.c
 *
 *  Created on: May 23, 2022
 *      Author: kendor
 */

#include "motor.h"
#include "MotorLib/bldc_scalar_user_interface.h"

ElectricTypeDef drive;
int32_t MotorStepTimer = 0;
int32_t HallTimer = 0;




/*Private functions*/
void HallTimerProc(void *args);
void MotorStepProc(void *args);


void MotorInit (void)
{
    MotorStepTimer = SYSTIMER_CreateTimer(1000, SYSTIMER_MODE_PERIODIC, MotorStepProc, NULL );
	HallTimer = SYSTIMER_CreateTimer(100, SYSTIMER_MODE_PERIODIC, HallTimerProc, NULL );

	SYSTIMER_StartTimer(HallTimer);
	SYSTIMER_StartTimer(MotorStepTimer);
    Motor0_BLDC_SCALAR_Init();
}

void MotorStart(void)
{
	Motor0_BLDC_SCALAR_MotorStart();
}
void MotorStop(void)
{
	DIGITAL_IO_ToggleOutput(&STATUS_LED_G);
	Motor0_BLDC_SCALAR_MotorStop();
}

void MotorSetSpeed(int32_t speed)
{
	Motor0_BLDC_SCALAR_SetSpeedVal(speed);
}
void MotorSetProportionalGain(uint16_t kp)
{
	Motor0_BLDC_SCALAR_SetSpeedProportionalGain(kp);
}
void MotorSetIntegralGain(uint16_t ki)
{
	Motor0_BLDC_SCALAR_SetSpeedIntegralGain(ki);
}
void MotorSetPILimit(uint8_t percent_limit)
{
	Motor0_BLDC_SCALAR_SetSpeedPILimit(percent_limit);
}

void MotorClearError(void)
{
	Motor0_BLDC_SCALAR_ClearErrorState();
}

void MotorRead(void)
{
	int32_t Cur,Vel;

	Motor0_BLDC_SCALAR_GetAverageDCLinkCurrent(&drive.RAWCurrent);
	Cur = abs(drive.RAWCurrent);
	drive.Current = (uint16_t)Cur;
	Motor0_BLDC_SCALAR_GetMotorSpeed(&drive.RAWVelocity);
	Vel = abs(drive.RAWVelocity);
	drive.Velocity = (uint16_t)Vel;
}
void HallTimerProc(void *args)
{
	uint32_t hall  = 0;
	static uint32_t prev_hall = 0;

	hall = Motor0_BLDC_SCALAR_SPEED_POS_HALL_GetHallPosition();
	if (hall != prev_hall)
	{
		if ((hall == 1) && (prev_hall == 5)) drive.RAWPosition++;
		if ((hall == 1) && (prev_hall == 3)) drive.RAWPosition--;

		if ((hall == 3) && (prev_hall == 1)) drive.RAWPosition++;
		if ((hall == 3) && (prev_hall == 2)) drive.RAWPosition--;

		if ((hall == 2) && (prev_hall == 3)) drive.RAWPosition++;
		if ((hall == 2) && (prev_hall == 6)) drive.RAWPosition--;

		if ((hall == 6) && (prev_hall == 2)) drive.RAWPosition++;
		if ((hall == 6) && (prev_hall == 4)) drive.RAWPosition--;

		if ((hall == 4) && (prev_hall == 6)) drive.RAWPosition++;
		if ((hall == 4) && (prev_hall == 5)) drive.RAWPosition--;

		if ((hall == 5) && (prev_hall == 4)) drive.RAWPosition++;
		if ((hall == 5) && (prev_hall == 1)) drive.RAWPosition--;
	}
	prev_hall = hall;
	drive.Position = (uint16_t) abs(drive.RAWPosition);
}

void MotorStepProc(void *args)
{
	Motor0_BLDC_SCALAR_MSM();
}
