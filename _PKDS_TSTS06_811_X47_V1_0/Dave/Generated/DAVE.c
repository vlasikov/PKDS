
/**
 * @cond
 ***********************************************************************************************************************
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
 * 2014-06-16:
 *     - Initial version<br>
 * 2015-08-28:
 *     - Added CLOCK_XMC1_Init conditionally
 * 2018-08-08:
 *     - Add creation of projectData.bak file
 * 2019-01-30:
 *     - Fix creation of projectData.bak file
 * 2019-04-29:
 *     - Make DAVE_Init() weak, the user can reimplement the function
 *
 * @endcond
 *
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "DAVE.h"

/***********************************************************************************************************************
 * API IMPLEMENTATION
 **********************************************************************************************************************/

/*******************************************************************************
 * @brief This function initializes the APPs Init Functions.
 *
 * @param[in]  None
 *
 * @return  DAVE_STATUS_t <BR>
 ******************************************************************************/
__WEAK DAVE_STATUS_t DAVE_Init(void)
{
  DAVE_STATUS_t init_status;
  
  init_status = DAVE_STATUS_SUCCESS;
     /** @Initialization of APPs Init Functions */
     init_status = (DAVE_STATUS_t)CLOCK_XMC4_Init(&CLOCK_XMC4_0);

  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance SERVICE_BUT */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&SERVICE_BUT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance STATUS_LED_G */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&STATUS_LED_G); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance STATUS_LED_Y */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&STATUS_LED_Y); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance STATUS_LED_R */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&STATUS_LED_R); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of SYSTIMER APP instance SYSTIMER_0 */
	 init_status = (DAVE_STATUS_t)SYSTIMER_Init(&SYSTIMER_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of CAN_NODE APP instance CAN_INT */
	 init_status = (DAVE_STATUS_t)CAN_NODE_Init(&CAN_INT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of INTERRUPT APP instance CAN_INT_RESET_INT */
	 init_status = (DAVE_STATUS_t)INTERRUPT_Init(&CAN_INT_RESET_INT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of ADC_MEASUREMENT APP instance ADC_MEASUREMENT_0 */
	 init_status = (DAVE_STATUS_t)ADC_MEASUREMENT_Init(&ADC_MEASUREMENT_0); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of PWM_CCU4 APP instance BUZZ_PWM */
	 init_status = (DAVE_STATUS_t)PWM_CCU4_Init(&BUZZ_PWM); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of PWM_CCU4 APP instance CLUTCH_PWM */
	 init_status = (DAVE_STATUS_t)PWM_CCU4_Init(&CLUTCH_PWM); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of INTERRUPT APP instance BUZZ_INT_CMP */
	 init_status = (DAVE_STATUS_t)INTERRUPT_Init(&BUZZ_INT_CMP); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of INTERRUPT APP instance BUZZ_INT_OVF */
	 init_status = (DAVE_STATUS_t)INTERRUPT_Init(&BUZZ_INT_OVF); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of INTERRUPT APP instance CLUTCH_INT_CMP */
	 init_status = (DAVE_STATUS_t)INTERRUPT_Init(&CLUTCH_INT_CMP); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of INTERRUPT APP instance CLUTCH_INT_OVF */
	 init_status = (DAVE_STATUS_t)INTERRUPT_Init(&CLUTCH_INT_OVF); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of INTERRUPT APP instance CAN_EXT_DSC1_INT */
	 init_status = (DAVE_STATUS_t)INTERRUPT_Init(&CAN_EXT_DSC1_INT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of INTERRUPT APP instance CAN_EXT_DSC3_INT */
	 init_status = (DAVE_STATUS_t)INTERRUPT_Init(&CAN_EXT_DSC3_INT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of INTERRUPT APP instance CAN_EXT_DSC2_INT */
	 init_status = (DAVE_STATUS_t)INTERRUPT_Init(&CAN_EXT_DSC2_INT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of CAN_NODE APP instance CAN_EXT */
	 init_status = (DAVE_STATUS_t)CAN_NODE_Init(&CAN_EXT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of INTERRUPT APP instance CAN_NODE_ALLERT */
	 init_status = (DAVE_STATUS_t)INTERRUPT_Init(&CAN_NODE_ALLERT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of BUS_IO APP instance DI_NPN */
	 init_status = (DAVE_STATUS_t)BUS_IO_Init(&DI_NPN); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of BUS_IO APP instance DI_PNP */
	 init_status = (DAVE_STATUS_t)BUS_IO_Init(&DI_PNP); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of BUS_IO APP instance GROUP_IN */
	 init_status = (DAVE_STATUS_t)BUS_IO_Init(&GROUP_IN); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of BUS_IO APP instance GROUP_OUT */
	 init_status = (DAVE_STATUS_t)BUS_IO_Init(&GROUP_OUT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DI_NPN_EN */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DI_NPN_EN); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance DI_PNP_EN */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&DI_PNP_EN); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance GROUP_IN_EN */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&GROUP_IN_EN); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance HS_SW_1 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&HS_SW_1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance HS_SW_2 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&HS_SW_2); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LS_SW_4 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LS_SW_4); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LS_SW_3 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LS_SW_3); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LS_SW_2 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LS_SW_2); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LS_SW_1 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LS_SW_1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LED_SW_NRES */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LED_SW_NRES); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LED_SW_8 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LED_SW_8); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LED_SW_7 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LED_SW_7); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LED_SW_6 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LED_SW_6); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LED_SW_5 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LED_SW_5); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LED_SW_4 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LED_SW_4); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LED_SW_3 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LED_SW_3); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LED_SW_2 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LED_SW_2); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LED_SW_1 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LED_SW_1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LED_POWER_EN2 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LED_POWER_EN2); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LED_POWER_EN1 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LED_POWER_EN1); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance HS_SW_8 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&HS_SW_8); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance HS_SW_7 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&HS_SW_7); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance HS_SW_6 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&HS_SW_6); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance HS_SW_5 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&HS_SW_5); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance HS_SW_4 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&HS_SW_4); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance HS_SW_3 */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&HS_SW_3); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance LS_SW_NRES */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&LS_SW_NRES); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance MOTOR_FAULT */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&MOTOR_FAULT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance POWER_SWITCH */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&POWER_SWITCH); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of DIGITAL_IO APP instance TRANS_OUT */
	 init_status = (DAVE_STATUS_t)DIGITAL_IO_Init(&TRANS_OUT); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of INTERRUPT APP instance CAN_EXT_TD */
	 init_status = (DAVE_STATUS_t)INTERRUPT_Init(&CAN_EXT_TD); 
   } 
  if (init_status == DAVE_STATUS_SUCCESS)
  {
	 /**  Initialization of INTERRUPT APP instance CAN_EXT_CCVS */
	 init_status = (DAVE_STATUS_t)INTERRUPT_Init(&CAN_EXT_CCVS); 
   }  
  return init_status;
} /**  End of function DAVE_Init */

