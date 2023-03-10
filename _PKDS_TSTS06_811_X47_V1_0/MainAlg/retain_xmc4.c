/*
 * retain.c
 *
 *  Created on: Jul 19, 2021
 *      Author: Primary
 */

/* ---------------------------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
#include "retain_xmc4.h"



/* ---------------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* EEPROM SECTOR numbers definitions */
#define E_EEPROM_XMC4_SECTOR_0    ((uint32_t)0U)
#define E_EEPROM_XMC4_SECTOR_1    ((uint32_t)1U)
#define E_EEPROM_XMC4_SECTOR_2    ((uint32_t)2U)
#define E_EEPROM_XMC4_SECTOR_3    ((uint32_t)3U)
#define E_EEPROM_XMC4_MAX_SECTORS ((uint32_t)4U)

/* Offset positions for CRC and user DATA definitions*/
#define E_EEPROM_XMC4_BCC_OFFSET  ((uint8_t)1U)
#define E_EEPROM_XMC4_DATA_OFFSET ((uint8_t)2U)

/* All four logical sector starting addresses defined */
#define E_EEPROM_XMC4_SECTOR0_START_ADDR   (XMC_FLASH_UNCACHED_BASE + 0x10000U)
#define E_EEPROM_XMC4_SECTOR1_START_ADDR   (XMC_FLASH_UNCACHED_BASE + 0x14000U)
#define E_EEPROM_XMC4_SECTOR2_START_ADDR   (XMC_FLASH_UNCACHED_BASE + 0x18000U)
#define E_EEPROM_XMC4_SECTOR3_START_ADDR   (XMC_FLASH_UNCACHED_BASE + 0x1C000U)
#define E_EEPROM_XMC4_SECTOR4_START_ADDR   (XMC_FLASH_UNCACHED_BASE + 0x20000U)

/* Local definitions for internal usage*/
#define E_EEPROM_XMC4_EMPTY                   ((uint32_t)0x0U)
#define E_EEPROM_XMC4_ALL_SECTORS_FILLED      ((uint8_t)0x0FU)
#define E_EEPROM_XMC4_MIN_WORDS_PER_PAGE      ((uint32_t)64U)
#define E_EEPROM_XMC4_SECTOR_SIZE             ((uint32_t)0x00004000U)
#define E_EEPROM_XMC4_SECTOR_POSITION_MASK    ((uint32_t)0x0000C000U)
#define E_EEPROM_XMC4_SECTOR_POSITION         ((uint32_t)14U)
#define E_EEPROM_XMC4_WORKING_BUFFER_SIZE     ((uint32_t)E_EEPROM_XMC4_ACTUAL_FLASH_BLOCK_SIZE - (uint32_t)(8U))
#define E_EEPROM_XMC4_DATA_SIZE_FOR_CRC       ((uint32_t)E_EEPROM_XMC4_ACTUAL_FLASH_BLOCK_SIZE - (uint32_t)(4U))
#define E_EEPROM_XMC4_MAX_PAGES               ((uint32_t)E_EEPROM_XMC4_ACTUAL_FLASH_BLOCK_SIZE >> (uint32_t)(8U))
#define E_EEPROM_XMC4_MAX_WORDS               ((uint32_t)E_EEPROM_XMC4_ACTUAL_FLASH_BLOCK_SIZE >> (uint32_t)(2U))



/* ---------------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/** Data structure to hold the complete state data information of sector*/
typedef struct E_EEPROM_XMC4_SECTOR_INFO
{
  uint32_t next_free_start_addr;

  uint32_t flash_data_addr;

  uint32_t  current_sector;

  uint32_t  erase_state;

} E_EEPROM_XMC4_SECTOR_INFO_t;

/* Data structure to hold the User Data block information (BCC + CRC + DATA)*/
typedef struct E_EEPROM_XMC4_RAM_BUFFER
{
  uint32_t crc;

  uint32_t block_cycle_count;

  uint8_t  eeprom_data[E_EEPROM_XMC4_WORKING_BUFFER_SIZE];

} E_EEPROM_XMC4_RAM_BUFFER_t;



/* ---------------------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* FCE configuration data structure definition */
static const XMC_FCE_t e_eeprom_xmc4_fce =
{
 .kernel_ptr     = (XMC_FCE_Kernel_t*)(void*)E_EEPROM_XMC4_FCE_KERNEL_BASE,
 .fce_cfg_update = {{
                     .config_refin  = 1U,
                     .config_refout = 1U,
                     .config_xsel   = 1U
                   }},
 .seedvalue      = 0U
};



/* ---------------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* RAM data buffer structure definition */
static E_EEPROM_XMC4_RAM_BUFFER_t e_eeprom_xmc4_data_buffer;

/* Sector info data structure definition */
static E_EEPROM_XMC4_SECTOR_INFO_t  e_eeprom_xmc4_sector_info  =
{
  .next_free_start_addr = 0U,
  .flash_data_addr      = 0U,
  .current_sector       = 0xFFFFFFFFU,
  .erase_state          = 0U
};

// EEPROM memory class instance
E_EEPROM_XMC4_t RETAIN = { .initialized  = false };



/* ---------------------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* ---------------------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* ---------------------------------------------------------------------------*/
static E_EEPROM_XMC4_STATUS_t E_EEPROM_XMC4_lWriteToFlash(void);

static void E_EEPROM_XMC4_lCopyFlashToRam(void);

static void E_EEPROM_XMC4_lInitReadSectorInfo(uint32_t sector);

static E_EEPROM_XMC4_STATUS_t E_EEPROM_XMC4_lInitEraseStateMachine(void);

static uint32_t E_EEPROM_XMC4_lCalculateCRC(const uint32_t *data_start_addr);



/* ---------------------------------------------------------------------------*/
/* Public Functions ----------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
E_EEPROM_XMC4_STATUS_t E_EEPROM_XMC4_Init(E_EEPROM_XMC4_t *const handle)
{
  uint32_t sector_count;
  E_EEPROM_XMC4_STATUS_t status ;

  XMC_ASSERT("E_EEPROM_XMC4_Init:Invalid handle Pointer", (handle != NULL));

  status = E_EEPROM_XMC4_STATUS_OK;

  if (handle->initialized == (bool)false)
  {
    e_eeprom_xmc4_data_buffer.block_cycle_count = 0U;
    e_eeprom_xmc4_sector_info.flash_data_addr = E_EEPROM_XMC4_EMPTY;

    XMC_FLASH_SetMargin(XMC_FLASH_MARGIN_TIGHT0);
    XMC_FLASH_DisableDoubleBitErrorTrap();

    XMC_FCE_Enable();

    /* Initialize FCE module for Hardware calculations */
    (void)XMC_FCE_Init(&e_eeprom_xmc4_fce);

    /* Iterate all 4 sectors to find out which is the active sector having the latest data block*/
    for (sector_count = 0U; sector_count < E_EEPROM_XMC4_MAX_SECTORS ; sector_count++)
    {
      E_EEPROM_XMC4_lInitReadSectorInfo(sector_count);
    }

    XMC_FLASH_SetMargin(XMC_FLASH_MARGIN_DEFAULT);

    /* Implement the OVER ERASE CHECK code here and return the status*/

    /* If Read was successful*/
    if (status == E_EEPROM_XMC4_STATUS_OK)
    {
      /* Execute erase state machine to free up the unwanted sectors and keep
       * only the sector which has latest valid block. If no valid block found then all sectors are emptied.
       */
      status = E_EEPROM_XMC4_lInitEraseStateMachine();

      /* If erase operations were successful, continue block data updates to RAM buffer */
      if (status == E_EEPROM_XMC4_STATUS_OK)
      {

        /* If a valid latest block were not detected, we shall assume that all sectors may be empty.
         * Then make Sector-0 as current sector and next free address as Sector0 start address
         */
        if (e_eeprom_xmc4_sector_info.flash_data_addr == E_EEPROM_XMC4_EMPTY)
        {
          e_eeprom_xmc4_sector_info.current_sector = E_EEPROM_XMC4_SECTOR_0;
          e_eeprom_xmc4_sector_info.next_free_start_addr =  E_EEPROM_XMC4_SECTOR0_START_ADDR;
        }
        else
        {
          /* If a valid latest block was detected, copy the valid block from flash to RAM. */
          E_EEPROM_XMC4_lCopyFlashToRam();

          if ((e_eeprom_xmc4_sector_info.next_free_start_addr - e_eeprom_xmc4_sector_info.flash_data_addr) !=
              E_EEPROM_XMC4_ACTUAL_FLASH_BLOCK_SIZE)
          {
            status = E_EEPROM_XMC4_STATUS_ERROR_OLD_DATA;
          }

          if (e_eeprom_xmc4_sector_info.next_free_start_addr >= E_EEPROM_XMC4_SECTOR4_START_ADDR)
          {
            e_eeprom_xmc4_sector_info.next_free_start_addr =  E_EEPROM_XMC4_SECTOR0_START_ADDR;
          }

        }
      }
    }

    XMC_FLASH_EnableDoubleBitErrorTrap();

    handle->initialized = (bool)true;
  }

  return (status);
}



/* Update a single byte to RAM buffer*/
bool E_EEPROM_XMC4_WriteByte(const uint16_t offset_address, const uint8_t value)
{
  uint8_t *address_ptr;
  bool status;

  XMC_ASSERT("E_EEPROM_XMC4_WriteByte: Wrong offset address", (offset_address < E_EEPROM_XMC4_DATA_BLOCK_SIZE));
  address_ptr = (uint8_t*)(void*)(&e_eeprom_xmc4_data_buffer.eeprom_data) + (uint32_t)offset_address;
  status = (*address_ptr != value);

  *address_ptr = value;

  return status;
}



/* Update a set of bytes to RAM buffer*/
bool E_EEPROM_XMC4_WriteArray(const uint16_t offset_address, const uint8_t *const data, const uint16_t length)
{
  uint16_t i;
  uint8_t  *address_ptr;
  bool status;

  XMC_ASSERT("E_EEPROM_XMC4_WriteArray: Wrong offset address", (offset_address < E_EEPROM_XMC4_DATA_BLOCK_SIZE));
  XMC_ASSERT("E_EEPROM_XMC4_WriteArray: Wrong length", ((offset_address + length) <= E_EEPROM_XMC4_DATA_BLOCK_SIZE));

  address_ptr = (uint8_t*)(void*)(&e_eeprom_xmc4_data_buffer.eeprom_data) + (uint32_t)offset_address;
  status = (memcmp(address_ptr, data, length) != 0);

  for (i = 0U; i < length; i++)
  {
      *(address_ptr + i) = *(data + i);
  }

  return status;
}



/* Read one byte from RAM Buffer */
void E_EEPROM_XMC4_ReadByte(const uint16_t offset_address, uint8_t *const value)
{
  uint8_t *address_ptr;
  XMC_ASSERT("E_EEPROM_XMC4_ReadByte: Wrong offset address", (offset_address < E_EEPROM_XMC4_DATA_BLOCK_SIZE));
  address_ptr = (uint8_t*)(void*)(&e_eeprom_xmc4_data_buffer.eeprom_data) + (uint32_t)offset_address;

  *value = *address_ptr;
}



/* Read a set of bytes from RAM Buffer */
void E_EEPROM_XMC4_ReadArray(const uint16_t offset_address, uint8_t *const data, const uint16_t length)
{
  uint16_t i;
  uint8_t  *address_ptr;
  XMC_ASSERT("E_EEPROM_XMC4_ReadArray: Wrong offset address", (offset_address < E_EEPROM_XMC4_DATA_BLOCK_SIZE));
  XMC_ASSERT("E_EEPROM_XMC4_ReadArray: Wrong length", ((offset_address + length) <= E_EEPROM_XMC4_DATA_BLOCK_SIZE));
  address_ptr = (uint8_t*)(void*)(&e_eeprom_xmc4_data_buffer.eeprom_data) + (uint32_t)offset_address;

  for (i=0U; i<length; i++)
  {
    *(data + i) = *(address_ptr + i);
  }
}



/* Copy data blocks from RAM to FLASH */
E_EEPROM_XMC4_STATUS_t E_EEPROM_XMC4_UpdateFlashContents(void)
{
  E_EEPROM_XMC4_STATUS_t status;
  uint32_t sector_start_addr;

  status = E_EEPROM_XMC4_STATUS_OK;

  /* Calculate the starting address of the active sector from where the first write started for the current cycle*/
  sector_start_addr = E_EEPROM_XMC4_SECTOR0_START_ADDR +
                     (E_EEPROM_XMC4_SECTOR_SIZE * e_eeprom_xmc4_sector_info.current_sector);

  /* If the next free address crosses current active sector starting address, then all the sectors are fully written*/
  if ((e_eeprom_xmc4_sector_info.next_free_start_addr == sector_start_addr) &&
     (e_eeprom_xmc4_data_buffer.block_cycle_count != 0U))
  {
    /* Update the current sector to the latest sector on which the last write was executed. */
    e_eeprom_xmc4_sector_info.current_sector =  ((e_eeprom_xmc4_sector_info.flash_data_addr &
                                                E_EEPROM_XMC4_SECTOR_POSITION_MASK) >>
                                                E_EEPROM_XMC4_SECTOR_POSITION);

    /* Mark all the sectors as filled with data */
    e_eeprom_xmc4_sector_info.erase_state = E_EEPROM_XMC4_ALL_SECTORS_FILLED ;

    /* Execute erase state machine to free up the unwanted sectors and keep only the sector which has latest block*/
    status = E_EEPROM_XMC4_lInitEraseStateMachine();
  }

  if (status ==  E_EEPROM_XMC4_STATUS_OK)
  {
    e_eeprom_xmc4_data_buffer.block_cycle_count++;

    status = E_EEPROM_XMC4_lWriteToFlash();

    /* If the flash write succeeds, update the latest flash data location in RAM for reference */
    if (status == E_EEPROM_XMC4_STATUS_OK)
    {
      e_eeprom_xmc4_sector_info.flash_data_addr = e_eeprom_xmc4_sector_info.next_free_start_addr;
    }

    /* Update the next free address to write the new data block*/
    e_eeprom_xmc4_sector_info.next_free_start_addr += E_EEPROM_XMC4_ACTUAL_FLASH_BLOCK_SIZE;

    /* If the next free address crosses 3rd sector end address relocate the address to 0th sector starting address*/
    if (e_eeprom_xmc4_sector_info.next_free_start_addr >= E_EEPROM_XMC4_SECTOR4_START_ADDR)
    {
      e_eeprom_xmc4_sector_info.next_free_start_addr = E_EEPROM_XMC4_SECTOR0_START_ADDR;
    }
  }

  return (status);
}


/* Check the availability data in the flash emulated EEPROM area */
bool E_EEPROM_XMC4_IsFlashEmpty(void)
{
  bool status = false;

  /* If data available flash_data_addr will have a valid address*/
  if (e_eeprom_xmc4_sector_info.flash_data_addr == 0U)
  {
    status = true;
  }
  return (status);
}



/* ---------------------------------------------------------------------------*/
/* Private Functions ---------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/

/* Local function to program data blocks from RAM into FLASH */
static E_EEPROM_XMC4_STATUS_t E_EEPROM_XMC4_lWriteToFlash(void)
{
  uint32_t *flash_addr_ptr;
  uint32_t *ram_addr_ptr;
  uint32_t  page_index;
  E_EEPROM_XMC4_STATUS_t status;

  status = E_EEPROM_XMC4_STATUS_OK;
  flash_addr_ptr = (uint32_t*)e_eeprom_xmc4_sector_info.next_free_start_addr;
  ram_addr_ptr   = (uint32_t*)(void*)&e_eeprom_xmc4_data_buffer;

  e_eeprom_xmc4_data_buffer.crc = E_EEPROM_XMC4_lCalculateCRC((uint32_t*)(void*)
                                                             (&(e_eeprom_xmc4_data_buffer.block_cycle_count)));

  for (page_index = 0U ; page_index < E_EEPROM_XMC4_MAX_PAGES; page_index++)
  {
    XMC_FLASH_ClearStatus();

    XMC_FLASH_ProgramPage(flash_addr_ptr,ram_addr_ptr);

    if ((XMC_FLASH_GetStatus() & (uint32_t)(XMC_FLASH_STATUS_VERIFY_ERROR | XMC_FLASH_STATUS_OPERATION_ERROR)) != 0)
    {
      status = E_EEPROM_XMC4_STATUS_WRITE_ERROR;
      break;
    }
    ram_addr_ptr   += E_EEPROM_XMC4_MIN_WORDS_PER_PAGE ;
    flash_addr_ptr += E_EEPROM_XMC4_MIN_WORDS_PER_PAGE ;
  }

  return (status);
}



static void E_EEPROM_XMC4_lInitReadSectorInfo(const uint32_t sector)
{
  uint32_t block_read_addr;
  uint32_t sector_start_addr;
  uint32_t free_block_addr;
  uint32_t *data_ptr;
  uint32_t block_cycle_count;
  uint32_t written_crc;
  uint32_t calculated_crc;

  /* Initialize starting address and last block address of the sector. */
  sector_start_addr = E_EEPROM_XMC4_SECTOR0_START_ADDR + (E_EEPROM_XMC4_SECTOR_SIZE * (uint32_t)sector);
  block_read_addr = (sector_start_addr + E_EEPROM_XMC4_SECTOR_SIZE) - E_EEPROM_XMC4_ACTUAL_FLASH_BLOCK_SIZE;
  free_block_addr = E_EEPROM_XMC4_EMPTY;

  do
  {
    /* Read first 32 bit data from the block which indicates the block cycle counter. */
    data_ptr = (uint32_t*)block_read_addr;
    block_cycle_count = *(data_ptr + E_EEPROM_XMC4_BCC_OFFSET);

    /* Check if block cycle count is a non zero value*/
    if (block_cycle_count != E_EEPROM_XMC4_EMPTY)
    {
      /* Mark sector as non-empty sector*/
      e_eeprom_xmc4_sector_info.erase_state |= ((uint32_t)1U << sector);

      /* If this is the first non empty block identified, then store the address as next free address */
      if (free_block_addr == E_EEPROM_XMC4_EMPTY)
      {
        free_block_addr = block_read_addr + E_EEPROM_XMC4_ACTUAL_FLASH_BLOCK_SIZE;
      }

      /* Read the second 32bit data which indicates the CRC */
      written_crc = *data_ptr;
      /* Calculate the CRC for the written data in flash (3rd word to the last word)*/
      calculated_crc = E_EEPROM_XMC4_lCalculateCRC(data_ptr + E_EEPROM_XMC4_BCC_OFFSET);

      if (calculated_crc == written_crc)
      {
        /* If both CRC matches and the current block cycle counter is greater than the previous recorded value,
         * Update the Data structure with the current block as the "latest" one and the current sector as "active".
         * Exit from the function.
         */
        if (block_cycle_count > e_eeprom_xmc4_data_buffer.block_cycle_count)
        {
          e_eeprom_xmc4_data_buffer.block_cycle_count = block_cycle_count;
          e_eeprom_xmc4_sector_info.current_sector = sector;
          e_eeprom_xmc4_sector_info.flash_data_addr = block_read_addr;
          e_eeprom_xmc4_sector_info.next_free_start_addr = free_block_addr;
          break;
        }
      }
    }
    /* Move the block read address to one block size up starting from the bottom of sector */
    block_read_addr -= E_EEPROM_XMC4_ACTUAL_FLASH_BLOCK_SIZE;

  /* Iterate the read process until the block read address crosses sector start address or a
   * latest valid block is identified.
   */
  } while ( block_read_addr >= sector_start_addr );

}



static E_EEPROM_XMC4_STATUS_t E_EEPROM_XMC4_lInitEraseStateMachine(void)
{
  uint32_t sector_count;
  uint32_t sector_start_addr;
  E_EEPROM_XMC4_STATUS_t status ;

  status = E_EEPROM_XMC4_STATUS_OK;
  sector_count = 0U;

  do
  {
    /* If the non empty sector is the current active sector, then do not erase it*/
    if (e_eeprom_xmc4_sector_info.current_sector != sector_count)
    {
      /* Check if the sector was previously identified as non-empty. i.e It is having old data or corrupted data
       * If so erase the sector and mark it as erase attempted.
       */
      if ((e_eeprom_xmc4_sector_info.erase_state >> sector_count) & ((uint32_t)1U))
      {
        sector_start_addr = E_EEPROM_XMC4_SECTOR0_START_ADDR + (E_EEPROM_XMC4_SECTOR_SIZE * (uint32_t)sector_count);

        XMC_FLASH_ClearStatus();
        XMC_FLASH_EraseSector((uint32_t*)sector_start_addr);

        if (XMC_FLASH_GetStatus() != (uint32_t)XMC_FLASH_STATUS_ERASE_STATE)
        {
          status = E_EEPROM_XMC4_STATUS_ERASE_ERROR;
          break;
        }
        e_eeprom_xmc4_sector_info.erase_state &= ~(((uint32_t)1U << sector_count));
      }
    }
    sector_count++;
    /* Iterate the erase loop until all 4 sectors are checked. Break and return failure on any sector erase errors.*/
  } while ( sector_count < E_EEPROM_XMC4_MAX_SECTORS );

  return (status);
}

/* Local function to CRC */
static uint32_t E_EEPROM_XMC4_lCalculateCRC(const uint32_t *data_start_addr)
{
  uint32_t result;

  /* Reset the CRC result register before new CRC calculation */
  XMC_FCE_InitializeSeedValue(&e_eeprom_xmc4_fce, 0U);

  (void)XMC_FCE_CalculateCRC32(&e_eeprom_xmc4_fce, data_start_addr, E_EEPROM_XMC4_DATA_SIZE_FOR_CRC, &result);

  return (result);
}



/* Local function to copy data blocks from FLASH to RAM */
static void E_EEPROM_XMC4_lCopyFlashToRam(void)
{
  uint32_t *flash_addr_ptr;
  uint32_t *ram_addr_ptr;
  uint32_t byte_index;

  flash_addr_ptr = (uint32_t*)e_eeprom_xmc4_sector_info.flash_data_addr;
  ram_addr_ptr = (uint32_t*)(void*)&e_eeprom_xmc4_data_buffer;

  for(byte_index = 0U ; byte_index < E_EEPROM_XMC4_MAX_WORDS; byte_index++)
  {
    *(ram_addr_ptr + byte_index) = *(flash_addr_ptr + byte_index);
  }
}
