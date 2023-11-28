/*
 * global.h
 *
 *  Created on: Nov 27, 2023
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"


#define waitReset 		10
#define sendADC		11
#define waitOk 		12
#define MAX_BUFFER_SIZE 30

extern int Parser;
extern int Uart;

extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;

extern uint8_t command_flag;
extern uint8_t command[MAX_BUFFER_SIZE];
extern uint8_t command_index;

extern char str[50];
// ADC Value
extern uint32_t ADCval;

#endif /* INC_GLOBAL_H_ */
