/*
 * main.c
 *
 *  Created on: 2021 Jun 08 11:10:51
 *  Author: kendor
 */




#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <MainAlg/main_alg.h>
#include "xmc_common.h"

#include <MainAlg/door_periph.h>
#include "AppInfo.h"
#include <MainAlg/presets.h>
#include <MainAlg/retain_xmc4.h>
#include <MainAlg/serv_mode.h>
/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */

extern uint8_t Can1Rx1Data[8];
extern uint8_t Can1Rx2Data[8];
extern uint8_t Can1Rx3Data[8];
//extern int32_t ExtCanOnline;


void ClutchCmpHandler (void)
{
	PWM_CCU4_ClearEvent(&CLUTCH_PWM,XMC_CCU4_SLICE_IRQ_ID_COMPARE_MATCH_UP);
	DIGITAL_IO_SetOutputLow(&HS_SW_1);
	DIGITAL_IO_SetOutputLow(&HS_SW_2);
}
void ClutchOvfHandler(void)
{
	PWM_CCU4_ClearEvent(&CLUTCH_PWM,XMC_CCU4_SLICE_IRQ_ID_PERIOD_MATCH);
	DIGITAL_IO_SetOutputHigh(&HS_SW_1);
	DIGITAL_IO_SetOutputHigh(&HS_SW_2);
}


void MCU_ProgramReset( void )
{

	// clear the reset cause field for proper reset detection of the ssw
	XMC_SCU_RESET_ClearDeviceResetReason();

	// set normal boot as boot mode in SWCON field of STCON register
	XMC_SCU_SetBootMode(XMC_SCU_BOOTMODE_NORMAL);

	// trigger power on reset
	PPB->AIRCR = 1 << PPB_AIRCR_SYSRESETREQ_Pos |0x5FA<<PPB_AIRCR_VECTKEY_Pos | 0x1 << PPB_AIRCR_PRIGROUP_Pos;

	while (1) {};

} //MCU_ProgramReset()

void Adc_Measurement_Handler(void)
{
	float temp = 0;

	static volatile int div = 0;

	Inputs.RIN1 = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Channel_A_handle);
/*
	if(Inputs.ActiveRubberLVal > 1800)
	{
		ActiveRubberL = 1;
	}
	else
	{
		ActiveRubberL = 0;
	}
*/
    Inputs.RIN2 = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Channel_B_handle);

   /* if(Inputs.ActiveRubberRVal > 100)
	{
	    ActiveRubberR = 1;
    }
    else
    {
        ActiveRubberR = 0;
    }
*/
   Inputs.DCIN = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Channel_C_handle);
   //temp = Inputs.InputPower;
   //temp = (1200 + (Inputs.InputPower - 1300)/20*18);
  // Inputs.InputPower = (uint16_t)temp;
/*
	div++;
	if(div >= 100)
	{
		div = 0;
		DIGITAL_IO_ToggleOutput(&STATUS_LED_R);
	}
*/

   //Inputs.DriveCurrent = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Channel_D_handle);
}
void ResetISRCan2Handler (void)
{
	char tempCanData[8] = {'C','M','D','_','B','O','O','T'};
	char tempCanDataAddress[8] = {'R','E','S','E','T','_','0','0'};
	uint8_t temp = 0;
	//uint64_t temp_long = 0;

	DIGITAL_IO_ToggleOutput(&STATUS_LED_Y);

	CAN_NODE_MO_Receive(&CAN_INT_LMO_08_Config);

	if (CAN_INT_LMO_08_Config.mo_ptr->can_identifier == 0x06)
	{
		uint64_t ul1 = CAN_INT_LMO_08_Config.mo_ptr->can_data_long;

		uint64_t * p = (uint64_t *)(tempCanData);
		uint64_t ul2 = *p;

		if (ul1 == ul2)
		{
			MCU_ProgramReset();
		}
	}

	CAN_NODE_MO_Receive(&CAN_EXT_LMO_08_Config);

	if (CAN_EXT_LMO_08_Config.mo_ptr->can_identifier == 0x06)
	{
		uint64_t ul1 = CAN_EXT_LMO_08_Config.mo_ptr->can_data_long;

		temp = (uint8_t)Presets.DOOR_NUMBER; // calculate address
		temp = temp/10;		// 00 - 90 from address (tens)
		tempCanDataAddress[6] += temp; // add to string

		temp = (uint8_t)Presets.DOOR_NUMBER;
		temp = temp%10;	// 0 - 9 from address
		tempCanDataAddress[7] += temp; // add to string

		uint64_t * p = (uint64_t *)(tempCanDataAddress);
		uint64_t ul2 = *p;

		if (ul1 == ul2)
		{
			MCU_ProgramReset();
		}
	}

}

void ServiceISRHandler(void)
{
	CAN_NODE_MO_Receive(&CAN_INT_LMO_06_Config);

	if (CAN_INT_LMO_06_Config.mo_ptr->can_identifier == 0x100)
	{
		for (int i = 0; i < 8; i++)
		{
			ServCanRxData1[i] = CAN_INT_LMO_06_Config.mo_ptr->can_data_byte[i];
		}
	}
	if (CAN_INT_LMO_06_Config.mo_ptr->can_identifier == 0x101)
	{
		for (int i = 0; i < 8; i++)
		{
			ServCanRxData2[i] = CAN_INT_LMO_06_Config.mo_ptr->can_data_byte[i];
		}
	}
}

int main(void)
{
  DAVE_STATUS_t status;

  status = DAVE_Init();           /* Initialization of DAVE APPs  */

  if (status != DAVE_STATUS_SUCCESS)
  {
    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
    XMC_DEBUG("DAVE APPs initialization failed\n");

    while(1U)
    {

    }
  }

  // Init Internal Retain Memory Code:

  E_EEPROM_XMC4_STATUS_t e_status = E_EEPROM_XMC4_Init( &RETAIN );
    switch ( e_status ) {
    	case  E_EEPROM_XMC4_STATUS_OK: {
    		  if ( E_EEPROM_XMC4_IsFlashEmpty())
    		  {
    			  SaveAllPresets(&DefaultPresets);
    		  } //if
    		  ReadAllPresets( &Presets );
    		break;
    	} //case

    	case E_EEPROM_XMC4_STATUS_ERROR_OLD_DATA:
    	case E_EEPROM_XMC4_STATUS_ERASE_ERROR:
    	{
    		/* add here the memory error handler */

    		Presets = DefaultPresets; // for example...
    		DIGITAL_IO_SetOutputHigh(&STATUS_LED_R);
    		break;
    	}

    	default :
    		DIGITAL_IO_SetOutputHigh(&STATUS_LED_R);
    		DIGITAL_IO_SetOutputHigh(&STATUS_LED_G);
    		DIGITAL_IO_SetOutputHigh(&STATUS_LED_Y);
    		break;

    	} //switch

  MainAlgInit();

  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
//
//	if(!DIGITAL_IO_GetInput(&SERVICE_BUT)) // button pressed
//	{
//		DIGITAL_IO_SetOutputHigh(&STATUS_LED_G); // on green led!
//	}
//	else
//	{
//
//	}
//
  }
}
