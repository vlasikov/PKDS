/*
 * Buzzer.c
 *
 *  Created on: Jun 7, 2022
 *      Author: kendor
 */

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "xmc_common.h"
#include <MainAlg/Peripherials/Buzzer.h>
#include "MainAlg/presets.h"



void InitBuzzer(int32_t buzzer_type)
{
	PWM_CCU4_SetFreqAndDutyCycle(&BUZZ_PWM, 440, 1000);
	DIGITAL_IO_SetOutputHigh(&TRANS_OUT);
	DIGITAL_IO_SetOutputLow(&HS_SW_8);
	PWM_CCU4_Stop(&BUZZ_PWM);
}
void WriteBuzzer(int32_t cmd)
{
static int32_t blink = 0;

	if((Presets.BUZZER_TYPE == BUZZER_TYPE_SFM) && (cmd == BUZZER_ON))
	{
		blink++;
//
//		if((blink >= 50) && (blink < 100))
//		{
//			DIGITAL_IO_SetOutputHigh(&TRANS_OUT);
//			//DIGITAL_IO_SetOutputLow(&HS_SW_8);
//			PWM_CCU4_Stop(&BUZZ_PWM);
//		}
//		if(blink < 50)
//		{
//			DIGITAL_IO_SetOutputHigh(&HS_SW_8);
//			PWM_CCU4_SetFreqAndDutyCycle(&BUZZ_PWM, 500, 5000);
//			PWM_CCU4_Start(&BUZZ_PWM);
//		}
//
//		if(blink >= 100)
//		{
//			blink = 0;
//		}
		if((blink >= 4) && (blink < 8))
		{
			DIGITAL_IO_SetOutputHigh(&HS_SW_8);
			PWM_CCU4_SetFreqAndDutyCycle(&BUZZ_PWM, 830, 2000); // Hz, Duty
			PWM_CCU4_Start(&BUZZ_PWM);
		}
		if(blink < 4)
		{
			DIGITAL_IO_SetOutputHigh(&HS_SW_8);
			PWM_CCU4_SetFreqAndDutyCycle(&BUZZ_PWM, 1047, 2000); // Hz, Duty
			PWM_CCU4_Start(&BUZZ_PWM);
		}
		if(blink >= 8)
		{
			blink = 0;
		}

	}

	if((Presets.BUZZER_TYPE == BUZZER_TYPE_BPT) && (cmd == BUZZER_ON))
	{
		blink++;

		if((blink >= 4) && (blink < 8))
		{
			DIGITAL_IO_SetOutputHigh(&HS_SW_8);
			PWM_CCU4_SetFreqAndDutyCycle(&BUZZ_PWM, 830, 8500); // Hz, Duty
			PWM_CCU4_Start(&BUZZ_PWM);
		}
		if(blink < 4)
		{
			DIGITAL_IO_SetOutputHigh(&HS_SW_8);
			PWM_CCU4_SetFreqAndDutyCycle(&BUZZ_PWM, 1047, 8500); // Hz, Duty
			PWM_CCU4_Start(&BUZZ_PWM);
		}
		if(blink >= 8)
		{
			blink = 0;
		}
	}
	if((cmd == BUZZER_OFF))
	{
		DIGITAL_IO_SetOutputHigh(&TRANS_OUT);
		DIGITAL_IO_SetOutputLow(&HS_SW_8);
		PWM_CCU4_Stop(&BUZZ_PWM);
		blink = 0;
	}
}


void BuzzerCmpISRHandler (void)
{
	PWM_CCU4_ClearEvent(&BUZZ_PWM,XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP);
	DIGITAL_IO_SetOutputLow(&TRANS_OUT);
}

void BuzzerOvfISRHandler (void)
{
	PWM_CCU4_ClearEvent(&BUZZ_PWM,XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
	DIGITAL_IO_SetOutputHigh(&TRANS_OUT);
}
