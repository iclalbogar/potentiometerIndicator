/*
 * uart_link.h
 *
 *  Created on: 21 Tem 2026
 *      Author: iclal
 */

#ifndef INC_UART_LINK_H_
#define INC_UART_LINK_H_
#include "main.h"

void UartLink_Init(UART_HandleTypeDef *huart);
void UartLink_Send(uint8_t *data, uint16_t len);



#endif /* INC_UART_LINK_H_ */
