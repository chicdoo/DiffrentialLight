/* ------------------------------------------------------------------------------ *
 * @file        inc/etc.c
 * @author      Eungdoo Kim
 * @version     v0.0
 * @date        2022-03-22
 * @brief       Setup minor things.
 * ------------------------------------------------------------------------------ *
 * @reference   See inc/etc.h
 * ------------------------------------------------------------------------------ */

/* Includes --------------------------------------------------------------------- */
#include "etc.h"
#include "gpio.h"

/* Private functions ------------------------------------------------------------ */
void ETC_Init()
{
  if ( CFG_FAN_ENABLE ) {
    ETC_FanEnable(TRUE);
  }
}

void ETC_FanEnable(int enable)
{
  if ( enable == TRUE ) {
    HAL_GPIO_WritePin(FAN_EN_GPIO_Port, FAN_EN_Pin, GPIO_PIN_SET);
  }
  else {
    HAL_GPIO_WritePin(FAN_EN_GPIO_Port, FAN_EN_Pin, GPIO_PIN_RESET);
  }
}
