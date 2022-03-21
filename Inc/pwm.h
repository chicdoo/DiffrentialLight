/* ------------------------------------------------------------------------------ *
 * @file        src/pwm.h
 * @author      Eungdoo Kim
 * @version     v0.0
 * @date        2022-03-22
 * @brief       Set pwm hz and duty.
 * ------------------------------------------------------------------------------ *
 * @reference   See inc/pwm.h
 * ------------------------------------------------------------------------------ *
 * 2022-03-22   Create.
 * ------------------------------------------------------------------------------ */

/* Define to prevent recursive inclusion ---------------------------------------- */
#ifndef __PWM_H__
#define __PWM_H__

/* Includes --------------------------------------------------------------------- */
#include "config.h"
#include "stdio.h"
#include "tim.h"


/* Private functions ------------------------------------------------------------ */
void PWM_Init();
void PWM_DeInit();
void PWM_SetDuty(int channel, int duty);












#endif /* __PWM_H__ */
