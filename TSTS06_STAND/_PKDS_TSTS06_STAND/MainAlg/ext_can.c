/*
 * ext_can.c
 *
 *  Created on: Jun 10, 2021
 *      Author: kendor
 */

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "xmc_common.h"
#include "MainAlg/main_alg.h"
#include "MainAlg/door_periph.h"
//#include "bldc_scalar_user_interface.h"
//#include "stdlib.h"
#include "MainAlg/ext_can.h"
#include <MainAlg/presets.h>
#include <MainAlg/retain_xmc4.h>





uint8_t Can1Rx1Data[8];
uint8_t Can1Rx2Data[8];
uint8_t Can1Rx3Data[8];

extern int32_t MainState;

DSC1_t DSC1;
DSC2_t DSC2;
EDSC1_t EDSC1;
EDSC2_t EDSC2;

int32_t ExtCanOnline = 0;

int32_t CanCmdOpenEnable = 0;
int32_t CanCmdUnlock = 0;
int32_t CanCmdOpenCmd = 0;
int32_t CanCmdCloseCmd = 0;
int32_t CanCmdCloseAll = 0;
int32_t CanCmdEnablePassengersButton = 0;


void Can1Tx1Send(void)
{
	CAN_NODE_MO_UpdateID(&CAN_EXT_LMO_07_Config, (0x100 + Presets.CAN_ADRESS));
	CAN_NODE_MO_UpdateData(&CAN_EXT_LMO_07_Config, &Can1TxData1[0]);
	CAN_NODE_MO_Transmit(&CAN_EXT_LMO_07_Config);
}

void Can1Rx1Parce(void)
{
	uint8_t temp = 0;
	uint8_t temp2 = 0;

	temp = Can1Rx1Data[0];

	if(temp & (1<<2))
	{
		CanCmdUnlock = 1;
	}
	else
	{
		CanCmdUnlock = 0;
	}
	temp2 = Can1Rx1Data[5];
// Enable open all
	if ((temp & (1<<0)))// && (temp2 & (1<<Presets.CAN_ADRESS)))
	{
		CanCmdOpenEnable = 1;
	}
	else
	{
		CanCmdOpenEnable = 0;
	}


}
void Can1Rx2Parce(void)
{
	uint32_t temp = 0;
	uint32_t *pt;

	pt = (uint32_t*)(Can1Rx2Data);
	temp = *pt;

	if(temp & (1<<(Presets.CAN_ADRESS * 4)))
	{
		CanCmdOpenCmd = 1;
	}
	else
	{
		CanCmdOpenCmd = 0;
	}
}

void Can1Rx3Parce(void)
{
	uint32_t temp = 0;
	uint32_t *pt;

	pt = (uint32_t*)(Can1Rx3Data);
	temp = *pt;

	if(temp & (1<<(Presets.CAN_ADRESS * 4)))
	{
		CanCmdCloseCmd = 1;
	}
	else
	{
		CanCmdCloseCmd = 0;
	}

	pt = (uint32_t*)(Can1Rx2Data);
	//temp = *pt;

	if (!temp && CanCmdOpenEnable && !(*pt)) // 22/04/2022 // need dbg
	{
		CanCmdEnablePassengersButton = 1;
	}
	else
	{
		CanCmdEnablePassengersButton = 0;
	}

}

void Can1Tx1Prep (void)
{
	uint8_t temp = 0;

	temp = 0x01;

	Can1TxData1[0] = temp;

	temp = 0;

	switch (MainState)
	{
		case MS_CLOSED:
		{
			temp |= (1<<0);
		}break;
		case MS_CLOSING:
		{
			temp |= (1<<1);
		}break;
		case MS_OPENED:
		{
			temp |= (1<<2);
		}break;
		case MS_OPENING:
		{
			temp |= (1<<3);
		}break;
		case MS_BLOCKAGE_ALL:
		{
			temp |= (1<<4);
		}break;
		case MS_BLOCKAGE_OPN:
		{
			temp |= (1<<4);
		}
	}
	if (CloseSensor)
	{
		temp |= 1;
	}
//	if(PassengerButton)
//	{
//		temp |= (1<<6);
//	}
	Can1TxData1[1] = temp;

	temp = 0;
	if(ActiveRubberL)
	{
		temp |= (1<<0);
	}

	if(MainState == MS_BLOCKAGE_CLS)
	{
		temp |= (1<<1);
	}

/*	if(PhotoSensor)
	{
		temp |= (1<<2);
	}
*/
	Can1TxData1[2] = temp;

	temp = 0;

	if(DisabledButton)
	{
		temp |= (0x04);
	}

	Can1TxData1[3] = temp;

	temp = 0;
/*	if(MainState == MS_CLOSED)
	{
		temp = ((1<<0) || (1<<4));
	}
	if(MainState == MS_OPENED)
	{
		temp = ((1<<2) || (1<<6));
	}

	Can1TxData1[4] = temp;
*/
	temp = 0;
	if(MainState == MS_OPENING || MainState == MS_BLOCKAGE_OPN)
	{
		temp = 0x40;
	}
	if(MainState == MS_OPENED || MainState == MS_CLOSING || MainState == MS_OPENED_BLOCK || MainState == MS_BLOCKAGE_CLS || MainState == MS_HOMING)
	{
		temp = 0x60;
	}
	if(MainState == MS_CLOSED)
	{
		temp = 0;
	}
	if(MainState == MS_BLOCKAGE_ALL || MainState == MS_BLOCKAGE_CLS || MainState == MS_ERROR_MAX_CURRENT || MainState == MS_ERROR_MOV_TIMEOUT)
	{
		temp |= 0x01;
	}

	Can1TxData1[6] = temp;

	if(Presets.CAN_ADRESS == 0)
	{
		temp = 0x86;
	}
	if(Presets.CAN_ADRESS == 5)
	{
		temp = 0x87;
	}
	if((Presets.CAN_ADRESS != 0) && (Presets.CAN_ADRESS != 5))
	{
		temp = 0x96;
	}
	Can1TxData1[7] = temp;
}



void CAN1RxHandler (void)
{
	static uint32_t pack_counter = 0;

	//DIGITAL_IO_ToggleOutput(&STATUS_LED_G);

	CAN_NODE_MO_Receive(&CAN_EXT_LMO_01_Config);

	pack_counter ++; // for ident no link

	if(pack_counter >= 200)
	{
		ExtCanOnline = 1;
	}


	if (CAN_EXT_LMO_01_Config.mo_ptr->can_identifier == 0x80)
	{

		for (int i = 0; i < 8; i++)
		{
			Can1Rx1Data[i] = CAN_EXT_LMO_01_Config.mo_ptr->can_data_byte[i];
		}

		Can1Rx1Parce();
	}

	if (CAN_EXT_LMO_01_Config.mo_ptr->can_identifier == 0x81)
	{

		for (int i = 0; i < 8; i++)
		{
			Can1Rx2Data[i] = CAN_EXT_LMO_01_Config.mo_ptr->can_data_byte[i];
		}

		Can1Rx2Parce();
	}

	if (CAN_EXT_LMO_01_Config.mo_ptr->can_identifier == 0x82)
	{

		for (int i = 0; i < 8; i++)
		{
			Can1Rx3Data[i] = CAN_EXT_LMO_01_Config.mo_ptr->can_data_byte[i];
		}

		Can1Rx3Parce();
	}
}

void TrapSensorISRHandler(void)
{
	uint8_t temp = 0;

	CAN_NODE_MO_Receive(&CAN_EXT_LMO_05_Config);

	if (((CAN_EXT_LMO_05_Config.mo_ptr->can_identifier == 0x240000) && (Presets.CAN_ADRESS == 2)))
	{
		temp = CAN_EXT_LMO_05_Config.mo_ptr->can_data_byte[0];

		//DIGITAL_IO_ToggleOutput(&STATUS_LED_Y);

		if(temp & (1<<1)) // trap sensor transmit via CAN in 0x240000[0].1
		{
			TrapSensor = 1;
		}
		else
		{
			TrapSensor = 0;
		}
	}
}

void StopButISRHanler (void)
{
	uint8_t temp = 0;


	CAN_NODE_MO_Receive(&CAN_EXT_LMO_04_Config);

	// In Lionet Stop Buttons transmit via CAN in 0x600000[0].3; 0x602000[0].3; 0x604000[0].3; 0x608000[0].3
	// In Vityaz' Stop Buttons transmit via CAN in 0x600000[0].3; 0x602000[0].3; 0x604000[0].3; 0x60A000[0].3; 0x60C000[0].3; 0x60E000[0].3
	// In Bogatyr' I DON'T KNOW
	if (((Presets.CAN_ADRESS <= 2) && (CAN_EXT_LMO_04_Config.mo_ptr->can_identifier == (0x600000 + (Presets.CAN_ADRESS * 2) * 0x1000))) || ((Presets.CAN_ADRESS == 3) && (CAN_EXT_LMO_04_Config.mo_ptr->can_identifier == 0x608000)))
	{
		//DIGITAL_IO_ToggleOutput(&STATUS_LED_Y);
		temp = CAN_EXT_LMO_04_Config.mo_ptr->can_data_byte[0];

		if(temp & (1<<3))
		{
			StopButton = 1;
		}
		else
		{
			StopButton = 0;
		}
	}
}


void CanNodeAllertIsrHandler(void)
{
	// If CAN node not OK
	//DIGITAL_IO_ToggleOutput(&STATUS_LED_R);

	if (CAN_NODE_GetStatus(&CAN_EXT))
	{
		CAN_NODE_Init(&CAN_EXT); // Reset node
	}
}

