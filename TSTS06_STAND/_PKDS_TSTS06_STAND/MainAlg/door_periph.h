/*
 * door_periph.h
 *
 *  Created on: Mar 3, 2021
 *      Author: kendor
 */

#ifndef MAINALG_DOOR_PERIPH_H_
#define MAINALG_DOOR_PERIPH_H_

#define MODE_OFF 		0
#define MODE_ON 		1
#define MODE_BLINK 		2
#define MODE_TIME_ON 	3

#define CLUTCH_UNLOCK 1
#define CLUTCH_LOCK 0

#define CMD_ON 1
#define CMD_OFF 0


#define CL_RED 		0xFF000000U
#define CL_GREEN 	0x00FF0000U
#define CL_YELLOW   0xFFFF0000U
#define CL_BLACK 	0x00000000U


#define BLOCKAGE_TIME_MS 300
#define RUBBER_BLINK_MS 500

typedef struct __LED_RUBBER_LIGHT
{
  int32_t red_outern;
  int32_t green_outern;
  int32_t blue_outern;

  int32_t red_intern;
  int32_t green_intern;
  int32_t blue_intern;

} LED_RUBBER_LIGHT_t;

typedef struct __INPUT_SIGNALS
{
	uint16_t PNP;
	uint16_t NPN;
	uint16_t GIO;
	uint16_t SB;

	uint16_t RIN1;
	uint16_t RIN2;

	uint16_t DCIN;
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


void WriteRubberLights(uint32_t color, int32_t mode, int32_t time_ms); // mb change

void HallTimerProc(void *args);
extern void MotorStepProc(void *args);
void LedPwmTimerProc(void *args);

//void PID_Step(PID_t * target_pid);

// read hall sensor

// Read inputs

// Set Outputs




#endif /* MAINALG_DOOR_PERIPH_H_ */
