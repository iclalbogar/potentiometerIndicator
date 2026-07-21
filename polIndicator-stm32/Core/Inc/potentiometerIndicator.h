/*
 * potentiometerIndicator.h
 *
 *  Created on: 21 Tem 2026
 *      Author: iclal
 */

#ifndef INC_POTENTIOMETERINDICATOR_H_
#define INC_POTENTIOMETERINDICATOR_H_
#include "main.h"

#define POT_STX          0xAA   // frame başlangıç byte'ı
#define POT_ETX          0x55   // frame bitiş byte'ı
#define POT_MSG_ID_VALUE 0x01   // "bu bir potansiyometre değeri" mesaj tipi


void     PotIndicator_Init(ADC_HandleTypeDef *hadc, UART_HandleTypeDef *huart);
uint16_t PotIndicator_GetRawValue(void);
void     PotIndicator_SendValue(void);




#endif /* INC_POTENTIOMETERINDICATOR_H_ */
