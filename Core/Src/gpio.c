/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
        * Free pins are configured automatically as Analog (this feature is enabled through
        * the Code Generation settings)
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CH25_Pin|CH22_Pin|CH23_Pin|CH20_Pin
                          |CH21_Pin|CH0_Pin|CH1_Pin|CH2_Pin
                          |CH3_Pin|CH4_Pin|CH5_Pin|CH6_Pin
                          |CH8_Pin|CH26_Pin|CH29_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, TEST_PORT_Pin|CH56_Pin|CH57_Pin|CH54_Pin
                          |CH55_Pin|CH46_Pin|CH53_Pin|CH50_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, HC4067_S2_1_Pin|HC4067_EN_1_Pin|HC4067_S3_2_Pin|HC4067_S0_3_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, HC4067_S1_1_Pin|HC4067_S0_1_Pin|HC4067_S3_1_Pin|HC4067_S1_2_Pin
                          |HC4067_S0_2_Pin|HC4067_S2_2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, HC4067_EN_2_Pin|HC4067_S3_3_Pin|HC4067_S1_3_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, HC4067_EN_3_Pin|HC4067_S2_3_Pin|HC4067_S1_4_Pin|HC4067_S0_4_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, HC4067_S3_4_Pin|HC4067_EN_4_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(HC4067_S2_4_GPIO_Port, HC4067_S2_4_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, CH9_Pin|CH7_Pin|CH12_Pin|CH11_Pin
                          |CH10_Pin|CH13_Pin|CH32_Pin|CH33_Pin
                          |CH30_Pin|CH31_Pin|CH28_Pin|CH24_Pin
                          |CH27_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, CH14_Pin|CH15_Pin|CH16_Pin|CH17_Pin
                          |CH18_Pin|CH19_Pin|CH62_Pin|CH63_Pin
                          |CH51_Pin|CH48_Pin|CH47_Pin|CH44_Pin
                          |CH45_Pin|CH42_Pin|CH43_Pin|CH40_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, CH60_Pin|CH61_Pin|CH58_Pin|CH59_Pin
                          |CH41_Pin|CH38_Pin|CH39_Pin|CH36_Pin
                          |CH37_Pin|CH34_Pin|CH35_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, CH52_Pin|CH49_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : CH25_Pin CH22_Pin CH23_Pin CH20_Pin
                           CH21_Pin HC4067_S2_4_Pin CH0_Pin CH1_Pin
                           CH2_Pin CH3_Pin CH4_Pin CH5_Pin
                           CH6_Pin CH8_Pin CH26_Pin CH29_Pin */
  GPIO_InitStruct.Pin = CH25_Pin|CH22_Pin|CH23_Pin|CH20_Pin
                          |CH21_Pin|HC4067_S2_4_Pin|CH0_Pin|CH1_Pin
                          |CH2_Pin|CH3_Pin|CH4_Pin|CH5_Pin
                          |CH6_Pin|CH8_Pin|CH26_Pin|CH29_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : TEST_PORT_Pin */
  GPIO_InitStruct.Pin = TEST_PORT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TEST_PORT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PC14 PC15 PC0 */
  GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PF0 PF1 PF2 PF3
                           PF4 PF5 PF6 PF7
                           PF8 PF9 PF10 PF15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : HC4067_S2_1_Pin HC4067_EN_1_Pin HC4067_S3_2_Pin HC4067_S0_3_Pin
                           CH56_Pin CH57_Pin CH54_Pin CH55_Pin
                           CH46_Pin CH53_Pin CH50_Pin */
  GPIO_InitStruct.Pin = HC4067_S2_1_Pin|HC4067_EN_1_Pin|HC4067_S3_2_Pin|HC4067_S0_3_Pin
                          |CH56_Pin|CH57_Pin|CH54_Pin|CH55_Pin
                          |CH46_Pin|CH53_Pin|CH50_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : HC4067_S1_1_Pin HC4067_S0_1_Pin HC4067_S3_1_Pin HC4067_S1_2_Pin
                           HC4067_S0_2_Pin HC4067_S2_2_Pin CH52_Pin CH49_Pin */
  GPIO_InitStruct.Pin = HC4067_S1_1_Pin|HC4067_S0_1_Pin|HC4067_S3_1_Pin|HC4067_S1_2_Pin
                          |HC4067_S0_2_Pin|HC4067_S2_2_Pin|CH52_Pin|CH49_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA4 PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : HC4067_EN_2_Pin HC4067_S3_3_Pin HC4067_S1_3_Pin CH9_Pin
                           CH7_Pin CH12_Pin CH11_Pin CH10_Pin
                           CH13_Pin CH32_Pin CH33_Pin CH30_Pin
                           CH31_Pin CH28_Pin CH24_Pin CH27_Pin */
  GPIO_InitStruct.Pin = HC4067_EN_2_Pin|HC4067_S3_3_Pin|HC4067_S1_3_Pin|CH9_Pin
                          |CH7_Pin|CH12_Pin|CH11_Pin|CH10_Pin
                          |CH13_Pin|CH32_Pin|CH33_Pin|CH30_Pin
                          |CH31_Pin|CH28_Pin|CH24_Pin|CH27_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : HC4067_EN_3_Pin HC4067_S2_3_Pin HC4067_S1_4_Pin HC4067_S0_4_Pin */
  GPIO_InitStruct.Pin = HC4067_EN_3_Pin|HC4067_S2_3_Pin|HC4067_S1_4_Pin|HC4067_S0_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : HC4067_S3_4_Pin HC4067_EN_4_Pin CH60_Pin CH61_Pin
                           CH58_Pin CH59_Pin CH41_Pin CH38_Pin
                           CH39_Pin CH36_Pin CH37_Pin CH34_Pin
                           CH35_Pin */
  GPIO_InitStruct.Pin = HC4067_S3_4_Pin|HC4067_EN_4_Pin|CH60_Pin|CH61_Pin
                          |CH58_Pin|CH59_Pin|CH41_Pin|CH38_Pin
                          |CH39_Pin|CH36_Pin|CH37_Pin|CH34_Pin
                          |CH35_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : CH14_Pin CH15_Pin CH16_Pin CH17_Pin
                           CH18_Pin CH19_Pin CH62_Pin CH63_Pin
                           CH51_Pin CH48_Pin CH47_Pin CH44_Pin
                           CH45_Pin CH42_Pin CH43_Pin CH40_Pin */
  GPIO_InitStruct.Pin = CH14_Pin|CH15_Pin|CH16_Pin|CH17_Pin
                          |CH18_Pin|CH19_Pin|CH62_Pin|CH63_Pin
                          |CH51_Pin|CH48_Pin|CH47_Pin|CH44_Pin
                          |CH45_Pin|CH42_Pin|CH43_Pin|CH40_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PG6 PG7 PG8 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*AnalogSwitch Config */
  HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PC2, SYSCFG_SWITCH_PC2_CLOSE);

  /*AnalogSwitch Config */
  HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PC3, SYSCFG_SWITCH_PC3_CLOSE);

  /*AnalogSwitch Config */
  HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PA0, SYSCFG_SWITCH_PA0_CLOSE);

  /*AnalogSwitch Config */
  HAL_SYSCFG_AnalogSwitchConfig(SYSCFG_SWITCH_PA1, SYSCFG_SWITCH_PA1_CLOSE);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
