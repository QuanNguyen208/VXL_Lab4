/*
 * uart_com.h
 *
 *  Created on: Nov 28, 2023
 *      Author: Admin
 */

#ifndef INC_UART_COM_H_
#define INC_UART_COM_H_

#include "main.h"
#include "software_timer.h"
#include "stdio.h"
#include "stdlib.h"
#include "global.h"
#include "string.h"
#include "math.h"
#include "global.h"

void command_parser_fsm();
void uart_communiation_fsm(ADC_HandleTypeDef hadc1, UART_HandleTypeDef huart2);

#endif /* INC_UART_COM_H_ */
