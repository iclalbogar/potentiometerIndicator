#include "uart_link.h"

static UART_HandleTypeDef *uart_handle;

void UartLink_Init(UART_HandleTypeDef *huart)
{
    uart_handle = huart;
}

void UartLink_Send(uint8_t *data, uint16_t len)
{
    HAL_UART_Transmit(uart_handle, data, len, HAL_MAX_DELAY);
}

/*
 * uart_link.c
 *
 *  Created on: 21 Tem 2026
 *      Author: iclal
 */


