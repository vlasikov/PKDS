/*
 * serv_mode.h
 *
 *  Created on: Feb 17, 2022
 *      Author: kendor
 */

#ifndef MAINALG_SERV_MODE_H_
#define MAINALG_SERV_MODE_H_

extern uint8_t ServCanRxData1[8];
extern uint8_t ServCanRxData2[8];

typedef struct __ServCan
{
	uint8_t ModeCmd;
	uint8_t DoorCmd;
	uint8_t OutHS;
	uint8_t OutLS;
	uint8_t OutLED;

	uint8_t Dir;
	uint8_t Value;




} ServCan_t;





#endif /* MAINALG_SERV_MODE_H_ */
