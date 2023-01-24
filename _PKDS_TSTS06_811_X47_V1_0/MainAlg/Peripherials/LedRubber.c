/*
 * LedRubber.c
 *
 *  Created on: Sep 27, 2022
 *      Author: kendor
 */
#include "LedRubber.h"
#include "DAVE.h"
#include "xmc_common.h"
#include "MainAlg/main_alg.h"


#define INTER_RUBBER_PERCENT 20
#define OUTER_RUBBER_PERCENT 50

LED_RUBBER_LIGHT_t led_rubber;
int32_t LedPwmTimer = 0;



void InitLedRubber(int32_t mode)
{
	if(mode == MODE_ON)
	{
		  LedPwmTimer = SYSTIMER_CreateTimer(100, SYSTIMER_MODE_PERIODIC, LedPwmTimerProc, NULL );
		  SYSTIMER_StartTimer(LedPwmTimer);
		  DIGITAL_IO_SetOutputHigh(&LED_SW_NRES);

		  DIGITAL_IO_SetOutputHigh(&LED_POWER_EN2);
		  DIGITAL_IO_SetOutputHigh(&LED_POWER_EN1);
	}
	else
	{
		return;
	}
}


void WriteRubberLights(uint32_t color, int32_t mode, int32_t time_ms)
{
static int32_t timer = 0;
static int32_t previous_mode = 0;

	if ((mode == previous_mode)) // если режим не поменялся
	{
		if (mode == MODE_TIME_ON) // Светим время time_ms, затем гасим
		{
			if (timer * MAIN_TIMER_TIME_MS >= time_ms)
			{
				led_rubber.red_outern = 0;
				led_rubber.green_outern = 0;
				led_rubber.blue_outern = 0;
				led_rubber.red_intern = 0;
				led_rubber.green_intern = 0;
				led_rubber.blue_intern = 0;
			}
			else
			{
				timer ++;
				if (color == CL_RED)
				{
					led_rubber.red_outern = OUTER_RUBBER_PERCENT;
					led_rubber.green_outern = 0;
					led_rubber.blue_outern = 0;
					led_rubber.red_intern = INTER_RUBBER_PERCENT;
					led_rubber.green_intern = 0;
					led_rubber.blue_intern = 0;

				}
				if (color == CL_GREEN)
				{
					led_rubber.red_outern = 0;
					led_rubber.green_outern = OUTER_RUBBER_PERCENT;
					led_rubber.blue_outern = 0;
					led_rubber.red_intern = 0;
					led_rubber.green_intern = INTER_RUBBER_PERCENT;
					led_rubber.blue_intern = 0;

				}
				if (color == CL_YELLOW)
				{
					led_rubber.red_outern = OUTER_RUBBER_PERCENT/2;
					led_rubber.green_outern = OUTER_RUBBER_PERCENT/2;
					led_rubber.blue_outern = 0;
					led_rubber.red_intern = INTER_RUBBER_PERCENT;
					led_rubber.green_intern = INTER_RUBBER_PERCENT;
					led_rubber.blue_intern = 0;

				}
			}
		}// end mode time on

		if (mode == MODE_BLINK)
		{
			timer ++;

			if (timer*10 < time_ms) // если меньше полупериода
			{
				if (color == CL_RED)
				{
					led_rubber.red_outern = OUTER_RUBBER_PERCENT;
					led_rubber.green_outern = 0;
					led_rubber.blue_outern = 0;
					led_rubber.red_intern = INTER_RUBBER_PERCENT;
					led_rubber.green_intern = 0;
					led_rubber.blue_intern = 0;

				}
				if (color == CL_GREEN)
				{
					led_rubber.red_outern = 0;
					led_rubber.green_outern = OUTER_RUBBER_PERCENT;
					led_rubber.blue_outern = 0;
					led_rubber.red_intern = 0;
					led_rubber.green_intern = INTER_RUBBER_PERCENT;
					led_rubber.blue_intern = 0;
				}
				if (color == CL_YELLOW)
				{
					led_rubber.red_outern = OUTER_RUBBER_PERCENT/2;
					led_rubber.green_outern = OUTER_RUBBER_PERCENT/2;
					led_rubber.blue_outern = 0;
					led_rubber.red_intern = INTER_RUBBER_PERCENT;
					led_rubber.green_intern = INTER_RUBBER_PERCENT;
					led_rubber.blue_intern = 0;

				}
			}
			if ((timer*10 < time_ms*2) && (timer*10 >= time_ms)) // если больше полупериода и меньше периода
			{
				led_rubber.red_outern = 0;
				led_rubber.green_outern = 0;
				led_rubber.blue_outern = 0;
				led_rubber.red_intern = 0;
				led_rubber.green_intern = 0;
				led_rubber.blue_intern = 0;
			}
			if (timer*10 >= time_ms*2)
			{
				timer = 0;
			}
		}
		if (mode == MODE_OFF)
		{
			led_rubber.red_outern = 0;
			led_rubber.green_outern = 0;
			led_rubber.blue_outern = 0;
			led_rubber.red_intern = 0;
			led_rubber.green_intern = 0;
			led_rubber.blue_intern = 0;
		}
		if (mode == MODE_ON)
		{
			if (color == CL_RED)
			{
				led_rubber.red_outern = OUTER_RUBBER_PERCENT;
				led_rubber.green_outern = 0;
				led_rubber.blue_outern = 0;
				led_rubber.red_intern = INTER_RUBBER_PERCENT;
				led_rubber.green_intern = 0;
				led_rubber.blue_intern = 0;

			}
			if (color == CL_GREEN)
			{
				led_rubber.red_outern = 0;
				led_rubber.green_outern = OUTER_RUBBER_PERCENT;
				led_rubber.blue_outern = 0;
				led_rubber.red_intern = 0;
				led_rubber.green_intern = INTER_RUBBER_PERCENT;
				led_rubber.blue_intern = 0;

			}
			if (color == CL_YELLOW)
			{
				led_rubber.red_outern = OUTER_RUBBER_PERCENT/2;
				led_rubber.green_outern = OUTER_RUBBER_PERCENT/2;
				led_rubber.blue_outern = 0;
				led_rubber.red_intern = INTER_RUBBER_PERCENT;
				led_rubber.green_intern = INTER_RUBBER_PERCENT;
				led_rubber.blue_intern = 0;

			}

		}
	} // end_of mode not changed

	if (mode != previous_mode)
	{
		timer = 0;
	}
	previous_mode = mode;

}
void LedPwmTimerProc(void *args)
{
	static int32_t timer = 0;

	if (timer >= 100)
	{
		timer = 0;
	}
	if(!timer)
	{
		if(led_rubber.red_outern)
		{
			DIGITAL_IO_SetOutputHigh(&LED_SW_1);
		}
		if(led_rubber.green_outern)
		{
			DIGITAL_IO_SetOutputHigh(&LED_SW_2);
		}
		if(led_rubber.blue_outern)
		{
			DIGITAL_IO_SetOutputHigh(&LED_SW_3);
		}
		if(led_rubber.red_intern)
		{
			DIGITAL_IO_SetOutputHigh(&LED_SW_4);
		}
		if(led_rubber.green_intern)
		{
			DIGITAL_IO_SetOutputHigh(&LED_SW_5);
		}
		if(led_rubber.blue_intern)
		{
			DIGITAL_IO_SetOutputHigh(&LED_SW_6);
		}
	}


	if ((led_rubber.red_outern <= timer))
	{
		DIGITAL_IO_SetOutputLow(&LED_SW_1);
	}
	if ((led_rubber.green_outern <= timer))
	{
		DIGITAL_IO_SetOutputLow(&LED_SW_2);
	}
	if ((led_rubber.blue_outern <= timer))
	{
		DIGITAL_IO_SetOutputLow(&LED_SW_3);
	}
	if ((led_rubber.red_intern <= timer))
	{
		DIGITAL_IO_SetOutputLow(&LED_SW_4);
	}
	if ((led_rubber.green_intern <= timer))
	{
		DIGITAL_IO_SetOutputLow(&LED_SW_5);
	}
	if ((led_rubber.blue_intern <= timer))
	{
		DIGITAL_IO_SetOutputLow(&LED_SW_6);
	}

	timer++;
}
