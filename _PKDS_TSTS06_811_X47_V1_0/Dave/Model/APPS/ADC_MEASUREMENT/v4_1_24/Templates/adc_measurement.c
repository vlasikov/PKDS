/**
 * @file adc_measurement.c
 * @date 2016-08-18
 *
 * NOTE:
 * This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
 *
 * @cond
 ***********************************************************************************************************************
 * ADC_MEASUREMENT v4.1.24 - Incorporates analog to digital conversion for the required measurements.
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
 * 2015-02-19:
 *     - Added GetResult APIs for XMC1100 devices.
 *
 * 2015-05-14:
 *     - Optimized the Manifest.<BR>
 *     - Modified the structure ADC_MEASUREMENT_channel_t to ADC_MEASUREMENT_CHANNEL_t.<BR>
 *
 * 2015-06-26:
 *     - Added input class resource consumption.<BR>
 *
 * 2015-07-09:
 *     - Documentation updated.<BR>
 *
 * 2015-07-31:
 *     - Updated the APP to support new devices.<BR>
 *
 * 2015-10-01:
 *     - Updated the APP to support the interrupt control in XMC14.<BR>
 *
 * 2015-10-08:
 *     - Added support for XMC4700/XMC4800 devices.<BR>
 *
 * 2015-10-20:
 *     - Documentation updated.<BR>
 *
 * 2015-12-03:
 *     - Added support for XMC4300 device.<BR>
 *
 * 2016-02-09:
 *     - Updated the APP for the minimum required ANALOG_IO APP version.<BR>
 *
 * 2016-03-18:
 *     - Maximum number of channels for XMC41/42 increased to 9.<BR>
 *     - Added Post calibration time for XMC1x series in Total conversion Time.<BR>
 *     - Fixed the ADC_MEASUREMENT_Init() for ANALOG_IO initialization.<BR>
 *     - For XMC1100 series only: Deprecated the API ADC_MEASUREMENT_GetResult() and
 *       ADC_MEASUREMENT_GetDetailedResult().<BR>
 *     - For XMC1100 series only: Added new API ADC_MEASUREMENT_GetGlobalResult() and
 *       ADC_MEASUREMENT_GetGlobalDetailedResult().<BR>
 *
 * 2016-08-18:
 *     - Minimum sample time at low frequencies changed to incorporate Errata ADC_AI.H006 and ADC_AI.H007.
 *
 * @endcond
 *
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "adc_measurement.h"

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * LOCAL DATA
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * API IMPLEMENTATION
 **********************************************************************************************************************/

/*This function returns the version of the ADC_MEASUREMENT App*/
DAVE_APP_VERSION_t ADC_MEASUREMENT_GetAppVersion(void)
{
  DAVE_APP_VERSION_t version;

  version.major = (uint8_t) ADC_MEASUREMENT_MAJOR_VERSION;
  version.minor = (uint8_t) ADC_MEASUREMENT_MINOR_VERSION;
  version.patch = (uint8_t) ADC_MEASUREMENT_PATCH_VERSION;

  return version;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Initialization routine to call ADC LLD API's */
ADC_MEASUREMENT_STATUS_t ADC_MEASUREMENT_Init(ADC_MEASUREMENT_t *const handle_ptr)
{
  const ADC_MEASUREMENT_CHANNEL_t *indexed;
  uint8_t j;
  ADC_MEASUREMENT_STATUS_t status;

  XMC_ASSERT("ADC_MEASUREMENT_Init:Invalid handle_ptr", (handle_ptr != NULL));

  if (ADC_MEASUREMENT_STATUS_UNINITIALIZED == handle_ptr->init_state)
  {
    /* Call the function to initialise Clock and ADC global functional units*/
    status = (ADC_MEASUREMENT_STATUS_t) GLOBAL_ADC_Init(handle_ptr->global_handle);
  
    /*Initialize the Global Conversion class 0*/
    XMC_VADC_GLOBAL_InputClassInit(handle_ptr->global_handle->module_ptr,*handle_ptr->iclass_config_handle,
                                      XMC_VADC_GROUP_CONV_STD,ADC_MEASUREMENT_ICLASS_NUM);
#if (UC_SERIES == XMC11)
    /*Initialize the Global Conversion class 1*/
    XMC_VADC_GLOBAL_InputClassInit(handle_ptr->global_handle->module_ptr,*handle_ptr->iclass_config_handle,
                                      XMC_VADC_GROUP_CONV_STD,ADC_MEASUREMENT_ICLASS_NUM_XMC11);
#endif
  
    /* Initialize the Background Scan hardware */
    XMC_VADC_GLOBAL_BackgroundInit(handle_ptr->global_handle->module_ptr, handle_ptr->backgnd_config_handle);
  
#if (XMC_VADC_GROUP_AVAILABLE == 0U)
    /* Initialize the global result register */
    XMC_VADC_GLOBAL_ResultInit(handle_ptr->global_handle->module_ptr,handle_ptr->array->res_handle);
#endif

    for (j = (uint8_t)0; j < (uint8_t)ADC_MEASUREMENT_MAXCHANNELS; j++)
    {
      indexed = handle_ptr->array->channel_array[j];
#if (XMC_VADC_GROUP_AVAILABLE == 1U)
      /* Initialize for configured channels*/
      XMC_VADC_GROUP_ChannelInit(indexed->group_handle,(uint32_t)indexed->ch_num, indexed->ch_handle);
  
      /* Initialize for configured result registers */
      XMC_VADC_GROUP_ResultInit(indexed->group_handle, (uint32_t)indexed->ch_handle->result_reg_number,
                                indexed->res_handle);
#endif
      /* Add all channels into the Background Request Source Channel Select Register */
      XMC_VADC_GLOBAL_BackgroundAddChannelToSequence(handle_ptr->global_handle->module_ptr,
                                                     (uint32_t)indexed->group_index, (uint32_t)indexed->ch_num);

#ifdef ADC_MEASUREMENT_ANALOG_IO_USED
      /* ANALOG_IO initialization for the channel*/
      if(indexed->analog_io_config != NULL)
      {
        status |= (ADC_MEASUREMENT_STATUS_t) ANALOG_IO_Init(indexed->analog_io_config);
      }
#endif
    }
#if(UC_SERIES != XMC11)
    if ((handle_ptr->backgnd_config_handle->req_src_interrupt) && (handle_ptr->req_src_intr_handle != NULL ))
    {
#if (UC_FAMILY == XMC1)
      NVIC_SetPriority((IRQn_Type)handle_ptr->req_src_intr_handle->node_id,
                        handle_ptr->req_src_intr_handle->priority);
#else
      NVIC_SetPriority((IRQn_Type)handle_ptr->req_src_intr_handle->node_id,
                        NVIC_EncodePriority(NVIC_GetPriorityGrouping(),
                        handle_ptr->req_src_intr_handle->priority, handle_ptr->req_src_intr_handle->sub_priority));
#endif
      /* Connect background Request Source Event to NVIC node */
      XMC_VADC_GLOBAL_BackgroundSetReqSrcEventInterruptNode(handle_ptr->global_handle->module_ptr,
                                                 (XMC_VADC_SR_t) handle_ptr->srv_req_node);
    
      /* Enable Background Scan Request source IRQ */
      NVIC_EnableIRQ((IRQn_Type)handle_ptr->req_src_intr_handle->node_id);
#ifdef ADC_MEASUREMENT_NON_DEFAULT_IRQ_SOURCE_SELECTED
  XMC_SCU_SetInterruptControl(handle_ptr->req_src_intr_handle->node_id,
                              ((handle_ptr->req_src_intr_handle->node_id << 8) | handle_ptr->req_src_intr_handle->irqctrl));
#endif
    }
#else /* Selected device is XMC11*/
    XMC_VADC_GLOBAL_SetResultEventInterruptNode(handle_ptr->global_handle->module_ptr, handle_ptr->srv_req_node );
#ifdef ADC_MEASUREMENT_CPU_1X /* End of single measurement is enabled*/
    NVIC_SetPriority((IRQn_Type)handle_ptr->result_intr_handle->node_id,
                            handle_ptr->result_intr_handle->priority);

    /* Enable Background Scan Request source IRQ */
    NVIC_EnableIRQ((IRQn_Type)handle_ptr->result_intr_handle->node_id);
#endif
#endif
    /* Mux Configuration is done*/
    if (handle_ptr->mux_config != NULL)
    {
      (handle_ptr->mux_config)();
    }
  
    if (handle_ptr->start_conversion != (bool)false)
    {
      /* Start conversion manually using load event trigger*/
      XMC_VADC_GLOBAL_BackgroundTriggerConversion(handle_ptr->global_handle->module_ptr);
    }
    handle_ptr->init_state = status;
  }
  return (handle_ptr->init_state);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* This API will Software trigger ADC Background request source and starts conversion*/
void ADC_MEASUREMENT_StartConversion(ADC_MEASUREMENT_t *const handle_ptr)
{
  XMC_ASSERT("ADC_MEASUREMENT_Start:Invalid handle_ptr", (handle_ptr != NULL));

  /* Generate a load event to start background request source conversion*/
  XMC_VADC_GLOBAL_BackgroundTriggerConversion(handle_ptr->global_handle->module_ptr);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#if(XMC_VADC_GROUP_AVAILABLE == 1U)
/* This API will get the result of a conversion for a specific channel*/
XMC_VADC_RESULT_SIZE_t ADC_MEASUREMENT_GetResult(ADC_MEASUREMENT_CHANNEL_t *const handle_ptr)
{
  XMC_VADC_RESULT_SIZE_t result;

  XMC_ASSERT("ADC_MEASUREMENT_GetResult:Invalid handle_ptr", (handle_ptr != NULL));

  result = XMC_VADC_GROUP_GetResult(handle_ptr->group_handle, handle_ptr->ch_handle->result_reg_number);

  return (result);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* This API will get the result of a conversion for a specific channel. It will return the complete result register*/
uint32_t ADC_MEASUREMENT_GetDetailedResult(ADC_MEASUREMENT_CHANNEL_t *const handle_ptr)
{
  uint32_t result;

  XMC_ASSERT("ADC_MEASUREMENT_GetDetailedResult:Invalid handle_ptr", (handle_ptr != NULL));

  result = XMC_VADC_GROUP_GetDetailedResult(handle_ptr->group_handle, handle_ptr->ch_handle->result_reg_number);

  return (result);
}

#else /* Applicable for XMC1100 devices */
/* This API will get the result of the conversion from the global result
 *
 * This API has been deprecated. Use ADC_MEASUREMENT_GetGlobalResult() to get the global result.
 * */
XMC_VADC_RESULT_SIZE_t ADC_MEASUREMENT_GetResult(ADC_MEASUREMENT_t *const handle_ptr)
{
  XMC_VADC_RESULT_SIZE_t result;

  XMC_ASSERT("ADC_MEASUREMENT_GetResult:Invalid handle_ptr", (handle_ptr != NULL));

  XMC_UNUSED_ARG(handle_ptr);

  result = ADC_MEASUREMENT_GetGlobalResult();
  return (result);
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* This API will get the result of a conversion for a specific channel. It will return the global result register
 *
 * This API has been deprecated. Use ADC_MEASUREMENT_GetGlobalDetailedResult() to get the global result.
 * */
uint32_t ADC_MEASUREMENT_GetDetailedResult(ADC_MEASUREMENT_t *const handle_ptr)
{
  uint32_t result;

  XMC_ASSERT("ADC_MEASUREMENT_GetDetailedResult:Invalid handle_ptr", (handle_ptr != NULL));

  XMC_UNUSED_ARG(handle_ptr);

  /* Needed only for XMC1100 devices to read global result register*/
  result = ADC_MEASUREMENT_GetGlobalDetailedResult();
  return (result);
}
#endif
