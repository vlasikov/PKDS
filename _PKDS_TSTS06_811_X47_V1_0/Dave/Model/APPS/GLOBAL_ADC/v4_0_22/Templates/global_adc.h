/**
 * @file global_adc.h
 * @date 2021-01-08
 *
 * NOTE:
 * This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
 *
 * @cond
 ***********************************************************************************************************************
 * GLOBAL_ADC v4.0.22 - Initializes VADC GLOBAL and GROUP resources.
 *
 * Copyright (c) 2015-2020, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2015-02-16:
 *     - Initial version for DAVEv4.<BR>
 *
 * 2015-04-27:
 *     - Configuration structure modified.<BR>
 *     - GLOBAL_ADC_group_t changed to GLOBAL_ADC_GROUP_t.<BR>
 *
 * 2015-06-20:
 *     - Updated the copyright section.<BR>
 *
 * 2015-09-01:
 *     - Added support for XMC14 and XMC48/47.<BR>
 *
 * 2015-10-01:
 *     - Analog clock default value changed to 26Mhz in XMC42.<BR>
 *
 * 2015-10-08:
 *     - Added support for XMC4700/XMC4800 devices.<BR>
 *
 * 2015-12-03:
 *     - Added support for XMC4300 devices.<BR>
 *     - Optimized the manifest.<BR>
 *
 * 2016-03-18:
 *     -Modified the minimum configurable value for Desired analog clock in XMC1x to 1MHz.<BR>
 *
 * 2016-07-08:
 *     - Fixed incorrect case for an included header.<br>
 *
 * 2016-08-18:
 *     - Added support for low frequency operations by configuring DIVS.<BR>
 *
 * 2021-01-08:
 *     - Modified check for minimum XMCLib version
 *
 * @endcond
 *
 */

#ifndef GLOBAL_ADC_H
#define GLOBAL_ADC_H

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "xmc_vadc.h"
#include "global_adc_conf.h"
#include "DAVE_Common.h"

 /**********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
#define GLOBAL_ADC_XMC_LIB_MAJOR_VERSION 2
#define GLOBAL_ADC_XMC_LIB_MINOR_VERSION 1
#define GLOBAL_ADC_XMC_LIB_PATCH_VERSION 14

#if !((XMC_LIB_MAJOR_VERSION > GLOBAL_ADC_XMC_LIB_MAJOR_VERSION) ||\
      ((XMC_LIB_MAJOR_VERSION == GLOBAL_ADC_XMC_LIB_MAJOR_VERSION) && (XMC_LIB_MINOR_VERSION > GLOBAL_ADC_XMC_LIB_MINOR_VERSION)) ||\
      ((XMC_LIB_MAJOR_VERSION == GLOBAL_ADC_XMC_LIB_MAJOR_VERSION) && (XMC_LIB_MINOR_VERSION == GLOBAL_ADC_XMC_LIB_MINOR_VERSION) && (XMC_LIB_PATCH_VERSION >= GLOBAL_ADC_XMC_LIB_PATCH_VERSION)))
#error "GLOBAL_ADC requires XMC Peripheral Library v2.1.14 or higher"
#endif

 /**********************************************************************************************************************
 * ENUMS
 **********************************************************************************************************************/
/**
 * @ingroup GLOBAL_ADC_enumerations
 * @{
 */

/**
 * @brief GLOBAL_ADC state information
 */
typedef enum GLOBAL_ADC_STATUS
{
  GLOBAL_ADC_SUCCESS = 0, /**< APP is in INITIALIZED state after execution of the Init function*/
  GLOBAL_ADC_FAILURE, 		 /**< Initialization failed returns this as status */
  GLOBAL_ADC_UNINITIALIZED	 /**< This is the default state after power on reset.*/
} GLOBAL_ADC_STATUS_t;

/**
 * @}
 */
/**********************************************************************************************************************
* DATA STRUCTURES
**********************************************************************************************************************/
/**
 * @ingroup GLOBAL_ADC_datastructures
 * @{
 */
/**
 * @brief Structure to hold the configuration information of a group
 */
#if XMC_VADC_GROUP_AVAILABLE == 1U
typedef struct GLOBAL_ADC_GROUP
{
  XMC_VADC_GROUP_t *const group_handle; 						/**<This holds the VADC group Registers. */

  const XMC_VADC_GROUP_CONFIG_t* const group_config_handle; /**<This is the pointer to the Handle of the Group APP. */

  const bool post_calibration;                              /**< This enables the post calibration for a specific group*/

  GLOBAL_ADC_STATUS_t state; 									/**<This enumerates the state of the APP. */
} GLOBAL_ADC_GROUP_t;
#endif
/**
 *  @brief  Configuration Data structure of GLOBAL_ADC APP
 */
typedef struct GLOBAL_ADC
{
#if XMC_VADC_GROUP_AVAILABLE == 1U
  GLOBAL_ADC_GROUP_t* const group_ptrs_array[XMC_VADC_MAXIMUM_NUM_GROUPS]; /**<This is an array of pointers to the ADC Groups*/
#endif
  const XMC_VADC_GLOBAL_CONFIG_t* const global_config_handle; 	   /**<This is the pointer to the Global LLD Handle.*/

  XMC_VADC_GLOBAL_t* const module_ptr; /**<This is the register structure pointer to the VADC kernel. */

#if(XMC_VADC_SHS_AVAILABLE == 1U)
  XMC_VADC_GLOBAL_SHS_t* const global_shs_ptr; /**< This is the sample and hold structure pointer*/
  XMC_VADC_GLOBAL_SHS_CONFIG_t* const global_shscfg; /**< This is the sample and hold structure pointer*/
#endif
  GLOBAL_ADC_STATUS_t init_state; 		 /**< This hold the State of the GLOBAL_ADC APP*/

  const bool enable_startup_calibration;       /**< Enable startup calibration for all the converters*/
} GLOBAL_ADC_t;

/**
 * @}
 */

/**
 * @ingroup GLOBAL_ADC_apidoc
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif
/***********************************************************************************************************************
 * API Prototypes
 **********************************************************************************************************************/

/**
 * @brief Get GLOBAL_ADC APP version
 * @return DAVE_APP_VERSION_t APP version information (major, minor and patch number)
 *
 * \par<b>Description: </b><br>
 * The function can be used to check application software compatibility with a
 * specific version of the APP.
 *
 * Example Usage:
 *
 * @code
 * #include "DAVE.h"
 *
 * int main(void) {
 *   DAVE_STATUS_t init_status;
 *   DAVE_APP_VERSION_t version;
 *
 *   // Initialize GLOBAL_ADC APP:
 *   // GLOBAL_ADC_Init() is called from within DAVE_Init().
 *   init_status = DAVE_Init();
 *
 *   version = GLOBAL_ADC_GetAppVersion();
 *   if (version.major != 1U) {
 *     // Probably, not the right version.
 *   }
 *
 *   // More code here
 *   while(1) {
 *
 *   }
 *   return (0);
 * }
 * @endcode
 */
DAVE_APP_VERSION_t GLOBAL_ADC_GetAppVersion(void);

/**
 * @brief Initializes the ADC global as per user configured values.
 * @return void
 * <BR>
 *
  \par<b>Description:</b><br>
 * Initializes the VADC peripheral.
 * Invokes various VADC LLD drivers to initialize the VADC peripheral. This would invoke
 * The XMC_VADC_GLOBAL_Init(), XMC_VADC_GROUP_Init(). It also invokes XMC_VADC_GROUP_SetPowerMode() to power
 * on available groups.
 *
 * Example Usage:
 * @code
 *  #include "DAVE.h"
 *
 *  int main (void)
 *  {
 *    DAVE_Init(); //GLOBAL_ADC_Init is called within DAVE_Init
 *    while(1);
 *    return 0;
 *  }
 * @endcode 
 */
GLOBAL_ADC_STATUS_t GLOBAL_ADC_Init(GLOBAL_ADC_t *const handle_ptr);

#include "global_adc_extern.h"

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
  
#endif /* GLOBAL_ADC_H_ */
