/* ------------------------------------------------------------------------------ *
 * @file        inc/log.h
 * @author      Eungdoo Kim
 * @version     v0.0
 * @date        2022-03-08
 * @brief       Define log format like [time][function name][log level][content].
 * ------------------------------------------------------------------------------ *
 * 2022-03-08   Create.
 * ------------------------------------------------------------------------------ */


/* ------------------------------------------------------------------------------ *
 * If plan to use log, please check each thread stack size. It should be enough.  *
 * ------------------------------------------------------------------------------ */

/* Define to prevent recursive inclusion ---------------------------------------- */
#ifndef __LOG_H__
#define __LOG_H__

/* Includes --------------------------------------------------------------------- */
#include "config.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "main.h"

/* Define log property; could be set -------------------------------------------- */
#define LOG_UART_PORT     USART1
#define LOG_UART_INST     CFG_UART_INTERFACE

#define LOG_QUEUE_SIZE    8
#define LOG_DATA_SIZE     128

#define LOG_WAIT_TIMEOUT  100
#define LOG_MSG_TIMEOUT   100
#define LOG_SEND_TIMEOUT  100

#define LOG_LEVEL         CFG_LOG_LEVEL

/* Private functions ------------------------------------------------------------ */
void LOG_Init();
void LOG_DeInit();
void LOG_Thread(const void*);
char* LOG_GetTime();
void LOG_Push(char level, const char* func, char* message, ...);


/* Define macro ------------------------------------------------------------------ */
#if   (LOG_LEVEL == 0)
#define LOGV(fmt,args...)   do {} while(0)
#define LOGD(fmt,args...)   do {} while(0)
#define LOGI(fmt,args...)   do {} while(0)
#define LOGE(fmt,args...)   do {} while(0)

#elif (LOG_LEVEL == 1)
#define LOGV(fmt,args...)   do {} while(0)
#define LOGD(fmt,args...)   do {} while(0)
#define LOGI(fmt,args...)   do {} while(0)
#define LOGE(fmt,args...)   do { LOG_Push('E',__FUNCTION__,fmt,##args); } while(0)

#elif (LOG_LEVEL == 2)
#define LOGV(fmt,args...)   do {} while(0)
#define LOGD(fmt,args...)   do {} while(0)
#define LOGI(fmt,args...)   do { LOG_Push('I',__FUNCTION__,fmt,##args); } while(0)
#define LOGE(fmt,args...)   do { LOG_Push('E',__FUNCTION__,fmt,##args); } while(0)

#elif (LOG_LEVEL == 3)
#define LOGV(fmt,args...)   do {} while(0)
#define LOGD(fmt,args...)   do { LOG_Push('D',__FUNCTION__,fmt,##args); } while(0)
#define LOGI(fmt,args...)   do { LOG_Push('I',__FUNCTION__,fmt,##args); } while(0)
#define LOGE(fmt,args...)   do { LOG_Push('E',__FUNCTION__,fmt,##args); } while(0)

#elif (LOG_LEVEL == 4)
#define LOGV(fmt,args...)   do { LOG_Push('V',__FUNCTION__,fmt,##args); } while(0)
#define LOGD(fmt,args...)   do { LOG_Push('D',__FUNCTION__,fmt,##args); } while(0)
#define LOGI(fmt,args...)   do { LOG_Push('I',__FUNCTION__,fmt,##args); } while(0)
#define LOGE(fmt,args...)   do { LOG_Push('E',__FUNCTION__,fmt,##args); } while(0)
#endif

#define LOGA(fmt,args...)   do { LOG_Push('A',__FUNCTION__,fmt,##args); } while(0)


#endif  /* __LOG_H__ */
