/*
 * Zoommer.h
 *
 *  Created on: Jun 7, 2022
 *      Author: kendor
 */

#ifndef MAINALG_PERIPHERIALS_BUZZER_H_
#define MAINALG_PERIPHERIALS_BUZZER_H_


#define BUZZER_TYPE_SFM 0
#define BUZZER_TYPE_BPT 1

#define BUZZER_ON 1
#define BUZZER_OFF 0

void InitBuzzer(int32_t buzzer_type);
void WriteBuzzer(int32_t cmd);



#endif /* MAINALG_PERIPHERIALS_BUZZER_H_ */
