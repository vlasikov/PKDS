/*
 * MainAlg.c
 *
 *  Created on: Mar 2, 2021
 *      Author: kendor
 */

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "xmc_common.h"
#include "MainAlg/main_alg.h"
#include "MainAlg/door_periph.h"
//#include "MotorLib/bldc_scalar_user_interface.h"
#include "MotorLib/motor.h"
#include "stdlib.h"
#include <MainAlg/presets.h>
#include <MainAlg/retain_xmc4.h>
#include <MainAlg/moving.h>
#include <MainAlg/Peripherials/Buzzer.h>
#include "MainAlg/Peripherials/LedRubber.h"
#include "MainAlg/Peripherials/Scheme.h"


#define FILT_NUM 16

uint16_t OpenTime = 0;
uint16_t CloseTime = 0;


uint8_t Can1TxData1[8];
uint8_t Can1TxData2[8];
uint8_t Can2TxData1[8];
uint8_t Can2TxData2[8];
uint8_t Can2TxData3[8];

extern uint8_t Can1Rx1Data[8];
extern uint8_t Can1Rx2Data[8];
extern uint8_t Can1Rx3Data[8];

extern int32_t ServiceMode;


int32_t MainTimer = 0;
int32_t SaveTimer = 0;

int32_t MainState = 0;
int32_t HomingDone = 0;

int32_t  OPEN_DIR = -1;

int32_t PassMemo = 0;

extern int32_t ExtCanOnline;

int32_t FromCan = 0;


int32_t serv_from_but = 0;



void MainAlgInit(void)
{

	DoorPeriphInit();
	MotorInit();

	MainTimer = SYSTIMER_CreateTimer((MAIN_TIMER_TIME_MS * 1000), SYSTIMER_MODE_PERIODIC, MainProc, NULL );
	SYSTIMER_StartTimer(MainTimer);

//	SaveTimer = SYSTIMER_CreateTimer((1000*1000), SYSTIMER_MODE_PERIODIC, SaveProc, NULL);
//	SYSTIMER_StartTimer(SaveTimer);

	OPEN_DIR = -Presets.CLOSE_DIR;

}

void MainProc (void *args)
{

}
/*	int32_t temp = 0;

	static int32_t blink = 0;
	static int32_t wait_timer = 0;
	static int32_t pause = 0;
	static int32_t butt_blink = 0;
	static int32_t rl_blink = 0;


	static int32_t ClutchControl = 0;
	static int32_t ClutchGo = 0;

	static int32_t CanCmdOpenEnablePrev = 0;


	ReadInputs();
	ReadPeripherials();
	MotorRead();
	TrapSensor = 0;

	if ((Inputs.GIO & 0x0008)) // enter to service mode
	{
		ServiceMode = 1;
	}
	else
	{
		ServiceMode = 0;
	}


	if(MainState == MS_CLOSED)
	{
		if(!CanCmdEnablePassengersButton)
		{
			if(PassengerButton || StopButton || DisabledButton)
			{
				PassMemo = 1;
			}
		}
	}
	if((CanCmdOpenEnable) && (!PassMemo) && (!ServiceMode))
	{
		WritePassengerButton(CMD_ON);
	}
	if((!CanCmdOpenEnable) && (!PassMemo))
	{
		WritePassengerButton(CMD_OFF);
	}
	//	WriteRubberLights(CL_RED, MODE_ON, 1000);

	if((MainState != MS_CLOSED) && (MainState != MS_START))
	{
		DIGITAL_IO_SetOutputHigh(&HS_SW_3); // entrance lights
		DIGITAL_IO_SetOutputHigh(&HS_SW_4); // Passengers counter
	}
	else
	{
		DIGITAL_IO_SetOutputLow(&HS_SW_3);
		DIGITAL_IO_SetOutputLow(&HS_SW_4);
	}
//
//	if(MainState == MS_CLOSING || MainState == MS_OPENING || MainState == MS_HOMING)
//	{
//		rl_blink++;
//		if(rl_blink <= 20)
//		{
//			DIGITAL_IO_SetOutputHigh(&HS_SW_4);
//		}
//		if(rl_blink > 20)
//		{
//			DIGITAL_IO_SetOutputLow(&HS_SW_4);
//		}
//		if(rl_blink >= 40)
//		{
//			rl_blink = 0;
//		}
//
//	}
//	else
//	{
//		DIGITAL_IO_SetOutputLow(&HS_SW_4);
//	}

	if(PassMemo && !ServiceMode)
	{
		butt_blink++;
		if(butt_blink <= 100)
		{
			WritePassengerButton(CMD_ON);
		}
		if(butt_blink > 100)
		{
			WritePassengerButton(CMD_OFF);
		}
		if(butt_blink >= 200)
		{
			butt_blink = 0;
		}
	}

if (!ServiceMode) // main algorithm from cabine commands
{
	switch (MainState)
	{
		case MS_START:
		{
			wait_timer++;
			if(wait_timer >= Presets.STARTUP_TIME)
			{
				wait_timer = 0;
				WritePassengerButton(CMD_ON);

				if(CloseSensor)
				{
					MainState = MS_CLOSED;
					//Motor0_BLDC_SCALAR_SetSpeedProportionalGain(1000);
					//Motor0_BLDC_SCALAR_SetSpeedIntegralGain(20);

//					DIGITAL_IO_SetOutputHigh(&STATUS_LED_G);
				}
				else
				{
					MainState = MS_UNKNOWN;
//					DIGITAL_IO_SetOutputHigh(&STATUS_LED_Y);
				}
			}
			else
			{
				OpenDoor(0);
				CloseDoor(0);
				Homing(0);

				WriteRubberLights(CL_BLACK, MODE_OFF, 0);
			}


//			blink++;
//
//			if((blink >= 2) && (blink < 4))
//			{
//				DIGITAL_IO_SetOutputHigh(&HS_SW_8);
//				PWM_CCU4_SetFreqAndDutyCycle(&BUZZ_PWM, 1000, 50);
//				PWM_CCU4_Start(&BUZZ_PWM);
//			}
//			if(blink < 2)
//			{
//				DIGITAL_IO_SetOutputHigh(&HS_SW_8);
//				PWM_CCU4_SetFreqAndDutyCycle(&BUZZ_PWM, 800, 50);
//				PWM_CCU4_Start(&BUZZ_PWM);
//			}
//			if(blink >= 4)
//			{
//				blink = 0;
//			}
		}
			break;

		case MS_UNKNOWN:
		{
//			WritePassengerButton(CMD_ON);
			//WriteRubberLights(CL_GREEN, MODE_TIME_ON, 1000);

			//WriteClutch(CLUTCH_LOCK);

			wait_timer ++;
//
//			DIGITAL_IO_SetOutputHigh(&TRANS_OUT);
//			DIGITAL_IO_SetOutputLow(&HS_SW_8);
//
//			if (2 == Presets.CAN_ADRESS)
//			{
//				if(((DSC1.DoorCmd == 0x02) || (!DSC1.VelocityIsZero && ExtCanOnline)) && TrapSensor)// || (wait_timer >= 200))
//				{
//					MainState = MS_HOMING;
//					wait_timer = 0;				}
//
//			}

			if((CanCmdCloseAll || CanCmdCloseCmd || !CanCmdUnlock) && !TrapSensor)
			{
				MainState = MS_HOMING;
				wait_timer = 0;
				//WriteClutch(CLUTCH_LOCK);
			}

//			if ((Presets.CAN_ADRESS == 0) && CloseSensor && Open1DoorBut)
//			{
//				MainState = MS_OPENING;
//			}
//			if ((Presets.CAN_ADRESS == 0) && !CloseSensor && Open1DoorBut)
//			{
//				MainState = MS_HOMING;
//			}

		}
			break;

		case MS_HOMING:
		{
			WriteRubberLights(CL_YELLOW, MODE_BLINK, 1000);


			//WriteClutch(CLUTCH_UNLOCK);
			temp = Homing(1);
			if (temp == 1) // homing done success!
			{
				//DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
				//DIGITAL_IO_SetOutputHigh(&STATUS_LED_G);

				DIGITAL_IO_SetOutputHigh(&TRANS_OUT);
				DIGITAL_IO_SetOutputLow(&HS_SW_8);
				PWM_CCU4_Stop(&BUZZ_PWM);

				HomingDone = 1;
				MainState = MS_CLOSED;
			}
			if (temp == 0)
			{
				WriteBuzzer(BUZZER_ON);
			}
			if (temp == -1)
			{
				MainState = MS_ERROR_MOV_TIMEOUT;
				//DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
				//DIGITAL_IO_SetOutputLow(&STATUS_LED_G);
				Homing(0);
			}
			if (temp == -2)
			{
				//DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
				//DIGITAL_IO_SetOutputLow(&STATUS_LED_G);
				MainState = MS_ERROR_MAX_CURRENT;
				Homing(0);
			}
			if (temp == -3)
			{
				//DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
				//DIGITAL_IO_SetOutputLow(&STATUS_LED_G);
				MainState = MS_ERROR_BAD_HOMING;
				Homing(0);
			}
			if (-4 == temp)
			{
				MainState = MS_UNKNOWN;
				Homing(0);
			}
		}
			break;

		case MS_CLOSED:
		{
			wait_timer++;
			//WriteClutch(CLUTCH_LOCK);

			if(wait_timer >= 200)
			{
				MotorStop();
			}

			if(CanCmdUnlock)
			{
				DIGITAL_IO_SetOutputLow(&HS_SW_5);
				//DIGITAL_IO_SetOutputLow(&HS_SW_2);
			}
			else
			{
				DIGITAL_IO_SetOutputHigh(&HS_SW_5);
				//DIGITAL_IO_SetOutputHigh(&HS_SW_2);
			}

			if(wait_timer > 50)
			{
				if(CanCmdUnlock && CanCmdOpenEnable)
				{
					WriteRubberLights(CL_GREEN, MODE_ON, 0);
				}
				else
				{
					WriteRubberLights(CL_BLACK, MODE_OFF, 0);
				}
			}
			else
			{
				WriteRubberLights(CL_RED, MODE_TIME_ON, 500);
			}

			WriteBuzzer(BUZZER_OFF);

			if(CanCmdOpenCmd && CanCmdOpenEnable && CanCmdUnlock)
			{
				MainState = MS_OPENING;
				FromCan = 1;
				OpenTime = 0;
				wait_timer = 0;
			}
			if(((PassengerButton || DisabledButton || PassMemo) && CanCmdEnablePassengersButton && CanCmdUnlock))
			{
				MainState = MS_OPENING;
				OpenTime = 0;
				wait_timer = 0;
			}

			if(!CloseSensor)
			{
				MainState = MS_UNKNOWN;
			}

*/
//	for stand or no can

//			if(/*(wait_timer >= 1500) || */PassengerButton || DisabledButton|| ServiceButton)
//			{
//				MainState = MS_OPENING;
//				//MainState = MS_UNKNOWN;
//				OpenTime = 0;
//				wait_timer = 0;
//				//WriteClutch(CLUTCH_UNLOCK);
//			}
//


			//WriteRubberLights(CL_RED, MODE_TIME_ON, 1000);
/*
			if ((Presets.CAN_ADRESS == 0) && Open1DoorBut)
			{
				MainState = MS_OPENING;
			}
*/
//
/*		}
			break;
		case MS_OPENING:
		{
			WriteRubberLights(CL_GREEN, MODE_BLINK, 500);
			WriteBuzzer(BUZZER_OFF);
			OpenTime++;
			PassMemo = 0;
			butt_blink = 0;

			temp = OpenDoor(1);
			if (temp == 1)
			{
				//if(Presets.CYCLES_COUNTER % 200)
				//{
				wait_timer = 0;
				MainState = MS_OPENED;
				//}
				//else
				//{
				//	MainState = MS_START;
				//}

				//DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
				//DIGITAL_IO_SetOutputHigh(&STATUS_LED_G);

			}
			if (temp == 0)
			{
				blink++;
				if(blink >= 50)
				{
					//DIGITAL_IO_ToggleOutput(&STATUS_LED_Y);
//					DIGITAL_IO_ToggleOutput(&TRANS_OUT);
//					DIGITAL_IO_ToggleOutput(&HS_SW_8);
					blink = 0;
				}
			}
			if (temp == -1)
			{
				MainState = MS_ERROR_MOV_TIMEOUT;
				OpenDoor(0);
			}
			if (temp == -2)
			{
				MainState = MS_ERROR_MAX_CURRENT;
				OpenDoor(0);
			}
			if (temp == -3)
			{
				MainState = MS_ERROR_BAD_STATE;
				OpenDoor(0);
			}
			if(-4 == temp)
			{
				OpenDoor(0);
				MainState = MS_BLOCKAGE_OPN;
			}

//			wait_timer++;

//			if((wait_timer > 50) && (PassengerButton || DisabledButton))
//			{
//				OpenDoor(0);
//				wait_timer = 0;
//				MainState = MS_CLOSING;
//			}

			if(CanCmdCloseAll || CanCmdCloseCmd || (!CanCmdUnlock && ExtCanOnline))// && !Open1DoorBut))
			{
				OpenDoor(0);
				MainState = MS_CLOSING;
			}

		}
			break;
		case MS_OPENED:
		{
			WriteBuzzer(BUZZER_OFF);

			WriteRubberLights(CL_GREEN, MODE_ON, 0);


				if(((CanCmdCloseAll || CanCmdCloseCmd || (!CanCmdUnlock && ExtCanOnline))))//&& !Open1DoorBut)))//
				{
					wait_timer = 0;
					MainState = MS_CLOSING;
					CloseTime = 0;
					FromCan = 0;
				}

			wait_timer++;
*/
//			if(/*(wait_timer >= 500) ||*/ PassengerButton || DisabledButton|| ServiceButton)
//			{
//				wait_timer = 0;
//				MainState = MS_CLOSING;
//				CloseTime = 0;
//				FromCan = 0;
//			}

//			if ((Presets.CAN_ADRESS == 0) && Open1DoorBut)
//			{
//				MainState = MS_CLOSING;
//			}

/*		}
			break;
		case MS_OPENED_BLOCK:
		{
//			DIGITAL_IO_SetOutputHigh(&TRANS_OUT);
//			DIGITAL_IO_SetOutputLow(&HS_SW_8);
			WriteRubberLights(CL_RED, MODE_BLINK, 500);
//			WriteBuzzer(BUZZER_OFF);

			wait_timer++;

				if(((CanCmdCloseAll || CanCmdCloseCmd || (!CanCmdUnlock && ExtCanOnline)) && (wait_timer  >= 2) ))//(((DSC1.DoorCmd == 0x02) || (!DSC1.VelocityIsZero && ExtCanOnline)))// || (wait_timer >= 200))
				{
					wait_timer = 0;
					MainState = MS_CLOSING;
					CloseTime = 0;
					//wait_timer = 0;
					blink = 0;
				}
//
//				if( PassengerButton || DisabledButton|| ServiceButton)
//				{
//					wait_timer = 0;
//					MainState = MS_CLOSING;
//					CloseTime = 0;
//					//wait_timer = 0;
//					blink = 0;
//				}


//			}
//
//				if ((Presets.CAN_ADRESS == 0) && Open1DoorBut)
//				{
//					MainState = MS_CLOSING;
//					blink = 0;
//				}
//
				WriteBuzzer(BUZZER_ON);
		}
			break;

		case MS_CLOSING:
		{
			WriteRubberLights(CL_RED, MODE_BLINK, 500);
			CloseTime++;
			temp = CloseDoor(1);
			if (temp == 1) //
			{
				//DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
				//DIGITAL_IO_SetOutputHigh(&STATUS_LED_G);
				MainState = MS_CLOSED;
				wait_timer = 0;
				blink = 0;
			}
			if (temp == 0)
			{
				WriteBuzzer(BUZZER_ON);
			}
			if (temp == -1)
			{
				MainState = MS_ERROR_MOV_TIMEOUT;
				CloseDoor(0);
			}
			if (temp == -2)
			{
				MainState = MS_ERROR_MAX_CURRENT;
				CloseDoor(0);
			}
			if (temp == -3)
			{
				MainState = MS_ERROR_BAD_STATE;
				CloseDoor(0);
			}
			if(-4 == temp)
			{
				CloseDoor(0);
				MainState = MS_BLOCKAGE_CLS;
			}

			if(((CanCmdOpenCmd) && (CanCmdOpenEnable)) && CanCmdUnlock)
			{
				CloseDoor(0);
				MainState = MS_OPENING;
			}
//			wait_timer++;
//			if((wait_timer > 50) && (PassengerButton || DisabledButton || ServiceButton))
//			{
//				CloseDoor(0);
//				wait_timer = 0;
//				MainState = MS_OPENING;
//			}


		}
			break;

		case MS_BLOCKAGE_CLS:
		{
//			DIGITAL_IO_SetOutputHigh(&TRANS_OUT);
//			DIGITAL_IO_SetOutputLow(&HS_SW_8);
			wait_timer++;
			pause++;
			if (pause >= 50)
			{
				temp = OpenAfterBlockage(1);
				WriteRubberLights(CL_RED, MODE_BLINK, 500);
				if (temp == 1)
				{
					MainState = MS_OPENED_BLOCK;
					pause = 0;
					//DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
					//DIGITAL_IO_SetOutputHigh(&STATUS_LED_G);
					blink = 0;
				}
				if (temp == 0)
				{
					WriteBuzzer(BUZZER_ON);
				}
				if (temp == -1)
				{
					pause = 0;
					MainState = MS_ERROR_MOV_TIMEOUT;
					OpenAfterBlockage(0);
				}
				if (temp == -2)
				{
					pause = 0;
					MainState = MS_ERROR_MAX_CURRENT;
					OpenAfterBlockage(0);
				}
				if (temp == -3)
				{
					pause = 0;
					MainState = MS_ERROR_BAD_STATE;
					OpenAfterBlockage(0);
				}
				if(-4 == temp)
				{
					pause = 0;
					OpenAfterBlockage(0);
					MainState = MS_BLOCKAGE_OPN;
				}
 //maybe off
				if((CanCmdCloseAll || CanCmdCloseCmd && (pause >= 150))|| (!CanCmdUnlock))
				{
					OpenAfterBlockage(0);
					MainState = MS_CLOSING;
					pause = 0;
				}
//				if( PassengerButton || DisabledButton|| ServiceButton)
//				{
//					OpenAfterBlockage(0);
//					MainState = MS_CLOSING;
//					wait_timer = 0;
//				}
			}
			else
			{
				MotorStop();
				//WriteRubberLights(CL_YELLOW, MODE_ON, 100);
			}
		}
			break;

		case MS_BLOCKAGE_OPN:
		{
			wait_timer ++;

			MotorStop();
			WriteBuzzer(BUZZER_OFF);

			WriteRubberLights(CL_GREEN, MODE_ON, 100);

			if((CanCmdCloseAll || CanCmdCloseCmd || !CanCmdUnlock) && !TrapSensor )//if((DSC1.DoorCmd == 0x02) || (!DSC1.VelocityIsZero && ExtCanOnline))
			{
				//Motor0_BLDC_SCALAR_ClearErrorState();
				MainState = MS_CLOSING;
				wait_timer = 0;
			}

//
//			if( PassengerButton || DisabledButton|| ServiceButton)
//			{
//				//Motor0_BLDC_SCALAR_ClearErrorState();
//				MainState = MS_CLOSING;
//				wait_timer = 0;
//			}


			if((CanCmdOpenCmd) && CanCmdOpenEnable)
			{
				//Motor0_BLDC_SCALAR_ClearErrorState();
				MainState = MS_OPENING;
				wait_timer = 0;
			}
		}
			break;
*/
/*		case MS_OPEN_1_DOOR:
		{
			OpenTime++;
			temp = OpenDoor(1);
			if (temp == 1)
			{
				//if(Presets.CYCLES_COUNTER % 200)
				//{
					MainState = MS_OPENED;
				//}
				//else
				//{
				//	MainState = MS_START;
				//}

				DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
				DIGITAL_IO_SetOutputHigh(&STATUS_LED_G);

			}
			if (temp == 0)
			{
				blink++;
				if(blink >= 50)
				{
					DIGITAL_IO_ToggleOutput(&STATUS_LED_Y);
					blink = 0;
				}
			}
			if (temp == -1)
			{
				MainState = MS_ERROR_MOV_TIMEOUT;
				OpenDoor(0);
			}
			if (temp == -2)
			{
				MainState = MS_ERROR_MAX_CURRENT;
				OpenDoor(0);
			}
			if (temp == -3)
			{
				MainState = MS_ERROR_BAD_STATE;
				OpenDoor(0);
			}
			if(-4 == temp)
			{
				OpenDoor(0);
				MainState = MS_BLOCKAGE_OPN;
			}
			if((DSC1.DoorCmd == 0x02) || (!DSC1.VelocityIsZero && ExtCanOnline))
			{
				OpenDoor(0);
				MainState = MS_CLOSING;
			}
		}
			break;
*/
//		case MS_CLOSE_1_DOOR:
//		{
////			WriteClutch(CLUTCH_UNLOCK);
//			temp = Homing(1);
//			if (temp == 1) // homing done success!
//			{
//				DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
//				DIGITAL_IO_SetOutputHigh(&STATUS_LED_G);
//				HomingDone = 1;
//				MainState = MS_CLOSED;
//			}
//			if (temp == 0)
//			{
//				blink++;
//				if(blink >= 50)
//				{
//					DIGITAL_IO_ToggleOutput(&STATUS_LED_Y);
//					blink = 0;
//				}
//			}
//			if (temp == -1)
//			{
//				MainState = MS_ERROR_MOV_TIMEOUT;
//				DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
//				DIGITAL_IO_SetOutputLow(&STATUS_LED_G);
//				Homing(0);
//			}
//			if (temp == -2)
//			{
//				DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
//				//DIGITAL_IO_SetOutputLow(&STATUS_LED_G);
//				MainState = MS_ERROR_MAX_CURRENT;
//				Homing(0);
//			}
//			if (temp == -3)
//			{
//				DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
//				DIGITAL_IO_SetOutputLow(&STATUS_LED_G);
//				MainState = MS_ERROR_BAD_HOMING;
//				Homing(0);
//			}
//			if (-4 == temp)
//			{
//				MainState = MS_UNKNOWN;
//				Homing(0);
//			}
//
//		}
//			break;
//

/*
		default: // now it is error handler, todo: different errors
		{
//			blink++;
			wait_timer++;
			WriteBuzzer(BUZZER_OFF);

			MotorStop();
//			WritePassengerButton(CMD_OFF);
//			WriteClutch(CLUTCH_LOCK);
			//DIGITAL_IO_SetOutputLow(&HS_SW_1);
			//DIGITAL_ IO_SetOutputLow(&HS_SW_2);
			WriteRubberLights(CL_RED, MODE_BLINK, 200);
//
//
//			if((wait_timer >= 500)|| PassengerButton || DisabledButton|| ServiceButton)
//			{
//				//Motor0_BLDC_SCALAR_ClearErrorState();
//				MainState = MS_CLOSING;
//				wait_timer = 0;
//			}
//

			if((CanCmdCloseAll || CanCmdCloseCmd || (!CanCmdUnlock && ExtCanOnline)))
			{
				MainState = MS_CLOSING;
			}
			if((CanCmdOpenCmd) && CanCmdOpenEnable)
			{
				MainState = MS_OPENING;
				blink = 0;
			}

*/
			/*if(ServiceButton)
			{
				MainState = MS_START;
				DIGITAL_IO_SetOutputLow(&STATUS_LED_G);
				DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
				DIGITAL_IO_SetOutputLow(&STATUS_LED_R);
				WriteRubberLights(CL_BLACK, MODE_OFF, 0);
			}*/
			//DIGITAL_IO_SetOutputHigh(&STATUS_LED_R);
/*		}
		break;
	}
}
else
{
	if(ServiceButtonFront)
	{
		ClutchControl = 1;
		MainState = 0;
		//Motor0_BLDC_SCALAR_MotorStop();
		WritePassengerButton(CMD_OFF);
		wait_timer = 0;
	}
	if(PassengerButton || (Inputs.GIO & 0x0004))
	{
		ClutchControl = 0;
		ClutchGo = 0;
		WritePassengerButton(CMD_ON);
	}

	if(ClutchControl)
	{
		switch (ClutchGo)
		{
			case 0:
			{
				ClutchGo++;
			}
			break;
			case 1:
			{
				if(ServiceButtonFront)
				{
					ClutchGo++;
				}
				WriteBuzzer(BUZZER_OFF);
			}
			break;
			case 2:
			{
				pause++;
//				DIGITAL_IO_SetOutputHigh(&HS_SW_1);
//				DIGITAL_IO_SetOutputHigh(&HS_SW_2);

				if (pause >= 1)
				{
					ClutchGo++;
					pause = 0;
				}
			}
			break;
			case 3:
			{
				WriteClutch(CLUTCH_UNLOCK);
				//WriteBuzzer(BUZZER_ON);
				if(ServiceButtonFront)
				{
					ClutchGo++;
				}
			}
			break;
			case 4:
			{
				WriteClutch(CLUTCH_LOCK);
				//WriteBuzzer(BUZZER_OFF);
				if(ServiceButtonFront)
				{
					ClutchGo = 2;
				}
			}
			break;
		}
	}


if(!ClutchControl)
{
	WritePassengerButton(CMD_ON);

	switch (MainState)
	{
		case MS_START:
		{
			wait_timer++;
			if(wait_timer >= Presets.STARTUP_TIME)
			{
				wait_timer = 0;
				//WritePassengerButton(CMD_ON);

				//if(CloseSensor)
				//{
				//	MainState = MS_CLOSED;
				//	Motor0_BLDC_SCALAR_SetSpeedProportionalGain(1000);
				//	Motor0_BLDC_SCALAR_SetSpeedIntegralGain(20);
				//	Motor0_BLDC_SCALAR_ClearErrorState();
				//	DIGITAL_IO_SetOutputHigh(&STATUS_LED_G);
				//}
				//else
				//{
					MainState = MS_UNKNOWN;
				//	DIGITAL_IO_SetOutputHigh(&STATUS_LED_Y);
				//}
			}
			else
			{
				OpenDoor(0);
				CloseDoor(0);
				Homing(0);
				//Motor0_BLDC_SCALAR_ClearErrorState();
				WriteRubberLights(CL_BLACK, MODE_OFF, 0);
			}
		}
			break;

		case MS_UNKNOWN:
		{
			//WritePassengerButton(CMD_ON);

			wait_timer++;

			if((PassengerButton))// || (wait_timer >= Presets.STARTUP_TIME))
			{
				MainState = MS_HOMING;
				wait_timer = 0;
			}
			if(Inputs.GIO & 0x0004)
			{
				MainState = MS_HOMING;
				wait_timer = 0;
				serv_from_but = 1;
			}
		}
			break;

		case MS_HOMING:
		{
			WriteRubberLights(CL_YELLOW, MODE_BLINK, 1000);
			temp = Homing(1);
			if (temp == 1) // homing done success!
			{
				DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
				DIGITAL_IO_SetOutputHigh(&STATUS_LED_G);
				HomingDone = 1;
				MainState = MS_CLOSED;
				serv_from_but = 0;
			}
			if (temp == 0)
			{
				blink++;
				if(blink >= 50)
				{
					DIGITAL_IO_ToggleOutput(&STATUS_LED_Y);
					blink = 0;
				}
				WriteBuzzer(BUZZER_ON);
			}
			if (temp == -1)
			{
				MainState = MS_ERROR_MOV_TIMEOUT;
				DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
				DIGITAL_IO_SetOutputLow(&STATUS_LED_G);
				Homing(0);
			}
			if (temp == -2)
			{
				DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
				//DIGITAL_IO_SetOutputLow(&STATUS_LED_G);
				MainState = MS_ERROR_MAX_CURRENT;
				Homing(0);
			}
			if (temp == -3)
			{
				DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
				DIGITAL_IO_SetOutputLow(&STATUS_LED_G);
				MainState = MS_ERROR_BAD_HOMING;
				Homing(0);
			}
		}
			break;

		case MS_CLOSED:
		{
			//wait_timer++;
			wait_timer++;
			//WriteClutch(CLUTCH_LOCK);


			if(wait_timer >= 200)
			{
				MotorStop();
			}

			WriteBuzzer(BUZZER_OFF);
			//
			if((PassengerButton))// || (wait_timer >= 2000))
			{
				MainState = MS_OPENING;
				OpenTime = 0;
				wait_timer = 0;
			}
			if(Inputs.GIO & 0x0004)// || (wait_timer >= 2000))
			{
				MainState = MS_OPENING;
				OpenTime = 0;
				wait_timer = 0;
				serv_from_but = 1;
			}

			WriteRubberLights(CL_RED, MODE_TIME_ON, 1000);

		}
			break;
		case MS_OPENING:
		{
			WriteRubberLights(CL_GREEN, MODE_BLINK, 500);
			OpenTime++;
			WriteBuzzer(BUZZER_OFF);
			temp = OpenDoor(1);
			if (temp == 1)
			{
//				if(Presets.CYCLES_COUNTER % 200)
//				{
					MainState = MS_OPENED;
					serv_from_but = 0;
//				}
//				else
//				{
//					MainState = MS_START;
//				}
//
				DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
				DIGITAL_IO_SetOutputHigh(&STATUS_LED_G);

			}
			if (temp == 0)
			{
				blink++;
				if(blink >= 50)
				{
					DIGITAL_IO_ToggleOutput(&STATUS_LED_Y);
					blink = 0;
				}
			}
			if (temp == -1)
			{
				MainState = MS_ERROR_MOV_TIMEOUT;
				OpenDoor(0);
			}
			if (temp == -2)
			{
				MainState = MS_ERROR_MAX_CURRENT;
				OpenDoor(0);
			}
			if (temp == -3)
			{
				MainState = MS_ERROR_BAD_STATE;
				OpenDoor(0);
			}
			if(-4 == temp)
			{
				OpenDoor(0);
				MainState = MS_CLOSING;
			}

		}
			break;
		case MS_OPENED:
		{
			WriteRubberLights(CL_GREEN, MODE_ON, 0);
			WriteBuzzer(BUZZER_OFF);
			wait_timer++;
			if((PassengerButton))// || (wait_timer >= 200))
			{
				MainState = MS_CLOSING;
				CloseTime = 0;
				wait_timer = 0;
			}
			if((Inputs.GIO & 0x0004))// || (wait_timer >= 200))
			{
				MainState = MS_CLOSING;
				CloseTime = 0;
				wait_timer = 0;
				serv_from_but = 1;
			}

		}
			break;
		case MS_CLOSING:
		{
			WriteRubberLights(CL_RED, MODE_BLINK, 500);
			CloseTime++;
			temp = CloseDoor(1);
			if (temp == 1) //
			{
				DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
				DIGITAL_IO_SetOutputHigh(&STATUS_LED_G);
				MainState = MS_CLOSED;
				serv_from_but = 0;
			}
			if (temp == 0)
			{
				blink++;
				if(blink >= 50)
				{
					DIGITAL_IO_ToggleOutput(&STATUS_LED_Y);
					blink = 0;
				}
				WriteBuzzer(BUZZER_ON);
			}
			if (temp == -1)
			{
				MainState = MS_ERROR_MOV_TIMEOUT;
				CloseDoor(0);
			}
			if (temp == -2)
			{
				MainState = MS_ERROR_MAX_CURRENT;
				CloseDoor(0);
			}
			if (temp == -3)
			{
				MainState = MS_ERROR_BAD_STATE;
				CloseDoor(0);
			}
			if(-4 == temp)
			{
				CloseDoor(0);
				MainState = MS_OPENING;
			}
		}
			break;

		default: // now it is error handler, todo: different errors
		{
			blink++;
			//DIGITAL_IO_SetOutputLow(&STATUS_LED_G);
			//DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);

			if(blink >= 10)
			{
				DIGITAL_IO_ToggleOutput(&STATUS_LED_R);
				blink = 0;
			}
			WriteBuzzer(BUZZER_ON);
			//Motor0_BLDC_SCALAR_MotorStop();
			WritePassengerButton(CMD_OFF);
			WriteClutch(CLUTCH_LOCK);
			//DIGITAL_IO_SetOutputLow(&HS_SW_1);
			//DIGITAL_IO_SetOutputLow(&HS_SW_2);
			WriteRubberLights(CL_RED, MODE_BLINK, 200);
*/
			/*if(ServiceButton)
			{
				MainState = MS_START;
				DIGITAL_IO_SetOutputLow(&STATUS_LED_G);
				DIGITAL_IO_SetOutputLow(&STATUS_LED_Y);
				DIGITAL_IO_SetOutputLow(&STATUS_LED_R);
				WriteRubberLights(CL_BLACK, MODE_OFF, 0);
			}
			*/
			//DIGITAL_IO_SetOutputHigh(&STATUS_LED_R);
/*		}
		break;
	}
	}
}
	SendDiagnostics();
	SendExtCan();
	CanCmdOpenEnablePrev = CanCmdOpenEnable;

}// end_main_proc


void ReadPeripherials (void)
{
//	Motor0_BLDC_SCALAR_GetInstantaneousDCLinkCurrent(&ICurrent);
	//Motor0_BLDC_SCALAR_GetAverageDCLinkCurrent(&Current);
	//Current = abs(Current);

//	ICurrent = abs(ICurrent);
//	ACurrent = abs(ACurrent);
	//Motor0_BLDC_SCALAR_GetMotorSpeed(&Velocity);
	//Velocity = abs(Velocity);



//	Motor0_BLDC_SCALAR_GetMotorSpeed(&Velocity);
//	Velocity = abs(Velocity);

	//if (Current > Max_Close_current) Max_Close_current = Current;
	//if (Current > Max_Open_current) Max_Open_current = Current;

	ReadCloseSensor();
	ReadPassengerButton();
	ReadServiceButton();
	ReadActiveRubber();
//	ReadDisabledButton();
//	ReadPhotoSensor();
	ReadOpen1DoorButton();
//	if ((2 == Presets.CAN_ADRESS) || (3 == Presets.CAN_ADRESS) )
//	{
		ReadDisabledButton();
//		ReadTrapSensor();
//	}


}

void SendExtCan(void)
{
	static int32_t edsc1_timer = 0;
//	static int32_t edsc2_timer = 0;
//	static uint8_t PrevCan2TxData2[8];

//	int32_t new_data = 0;

	// todo: add OnChange

	edsc1_timer++;
//	edsc2_timer++;

//	Can1Tx1Prep();
//	Can1Tx2Prep();

//
//	for(int32_t i=0; i<8; i++)
//	{
//		if(Can2TxData2[i] != PrevCan2TxData2[i])
//		{
//			new_data = 1;
//		}
//	}
//
//	if(new_data)
//	{
//		edsc2_timer = 0;
//		Can1Tx2Send();
//	}
//
//	for(int32_t i = 0; i < 8; i++)
//	{
//		 PrevCan2TxData2[i] = Can2TxData2[i];
//	}

	if (10 <= edsc1_timer || DisabledButton)
	{
		Can1Tx1Prep();
		edsc1_timer = 0;
		Can1Tx1Send();
	}
//	if (100 <= edsc2_timer)
//	{
//		edsc2_timer = 0;
//		Can1Tx2Send();
//	}
}

void SendDiagnostics(void)
{
	static int32_t send_timer = 0;

	uint16_t temp16;
	uint8_t	temp8;
	uint32_t * p32;
	uint16_t * p16;

	if ((MainState == MS_OPENING) || (MainState == MS_CLOSING) || (MainState == MS_BLOCKAGE_CLS) || (MainState == MS_BLOCKAGE_OPN) || (MainState == MS_HOMING) || ServiceMode )	// only when moving
	{

		p16 = (uint16_t*)(Can2TxData1 + 0);
		*p16 = drive.Current;;

		p16 = (uint16_t*)(Can2TxData1 + 2);
		*p16 = drive.Velocity;;

		p16 = (uint16_t*)(Can2TxData1 + 4);
		*p16 = drive.Position;;

		temp16 = (uint16_t)CloseSensor * 100;
		p16 = (uint16_t*)(Can2TxData1 + 6);
		*p16 = temp16;

		CAN_NODE_MO_UpdateID(&CAN_INT_LMO_01_Config, 0x64);
		CAN_NODE_MO_UpdateData(&CAN_INT_LMO_01_Config, &Can2TxData1[0]);
		CAN_NODE_MO_Transmit(&CAN_INT_LMO_01_Config);
	}


	Can2TxData3[0] = (uint8_t)Inputs.PNP;
	Can2TxData3[1] = (uint8_t)Inputs.NPN;
	Can2TxData3[2] = (uint8_t)Inputs.GIO;
	Can2TxData3[3] = (uint8_t)Inputs.SB;
	p16 = (uint16_t*)(Can2TxData3 + 4);
	*p16 = Inputs.RIN1;

	p16 = (uint16_t*)(Can2TxData3 + 6);
	*p16 = (uint16_t)Inputs.DCIN;


	CAN_NODE_MO_UpdateID(&CAN_INT_LMO_03_Config, 0x66);
	CAN_NODE_MO_UpdateData(&CAN_INT_LMO_03_Config, &Can2TxData3[0]);
	CAN_NODE_MO_Transmit(&CAN_INT_LMO_03_Config);

	temp16 = OpenTime/10;
	temp8 = (uint8_t)temp16;
	Can2TxData2[0] = temp8;

	temp16 = CloseTime/10;
	temp8 = (uint8_t)temp16;
	Can2TxData2[1] = temp8;

	p16 = (uint16_t*)(Can2TxData2 + 2);
	//*p32 = Presets.CYCLES_COUNTER;
	*p16 = Inputs.DCIN;

	CAN_NODE_MO_UpdateID(&CAN_INT_LMO_02_Config, 0x65);
	CAN_NODE_MO_UpdateData(&CAN_INT_LMO_02_Config, &Can2TxData2[0]);
	CAN_NODE_MO_Transmit(&CAN_INT_LMO_02_Config);

//	p16 = (uint16_t*)(Can2TxData2 + 0);
//	*p16 = Inputs.InputPower;
//
//	CAN_NODE_MO_UpdateID(&CAN_2_LMO_02_Config, 0x65);
//	CAN_NODE_MO_UpdateData(&CAN_2_LMO_02_Config, &Can2TxData2[0]);
//	CAN_NODE_MO_Transmit(&CAN_2_LMO_02_Config);
//

	send_timer++;
	if((send_timer >= 10)) // send 1 message per second
	{
		send_timer = 0;
*/
/*		temp16 = OpenTime/10;
		temp8 = (uint8_t)temp16;
		Can2TxData2[0] = temp8;

		temp16 = CloseTime/10;
		temp8 = (uint8_t)temp16;
		Can2TxData2[1] = temp8;

		p16 = (uint16_t*)(Can2TxData2 + 2);
		//*p32 = Presets.CYCLES_COUNTER;
		*p16 = Inputs.InputPower;

		CAN_NODE_MO_UpdateID(&CAN_INT_LMO_02_Config, 0x65);
		CAN_NODE_MO_UpdateData(&CAN_INT_LMO_02_Config, &Can2TxData2[0]);
		CAN_NODE_MO_Transmit(&CAN_INT_LMO_02_Config);
*/
/*	}


}
*/
/*
void SaveProc(void *args)
{
	static int32_t count = 0;

	count++;
	if (count >= 300) // 1 time per 5 minutes
	{
		if (MS_CLOSED == MainState)
			{
				//E_EEPROM_XMC4_STATUS_t status = SaveParameter( &Presets, (pntrParam_t)&Presets.CyclesCounter);
				E_EEPROM_XMC4_STATUS_t status = SaveAllPresets( &Presets);//
				count = 0;
			}
	}
}



int32_t GetFiltValue(int32_t data)
{
	static int32_t buf[FILT_NUM];
	static int32_t pointer = 0;
	int32_t result = 0;

	buf[pointer] = data;
	pointer ++;
	if (pointer >= FILT_NUM)
	{
		pointer = 0;
	}

	for (uint32_t i=0;i<FILT_NUM;i++)
	{
		result += buf[i];
	}

	return (result/(FILT_NUM));
}

*/
