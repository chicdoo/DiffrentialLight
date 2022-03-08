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

/* Private define --------------------------------------------------------------- */
typedef void (*pCMD)(char*);

/* Exported variables ----------------------------------------------------------- */


/* Private variables ------------------------------------------------------------ */
static osMessageQId   hCmdMessage;
static osThreadId     hCmdThread;

static char cmdData[CMD_DATA_SIZE];

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
  osThreadDef(CmdThread, CMD_Thread, osPriorityAboveNormal, 0, 512);
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

    if ( HAL_UART_Receive_DMA(&CMD_UART_INST, (uint8_t*)cmdData, CMD_DATA_SIZE) == HAL_OK ) {
      /* DMA function is non-blocking. Therefore make block by message queue. */
      event = osMessageGet(hCmdMessage, osWaitForever);

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
 * @brief   Set PWM frequency. Channel is xx ~ xx. Frequency range is xx ~ xx.
 */
void CMD_SetPWMHz(char* args)
{


}

/**
 * @brief   Set PWM duty. Channel is xx ~ xx. Duty range is xx ~ xx.
 */
void CMD_SetPWMDuty(char* args)
{


}

/**
 * @brief   Set LED off. Channel is xx ~ xx.
 */
void CMD_SetLEDOff(char* args)
{


}

/**
 * @brief   Set LED on. Channel is xx ~ xx.
 */
void CMD_SetLEDOn(char* args)
{


}
