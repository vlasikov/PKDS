/*
 * Scheme.h
 *
 *  Created on: Dec 18, 2022
 *      Author: kendor
 */

#ifndef MAINALG_PERIPHERIALS_SCHEME_H_
#define MAINALG_PERIPHERIALS_SCHEME_H_

#include <DAVE.h>
#include "iomap.h"


#define CMD_OFF 0
#define CMD_ON 1
#define CMD_TOGGLE 2

extern INPUT_SIGNALS_t Inputs;


void ReadInput(INPUT_DIGITAL_t * input);
void ReadCaptronButton(CAPTRON_BUTTON_t * button);

void WriteOutput(OUTPUT_DIGITAL_t * out, uint8_t value);
void WriteCaptronButton(CAPTRON_BUTTON_t * out, uint8_t value);




#endif /* MAINALG_PERIPHERIALS_SCHEME_H_ */
