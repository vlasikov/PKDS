/*
 * door_periph.h
 *
 *  Created on: Mar 3, 2021
 *      Author: kendor
 */

#ifndef MAINALG_DOOR_PERIPH_H_
#define MAINALG_DOOR_PERIPH_H_


#define CLUTCH_UNLOCK 1
#define CLUTCH_LOCK 0

#define CMD_ON 1
#define CMD_OFF 0



#define BLOCKAGE_TIME_MS 300




typedef struct __INPUT_SIGNALS
{
	uint16_t PNP;
	uint16_t NPN;
	uint16_t IO;
	uint16_t ServiceButton;

	uint16_t ActiveRubberLVal;
	uint16_t ActiveRubberRVal;

	uint16_t InputPower;
	uint16_t DriveCurrent;

}	INPUT_SIGNALS_t;

/*
typedef struct __INPUT_PERIFERIAL
{



}INPUT_PERIPHERIAL_t;
*/

extern INPUT_SIGNALS_t Inputs;


extern int32_t Position;
extern int32_t VPower;
extern int32_t CloseSensor;
extern int32_t ActiveRubberL;
extern int32_t ActiveRubberR;
extern int32_t ServiceButton;
extern int32_t ServiceButtonFront;
extern int32_t PassengerButton;
extern int32_t DisabledButton;
extern int32_t TrapSensor;
extern int32_t StopButton;
extern int32_t PhotoSensor;

extern int32_t Open1DoorBut;
extern int32_t Close1DoorBut;

extern int32_t PidEnable;


void DoorPeriphInit(void); // Init door peripherial devices

int32_t Blockage(int32_t cmd); //


void ReadInputs(void);



void ReadCloseSensor (void);
void ReadServiceButton(void);
void ReadPassengerButton(void);
void ReadDisabledButton(void);
void ReadActiveRubber(void);
void ReadTrapSensor(void);
void ReadStopButton(void);
void ReadPhotoSensor(void);

void ReadOpen1DoorButton(void);
void ReadClose1DoorButton(void);

void WriteClutch(int32_t cmd);
void WritePassengerButton (int32_t cmd);
//void WriteDisabledButton (int32_t cmd);
void WriteStopButton (int32_t cmd);


void HallTimerProc(void *args);
extern void MotorStepProc(void *args);


//void PID_Step(PID_t * target_pid);

// read hall sensor

// Read inputs

// Set Outputs




#endif /* MAINALG_DOOR_PERIPH_H_ */
