/* ------------------------------------------------------------------------------ *
 * @file        src/pwm.c
 * @author      Eungdoo Kim
 * @version     v0.0
 * @date        2022-03-22
 * @brief       Set pwm hz and duty.
 * ------------------------------------------------------------------------------ *
 * @reference   See inc/pwm.h
 * ------------------------------------------------------------------------------ */

/* Includes ------------------------------------------------------------------*/
#include "pwm.h"
#include "log.h"


/* Private variables ------------------------------------------------------------ */


/* Exported variables ----------------------------------------------------------- */
/* PWM_CH3 and PWM_CH4 are not supported. */
extern TIM_HandleTypeDef htim8; /* PWM_CH1, PWM_CH2 */
extern TIM_HandleTypeDef htim9; /* PWM_CH5, PWM_CH6 */


/* Exported functions ----------------------------------------------------------- */


/* Private functions ------------------------------------------------------------ */

/**
 * @brief   Initialize PWM functions.
 *          This function must be called after MX_TIM8_Init and MX_TIM9_Init called.
 */
void PWM_Init()
{
  LOGD("[+]");

  /* First of all start all PWM, and set duty zero. */
  htim8.Instance->CNT = 0;
  htim8.Instance->CCR1 = 0; /* PWM_CH1 duty */
  htim8.Instance->CCR4 = 0; /* PWM_CH4 duty */

  htim9.Instance->CNT = 0;
  htim9.Instance->CCR1 = 0; /* PWM_CH5 duty */
  htim9.Instance->CCR2 = 0; /* PWM_CH6 duty */

  /* Start PWM CH1 ~ CH4, but CH2 and CH4 not supported. */
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
  /* Start PWM CH5 ~ CH6. */
  HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_ALL);

  LOGD("[-]");
}

/**
 * @brief   De-initialize PWM functions.
 */
void PWM_DeInit()
{
  LOGD("[+]");

  HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_ALL);
  HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_ALL);

  LOGD("[-]");
}

/**
 * @brief   Set PWM duty. Duty range is from 0 to 4000.
 */
void PWM_SetDuty(int channel, int duty)
{
  LOGD("[+]");

  LOGI("CH: %d, Duty: %d", channel, duty);

  if ( duty < 0 || duty > 4000 ) {
    LOGE("Invalid duty range - %d", duty);
  }
  else {
    switch ( channel ) {

    case 1:
      htim8.Instance->CCR1 = duty;
      break;

    case 2:
      LOGE("Currently not support channel 2");
      break;

    case 3:
      LOGE("Currently not support channel 3");

    case 4:
      htim8.Instance->CCR4 = duty;
      break;

    case 5:
      htim9.Instance->CCR1 = duty;
      break;

    case 6:
      htim9.Instance->CCR2 = duty;
      break;

    default:
      LOGE("Invalid channel - %d", channel);
    }
  }

  LOGD("[-]");
}
