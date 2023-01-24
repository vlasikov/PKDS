/*
 * Scheme.c
 *
 *  Created on: Dec 18, 2022
 *      Author: kendor
 */

#include "iomap.h"
#include <DAVE.h>

INPUT_SIGNALS_t Inputs;


INPUT_DIGITAL_t PhotoSensor =
{
	.port = &PHOTO_SENSOR_PORT,
	.mask = PHOTO_SENSOR_Msk,
};
INPUT_DIGITAL_t DisabledButSB3 =
{
	.port = &DISABLED_BUT_SB3_PORT,
	.mask = DISABLED_BUT_SB3_Msk,
};
INPUT_DIGITAL_t Open1DoorBut =
{
	.port = &OPEN_1_DOOR_BUT_PORT,
	.mask = OPEN_1_DOOR_BUT_Msk,
};
INPUT_DIGITAL_t StopBut =
{
	.port = &STOP_BUT_SB2_PORT,
	.mask = STOP_BUT_SB2_Msk,
};
INPUT_DIGITAL_t CloseSensor =
{
	.port = &CLOSE_SENSOR_PORT,
	.mask = CLOSE_SENSOR_Msk,
};
INPUT_DIGITAL_t ExternAlarmHandle =
{
	.port = &EXTERN_ALARM_HANDLE_PORT,
	.mask = EXTERN_ALARM_HANDLE_Msk,
};

CAPTRON_BUTTON_t PassengerButton =
{
	.inport_handler = &PASSENGER_BUTTON_IN_PORT,
	.outport_handler = &PASSENGER_BUTTON_OUT_PORT,
	.mask = PASSENGER_BUTTON_Msk,
};

CAPTRON_BUTTON_t DisabledButton =
{
	.inport_handler = &DISABLED_BUTTON_IN_PORT,
	.outport_handler = &DISABLED_BUTTON_OUT_PORT,
	.mask = DISABLED_BUTTON_Msk,
};


OUTPUT_DIGITAL_t InternAlarmHandle =
{
	.handler = &INTERN_ALARM_HANDLER_BLOCK_OUT,
};


OUTPUT_DIGITAL_t StepLights =
{
	.handler = &STEP_LIGHTS_OUT,
};




void ReadInput(INPUT_DIGITAL_t * input)
{
	if(BUS_IO_Read(input->port) & input->mask)
	{
		input->value = 1;
	}
	else
	{
		input->value = 0;
	}

	if(input->value && !input->previousValue)
	{
		input->edgeR = 1;
	}
	else
	{
		input->edgeR = 0;
	}

	if(!input->value && input->previousValue)
	{
		input->edgeF = 1;
	}
	else
	{
		input->edgeF = 0;
	}

	input->previousValue = input->value;

}
void ReadCaptronButton(CAPTRON_BUTTON_t * button)
{
	if(BUS_IO_Read(button->inport_handler) & button->mask)
	{
		button->value = 1;
	}
	else
	{
		button->value = 0;
	}

	if(button->value && !button->previousValue)
	{
		button->edgeR = 1;
	}
	else
	{
		button->edgeR = 0;
	}

	if(!button->value && button->previousValue)
	{
		button->edgeF = 1;
	}
	else
	{
		button->edgeF = 0;
	}

	button->previousValue = button->value;
}

void WriteOutput(OUTPUT_DIGITAL_t * out, uint8_t value)
{
	if(value)
	{
		DIGITAL_IO_SetOutputHigh(out->handler);
	}
	else
	{
		DIGITAL_IO_SetOutputLow(out->handler);
	}
}
void WriteCaptronButton(CAPTRON_BUTTON_t * out, uint8_t value)
{
	uint16_t temp = 0;

	temp = BUS_IO_Read(out->outport_handler);

	if(value)
	{
		temp |= out->mask;
	}
	else
	{
		temp &=~ out->mask;
	}

	BUS_IO_Write(out->outport_handler, temp);
}

