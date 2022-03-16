/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "gpio.h"
#include "spi.h"
#include "usart.h"
#include "log.h"
#include "command.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern TIM_HandleTypeDef htim8;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */

  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 512);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  LOG_Init();
  CMD_Init();
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */

//
//
//  uint8_t pData[2];
//  uint8_t msg[64];
//
//  pData[0] = 0x20;
//  pData[1] = 0x04;
//
//  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
//  HAL_GPIO_WritePin(LED_OFF1_GPIO_Port, LED_OFF1_Pin, GPIO_PIN_RESET);
//
////  HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_RESET);
////  HAL_SPI_Transmit(&hspi1, pData, 2, 100);
////  HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_RESET);
//  osDelay(1000);

//  pData[0] = 0xFF;
//  pData[1] = 0x2F;
//
//  HAL_SPI_Transmit(&hspi1, pData, 1, 100);
//  osDelay(1);
//  HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_SET);
//  osDelay(1);
//  HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_RESET);
//
//  osDelay(2000);

  for(;;)
  {
//    HAL_GPIO_TogglePin(DA1_EN_GPIO_Port, DA1_EN_Pin);
//    HAL_SPI_Transmit(&hspi1, pData, 2, 1);

//    pData[0] = 0x00;
//    pData[1] = 0x20;
//
//    HAL_SPI_Transmit(&hspi1, pData, 1, 100);
//    osDelay(1);
//    HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_SET);
//    osDelay(1);
//    HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_RESET);

    LOGD("Hello");
//    sprintf((char*)msg, "LED: %d\r\n", pData[0]);
//
//    HAL_UART_Transmit(&huart1, msg, (uint16_t)strlen(msg), 100);

    osDelay(5000);

//
//
//    pData[0] = 0x00;
//    pData[1] = 0x20;
//
//
//    HAL_SPI_Transmit(&hspi1, pData, 1, 100);
//    osDelay(1);
//    HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_SET);
//    osDelay(1);
//    HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_RESET);
//
//
//    sprintf((char*)msg, "LED: %d", pData[0]);
//
//    HAL_UART_Transmit(&huart1, msg, strlen(msg), 100);
//
//    osDelay(2000);

//    pData[0] = 0x04;
//    pData[1] = 0x20;
//
//    HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_RESET);
//    HAL_SPI_Transmit(&hspi1, pData, 2, 100);
//    HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_SET);
//
//    osDelay(1000);
//
//    pData[0] = 0x04;
//    pData[1] = 0x30;
//
//    HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_RESET);
//    HAL_SPI_Transmit(&hspi1, pData, 2, 100);
//    HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_SET);
//
//    osDelay(1000);
//
//    pData[0] = 0x04;
//    pData[1] = 0x40;
//
//    HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_RESET);
//    HAL_SPI_Transmit(&hspi1, pData, 2, 100);
//    HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_SET);
//
//    osDelay(1000);

  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
