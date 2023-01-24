/*
 * presets.h
 *
 *  Created on: Jul 14, 2021
 *      Author: Primary
 */

#ifndef PRESETS_H_
#define PRESETS_H_

/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
#include <MainAlg/retain_xmc4.h>



/* ---------------------------------------------------------------------------*/
/* Defines -------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
#define RETAIN_SIZE		E_EEPROM_XMC4_DATA_BLOCK_SIZE



/* ---------------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
typedef uint8_t *const pntrParam_t;



/* WARNING! Use 32-bits types of data only (uint32_t / int32_t / float) */
typedef struct __PresetsTypeDef
{

	int32_t  CLOSE_DIR;
	uint32_t CLOSE_SENSOR_TYPE;
	uint32_t DOOR_NUMBER;
	uint32_t PROJECT_NUM;
	uint32_t SOFTWARE_VERSION;
	uint32_t HARDWARE_VERSION;
	uint32_t CYCLES_COUNTER;

	uint32_t  STARTUP_TIME;
	uint32_t  MAXIMUM_CURRENT;
	uint32_t  OPEN_POSITION;

	uint32_t  VEHICLE_SPEED_THRESHOLD;
	uint32_t  HOMING_VELOCITY;
	uint32_t  HOMING_DONE_CURRENT;

	uint32_t  CLOSING_TIMEOUT;
	uint32_t  CLOSING_VELOCITY;
	uint32_t  CLOSING_DONE_CURRENT;

	uint32_t  OPENING_TIMEOUT;
	uint32_t  OPENING_VELOCITY;
	//uint32_t  CYCLES_COUNTER;
	uint32_t BUZZER_TYPE;


	/* Add here new parameters up to the RETAIN_SIZE bytes */

} PresetsTypeDef;



/* ---------------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/* ---------------------------------------------------------------------------*/
void ReadAllPresets( const PresetsTypeDef *const pntrPresets );
void ReadParameter( const PresetsTypeDef *const pntrPresets, pntrParam_t pntrParam );
E_EEPROM_XMC4_STATUS_t SaveAllPresets( const PresetsTypeDef *const pntrPresets );
E_EEPROM_XMC4_STATUS_t SaveParameter( const PresetsTypeDef *const pntrPresets, const pntrParam_t pntrParam );



/* ---------------------------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
extern E_EEPROM_XMC4_t RETAIN;
extern PresetsTypeDef Presets;
extern const PresetsTypeDef DefaultPresets;
/* ---------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

__STATIC_INLINE bool GetRetainInitStatus( void ) {
	return RETAIN.initialized;
}
#if ( RETAIN_SIZE + 8 ) % 512 != 0
	#error <Data block size> parameter of the E_EEPROM_XMC4 DAVE app is not optimal. Recommended values are 504 / 1016 / 2040 / 4088 / 8184.
#endif



#endif /* PRESETS_H_ */
