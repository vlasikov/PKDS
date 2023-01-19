/*
 * ext_can.h
 *
 *  Created on: Jun 10, 2021
 *      Author: kendor
 */

#ifndef MAINALG_EXT_CAN_H_
#define MAINALG_EXT_CAN_H_

#define EXT_CAN_MAIN_LMO_DEF CAN_1_LMO_01_Config




typedef struct __DSC1
{
	// byte 1
	uint8_t DoorCmd;			//	bits0..1
	uint8_t DriverDoorCmd;		//  bits2..3	// not used here
	uint8_t RESERVED_1_1;		//  bits4..5
	uint8_t VelocityIsZero;		//  bits6..7

	//byte 2
	uint8_t PassengerExButEn;	//	bits0..1
	uint8_t PassengerInButEn;	//	bits2..3	// not used here
	uint8_t DisabledExButEn;	//	bits4..5
	uint8_t DisabledInButEn;	//	bits6..7	// not used here

	//byte 3
	uint8_t ReservedByte3;
	uint8_t ReservedByte4;
	uint8_t ReservedByte5;
	uint8_t ReservedByte6;
	uint8_t ReservedByte7;
	uint8_t ReservedByte8;

} DSC1_t;

typedef struct __DSC2
{
	// byte 1
	uint8_t RubberLightsL;		//	bits0..3	// not used here
	uint8_t RubberLightsR;		//  bits4..8	// not used here

	//byte 2
	uint8_t HeatCurtain;		//	bits0..1	// not used here
	uint8_t Zoomer;				//	bits2..5
	uint8_t NeonLights;			//	bits6..7	// not used here

	//byte 3
	uint8_t StairLight;			//	bits0..1
	uint8_t RedLight;			//	bits2..3	// not used here
	uint8_t PassengerInButLight;//	bits4..5	// not used here
	uint8_t PassengerExButLight;//	bits6..7

	//byte 4
	uint8_t DisabledInButLight;//	bits0..1	// not used here
	uint8_t DisabledExButLight;//	bits2..3
	uint8_t StopBut1Light;	   //	bits4..5
	uint8_t StopBut2Light;	   //	bits6..7	// not used here

	uint8_t ReservedByte5;
	uint8_t ReservedByte6;
	uint8_t ReservedByte7;
	uint8_t ReservedByte8;


} DSC2_t;

typedef struct __EDSC1
{
	//byte 1
	uint8_t DoorState; 			//	bits0..3
	uint8_t DoorIsClosed; 		//	bits4..5
	uint8_t TrapSensor; 		//	bits6..7

	//byte 2
	uint8_t AlarmOpen;			//	bits0..1
	uint8_t DoorIsDisabled;		//  bits2..3
	uint8_t BlockageIsWork;		//  bits4..5
	uint8_t DriveIsUnCalibrated;//  bits6..7

	//byte 3
	uint8_t CriticalError;		//	bits0..1
	uint8_t NonCriticalError;	//  bits2..3
	uint8_t DoorIsOpenedIllegal;//  bits4..5
	uint8_t RESERVED_3_7;		//  bits6..7	// not used here

	//byte 4
	uint8_t DoorIsBlockedCls;	//	bits0..1
	uint8_t DoorIsBlockedOpn;	//  bits2..3
	uint8_t RESERVED_4_7;		//  bits4..7

	uint8_t ReservedByte5;
	uint8_t ReservedByte6;

	//byte7
	uint8_t DSCInServiceMod;	//	bits0..1
	uint8_t RESERVED_7_7;		//  bits2..7

	uint8_t ReservedByte8;

} EDSC1_t;

typedef struct __EDSC2
{
	//byte 1
	uint8_t PassengerCabineBut;	//	bits0..1	// not used here
	uint8_t PassengerButton;	//  bits2..3
	uint8_t DisabledCabineBut;	//  bits4..5	// not used here
	uint8_t DisabledButton;		//  bits6..7

	//byte 2
	uint8_t TestButton;			//	bits0..1	// not used here
	uint8_t AlarmHandleIntern;	//  bits2..3	// not used here
	uint8_t AlarmHandleExtern;	//  bits4..5	// not used here
	uint8_t AlarmHandleInCap;	//  bits6..7	// not used here

	//byte 3
	uint8_t AlarmHandleExCap;	//  bits0..1	// not used here
	uint8_t ActiveRubber1;		//  bits2..3
	uint8_t ActiveRubber2;		//  bits4..5	// not used here
	uint8_t SafetyRelay;		//  bits6..7	// not used here

	//byte 4
	uint8_t TrapSensor; 		//  bits0..1
	uint8_t StairLight;			//  bits2..3
	uint8_t RedLight;			//  bits4..5	// not used here
	uint8_t NeonLight;			//  bits6..7	// not used here

	//byte 5
	uint8_t RubberLightsL;		//  bits0..3	// not used here
	uint8_t RubberLightsR;		//  bits4..7	// not used here

	//byte6
	uint8_t Zoomer;				//	bits0..3
	uint8_t HeatCurtain;		//	bits4..5	// not used here
	uint8_t PhotoSensor;		//	bits6..7	// not used here

	//byte7
	uint8_t CloseSensor; 		//  bits0..1
	uint8_t OpenSensor;			//  bits2..3	// not used here
	uint8_t StopButon1;			//  bits4..5
	uint8_t StopButon2;			//  bits6..7	// not used here

	//byte8
	uint8_t	SignalButton; 		//  bits0..1
	uint8_t EmergencyBrake;		//  bits2..3
	uint8_t RESERVED_8_7;		//  bits4..7

} EDSC2_t;

extern DSC1_t DSC1;
extern DSC2_t DSC2;
extern EDSC1_t EDSC1;
extern EDSC2_t EDSC2;



extern int32_t CanCmdOpenEnable;
extern int32_t CanCmdUnlock;
extern int32_t CanCmdOpenCmd;
extern int32_t CanCmdCloseCmd;
extern int32_t CanCmdCloseAll;
extern int32_t CanCmdEnablePassengersButton;



void Can1Rx1Parce(void);
void Can1Rx2Parce(void);
void Can1Rx3Parce(void);



void Can1Tx1Prep(void);
void Can1Tx2Prep(void);

void Can1Tx1Send(void);
void Can1Tx2Send(void);



#endif /* MAINALG_EXT_CAN_H_ */
