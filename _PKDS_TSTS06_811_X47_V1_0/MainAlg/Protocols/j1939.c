/*
 * j1939.c
 *
 *  Created on: Jan 22, 2023
 *      Author: kendor
 *
 */
#include <DAVE.h>
#include "j1939.h"
#include <xmc_can.h>
#include "MainAlg/presets.h"


// CAN BASE_IDs
#define DSC1_ID_BASE 0x18B6CC27
#define DCS2_ID_BASE 0x18B7CC27
#define DCS3_ID_BASE 0x18EFCC27
// CAN GLOBAL_IDs
#define CCVS_ID 0x18FEF100
#define TD_ID 0x18FEE600


// CAN DSC1_MASKS
#define DSC1_OPEN_CMD_Msk (1UL<<0)
#define DSC1_CLOSE_CMD_Msk (1UL<<1)

#define DSC1_INTERN_PASSENGER_BUTTON_ON_Msk (1UL<<2)
#define DSC1_INTERN_PASSENGER_BUTTON_NON_Msk (1UL<<3)

#define DSC1_EXTERN_PASSENGER_BUTTON_ON_Msk (1UL<<4)
#define DSC1_EXTERN_PASSENGER_BUTTON_NON_Msk (1UL<<5)

#define DSC1_OPEN_DRIVER_DOOR_Msk (1UL<<6)
#define DSC1_CLOSE_DRIVER_DOOR_Msk (1UL<<7)

#define DSC1_IGNITION_ON_Msk (1UL<<8)
#define DSC1_IGNITION_NON_Msk (1UL<<9)

#define DSC1_LINK_ON_Msk (1UL<<10)
#define DSC1_LINK_NON_Msk (1UL<<11)

#define DSC1_PARKING_LIGHTS_ON_Msk (1UL<<12)
#define DSC1_PARKING_LIGHTS_NON_Msk (1UL<<13)

// etc..............................


// Public vars
CAN_CMD_t CanCmd;
CAN_Periph_ctrl_t CanPeriphControl;
CAN_Time_t CanTime;


// private vars
uint16_t VehicleSpeed;
uint16_t VehicleSpeedThreshold;

void DSC1IsrHandler(void)
{
	XMC_CAN_MO_t* Msg;
	Msg = CAN_EXT_LMO_01_Config.mo_ptr;

	uint32_t data[2] = {0,0};

	if(Msg->can_identifier == (DSC1_ID_BASE + ((Presets.DOOR_NUMBER - 1) * 0x0100)) )
	{
		data[0] = Msg->can_data[0];
		//data[1] = Msg->can_data[1];
	}
	//Parce to CanCmd struct


	if((data[0] & DSC1_CLOSE_CMD_Msk) && !(data[0] & DSC1_OPEN_CMD_Msk))
	{
		CanCmd.close = 1;
	}
	else
	{
		CanCmd.close = 0;
	}

	if((data[0] & DSC1_OPEN_CMD_Msk) && !(data[0] & DSC1_CLOSE_CMD_Msk))
	{
		CanCmd.open = 1;
	}
	else
	{
		CanCmd.open = 0;
	}

	if( ((data[0] & DSC1_EXTERN_PASSENGER_BUTTON_ON_Msk) && !(data[0] & DSC1_EXTERN_PASSENGER_BUTTON_NON_Msk)) ||
		((data[0] & DSC1_INTERN_PASSENGER_BUTTON_ON_Msk) && !(data[0] & DSC1_INTERN_PASSENGER_BUTTON_NON_Msk)) )
	{
		CanCmd.passengersButtonEn = 1;
	}
	else
	{
		CanCmd.passengersButtonEn = 0;
	}

	if((data[0] & DSC1_OPEN_DRIVER_DOOR_Msk) && !(data[0] & DSC1_CLOSE_DRIVER_DOOR_Msk))
	{
		CanCmd.openDriverDoor = 1;
	}
	else
	{
		CanCmd.openDriverDoor = 0;
	}

	if((data[0] & DSC1_CLOSE_DRIVER_DOOR_Msk) && !(data[0] & DSC1_OPEN_DRIVER_DOOR_Msk))
	{
		CanCmd.closeDriverDoor = 1;
	}
	else
	{
		CanCmd.closeDriverDoor = 0;
	}

	if((data[0] & DSC1_IGNITION_ON_Msk) && !(data[0] & DSC1_IGNITION_NON_Msk))
	{
		CanCmd.ignitionOn = 1;
	}
	else
	{
		CanCmd.ignitionOn = 0;
	}

	if((data[0] & DSC1_LINK_ON_Msk) && !(data[0] & DSC1_LINK_NON_Msk))
	{
		CanCmd.linkOn = 1;
	}
	else
	{
		CanCmd.linkOn = 0;
	}

	if((data[0] & DSC1_PARKING_LIGHTS_ON_Msk) && !(data[0] & DSC1_PARKING_LIGHTS_NON_Msk))
	{
		CanCmd.parkingLightsEn = 1;
	}
	else
	{
		CanCmd.parkingLightsEn = 0;
	}
}

void DSC2IsrHandler (void)
{
	XMC_CAN_MO_t* Msg;
	Msg = CAN_EXT_LMO_02_Config.mo_ptr;

	uint32_t data[2] = {0,0};

	if(Msg->can_identifier == (DCS2_ID_BASE + ((Presets.DOOR_NUMBER - 1) * 0x0100)) )
	{
		data[0] = Msg->can_data[0];
		data[1] = Msg->can_data[1];
	}

	// Parce to CanPeriphControl struct
}


void DSC3IsrHandler (void)
{
	XMC_CAN_MO_t* Msg;
	Msg = CAN_EXT_LMO_03_Config.mo_ptr;

	uint32_t data[2] = {0,0};

	if(Msg->can_identifier == (DCS3_ID_BASE + ((Presets.DOOR_NUMBER - 1) * 0x0100)) )
	{
		data[0] = Msg->can_data[0];
		data[1] = Msg->can_data[1];
	}

	// don't parce yet. Need to think how it can be doing
}

void CCVSIsrHandler(void)
{
	XMC_CAN_MO_t* Msg;
	Msg = CAN_EXT_LMO_04_Config.mo_ptr;

	uint32_t data[2] = {0,0};

	if(Msg->can_identifier == CCVS_ID)
	{
		data[0] = Msg->can_data[0];
		data[1] = Msg->can_data[1];
	}
	// Parce to CanCmd.speedIsZero  throw compare with (uint16_t)Presets.VEHICLE_SPEED_THRESHOLD
}

void TDIsrHandler (void)
{
	XMC_CAN_MO_t* Msg;
	Msg = CAN_EXT_LMO_05_Config.mo_ptr;

	uint32_t data[2] = {0,0};

	if(Msg->can_identifier == TD_ID)
	{
		data[0] = Msg->can_data[0];
		data[1] = Msg->can_data[1];
	}

	//Parce to CanTime
}
