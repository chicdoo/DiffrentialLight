/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define PWM_CH5_Pin GPIO_PIN_5
#define PWM_CH5_GPIO_Port GPIOE
#define PWM_CH6_Pin GPIO_PIN_6
#define PWM_CH6_GPIO_Port GPIOE
#define LED_OFF1_Pin GPIO_PIN_4
#define LED_OFF1_GPIO_Port GPIOC
#define LED_OFF2_Pin GPIO_PIN_5
#define LED_OFF2_GPIO_Port GPIOC
#define DEV_TX_Pin GPIO_PIN_10
#define DEV_TX_GPIO_Port GPIOB
#define DEV_RX_Pin GPIO_PIN_11
#define DEV_RX_GPIO_Port GPIOB
#define DA1_EN_Pin GPIO_PIN_10
#define DA1_EN_GPIO_Port GPIOH
#define DA2_EN_Pin GPIO_PIN_11
#define DA2_EN_GPIO_Port GPIOH
#define DA3_EN_Pin GPIO_PIN_12
#define DA3_EN_GPIO_Port GPIOH
#define LED_OFF11_Pin GPIO_PIN_8
#define LED_OFF11_GPIO_Port GPIOD
#define LED_OFF12_Pin GPIO_PIN_9
#define LED_OFF12_GPIO_Port GPIOD
#define LED_OFF13_Pin GPIO_PIN_10
#define LED_OFF13_GPIO_Port GPIOD
#define LED_OFF14_Pin GPIO_PIN_11
#define LED_OFF14_GPIO_Port GPIOD
#define LED_OFF15_Pin GPIO_PIN_12
#define LED_OFF15_GPIO_Port GPIOD
#define LED_OFF16_Pin GPIO_PIN_13
#define LED_OFF16_GPIO_Port GPIOD
#define LED_OFF17_Pin GPIO_PIN_14
#define LED_OFF17_GPIO_Port GPIOD
#define LED_OFF18_Pin GPIO_PIN_15
#define LED_OFF18_GPIO_Port GPIOD
#define LED_OFF3_Pin GPIO_PIN_6
#define LED_OFF3_GPIO_Port GPIOC
#define LED_OFF4_Pin GPIO_PIN_7
#define LED_OFF4_GPIO_Port GPIOC
#define LED_OFF5_Pin GPIO_PIN_8
#define LED_OFF5_GPIO_Port GPIOC
#define LED_OFF6_Pin GPIO_PIN_9
#define LED_OFF6_GPIO_Port GPIOC
#define RS232_TX_Pin GPIO_PIN_9
#define RS232_TX_GPIO_Port GPIOA
#define RX232_RX_Pin GPIO_PIN_10
#define RX232_RX_GPIO_Port GPIOA
#define DA4_EN_Pin GPIO_PIN_13
#define DA4_EN_GPIO_Port GPIOH
#define DA5_EN_Pin GPIO_PIN_14
#define DA5_EN_GPIO_Port GPIOH
#define DA6_EN_Pin GPIO_PIN_15
#define DA6_EN_GPIO_Port GPIOH
#define PWM_CH4_Pin GPIO_PIN_2
#define PWM_CH4_GPIO_Port GPIOI
#define LED_OFF7_Pin GPIO_PIN_0
#define LED_OFF7_GPIO_Port GPIOD
#define LED_OFF8_Pin GPIO_PIN_1
#define LED_OFF8_GPIO_Port GPIOD
#define LED_OFF9_Pin GPIO_PIN_2
#define LED_OFF9_GPIO_Port GPIOD
#define LED_OFF10_Pin GPIO_PIN_3
#define LED_OFF10_GPIO_Port GPIOD
#define PWM_CH1_Pin GPIO_PIN_5
#define PWM_CH1_GPIO_Port GPIOI
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
