/*
 * j1939.h
 *
 *  Created on: Jan 22, 2023
 *      Author: kendor
 */

#ifndef MAINALG_PROTOCOLS_J1939_H_
#define MAINALG_PROTOCOLS_J1939_H_


typedef struct __CAN_CMD_t
{
	// from DSC_1 pack
	uint8_t close;
	uint8_t open;
	uint8_t passengersButtonEn;
	uint8_t openDriverDoor;
	uint8_t closeDriverDoor;
	uint8_t ignitionOn;
	uint8_t linkOn;
	uint8_t parkingLightsEn;
	// from CCVS pack and compare with threshold
	uint8_t speedIsZero;

}	CAN_CMD_t;

typedef struct __CAN_Time_t
{
	// from TD pack
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t day;
	uint8_t month;
	uint8_t year;

}	CAN_Time_t;


typedef struct __CAN_Periph_ctrl_t
{
	// from DSC_2 pack
	uint8_t rubberLightsIn;
	uint8_t rubberLightsOut;
	uint8_t heatScreen;
	uint8_t buzzer;
	uint8_t neonLight;
	uint8_t stepLight;
	uint8_t redLight;
	uint8_t passengerButtonLightIn;
	uint8_t passengerButtonLightOut;
	uint8_t disabledButtonLightIn;
	uint8_t disabledButtonLightOut;
	uint8_t stopIndicator;
	uint8_t greenIndicator;
	uint8_t redIndicator;

}	CAN_Periph_ctrl_t;


extern CAN_CMD_t CanCmd;
extern CAN_Periph_ctrl_t CanPeriphControl;
extern CAN_Time_t CanTime;


#endif /* MAINALG_PROTOCOLS_J1939_H_ */
