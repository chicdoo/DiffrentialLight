/* ------------------------------------------------------------------------------ *
 * @file        src/command.c
 * @author      Eungdoo Kim
 * @version     v0.0
 * @date        2022-03-08
 * @brief       Receive command from PC by RS232. And process it.
 * ------------------------------------------------------------------------------ *
 * @reference   See inc/command.h
 * ------------------------------------------------------------------------------ */

/* Includes --------------------------------------------------------------------- */
#include "command.h"
#include "cmsis_os.h"
#include "log.h"
#include "stdarg.h"
#include "usart.h"
#include "stdlib.h"
#include "tim.h"
#include "gpio.h"
#include "stm32f4xx_hal_uart.h"

/* Private define --------------------------------------------------------------- */
typedef void (*pCMD)(char*);

/* Exported variables ----------------------------------------------------------- */
extern TIM_HandleTypeDef htim8;

/* Private variables ------------------------------------------------------------ */
static osMessageQId   hCmdMessage;
static osThreadId     hCmdThread;

static char cmdData[CMD_DATA_SIZE];

typedef void (*pCMD)(char*);

/* Command Definition Start ------------------------------------------------------ */
/* Declare command functions */
void CMD_SetPWMHz(char* args);
void CMD_SetPWMDuty(char* args);
void CMD_SetLEDOff(char* args);
void CMD_SetLEDOn(char* args);
void CMD_SetDAC(char* args);
/* If need new command, add here. */
void CMD_Help(char* args);

typedef enum
{
  CMD_TYPE_SET_PWM_HZ,
  CMD_TYPE_SET_PWM_DUTY,
  CMD_TYPE_SET_LED_OFF,
  CMD_TYPE_SET_LED_ON,
  CMD_TYPE_SET_DAC,
  /* If need new command, add here. */
  CMD_TYPE_HELP,
  CMD_TYPE_MAX
} CMD_TypeDef;

char* CMD_list[CMD_TYPE_MAX] = {
  [CMD_TYPE_SET_PWM_HZ]       = "setPWMHz",
  [CMD_TYPE_SET_PWM_DUTY]     = "setPWMDuty",
  [CMD_TYPE_SET_LED_OFF]      = "setLEDOff",
  [CMD_TYPE_SET_LED_ON]       = "setLEDOn",
  [CMD_TYPE_SET_DAC]          = "setDAC",
  /* If need new command, add here. */
  [CMD_TYPE_HELP]             = "help"
};

char* CMD_info[CMD_TYPE_MAX] = {
  [CMD_TYPE_SET_PWM_HZ]       = "[channel] [frequency]",
  [CMD_TYPE_SET_PWM_DUTY]     = "[channel] [duty 0~4000]",
  [CMD_TYPE_SET_LED_OFF]      = "[channel]",
  [CMD_TYPE_SET_LED_ON]       = "[channel]",
  [CMD_TYPE_SET_DAC]          = "[channel] [data 0~1023]",
  /* If need new command, add here. */
  [CMD_TYPE_HELP]             = ""
};

void (*CMD_functions[CMD_TYPE_MAX])(char* args) = {
  [CMD_TYPE_SET_PWM_HZ]       = &CMD_SetPWMHz,
  [CMD_TYPE_SET_PWM_DUTY]     = &CMD_SetPWMDuty,
  [CMD_TYPE_SET_LED_OFF]      = &CMD_SetLEDOff,
  [CMD_TYPE_SET_LED_ON]       = &CMD_SetLEDOn,
  [CMD_TYPE_SET_DAC]          = &CMD_SetDAC,
  /* If need new command, add here. */
  [CMD_TYPE_HELP]             = &CMD_Help
};
/* Command Definition End ------------------------------------------------------- */


/**
 * @brief   Initialize command module.
 */
void CMD_Init()
{
  LOGD("[+]");

  /* Create command message queue. */
  osMessageQDef(CmdQueue, CMD_QUEUE_SIZE, CMD_IRQTypekDef);
  hCmdMessage = osMessageCreate(osMessageQ(CmdQueue), NULL);

  /* Create command thread. */
  osThreadDef(CmdThread, CMD_Thread, osPriorityAboveNormal, 0, 2048);
  hCmdThread = osThreadCreate(osThread(CmdThread), NULL);

  LOGD("[-]");
}

/**
 * @brief   De-initialize command module. But not used.
 */
void CMD_DeInit()
{
  LOGD("[+]");
  osThreadTerminate(hCmdThread);
  osMessageDelete(hCmdMessage);
  LOGD("[-]");
}

/**
 * @brief   Thread for command module. Get command from UART and process it.
 */
void CMD_Thread(const void* arg)
{
  int i;
  char* tok;
  osEvent event;
  CMD_TypeDef cmdType;

  for ( ; ; ) {
    /* For escaping busy waiting, use DMA when receiving data from UART. */
    if ( HAL_UART_Receive_DMA(&CMD_UART_INST, (uint8_t*)cmdData, CMD_DATA_SIZE) == HAL_OK ) {
      /* DMA function is non-blocking. Therefore make block by message queue. */
      event = osMessageGet(hCmdMessage, osWaitForever);
      LOGI("%s", cmdData);

      if ( event.value.v == CMD_IRQ_TYPE_ERR ) {
        LOGE("DMA error");
        continue;
      }

      if ( event.status == osEventMessage ) {

        LOGI("Command: %s", cmdData);

        /* Parse command */
        tok = strtok(cmdData, " ");
        if ( tok == NULL ) {
          LOGE("Invalid command - NULL");
          continue;
        }

        cmdType = CMD_TYPE_MAX;
        for ( i = 0 ; i < CMD_TYPE_MAX ; i++ ) {
          if ( !strcmp(tok, CMD_list[i]) ) {
            cmdType = (CMD_TypeDef)i;
            break;
          }
        }

        if ( cmdType == CMD_TYPE_MAX ) {
          LOGE("Invalid command - %s", tok);
          continue;
        }

        /* Execute command function according to command type. */
        tok = strtok(NULL, "\0");
        ((pCMD)(CMD_functions[cmdType]))(tok);

      }
      else {
        LOGE("osMessageGet ERROR(%d)", event.status);
      }
    }
  }
}

/**
 * @brief   Convert decimal or hex string number as integer type.
 */
uint32_t CMD_Atoi(char* strNum)
{
  uint32_t num = 0;
//  uint32_t exp = 1;
//  uint32_t i;

  if ( strNum == NULL || strlen(strNum) == 0 ) {
    LOGE("strNum is NULL.");
    return 0;
  }

  /* Hex number is not implemented yet. */

  num = (uint32_t)atoi(strNum);

  return num;
}



/* Define command functions from UART. --------------------------------------------------------- */

/**
 * @brief   Set PWM frequency. Channel is 1 ~ 18. Frequency range is xx ~ xx.
 */
void CMD_SetPWMHz(char* args)
{
  char* tok;
  uint32_t channel;
  uint32_t freq;

  tok = strtok(args, " ");
  channel = CMD_Atoi(tok);

  tok = strtok(args, NULL);
  freq = CMD_Atoi(tok);

  LOGI("ch: %d, freq: %d Hz", channel, freq);

  if ( channel == 1 ) {

  }
  else {
    LOGE("Not implemented %d channel yet.", channel);
  }
}

/**
 * @brief   Set PWM duty. Channel is 1 ~ 18. Duty range is 0 ~ 999.
 */
void CMD_SetPWMDuty(char* args)
{
  char* tok;
  uint32_t channel;
  uint32_t duty;

  tok = strtok(args, " ");
  channel = CMD_Atoi(tok);

  tok = strtok(args, NULL);
  duty = CMD_Atoi(tok);

  if ( channel == 1 ) {

    htim8.Instance->CNT = 0;
    htim8.Instance->CCR1 = duty;
  }
  else if ( channel == 2 ) {

    htim8.Instance->CNT = 0;
    htim8.Instance->CCR4 = duty;
  }
//  else if ( channel == 3 ) {
//
//    LOGE("Not support channel %d", channel);
//  }
//  else if ( channel == 4 ) {
//
//    LOGE("Not support channel %d", channel);
//  }
  else if ( channel == 5 ) {

    htim9.Instance->CNT = 0;
    htim9.Instance->CCR1 = duty;
  }
  else if ( channel == 6 ) {

    htim9.Instance->CNT = 0;
    htim9.Instance->CCR2 = duty;
  }
  else {
    LOGE("Not implemented %d channel yet.", channel);
  }
}

/**
 * @brief   Set LED off. Channel is 1 ~ 18.
 */
void CMD_SetLEDOff(char* args)
{
  char* tok;
  uint32_t channel;

  tok = strtok(args, " ");
  channel = CMD_Atoi(tok);

  if ( channel == 1 ) {
    HAL_GPIO_WritePin(LED_OFF1_GPIO_Port, LED_OFF1_Pin, GPIO_PIN_RESET);
  }
  else {
    LOGE("Not implemented %d channel yet.", channel);
  }
}

/**
 * @brief   Set LED on. Channel is xx ~ xx.
 */
void CMD_SetLEDOn(char* args)
{
  char* tok;
  uint32_t channel;

  tok = strtok(args, " ");
  channel = CMD_Atoi(tok);

  if ( channel == 1 ) {
    HAL_GPIO_WritePin(LED_OFF1_GPIO_Port, LED_OFF1_Pin, GPIO_PIN_SET);
  }
  else {
    LOGE("Not implemented %d channel yet.", channel);
  }
}

void CMD_SetDAC(char* args)
{
  char* tok;
  uint32_t channel;
  uint32_t data;

  tok = strtok(args, " ");
  channel = CMD_Atoi(tok);

  tok = strtok(NULL, " ");
  data = CMD_Atoi(tok);

  DAC_SetData((uint8_t)channel, (uint16_t)data);
}


/**
 * @brief   Print command list and arguments.
 */
void CMD_Help(char* args)
{
  int i;
  LOGI("-------------- Command List -----------------");
  for ( i = 0 ; i < CMD_TYPE_MAX ; i++ ) {
    LOGI("%s %s", CMD_list[i], CMD_info[i]);
  }
  LOGI("---------------------------------------------");
}


void CMD_IRQHandler(CMD_IRQTypekDef type)
{
  /* Why don't use LOG function? */
  osMessagePut(hCmdMessage, type, 100);
}

///**
//  * @brief  Rx Transfer completed callbacks.
//  */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//  if ( huart->Instance == CMD_UART_INST.Instance ) {
//    osMessagePut(hCmdMessage, CMD_IRQ_TYPE_RX, 100);
//  }
//}
//
///**
//  * @brief  UART error callbacks.
//  */
//void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
//{
//  if ( huart->Instance == CMD_UART_INST.Instance ) {
//
//    LOGE("DMA Error: %d", huart->ErrorCode);
//
////    osMessagePut(hCmdMessage, CMD_IRQ_TYPE_ERR, 100);
////    HAL_UART_DeInit(huart);
////    HAL_UART_Init(huart);
//  }
//}
