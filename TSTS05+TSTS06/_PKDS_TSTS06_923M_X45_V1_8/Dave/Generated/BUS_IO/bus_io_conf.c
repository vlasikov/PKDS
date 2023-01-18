/*********************************************************************************************************************
* DAVE APP Name : BUS_IO       APP Version: 4.0.4
*
* NOTE:
* This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
*********************************************************************************************************************/

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
 * 2016-04-06
 *     - Initial version<br>
 *
 * @endcond
 *
 */
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "bus_io.h"

const BUS_IO_PORT_PIN_t GROUP_IN_pin_list[] =
{
       {P5_0},
       {P5_1},
       {P5_2},
       {P5_3}
}; 
 
BUS_IO_t GROUP_IN =
{
  .pin_array = GROUP_IN_pin_list,
  .gpio_config = {
  .mode = XMC_GPIO_MODE_INPUT_TRISTATE,  
  },
  .number_of_pins = (uint8_t)4
};
const BUS_IO_PORT_PIN_t GROUP_OUT_pin_list[] =
{
       {P5_4},
       {P5_5},
       {P5_6},
       {P5_7}
}; 
 
BUS_IO_t GROUP_OUT =
{
  .pin_array = GROUP_OUT_pin_list,
  .gpio_config = {
  .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL, 
    .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW, 
    .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
  },
  .number_of_pins = (uint8_t)4
};
const BUS_IO_PORT_PIN_t DI_PNP_pin_list[] =
{
       {P14_15},
       {P14_14},
       {P14_13},
       {P14_12}
}; 
 
BUS_IO_t DI_PNP =
{
  .pin_array = DI_PNP_pin_list,
  .gpio_config = {
  .mode = XMC_GPIO_MODE_INPUT_TRISTATE,  
  },
  .number_of_pins = (uint8_t)4
};
const BUS_IO_PORT_PIN_t DI_NPN_pin_list[] =
{
       {P15_7},
       {P15_6},
       {P15_5},
       {P15_4}
}; 
 
BUS_IO_t DI_NPN =
{
  .pin_array = DI_NPN_pin_list,
  .gpio_config = {
  .mode = XMC_GPIO_MODE_INPUT_TRISTATE,  
  },
  .number_of_pins = (uint8_t)4
};
