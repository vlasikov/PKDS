/*
 * user_io.h
 *
 *  Created on: Jan 7, 2023
 *      Author: kendor
 */

#ifndef MAINALG_PERIPHERIALS_IOMAP_H_
#define MAINALG_PERIPHERIALS_IOMAP_H_

#include <DAVE.h>

typedef struct __INPUT_SIGNALS_t
{
	uint16_t PNP;
	uint16_t NPN;
	uint16_t GIN;
	uint16_t SBT;

	uint16_t RIN1;
	uint16_t RIN2;

	uint16_t DCIN;

}	INPUT_SIGNALS_t;

typedef struct __OUTPUT_SIGNALS_t
{
	uint16_t HS;
	uint16_t LS;
	uint16_t GOU;
	uint16_t LED;

}	OUTPUT_SIGNALS_t;

typedef struct __INPUT_DIGITAL_t
{
	BUS_IO_t * const port;
	uint16_t mask;

	uint8_t value;
	uint8_t edgeR;
	uint8_t edgeF;

	uint8_t previousValue;

}INPUT_DIGITAL_t;


typedef struct __OUTPUT_DIGITAL_t
{
	const DIGITAL_IO_t *const handler;

	uint8_t value;
	uint8_t mode;

}OUTPUT_DIGITAL_t;

typedef struct __CAPTRON_BUTTON_t
{
	BUS_IO_t * const inport_handler;
	uint16_t mask;

	uint8_t value;
	uint8_t edgeR;
	uint8_t edgeF;

	uint8_t previousValue;

	BUS_IO_t * const outport_handler;
	uint8_t led;
}CAPTRON_BUTTON_t;


// Inputs defs

#define PHOTO_SENSOR_PORT DI_PNP
#define PHOTO_SENSOR_PIN 1
#define PHOTO_SENSOR_Msk (1 << (PHOTO_SENSOR_PIN - 1)) // Here is not UL, cause port has uint16_t size

#define DISABLED_BUT_SB3_PORT DI_PNP
#define DISABLED_BUT_SB3_PIN 2
#define DISABLED_BUT_SB3_Msk (1 << (DISABLED_BUT_SB3_PIN - 1))

#define OPEN_1_DOOR_BUT_PORT DI_PNP
#define OPEN_1_DOOR_BUT_PIN 2
#define OPEN_1_DOOR_BUT_Msk (1 << (DISABLED_BUT_SB3_PIN - 1))

#define STOP_BUT_SB2_PORT DI_PNP
#define STOP_BUT_SB2_PIN 3
#define STOP_BUT_SB2_Msk (1 << (STOP_BUT_SB2_PIN - 1))

#define CLOSE_SENSOR_PORT DI_PNP
#define CLOSE_SENSOR_PIN 4
#define CLOSE_SENSOR_Msk (1 << (CLOSE_SENSOR_PIN - 1))

#define EXTERN_ALARM_HANDLE_PORT DI_NPN
#define EXTERN_ALARM_HANDLE_PIN 1
#define EXTERN_ALARM_HANDLE_Msk (1 << (EXTERN_ALARM_HANDLE_PIN - 1))


#define PASSENGER_BUTTON_IN_PORT GROUP_IN
#define PASSENGER_BUTTON_OUT_PORT GROUP_OUT
#define PASSENGER_BUTTON_PIN 1
#define PASSENGER_BUTTON_Msk (1 << (PASSENGER_BUTTON_PIN - 1))

#define DISABLED_BUTTON_IN_PORT GROUP_IN
#define DISABLED_BUTTON_OUT_PORT GROUP_OUT
#define DISABLED_BUTTON_PIN 2
#define DISABLED_BUTTON_Msk (1 << (DISABLED_BUTTON_PIN - 1))


// Outputs defs

#define INTERN_ALARM_HANDLER_BLOCK_OUT HS_SW_5
#define STEP_LIGHTS_OUT HS_SW_3


#endif /* MAINALG_PERIPHERIALS_IOMAP_H_ */
