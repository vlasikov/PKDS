/*
 * LedRubber.h
 *
 *  Created on: Sep 27, 2022
 *      Author: kendor
 */

#ifndef MAINALG_PERIPHERIALS_LEDRUBBER_H_
#define MAINALG_PERIPHERIALS_LEDRUBBER_H_

#include "DAVE.h"
#include "xmc_common.h"


#define MODE_OFF 		0
#define MODE_ON 		1
#define MODE_BLINK 		2
#define MODE_TIME_ON 	3


#define CL_BLACK 	0
#define CL_RED 		(1<<0)
#define CL_GREEN 	(1<<1)
#define CL_YELLOW   (CL_RED | CL_GREEN)
#define CL_BLUE		(1<<2)
#define CL_MARGENTA (CL_RED | CL_BLUE)
#define CL_CYAN 	(CL_GREEN | CL_BLUE)
#define CL_WHITE	(CL_GREEN | CL_RED | CL_BLUE)


//#define RUBBER_BLINK_MS 500

typedef struct __LED_RUBBER_LIGHT
{
  int32_t red_outern;
  int32_t green_outern;
  int32_t blue_outern;

  int32_t red_intern;
  int32_t green_intern;
  int32_t blue_intern;

} LED_RUBBER_LIGHT_t;

void InitLedRubber(int32_t mode);
void LedPwmTimerProc(void *args);
void WriteRubberLights(uint32_t color, int32_t mode, int32_t time_ms); // mb change

#endif /* MAINALG_PERIPHERIALS_LEDRUBBER_H_ */
