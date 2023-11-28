/*
 * uart_com.c
 *
 *  Created on: Nov 28, 2023
 *      Author: Admin
 */

#include "uart_com.h"

void command_parser_fsm() {
	switch (Parser) {
	case 0:
		if (temp == '!') {
			Parser = 1;
			command_index = 0;
		}
		break;

	case 1:
		if (temp == '#') {
			Parser = 0;
			command[command_index] = '\0';
			command_flag = 1;
		} else if (temp == '!') {
			command_index = 0;
		} else {
			command[command_index++] = temp;
			command_index %= MAX_BUFFER_SIZE;
		}
		break;

	default:
		break;
	}
}

void uart_communiation_fsm(ADC_HandleTypeDef hadc1, UART_HandleTypeDef huart2) {
	switch(Uart) {

	case waitReset:
		if (command_flag == 1) {
			command_flag = 0;
			if (command[0] == 'R' && command[1] == 'S' && command[2] == 'T') {
				// Get ADC value
				HAL_ADC_Start(&hadc1);
				ADCval = HAL_ADC_GetValue(&hadc1);
				HAL_ADC_Stop(&hadc1);
				HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "\r\n"), 1000);
				Uart = sendADC;
				setTimer(1, 3000);
			}
		}
		break;

	case sendADC:
		HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "!ADC=%lu#\r\n", ADCval), 1000);
		Uart = waitOk;
		break;

	case waitOk:
		// If command has completed and command = "OK" -> status = waitReset and clearTimer
		if (command_flag == 1) {
			command_flag = 0;
			if (command[0] == 'O' && command[1] == 'K') {
				HAL_UART_Transmit(&huart2, (void*)str, sprintf(str, "\r\n"), 1000);
				Uart = waitReset;
				clearTimer(1);
			}
		}
		// Else, if each after 3s the system doesn't receive string "OK" -> status = sendADC
		if(timer_flag[1] == 1) {
			Uart = sendADC;
			setTimer(1, 3000);
		}
		break;
	default:
		break;
	}
}
