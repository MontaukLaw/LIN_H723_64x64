/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CH25_Pin GPIO_PIN_2
#define CH25_GPIO_Port GPIOE
#define CH22_Pin GPIO_PIN_3
#define CH22_GPIO_Port GPIOE
#define CH23_Pin GPIO_PIN_4
#define CH23_GPIO_Port GPIOE
#define CH20_Pin GPIO_PIN_5
#define CH20_GPIO_Port GPIOE
#define CH21_Pin GPIO_PIN_6
#define CH21_GPIO_Port GPIOE
#define TEST_PORT_Pin GPIO_PIN_13
#define TEST_PORT_GPIO_Port GPIOC
#define CH0_Pin GPIO_PIN_8
#define CH0_GPIO_Port GPIOE
#define CH1_Pin GPIO_PIN_9
#define CH1_GPIO_Port GPIOE
#define CH2_Pin GPIO_PIN_10
#define CH2_GPIO_Port GPIOE
#define CH3_Pin GPIO_PIN_11
#define CH3_GPIO_Port GPIOE
#define CH4_Pin GPIO_PIN_12
#define CH4_GPIO_Port GPIOE
#define CH5_Pin GPIO_PIN_13
#define CH5_GPIO_Port GPIOE
#define CH6_Pin GPIO_PIN_14
#define CH6_GPIO_Port GPIOE
#define CH8_Pin GPIO_PIN_15
#define CH8_GPIO_Port GPIOE
#define CH9_Pin GPIO_PIN_10
#define CH9_GPIO_Port GPIOB
#define CH7_Pin GPIO_PIN_11
#define CH7_GPIO_Port GPIOB
#define CH12_Pin GPIO_PIN_12
#define CH12_GPIO_Port GPIOB
#define CH11_Pin GPIO_PIN_13
#define CH11_GPIO_Port GPIOB
#define CH10_Pin GPIO_PIN_14
#define CH10_GPIO_Port GPIOB
#define CH13_Pin GPIO_PIN_15
#define CH13_GPIO_Port GPIOB
#define CH14_Pin GPIO_PIN_8
#define CH14_GPIO_Port GPIOD
#define CH15_Pin GPIO_PIN_9
#define CH15_GPIO_Port GPIOD
#define CH16_Pin GPIO_PIN_10
#define CH16_GPIO_Port GPIOD
#define CH17_Pin GPIO_PIN_11
#define CH17_GPIO_Port GPIOD
#define CH18_Pin GPIO_PIN_12
#define CH18_GPIO_Port GPIOD
#define CH19_Pin GPIO_PIN_13
#define CH19_GPIO_Port GPIOD
#define CH62_Pin GPIO_PIN_14
#define CH62_GPIO_Port GPIOD
#define CH63_Pin GPIO_PIN_15
#define CH63_GPIO_Port GPIOD
#define CH60_Pin GPIO_PIN_2
#define CH60_GPIO_Port GPIOG
#define CH61_Pin GPIO_PIN_3
#define CH61_GPIO_Port GPIOG
#define CH58_Pin GPIO_PIN_4
#define CH58_GPIO_Port GPIOG
#define CH59_Pin GPIO_PIN_5
#define CH59_GPIO_Port GPIOG
#define CH56_Pin GPIO_PIN_6
#define CH56_GPIO_Port GPIOC
#define CH57_Pin GPIO_PIN_7
#define CH57_GPIO_Port GPIOC
#define CH54_Pin GPIO_PIN_8
#define CH54_GPIO_Port GPIOC
#define CH55_Pin GPIO_PIN_9
#define CH55_GPIO_Port GPIOC
#define CH52_Pin GPIO_PIN_8
#define CH52_GPIO_Port GPIOA
#define CH49_Pin GPIO_PIN_15
#define CH49_GPIO_Port GPIOA
#define CH46_Pin GPIO_PIN_10
#define CH46_GPIO_Port GPIOC
#define CH53_Pin GPIO_PIN_11
#define CH53_GPIO_Port GPIOC
#define CH50_Pin GPIO_PIN_12
#define CH50_GPIO_Port GPIOC
#define CH51_Pin GPIO_PIN_0
#define CH51_GPIO_Port GPIOD
#define CH48_Pin GPIO_PIN_1
#define CH48_GPIO_Port GPIOD
#define CH47_Pin GPIO_PIN_2
#define CH47_GPIO_Port GPIOD
#define CH44_Pin GPIO_PIN_3
#define CH44_GPIO_Port GPIOD
#define CH45_Pin GPIO_PIN_4
#define CH45_GPIO_Port GPIOD
#define CH42_Pin GPIO_PIN_5
#define CH42_GPIO_Port GPIOD
#define CH43_Pin GPIO_PIN_6
#define CH43_GPIO_Port GPIOD
#define CH40_Pin GPIO_PIN_7
#define CH40_GPIO_Port GPIOD
#define CH41_Pin GPIO_PIN_9
#define CH41_GPIO_Port GPIOG
#define CH38_Pin GPIO_PIN_10
#define CH38_GPIO_Port GPIOG
#define CH39_Pin GPIO_PIN_11
#define CH39_GPIO_Port GPIOG
#define CH36_Pin GPIO_PIN_12
#define CH36_GPIO_Port GPIOG
#define CH37_Pin GPIO_PIN_13
#define CH37_GPIO_Port GPIOG
#define CH34_Pin GPIO_PIN_14
#define CH34_GPIO_Port GPIOG
#define CH35_Pin GPIO_PIN_15
#define CH35_GPIO_Port GPIOG
#define CH32_Pin GPIO_PIN_3
#define CH32_GPIO_Port GPIOB
#define CH33_Pin GPIO_PIN_4
#define CH33_GPIO_Port GPIOB
#define CH30_Pin GPIO_PIN_5
#define CH30_GPIO_Port GPIOB
#define CH31_Pin GPIO_PIN_6
#define CH31_GPIO_Port GPIOB
#define CH28_Pin GPIO_PIN_7
#define CH28_GPIO_Port GPIOB
#define CH24_Pin GPIO_PIN_8
#define CH24_GPIO_Port GPIOB
#define CH27_Pin GPIO_PIN_9
#define CH27_GPIO_Port GPIOB
#define CH26_Pin GPIO_PIN_0
#define CH26_GPIO_Port GPIOE
#define CH29_Pin GPIO_PIN_1
#define CH29_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
