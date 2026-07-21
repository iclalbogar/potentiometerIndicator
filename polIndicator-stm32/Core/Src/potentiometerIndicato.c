#include "potentiometerIndicator.h"
#include "uart_link.h"

static ADC_HandleTypeDef *adc_handle;
static volatile uint16_t adc_dma_buf[1];

static uint8_t ComputeChecksum(const uint8_t *data, uint8_t len)
{
    uint8_t sum = 0;
    for (uint8_t i = 0; i < len; i++)
    {
        sum ^= data[i];
    }
    return sum;
}

void PotIndicator_Init(ADC_HandleTypeDef *hadc, UART_HandleTypeDef *huart)
{
    adc_handle = hadc;
    UartLink_Init(huart);
    HAL_ADC_Start_DMA(adc_handle, (uint32_t*)adc_dma_buf, 1);
}

uint16_t PotIndicator_GetRawValue(void)
{
    return adc_dma_buf[0];
}

void PotIndicator_SendValue(void)
{
    uint16_t value = PotIndicator_GetRawValue();

    uint8_t frame[7];
    uint8_t idx = 0;

    frame[idx++] = POT_STX;
    frame[idx++] = POT_MSG_ID_VALUE;
    frame[idx++] = 2;                        // payload uzunlugu: 2 byte
    frame[idx++] = (value >> 8) & 0xFF;      // MSB
    frame[idx++] = value & 0xFF;             // LSB

    uint8_t cksum = ComputeChecksum(&frame[1], idx - 1);
    frame[idx++] = cksum;
    frame[idx++] = POT_ETX;

    UartLink_Send(frame, idx);
}
/*
 * potentiometerIndicato.c
 *
 *  Created on: 21 Tem 2026
 *      Author: iclal
 */


