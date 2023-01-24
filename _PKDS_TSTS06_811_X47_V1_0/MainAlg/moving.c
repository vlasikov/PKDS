/*
 * moving.c
 *
 *  Created on: Feb 8, 2022
 *      Author: kendor
 */


#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "xmc_common.h"
//#include "MainAlg/main_alg.h"
#include "MainAlg/door_periph.h"
//#include "MotorLib/bldc_scalar_user_interface.h"
#include "MotorLib/motor.h"
#include "stdlib.h"
//#include "MainAlg/ext_can.h"
#include <MainAlg/presets.h>
#include <MainAlg/retain_xmc4.h>
#include <MainAlg/moving.h>

#define DOOR_DEFAULT_OPEN_POSITION 1300

//extern int32_t RAWPosition;
extern int32_t OPEN_DIR;
extern int32_t ServiceMode;
extern int32_t serv_from_but;
//
//int32_t Velocity = 0;
//int32_t Current = 0;
//int32_t ACurrent = 0;
//int32_t ICurrent = 0;
//int32_t Max_Close_current = 0;
//int32_t Max_Open_current = 0;
//int32_t Max_Velocity = 0;
//int32_t Min_Velocity = 0;
//
/*
int32_t Homing(int32_t cmd)
{
	int32_t result = 0;
	static int32_t state = 0;
	static int32_t pause = 0;
	static int32_t tim = 0;

	tim++;

	if(tim >= 2000)
	{
		MotorStop();
		state = 0;
		tim = 0;
		pause = 0;
		return -1; // timeout error
	}
	if (drive.Current >= 1500)
	{
		MotorStop();
		state = 0;
		tim = 0;
		pause = 0;
		return -2; // max current error
	}


	if(!cmd)
	{
		MotorStop();
		state = 0;
		tim = 0;
		pause = 0;
		//result = 0;
		return 0;
	}
	else
	{
		switch (state)
		{
		case 0:
		{
			MotorClearError();
			MotorSetPILimit(40);
			MotorSetProportionalGain(500);
			MotorSetIntegralGain(10);
			MotorSetSpeed(Presets.CLOSE_DIR * 150); //(Presets.CLOSE_DIR));
			MotorStart();
			state++;
			result = 0;
		}
		break;
		case 1:
		{
			if(drive.Current >= 200)
			{
				MotorStop();
				state++;
				result = 0;
			}
		}
		break;

			case 2:
			{
				WriteClutch(CLUTCH_UNLOCK);
				pause++;
				if(pause >= 20)
				{
					//pause = 0;
					//state = 1;
					MotorClearError();
					MotorSetPILimit(60);
					MotorSetProportionalGain(500);
					MotorSetIntegralGain(5);
					MotorSetSpeed(Presets.CLOSE_DIR * 300); //(Presets.CLOSE_DIR));
					MotorStart();
				}
				if(pause >= 23) // to eat start stable
				{
					pause = 0;
					state++;
				}
				result = 0;
			}
				break;

			case 3:
			{

				if(((drive.Current >= 2000) && !CloseSensor && !ServiceMode) || ActiveRubberL)
				{
					WriteClutch(CLUTCH_UNLOCK);
					MotorStop();
					result = -4;
				}
				else
				{
					result = 0;
				}

				if((!ServiceMode && CloseSensor && (drive.Current >= 300)) || (ServiceMode && (drive.Current >= 300)) || (ServiceMode && (drive.Current >= 300) && serv_from_but))//
				{
					WriteClutch(CLUTCH_LOCK);
					MotorSetProportionalGain(300);
					MotorSetIntegralGain(10);
					MotorSetPILimit(20);
					MotorSetSpeed(Presets.CLOSE_DIR * 5);
					MotorStart();
					state++;
					pause = 0;
				}

			}
				break;

			case 4:
			{
				WriteClutch(CLUTCH_LOCK);
				pause++;

				if (pause >= 20)//Presets.HOMING_CLUTCH_LOCK_PAUSE)
				{
					//MotorStop();
					drive.RAWPosition = 0;
					MotorSetPILimit(5);
					MotorSetProportionalGain(100);
					MotorSetIntegralGain(1);
					MotorSetSpeed(Presets.CLOSE_DIR * 5);
					result = 0; // success
					pause = 0;
					tim = 0;
					state++;

				}
				else
				{
					result = 0;
				}
			}
				break;
			case 5:
			{
				pause ++;
				if (5 <= pause)
				{
					pause = 0;
					result = 1;
					//drive.RAWPosition = 0;
					tim = 0;
					state = 0;
				}
				else
				{
					result = 0;
				}
			}
			break;
			default:
				return -3; // bad case;

				break;
		}//end switch
	}//end else (cmd!=0)
	return result;
}


int32_t CloseDoor(int32_t cmd)
{
	int32_t result = 0;
	static int32_t state = 0;
	static int32_t pause = 0;
	static int32_t tim = 0;


	tim++;

	if(tim >= 1000)
	{
		MotorStop();
		state = 0;
		tim = 0;
		pause = 0;
		return -1; // timeout error
	}
	if (drive.Current >= 3000)
	{
		MotorStop();
		state = 0;
		tim = 0;
		pause = 0;
		return -2; // max current error
	}


	if(!cmd)
	{
		MotorStop();
		state = 0;
		tim = 0;
		pause = 0;
		//result = 0;
		return 0;
	}
	else
	{
		switch (state)
		{
			case 0:
			{
				WriteClutch(CLUTCH_UNLOCK);
				pause++;
//
//				if(pause >= 20)
//				{
//					//pause = 0;
//					//state = 1;
//					Motor0_BLDC_SCALAR_SetSpeedProportionalGain(1000);
//					Motor0_BLDC_SCALAR_SetSpeedIntegralGain(100);
//					Motor0_BLDC_SCALAR_SetSpeedVal(Presets.CLOSE_DIR * 1000);
//					Motor0_BLDC_SCALAR_MotorStart();
//				}
//
//
				if(pause >= 5)
				{
					pause = 0;
					state = 1;
					MotorSetPILimit(80);
					MotorSetProportionalGain(1000);
					MotorSetIntegralGain(10);
					MotorSetSpeed(Presets.CLOSE_DIR * 1200);
					MotorStart();
				}
				result = 0;
			}
				break;

			case 1:
			{
				*//*if((Position > Presets.CLOSING_POSITION_1))
				{
					if (Current >= Presets.CLOSING_BLOCK_CURRENT_1)
					{
						result = -4;
						Motor0_BLDC_SCALAR_MotorStop();
					}
					else
					{
						result = 0;
					}
				}*/
/*				if((Position <= 600) && (Position > 400))
				{
					Motor0_BLDC_SCALAR_SetSpeedVal(Presets.CLOSE_DIR * 600);
					Motor0_BLDC_SCALAR_MotorStart();
					result = 0;
				}
*/
/*				if((drive.Position <= 550) && (drive.Position > 120))
				{
					MotorSetSpeed(Presets.CLOSE_DIR * 300);
					MotorStart();
					result = 0;
*/
					/*if (Current >= Presets.CLOSING_BLOCK_CURRENT_3)
					{
						result = -4;
						Motor0_BLDC_SCALAR_MotorStop();
					}
					else
					{
						result = 0;
					}*/
/*				}
				if((drive.Position <= 120) && (drive.Position > 20))
				{
					MotorSetProportionalGain(500);
					MotorSetIntegralGain(5);
					MotorSetSpeed(Presets.CLOSE_DIR * 150);
					MotorStart();
					result = 0;
*/
					/*if (Current >= Presets.CLOSING_BLOCK_CURRENT_4)
					{
						result = -4;
						Motor0_BLDC_SCALAR_MotorStop();
					}
					else
					{
						result = 0;
					}
					*/
/*				}
// blockge condition
				if(((drive.Current >= 2000) && (drive.Position >= 3)) || ActiveRubberL)// && !CloseSensor && !ServiceMode) || ActiveRubberL)
				{
					WriteClutch(CLUTCH_UNLOCK);
					MotorStop();
					result = -4;
				}
				else
				{
					result = 0;
				}
*/
/*				if(((Position <= 10)))
				{
					WriteClutch(CLUTCH_LOCK);
					result = 0;
				}
*/
// closed successful
//				if((/*(drive.Current > 400) && */(drive.Position <= 2)))// || ((CloseSensor) && (drive.Current >= 600)))//
//				{
//					WriteClutch(CLUTCH_LOCK);
//					MotorSetProportionalGain(100);
//					MotorSetIntegralGain(1);
//					MotorSetSpeed(Presets.CLOSE_DIR * 20);
//					MotorStart();
//					state = 2;
//					result = 0;
//					pause = 0;
//				}
//				//result = 0;
//
//				//if(ActiveRubberL || ActiveRubberR)
//				//{
//				//	result = -4;
//				//	Motor0_BLDC_SCALAR_MotorStop();
//				//}
//			}
//				break;
//
//			case 2:
//			{
//				WriteClutch(CLUTCH_LOCK);
//				pause++;
//				if (pause >= 40)//Presets.CLOSING_CLUTCH_LOCK_PAUSE)
//				{
//					{
//						//MotorStop();
//						MotorSetPILimit(5);
//						MotorSetProportionalGain(100);
//						MotorSetIntegralGain(1);
//						MotorSetSpeed(Presets.CLOSE_DIR * 5);
//						state = 0;
//						pause = 0;
//						result = 1;
//						tim = 0;
//					}
//				}
//				else
//				{
//					result = 0;
//				}
//			}
//				break;
//			default:
//				return -3; // bad case;
//
//				break;
//		}//end switch
//	}//end else (cmd!=0)
//	return result;
//}
//
//
//
//int32_t OpenDoor (int32_t cmd)
//{
//	int32_t result = 0;
//	static int32_t state = 0;
//	static int32_t pause = 0;
//	static int32_t tim = 0;
//
//	//static int32_t first_opening_done = 0;
//
//	tim++;
//
//
//	if(tim >= 2000)
//	{
//		MotorStop();
//		state = 0;
//		tim = 0;
//		pause = 0;
//		return -1; // timeout error
//	}
//	if (drive.Current >= 3000)
//	{
//		MotorStop();
//		state = 0;
//		tim = 0;
//		pause = 0;
//		return -2; // max current error
//	}
//
//
//	if(!cmd)
//	{
//		MotorStop();
//		state = 0;
//		pause = 0;
//		tim = 0;
//		//result = 0;
//		return 0;
//	}
//	else
//	{
//		switch (state)
//		{
//			case 0:
//			{
//				WriteClutch(CLUTCH_UNLOCK);
//				pause++;
//
//				if(pause <= 10)
//				{
//					MotorStop();
//				}
////				DIGITAL_IO_SetOutputHigh(&HS_SW_1);
////				DIGITAL_IO_SetOutputHigh(&HS_SW_2);
//				//DIGITAL_IO_SetOutputHigh(&STATUS_LED_R);
//
////
////				if((pause > 20) && (pause <= 30))
////				{
////					if(Current < 2500)
////					{
////						Motor0_BLDC_SCALAR_ClearErrorState();
////						Motor0_BLDC_SCALAR_SetSpeedProportionalGain(500);
////						Motor0_BLDC_SCALAR_SetSpeedIntegralGain(10);
////						Motor0_BLDC_SCALAR_SetSpeedVal(Presets.CLOSE_DIR * 10);
////						Motor0_BLDC_SCALAR_MotorStart();
////					}
////					else
////					{
////						Motor0_BLDC_SCALAR_MotorStop();
////					}
////				}
//
//				if((pause > 10) && (pause <= 20))
//				{
//					MotorSetPILimit(80);
//					MotorClearError();
//					MotorSetProportionalGain(500);
//					MotorSetIntegralGain(5);
//					MotorSetSpeed(Presets.CLOSE_DIR * 50);
//					MotorStart();
//
//				}
////
//				if(pause > 20)
//				{
//					MotorSetPILimit(80);
//					MotorClearError();
//					MotorSetProportionalGain(500);
//					MotorSetIntegralGain(5);
//					MotorSetSpeed(OPEN_DIR * 200);
//					MotorStart();
//					state  = 1;
//					pause = 0;
//					WriteClutch(CLUTCH_UNLOCK);
//				}
//
///*				if ((!HomingDone) && (pause >= (Presets.HOMING_CLUTCH_UNLOCK_PAUSE /2)))
//				{
//					state = 1;
//					pause = 0;
//					WriteClutch(CLUTCH_UNLOCK);
//				}
//*/
//				result = 0;
//			}
//				break;
//
//			case 1:
//			{
//				//DIGITAL_IO_SetOutputLow(&STATUS_LED_R);
//				if((Presets.OPEN_POSITION != 0x0))
//				{
//					if ((drive.Position >= 100) && (drive.Position < (Presets.OPEN_POSITION - 500)))
//					{
//						MotorClearError();
//						WriteClutch(CLUTCH_UNLOCK);
//						MotorSetProportionalGain(200);
//						MotorSetIntegralGain(5);
//						MotorSetSpeed(OPEN_DIR * 1000);
//						MotorStart();
//					}
//
//					if((drive.Position >= (Presets.OPEN_POSITION - 630)) && (drive.Position < (Presets.OPEN_POSITION - 200)))
//					{
//						MotorSetProportionalGain(200);
//						MotorSetIntegralGain(5);
//						MotorSetSpeed(OPEN_DIR * 400);
//						result = 0;
//					}
//
//					if(drive.Position >= (Presets.OPEN_POSITION - 120))
//					{
//						MotorSetProportionalGain(200);
//						MotorSetIntegralGain(5); // 10
//						MotorSetSpeed(OPEN_DIR * 150); //100
//						MotorStart();
//						state = 2;
//						result = 0;
//					}
//
//					if(((drive.Current >= 2500) && (drive.Position < (Presets.OPEN_POSITION - 500) ) && (drive.Position >= 500)) || ((drive.Current >= 2000) && (drive.Position < (Presets.OPEN_POSITION - 100) ) && (drive.Position >= (Presets.OPEN_POSITION - 500))) || (drive.Position >= (Presets.OPEN_POSITION - 100) && (drive.Current >= 1000)))
//					{
//						WriteClutch(CLUTCH_UNLOCK);
//						MotorStop();
//						result = -4;
//					}
//					else
//					{
//						result = 0;
//					}
//				}
//				else // if presets. openpos is clean
//				{
//
//					if ((drive.Position >= 100))
//					{
//						MotorClearError();
//						WriteClutch(CLUTCH_UNLOCK);
//						MotorSetProportionalGain(1000);
//						MotorSetIntegralGain(10);
//						MotorSetSpeed(OPEN_DIR * 600);
//						MotorStart();
//						result = 0;
//					}
//
//
//					if(drive.Position >= (DOOR_DEFAULT_OPEN_POSITION - 200))
//					{
//						MotorSetProportionalGain(2000);
//						MotorSetIntegralGain(10);
//						MotorSetSpeed(OPEN_DIR * 100);
//						MotorStart();
//						result = 0;
//					}
//
//
//					if((drive.Position >= DOOR_DEFAULT_OPEN_POSITION) && (drive.Current >= 100) && !ServiceMode)
//					{
//
//						MotorStop();
//						Presets.OPEN_POSITION = drive.Position;
//						SaveAllPresets(&Presets);
//						ReadAllPresets(&Presets);
//
//						state = 3;
//						result = 0;
//					}
//					if((drive.Position >= DOOR_DEFAULT_OPEN_POSITION) && (drive.Current >= 100) && ServiceMode)
//					{
//						//Presets.OPEN_POSITION = drive.Position;
//						MotorStop();
//						state = 3;
//						result = 0;
//					}
//					//result = 0;
//				}
//
//			}
//				break;
//
//			case 2:
//			{
//
////				if((Position < (Presets.OPEN_POSITION - 50)))
////				{
////					if (Current >= Presets.OPENING_BLOCK_CURRENT_3)
////					{
////						result = -4;
////						Motor0_BLDC_SCALAR_MotorStop();
////					}
////					else
////					{
////						result = 0;
////					}
////				}
//
//				if(((drive.Position >= (Presets.OPEN_POSITION - 5))))
//				{
//					MotorSetProportionalGain(400);
//					MotorSetIntegralGain(10);
//					MotorSetSpeed(OPEN_DIR * 5);
//					MotorStart();
//					//Motor0_BLDC_SCALAR_MotorStop();
//
//					state = 3;
//				}
//				result = 0;
//			}
//				break;
//
//			case 3:
//			{
//				pause++;
//				if (pause >= 1)
//				{
//					{
//						WriteClutch(CLUTCH_LOCK);
//						MotorStop();
//						state = 4;
//						pause = 0;
//						result = 0;
//					}
//				}
//				else
//				{
//					result = 0;
//				}
//			}
//				break;
//
//			case 4:
//			{
//				pause++;
//				if (pause >= 10)
//				{
//					{
//						WriteClutch(CLUTCH_LOCK);
//						MotorStop();
//						state = 0;
//						pause = 0;
//						result = 1;
//						tim = 0;
//						//Presets.CYCLES_COUNTER++;
//
//						//first_opening_done = 1;
//					}
//				}
//				else
//				{
//					result = 0;
//				}
//			}
//				break;
//			default:
//				return -3; // bad case;
//
//				break;
//		}//end switch
//	}//end else (cmd!=0)
//	return result;
//}
//
//int32_t OpenAfterBlockage (int32_t cmd)
//{
//	int32_t result = 0;
//	static int32_t state = 0;
//	static int32_t pause = 0;
//	static int32_t tim = 0;
//
//	//static int32_t first_opening_done = 0;
//
//	tim++;
//
//
//	if(tim >= 1000)
//	{
//		MotorStop();
//		state = 0;
//		tim = 0;
//		pause = 0;
//		return -1; // timeout error
//	}
//	if (drive.Current >= 3000)
//	{
//		MotorStop();
//		state = 0;
//		tim = 0;
//		pause = 0;
//		return -2; // max current error
//	}
//
//
//	if(!cmd)
//	{
//		MotorStop();
//		state = 0;
//		pause = 0;
//		tim = 0;
//		//result = 0;
//		return 0;
//	}
//	else
//	{
//		switch (state)
//		{
//			case 0:
//			{
//				WriteClutch(CLUTCH_UNLOCK);
//
////				DIGITAL_IO_SetOutputHigh(&HS_SW_1);
////				DIGITAL_IO_SetOutputHigh(&HS_SW_2);
//				//DIGITAL_IO_SetOutputHigh(&STATUS_LED_R);
//				pause++;
////
////				if((pause > 20) && (pause <= 30))
////				{
////					if(Current < 2500)
////					{
////						Motor0_BLDC_SCALAR_ClearErrorState();
////						Motor0_BLDC_SCALAR_SetSpeedProportionalGain(500);
////						Motor0_BLDC_SCALAR_SetSpeedIntegralGain(10);
////						Motor0_BLDC_SCALAR_SetSpeedVal(Presets.CLOSE_DIR * 10);
////						Motor0_BLDC_SCALAR_MotorStart();
////					}
////					else
////					{
////						Motor0_BLDC_SCALAR_MotorStop();
////					}
////				}
//
////				if((pause > 10) && (pause <= 20))
////				{
////					//Motor0_BLDC_SCALAR_MotorStop();
////					Motor0_BLDC_SCALAR_ClearErrorState();
////					Motor0_BLDC_SCALAR_SetSpeedProportionalGain(500);
////					Motor0_BLDC_SCALAR_SetSpeedIntegralGain(10);
////					Motor0_BLDC_SCALAR_SetSpeedVal(OPEN_DIR * 250);
////					Motor0_BLDC_SCALAR_MotorStart();
////				}
////
//				if(pause > 5)
//				{
//					MotorClearError();
//					MotorSetProportionalGain(2000);
//					MotorSetIntegralGain(20);
//					MotorSetSpeed(OPEN_DIR * 200);
//					MotorStart();
//					state  = 1;
//					pause = 0;
//					WriteClutch(CLUTCH_UNLOCK);
//				}
//
///*				if ((!HomingDone) && (pause >= (Presets.HOMING_CLUTCH_UNLOCK_PAUSE /2)))
//				{
//					state = 1;
//					pause = 0;
//					WriteClutch(CLUTCH_UNLOCK);
//				}
//*/
//				result = 0;
//			}
//				break;
//
//			case 1:
//			{
//				//DIGITAL_IO_SetOutputLow(&STATUS_LED_R);
////				if((Presets.OPEN_POSITION != 0x0))
//	//			{
//				if ((drive.Position >= 40) && (drive.Position < (Presets.OPEN_POSITION - 500)))
//				{
//					MotorClearError();
//				    WriteClutch(CLUTCH_UNLOCK);
//					MotorSetProportionalGain(1000);
//					MotorSetIntegralGain(10);
//					MotorSetSpeed(OPEN_DIR * 1000);
//					MotorStart();
//				}
//
//				if((drive.Position >= (Presets.OPEN_POSITION - 500)) && (drive.Position < (Presets.OPEN_POSITION - 200)))
//				{
//					MotorSetSpeed(OPEN_DIR * 400);
//					result = 0;
//				}
//
//
//				if(((drive.Current >= 2500) && (drive.Position < 1300) && (drive.Position >= 500)) || ((drive.Position > 1300) && (drive.Current >= 800)))
//				{
//					WriteClutch(CLUTCH_UNLOCK);
//					MotorStop();
//					result = -4;
//				}
//				else
//				{
//					result = 0;
//				}
//
//				if(drive.Position >= (Presets.OPEN_POSITION - 150))
//				{
//					MotorSetProportionalGain(2000);
//					MotorSetIntegralGain(10);
//					MotorSetSpeed(OPEN_DIR * 100);
//					MotorStart();
//					state = 2;
//					result = 0;
//				}
////				}
////				else // if presets. openpos is clean
////				{
////					if((Position >= DOOR_DEFAULT_OPEN_POSITION) && (Current >= 500))
////					{
////						Motor0_BLDC_SCALAR_SetSpeedProportionalGain(2000);
////						Motor0_BLDC_SCALAR_SetSpeedIntegralGain(20);
////						Motor0_BLDC_SCALAR_SetSpeedVal(OPEN_DIR * 5);
////						Motor0_BLDC_SCALAR_MotorStart();
////
////						Presets.OPEN_POSITION = Position;
////						SaveAllPresets(&Presets);
////						ReadAllPresets(&Presets);
////
////						state = 2;
////						result = 0;
////					}
////
////				}
//				//result = 0;
//			}
//				break;
//
//			case 2:
//			{
//
////				if((Position < (Presets.OPEN_POSITION - 50)))
////				{
////					if (Current >= Presets.OPENING_BLOCK_CURRENT_3)
////					{
////						result = -4;
////						Motor0_BLDC_SCALAR_MotorStop();
////					}
////					else
////					{
////						result = 0;
////					}
////				}
//
//				if(((drive.Position >= (Presets.OPEN_POSITION - 10))))
//				{
//					MotorSetProportionalGain(400);
//					MotorSetIntegralGain(10);
//					MotorSetSpeed(OPEN_DIR * 5);
//					MotorStart();
//					//Motor0_BLDC_SCALAR_MotorStop();
//
//					state = 3;
//				}
//				result = 0;
//			}
//				break;
//
//			case 3:
//			{
//				pause++;
//				if (pause >= 1)
//				{
//					{
//						WriteClutch(CLUTCH_LOCK);
//						MotorStop();
//						state = 4;
//						pause = 0;
//						result = 0;
//					}
//				}
//				else
//				{
//					result = 0;
//				}
//			}
//				break;
//
//			case 4:
//			{
//				pause++;
//				if (pause >= 10)
//				{
//					{
//						WriteClutch(CLUTCH_LOCK);
//						MotorStop();
//						state = 0;
//						pause = 0;
//						result = 1;
//						tim = 0;
//						//Presets.CYCLES_COUNTER++;
//
//						//first_opening_done = 1;
//					}
//				}
//				else
//				{
//					result = 0;
//				}
//			}
//				break;
//			default:
//				return -3; // bad case;
//
//				break;
//		}//end switch
//	}//end else (cmd!=0)
//	return result;
//}
//
//
//
