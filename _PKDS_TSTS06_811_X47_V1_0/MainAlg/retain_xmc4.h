/*
 * retain.h
 *
 *  Created on: Jul 19, 2021
 *      Author: Primary
 */

#ifndef RETAIN_XMC4_H_
#define RETAIN_XMC4_H_

/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
#include "xmc_flash.h"
#include "xmc_fce.h"
#include "DAVE_Common.h"



/* ---------------------------------------------------------------------------*/
/* Defines -------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
#define E_EEPROM_XMC4_DATA_BLOCK_SIZE 2040U /**< Data size defined in the UI interface "Data block size"*/

#define E_EEPROM_XMC4_ACTUAL_FLASH_BLOCK_SIZE 2048U /**< Internally assigned data block size by the APP
                                                                     Only allow multiples of 512 bytes till 8192*/

#define E_EEPROM_XMC4_FCE_KERNEL_BASE (FCE_KE0_BASE)  /**< FCE kernel number used for CRC calculation*/



/* ---------------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/** Defines the error codes for E_EEPROM_XMC4 application. Use @ref E_EEPROM_XMC4_STATUS_t type for accessing the member.  */
typedef enum E_EEPROM_XMC4_STATUS
{
  E_EEPROM_XMC4_STATUS_OK                 = 0U, /**< Successful completion of initialization */
  E_EEPROM_XMC4_STATUS_ERROR_OLD_DATA     = 1U, /**< Initialization succeeded with old data block. Latest has been found
                                                     corrupted or half programmed in previous power down cycle write. */
  E_EEPROM_XMC4_STATUS_READ_ERROR         = 2U, /**< Initialization failed due to read error */
  E_EEPROM_XMC4_STATUS_WRITE_ERROR        = 3U, /**< Initialization failed due to write error */
  E_EEPROM_XMC4_STATUS_ERASE_ERROR        = 4U, /**< Initialization failed due to erase error */
} E_EEPROM_XMC4_STATUS_t;



/**
* @brief Initialization data structure of E_EEPROM_XMC4 APP
*/
typedef struct E_EEPROM_XMC4
{
  bool initialized;                           /**< Initialization status */
} E_EEPROM_XMC4_t;



/* ---------------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/**
 * @ingroup E_EEPROM_XMC4_apidoc
 * @{
 */

/**
 * @brief Initializes flash emulated EEPROM to start read and write operations.
 * @param None
 *
 * @return E_EEPROM_XMC4_STATUS_OK, if Initialization succeeds, Else\n
 *         E_EEPROM_XMC4_STATUS_WRITE_ERROR, if initialization failed due to write error.
 *         E_EEPROM_XMC4_STATUS_ERASE_ERROR, if erase failed during initialization process.
 *         E_EEPROM_XMC4_STATUS_ERROR_OLD_DATA, if initialization succeeded with old data block. Latest has been found
 *                                              corrupted or half programmed in previous power down cycle write.
 *
 * \par<b>Description:</b><br>
 * Initializes Flash Emulated EEPROM application.\n
 * It checks for the latest written block starting from logical SECTOR 7 to SECTOR 4. If a latest block is identified
 * among any 4 sectors, the block gets copied to RAM. Hence it can be read any time from RAM. If no blocks identified,
 * SECTOR 4 is considered as current active sector for future writes. \n If more than one SECTOR has data blocks, all
 * sectors apart from the sector having the latest data block are erased. In this process, any flash errors results in
 * "E_EEPROM_XMC4_STATUS_ERASE_ERROR" state.\n  If the sector having the latest block doesn't have any free space, the Init
 * process will copy the latest block into new free sector and erase the old sector. If the copy process results in
 * flash write errors or when all sectors filled up, it returns the status \a E_EEPROM_XMC4_STATUS_WRITE_ERROR.
 *
 * \par<b>Related APIs:</b><BR>
 * None \n
 */
E_EEPROM_XMC4_STATUS_t E_EEPROM_XMC4_Init(E_EEPROM_XMC4_t *const handle);



/**
 * @brief Update a particular byte in the RAM copy of data block.
 * @param address RAM Offset address, where the data shall be written.
 * @param data    8bit data to be written into the RAM buffer.
 *
 * @return Boolean indicating if changes were detected since the last write to the address
 * @note If the function returns true, an update of the flash can be triggered by E_EEPROM_XMC4_UpdateFlashContents()
 *
 * \par<b>Description:</b><br>
 * Write a particular byte into the RAM buffer. Sets up the internal RAM buffer with data elements
 * which are targeted to be written into emulated flash area.\n
 *
 *<b>Related APIs : </b><BR>  None\n\n
 */
bool E_EEPROM_XMC4_WriteByte(const uint16_t offset_address, const uint8_t value);



/**
 * @brief Update a set of bytes in the RAM copy of data block.
 * @param address RAM Offset address from where the data write shall be started.
 * @param data    Constant pointer to array of 8bit data.
 * @param length  Length of the data array (specify the number bytes to be written).
 *
 * @return Boolean indicating if changes were detected since the last write to the same area
 * @note If the function returns true, an update of the flash can be triggered by E_EEPROM_XMC4_UpdateFlashContents()
 *
 * \par<b>Description:</b><br>
 * Write an array of data elements into the RAM buffer.\n
 *
 *<b>Related APIs : </b><BR>  None\n\n
 */
bool E_EEPROM_XMC4_WriteArray(const uint16_t offset_address, const uint8_t *const data, const uint16_t length);



/**
 * @brief Reads a particular byte from the RAM copy of data block.
 * @param address RAM Offset address from where the data read shall be started.
 * @param data    Constant pointer to 8bit data variable (address of variable).
 *
 *
 * @return None
 *
 * \par<b>Description:</b><br>
 * Read a particular byte from the RAM buffer.\n
 *
 *<b>Related APIs : </b><BR>  None\n\n
 */
void E_EEPROM_XMC4_ReadByte(const uint16_t offset_address, uint8_t *const value);



/**
 * @brief Reads a set of bytes from the RAM copy of data block.
 * @param address RAM Offset address from where the data read shall be started.
 * @param data    Constant pointer to array of 8bit data variable.
 * @param length  Length of the data array (specify the number bytes to be read).
 *
 * @return None
 *
 * \par<b>Description:</b><br>
 * Read an array of data elements from the RAM buffer.\n
 *
 * \par<b>Related APIs:</b><BR>
 * None\n
 */
void E_EEPROM_XMC4_ReadArray(const uint16_t offset_address, uint8_t *const data, const uint16_t length);



/**
 * @brief Programs the flash with the latest data block available in RAM.
 * @param None
 *
 * @return E_EEPROM_XMC4_STATUS_OK, if flash programming succeeds, Else\n
 *         E_EEPROM_XMC4_STATUS_WRITE_ERROR, fails due to flash write error or \n
 *         E_EEPROM_XMC4_STATUS_ERASE_ERROR, fails due to flash erase operation when all sectors are filled up.
 *
 * \par<b>Description:</b><br>
 * Programs the RAM buffer into emulated area of the FLASH. On successful completion of this API, the data block
 * gets saved in the flash. Hence data retention is possible over reset cycles. Call this API only in the POWER
 * DOWN cycle to ensure the flash endurance.
 *
 * \par<b>Related APIs:</b><BR>
 * None\n
 */
E_EEPROM_XMC4_STATUS_t E_EEPROM_XMC4_UpdateFlashContents(void);



/**
 * @brief Check at least one data block is available in the flash emulated EEPROM.
 * @param None
 *
 * @return  <BR>
 *        true, if the flash is empty
 *        else returns false.
 *
 * \par<b>Description:</b><br>
 *  During first time of the execution, flash can be programmed with data by checking this API status.
 *
 * \par<b>Related APIs:</b><BR>
 *  None\n
 */
bool E_EEPROM_XMC4_IsFlashEmpty(void);


/* ---------------------------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
#define E_EEPROM_XMC4_XMC_LIB_MAJOR_VERSION 2
#define E_EEPROM_XMC4_XMC_LIB_MINOR_VERSION 1
#define E_EEPROM_XMC4_XMC_LIB_PATCH_VERSION 4



/* ---------------------------------------------------------------------------*/
/* Private types -------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
#if !((XMC_LIB_MAJOR_VERSION > E_EEPROM_XMC4_XMC_LIB_MAJOR_VERSION) ||\
      ((XMC_LIB_MAJOR_VERSION == E_EEPROM_XMC4_XMC_LIB_MAJOR_VERSION) && (XMC_LIB_MINOR_VERSION > E_EEPROM_XMC4_XMC_LIB_MINOR_VERSION)) ||\
      ((XMC_LIB_MAJOR_VERSION == E_EEPROM_XMC4_XMC_LIB_MAJOR_VERSION) && (XMC_LIB_MINOR_VERSION == E_EEPROM_XMC4_XMC_LIB_MINOR_VERSION) && (XMC_LIB_PATCH_VERSION >= E_EEPROM_XMC4_XMC_LIB_PATCH_VERSION)))
#error "E_EEPROM_XMC4 requires XMC Peripheral Library v2.1.4 or higher"
#endif



#endif /* RETAIN_XMC4_H_ */
