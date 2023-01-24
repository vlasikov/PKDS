/*
 * MainAlg.h
 *
 *  Created on: Mar 2, 2021
 *      Author: kendor
 */

#ifndef MAINALG_MAIN_ALG_H_
#define MAINALG_MAIN_ALG_H_

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "xmc_common.h"

#define MS_START 0
#define MS_UNKNOWN 1
#define MS_HOMING 2
#define MS_CLOSED 3
#define MS_OPENING 4
#define MS_OPENED 5
#define MS_CLOSING 6
#define MS_OPENED_BLOCK 7
//#define MS_WAIT_CMD 7

#define MS_BLOCKAGE_CLS 10
#define MS_BLOCKAGE_OPN 11
#define MS_BLOCKAGE_ALL 12

#define MS_ERROR_BAD_HOMING 20
#define MS_ERROR_MOV_TIMEOUT 21
#define MS_ERROR_MAX_CURRENT 22
#define MS_ERROR_BAD_STATE 23

#define MS_OPEN_1_DOOR 34
#define MS_CLOSE_1_DOOR 36

#define MS_ERROR_CLUTCH 22



#define MAIN_TIMER_TIME_MS 10  // Период вызова MainProc()

//#define DOOR_CLOSE_DIRECTION -1 // Направление закрытия
//#define DOOR_OPEN_DIRECTION (-DOOR_CLOSE_DIRECTION) // Направление открытия


extern int32_t MainState;

extern uint8_t Can1TxData1[8];
extern uint8_t Can1TxData2[8];
extern uint8_t Can2TxData1[8];
extern uint8_t Can2TxData2[8];
extern uint8_t Can2TxData3[8];


// Main alg functions

void MainAlgInit(void); // init timers and periph

void MainProc(void *args); // systimer call for main_proc
void SaveProc(void *args);
void ReadPeripherials(void);
//void WritePeripherials(void);
void SendExtCan(void);
void SendDiagnostics(void);

int32_t GetFiltValue(int32_t data);


#endif /* MAINALG_MAIN_ALG_H_ */
