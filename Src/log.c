/* ------------------------------------------------------------------------------ *
 * @file        inc/log.h
 * @author      Eungdoo Kim
 * @version     v0.0
 * @date        2022-03-08
 * @brief       Define log format like [time][function name][log level][content].
 * ------------------------------------------------------------------------------ *
 * @reference   See inc/log.h
 * ------------------------------------------------------------------------------ */

/* Includes --------------------------------------------------------------------- */
#include "log.h"
#include <cmsis_os.h>
#include "stdarg.h"
#include "usart.h"
#include "rtc.h"

/* Private define --------------------------------------------------------------- */



/* Private variables ------------------------------------------------------------ */
osThreadId          hLogThread;
osMessageQId        hLogQueue;
osMutexId           hLogMutex;
int                 i32LogIndex;
char                strLogBuffer[LOG_DATA_SIZE];
char                strLogData[LOG_QUEUE_SIZE][LOG_DATA_SIZE];
char                strCurrentTime[16]; /* hh:MM:ss */

/* Exported variables ----------------------------------------------------------- */
extern UART_HandleTypeDef huart1; /* defined in src/usart.c */

/* Exported functions ----------------------------------------------------------- */


/* Private functions ------------------------------------------------------------ */

/**
 * @brief   Initialize log functions.
 */
void LOG_Init()
{
  osMutexDef(LogMutex);
  hLogMutex = osMutexCreate(osMutex(LogMutex));

  osMessageQDef(LogQueue, LOG_QUEUE_SIZE, uint8_t*);
  hLogQueue = osMessageCreate(osMessageQ(LogQueue), NULL);

  osThreadDef(LogThread, LOG_Thread, osPriorityHigh, 0, 512);
  hLogThread = osThreadCreate(osThread(LogThread), NULL);
}

/**
 * @brief   De-initialize log functions. But not called.
 */
void LOG_DeInit()
{
  osThreadSuspend(hLogThread);
  osMessageDelete(hLogQueue);
  osMutexDelete(hLogMutex);
}

/**
 * @brief   Thread for log. All log messages will be stored into LogQueue.
 *          In this thread, process getting message from queue and transmit by UART.
 */
void LOG_Thread(const void* args)
{
  osEvent event;
  uint8_t* data;
  uint16_t len;

  while ( 1 ) {

    event = osMessageGet(hLogQueue, osWaitForever);

    if ( event.status == osEventMessage ) {

      data = (uint8_t*)event.value.p;
      len = strlen((char*)data);
      HAL_UART_Transmit(&huart1, data, len, LOG_SEND_TIMEOUT);
    }
  }
}

/**
 * @brief   Push Logs message made in other thread, into log queue.
 */
void LOG_Push(char level, const char* func, char* message, ...)
{
  char msg[256] = {0, };
  __va_list args;

  if ( osMessageAvailableSpace(hLogQueue) == 0 ) {
    /* Message will be ignored. */
    return;
  }

  /* For not fixed number arguments */
  va_start(args, message);
  vsprintf(msg, message, args);
  va_end(args);

  if ( osMutexWait(hLogMutex, LOG_WAIT_TIMEOUT) == osOK ) {
    sprintf(strLogData[i32LogIndex], "[%s][%s][%c] %s\r\n", LOG_GetTime(), func, level, msg);
    osMessagePut(hLogQueue, (uint32_t)strLogData[i32LogIndex], LOG_WAIT_TIMEOUT);
    i32LogIndex = (i32LogIndex + 1) % LOG_QUEUE_SIZE;
    osMutexRelease(hLogMutex);
  }
}

/**
 * @brief   Get system time. This will be sent with log message.
 */
char* LOG_GetTime()
{
  uint32_t hour, min, sec, sub;

  uint32_t time = HAL_GetTick();

  sub = time % 1000;  /* ms */
  time = time / 1000;

  sec = time % 60;
  time = time / 60;

  min = time % 60;
  time = time / 60;

  hour = time % 24;

  sprintf(strCurrentTime, "%02d:%02d:%02d.%03d", (int)hour, (int)min, (int)sec, (int)sub);

  return strCurrentTime;
}
