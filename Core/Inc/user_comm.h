#ifndef _USER_COMM_H_
#define _USER_COMM_H_

#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/sys/sys_mpu.h"
#include "./SYSTEM/sys/sys_dma.h"
#include "./SYSTEM/usart/sys_usart.h"
#include "app.h"
#include "usart.h"

#include "adc.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
} GPIO_Channel;

#define CH_DEF(n) {CH##n##_GPIO_Port, CH##n##_Pin}
#define INPUT_CH_NUMBER 64


#define TOTAL_POINTS (64 * 64)
#define ADC_BUFFER_SIZE 10

#define TEST_PORT_UP TEST_PORT_GPIO_Port->BSRR = TEST_PORT_Pin; // Set GPIO pin PB0 high
#define TEST_PORT_DOWN TEST_PORT_GPIO_Port->BSRR |= TEST_PORT_Pin << 16;

#endif /* _USER_COMM_H_ */
