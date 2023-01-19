/**
 * @file nvic.h
  * @brief NVIC node intialization
 * -# Control loop event (CCU8 one match) - Priority 2
 * -# Pattern shadow transfer event (POSIF shadow transfer of multi-channel pattern) - Priority 1
 * -# Hall event (POSIF wrong hall event and correct hall event) - Priority 1
 * -# Protection event (VADC channel event for current and voltage) - Priority 0
 * -# Ctrap event (CCU8 input event 2) - Priority 0
 * -# State machine (Systick event) - Priority 3
 * @date 2016-08-31

 ***********************************************************************************************************************
 * BLDC_SCALAR_CONTROL v1.0.2 - BLDC motor control using block commutation
 * Copyright (c) 2015-2016, Infineon Technologies AG
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
 * 2016-08-31:
 *     - Initial version
 *
 * @endcond
 *
 */
/**
 * @addtogroup BLDC_SCALAR BLDC Motor Control
 * @{
 */

/**
 * @addtogroup MCUInit
 * @brief  MCU peripheral initialization <br>
 * @{
 */
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#ifndef MCUINIT_NVIC_H_
#define MCUINIT_NVIC_H_

#include "../Configuration/bldc_scalar_derived_parameter.h"
#include "../Configuration/bldc_scalar_mcuhw_config.h"

#ifdef __cplusplus
   extern "C" {
#endif
/***********************************************************************************************************************
 * API Prototypes
 **********************************************************************************************************************/
/**
 * @return None <br>
 *
 * \par<b>Description:</b><br>
 * Sets the interrupt node for
 * BLDC_SCALAR_CTRAP_NODE - If trap is enabled,
 * BLDC_SCALAR_PATTERN_UPDATE_NODE - MCM Pattern update,
 * BLDC_SCALAR_HALL_EVENT_NODE - Hall events,
 * BLDC_SCALAR_VADC_PROTECTION_NODE - Over current,Under/Over voltage protection if enabled
 */
void BLDC_SCALAR_NVIC_NodeInit(IRQn_Type node_id, uint32_t priority, uint32_t sub_priority);

/**
 * @}
 */

/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* MCUINIT_NVIC_H_ */
