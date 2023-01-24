/*
 * serv_mode.c
 *
 *  Created on: Feb 17, 2022
 *      Author: kendor
 */

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "xmc_common.h"
#include "MainAlg/main_alg.h"
#include "MainAlg/door_periph.h"
//#include "bldc_scalar_user_interface.h"
//#include "stdlib.h"
#include "MainAlg/ext_can.h"
#include <MainAlg/presets.h>
#include <MainAlg/retain_xmc4.h>


uint8_t ServCanRxData1[8];
uint8_t ServCanRxData2[8];

int32_t ServiceMode = 0;


