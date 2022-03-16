/* ------------------------------------------------------------------------------ *
 * @file        inc/command.h
 * @author      Eungdoo Kim
 * @version     v0.1
 * @date        2022-03-08
 * @brief       Receive command from PC by RS232. And process it.
 * ------------------------------------------------------------------------------ *
 * 2022-03-08   Create.
 * 2022-03-11   Debugging UART DMA rx. ErrorCode is 8 (overrun).
 *              Implements PWM functions. Not completed.
 * 2022-03-17   Fix UART DMA not working. Should be initialize UART before DMA.
 * ------------------------------------------------------------------------------ */

/* Define to prevent recursive inclusion ---------------------------------------- */
#ifndef __COMMAND_H__
#define __COMMAND_H__

/* Includes --------------------------------------------------------------------- */
#include "config.h"
#include "stdint.h"
#include "usart.h"

/* Exported constants ----------------------------------------------------------- */


/* Private define --------------------------------------------------------------- */
/* If want to change RS232 to other, change these. */
#define CMD_UART_PORT     USART1
#define CMD_UART_INST     CFG_UART_INTERFACE

#define CMD_QUEUE_SIZE    16
#define CMD_DATA_SIZE     128

/* Exported types --------------------------------------------------------------- */
typedef enum
{
  CMD_IRQ_TYPE_RX,
  CMD_IRQ_TYPE_ERR
} CMD_IRQTypekDef;

/* Move command definition to command.c, because of compile error. */
//typedef enum
//{
//  CMD_TYPE_SET_PWM_HZ,
//  CMD_TYPE_SET_PWM_DUTY,
//  CMD_TYPE_SET_LED_OFF,
//  CMD_TYPE_SET_LED_ON,
//  /* If need new command, add here. */
//  CMD_TYPE_HELP,
//  CMD_TYPE_MAX
//} CMD_TypeDef;
//
//char* CMD_list[CMD_TYPE_MAX] = {
//  [CMD_TYPE_SET_PWM_HZ]       = "setPWMHz",
//  [CMD_TYPE_SET_PWM_DUTY]     = "setPWMDuty",
//  [CMD_TYPE_SET_LED_OFF]      = "setLEDOff",
//  [CMD_TYPE_SET_LED_ON]       = "setLEDOn",
//  /* If need new command, add here. */
//  [CMD_TYPE_HELP]             = "help"
//};
//
//char* CMD_info[CMD_TYPE_MAX] = {
//  [CMD_TYPE_SET_PWM_HZ]       = "[channel] [frequency]",
//  [CMD_TYPE_SET_PWM_DUTY]     = "[channel] [duty 0~100]",
//  [CMD_TYPE_SET_LED_OFF]      = "[channel]",
//  [CMD_TYPE_SET_LED_ON]       = "[channel]",
//  /* If need new command, add here. */
//  [CMD_TYPE_HELP]             = ""
//};
//
//void (*CMD_functions[CMD_TYPE_MAX])(char* args) = {
//  [CMD_TYPE_SET_PWM_HZ]       = &CMD_SetPWMHz,
//  [CMD_TYPE_SET_PWM_DUTY]     = &CMD_SetPWMDuty,
//  [CMD_TYPE_SET_LED_OFF]      = &CMD_SetLEDOff,
//  [CMD_TYPE_SET_LED_ON]       = &CMD_SetLEDOn,
//  /* If need new command, add here. */
//  [CMD_TYPE_HELP]             = &CMD_Help
//};

/* Exported functions -------------------------------------------------------------- */
void CMD_Init();
void CMD_DeInit();
void CMD_IRQHandler(CMD_IRQTypekDef type);

/* Private functions --------------------------------------------------------------- */
void CMD_Thread(const void* arg);
uint32_t CMD_Atoi(char* strNum);



#endif /* __COMMAND_H__ */
