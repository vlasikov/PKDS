/*
 * door_periph.c
 *
 *  Created on: Mar 3, 2021
 *      Author: kendor
 */

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "xmc_common.h"
#include "MainAlg/door_periph.h"
#include "MotorLib/bldc_scalar_user_interface.h"
#include "MainAlg/main_alg.h"
#include "stdlib.h"
#include "MainAlg/moving.h"
#include "MainAlg/presets.h"
#include "MainAlg/Peripherials/LedRubber.h"
#include "MainAlg/Peripherials/Buzzer.h"
#include "MainAlg/Peripherials/Scheme.h"


#define CL_RED_OUT 		0x09
#define CL_GREEN_OUT 	0x12
#define CL_YELLOW_OUT   0x1B
#define CL_BLACK_OUT 	0x00


int32_t RAWPosition = 0;
int32_t Position = 0;
int32_t VPower = 0;
volatile int32_t ActiveRubberL =0;
int32_t ActiveRubberR =0;


//int32_t CloseSensor = 0;
//int32_t PassengerButton = 0;
//int32_t DisabledButton = 0;
//int32_t ServiceButton = 0;
//int32_t ServiceButtonFront = 0;
//int32_t PhotoSensor = 0;
//int32_t StopButton = 0;
//int32_t TrapSensor = 0;
//int32_t Open1DoorBut = 0;


void DoorPeriphInit(void)
{

	InitLedRubber(MODE_ON);
	InitBuzzer(BUZZER_TYPE_SFM);

	DIGITAL_IO_SetOutputHigh(&LS_SW_NRES);
	DIGITAL_IO_SetOutputLow(&DI_PNP_EN);
	DIGITAL_IO_SetOutputLow(&DI_NPN_EN);
	DIGITAL_IO_SetOutputLow(&GROUP_IN_EN);
	DIGITAL_IO_SetOutputHigh(&POWER_SWITCH);

	PWM_CCU4_SetFreqAndDutyCycle(&CLUTCH_PWM, 2000, 6000); //5200///5600

}


void ReadInputs(void)
{
	Inputs.PNP = BUS_IO_Read(&DI_PNP);
	Inputs.NPN = BUS_IO_Read(&DI_NPN);
	Inputs.GIN =  BUS_IO_Read(&GROUP_IN);

	if (DIGITAL_IO_GetInput(&SERVICE_BUT))
	{
		Inputs.SBT = 0;
	}
	else
	{
		Inputs.SBT = 1;
	}

	ADC_MEASUREMENT_StartConversion(&ADC_MEASUREMENT_0);







}
/*
void ReadOpen1DoorButton(void)
{
	if(1 == Presets.DOOR_NUMBER)
	{
		if (Inputs.GIN & 0x0002)
		{
			Open1DoorBut = 1;
		}
		else
		{
			Open1DoorBut = 0;
		}

	}
}

void ReadCloseSensor (void)
{

	if (Presets.CLOSE_SENSOR_TYPE)
	{
		if (Inputs.PNP & 0x0008)
		{
			CloseSensor = 0;
		}
		else
		{
			CloseSensor = 1;
		}
	}
	else
	{
		if (Inputs.PNP & 0x0008)
		{
			CloseSensor = 1;
		}
		else
		{
			CloseSensor = 0;
		}
	}
}

void ReadPhotoSensor(void)
{
	if (Inputs.NPN & 0x0004)
	{
		PhotoSensor = 0;
	}
	else
	{
		PhotoSensor = 1;
	}
}

void ReadServiceButton(void)
{
	static uint32_t previous_state;

	if (DIGITAL_IO_GetInput(&SERVICE_BUT))
	{
		ServiceButton = 0;
		//PassengerButton = 0;
	}
	else
	{
		ServiceButton = 1;
		//PassengerButton = 1;
	}
	if (ServiceButton && !previous_state)
	{
		ServiceButtonFront = 1;
	}
	else
	{
		ServiceButtonFront = 0;
	}

	previous_state = ServiceButton;

}
void ReadPassengerButton(void)
{
	uint16_t Group_inputs = 0;

	Group_inputs = BUS_IO_Read(&GROUP_IN);

	if ((Group_inputs & 0x0001))
	{
		 PassengerButton = 1;
	}
	else
	{
		 PassengerButton = 0;
	}

}

void ReadDisabledButton(void)
{
	uint16_t Group_inputs = 0;

	Group_inputs = BUS_IO_Read(&GROUP_IN);

	if ((Group_inputs & 0x0002))
	{
		 DisabledButton = 1;
	}
	else
	{
		 DisabledButton = 0;
	}
}

void ReadActiveRubber(void)
{
	if(Inputs.RIN1 >= Inputs.DCIN)
	{
		ActiveRubberL = 1;
	}
	else
	{
		ActiveRubberL = 0;
	}
}


void WriteClutch(int32_t cmd)
{
	static int32_t cmd_prev = 0;
	static int32_t timer = 0;
	static int32_t count_en = 0;

	if(cmd && !cmd_prev)
	{
		PWM_CCU4_SetFreqAndDutyCycle(&CLUTCH_PWM, 400,(10000 - 5000)); //12V
		PWM_CCU4_Start(&CLUTCH_PWM);
		count_en = 1;
	}

	if(count_en)
	{
		timer++;

		if(timer >= 200)
		{
			count_en = 0;
			timer = 0;
			PWM_CCU4_SetFreqAndDutyCycle(&CLUTCH_PWM, 400, (10000 - 2500)); // <15V
			PWM_CCU4_Start(&CLUTCH_PWM);
		}
	}

	if(cmd)
	{
		PWM_CCU4_Start(&CLUTCH_PWM);
	}
	else
	{
		PWM_CCU4_Stop(&CLUTCH_PWM);
		DIGITAL_IO_SetOutputLow(&HS_SW_1);
		DIGITAL_IO_SetOutputLow(&HS_SW_2);
		count_en = 0;
		timer = 0;
	}
	cmd_prev = cmd;
}
void WritePassengerButton(int32_t cmd)
{
	if(cmd)
	{
		BUS_IO_Write(&GROUP_OUT, 0xFF);
	}
	else
	{
		BUS_IO_Write(&GROUP_OUT, 0x00);
	}
}


int32_t Blockage(int32_t cmd)
{
	static int32_t timer = 0;
	static int32_t previous_position = 0;

	if (cmd)
	{
		if (Position == previous_position)
		{
			timer++;
			if ((timer * MAIN_TIMER_TIME_MS) >= BLOCKAGE_TIME_MS)
			{
				return 1;
			}
			else
			{
				timer = 0;
				return 0;
			}
		}
	}
	else
	{
		timer = 0;
		return 0;
	}
}
*/
