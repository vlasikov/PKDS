/*
 * presets.c
 *
 *  Created on: Jul 16, 2021
 *      Author: Primary
 */

/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
#include "MainAlg/presets.h"
#include "MainAlg/main_alg.h"



/* ---------------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
const PresetsTypeDef DefaultPresets = { // stored in the RAM default presets instance

	.CLOSE_DIR = 1, // for CA==0 is 1 for 1-3 is -1
	.CLOSE_SENSOR_TYPE = 1,
	.DOOR_NUMBER = 1,

	.PROJECT_NUM = 1,
	.SOFTWARE_VERSION = 0x00010005,
	.HARDWARE_VERSION = 0x00100245,
	.CYCLES_COUNTER = 0,

	.STARTUP_TIME = (2000/MAIN_TIMER_TIME_MS),
	.MAXIMUM_CURRENT = (3000),
	.OPEN_POSITION = (0), //1400//1480//1780

	.VEHICLE_SPEED_THRESHOLD = (5 * 256), //
	.HOMING_VELOCITY = (200),
	.HOMING_DONE_CURRENT = (2000),

	.CLOSING_TIMEOUT = (8000/MAIN_TIMER_TIME_MS),
	.CLOSING_VELOCITY = 160,
	.CLOSING_DONE_CURRENT = (800),

	.OPENING_TIMEOUT = (8000/MAIN_TIMER_TIME_MS),
	.OPENING_VELOCITY = 160,
//	.CYCLES_COUNTER = 0,
	.BUZZER_TYPE = 0,  //0 - SFM 1 - BPT use sfm(0) for all

	// ...
}; // for example only...



/* ---------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
PresetsTypeDef Presets; // stored in the RAM working presets instance



/* ---------------------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Public Functions ----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
void ReadAllPresets( const PresetsTypeDef *const pntrPresets ) {
	E_EEPROM_XMC4_ReadArray( 0, (uint8_t*)pntrPresets, sizeof(*pntrPresets) );
}



void ReadParameter( const PresetsTypeDef *const pntrPresets, pntrParam_t pntrParam ) {
	int32_t offset = pntrParam - (uint8_t*)pntrPresets;
	XMC_ASSERT("EEPROM ReadParameter: Wrong parameter address", (offset >= 0) );
	XMC_ASSERT("EEPROM ReadParameter: Wrong parameter address", (offset < RETAIN_SIZE) );
	XMC_ASSERT("EEPROM ReadParameter: Wrong parameter address", (offset % 4 == 0) );

	E_EEPROM_XMC4_ReadArray( (uint16_t)offset, pntrParam, 4 ); // read 4 bytes (one parameter)
}



E_EEPROM_XMC4_STATUS_t SaveAllPresets( const PresetsTypeDef *const pntrPresets ) {
	E_EEPROM_XMC4_WriteArray( 0, (uint8_t*)pntrPresets, sizeof(*pntrPresets) );
	return E_EEPROM_XMC4_UpdateFlashContents();
}



E_EEPROM_XMC4_STATUS_t SaveParameter( const PresetsTypeDef *const pntrPresets, const pntrParam_t pntrParam ) {
	uint16_t offset = pntrParam - (uint8_t*)pntrPresets;
	XMC_ASSERT("EEPROM SaveParameter: Wrong parameter address", (offset >= 0) );
	XMC_ASSERT("EEPROM SaveParameter: Wrong parameter address", (offset < RETAIN_SIZE) );
	XMC_ASSERT("EEPROM SaveParameter: Wrong parameter address", (offset % 4 == 0));

	E_EEPROM_XMC4_WriteArray( (uint16_t)offset, pntrParam, 4 ); // write 4 bytes (one parameter)
	return E_EEPROM_XMC4_UpdateFlashContents();
}

/* ---------------------------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
