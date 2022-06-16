/* ------------------------------------------------------------------------------ *
 * @file        inc/config.h
 * @author      Eungdoo Kim
 * @version     v0.0
 * @date        2022-03-09
 * @brief       Set DiffrentialLight project properties.
 * ------------------------------------------------------------------------------ *
 * 2022-03-09   Create.
 * 2022-03-22   Add configure using RS485 possible.
 * ------------------------------------------------------------------------------ */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#define TRUE                1
#define FALSE               0


/* Log level range is 0 ~ 4. */
#define CFG_LOG_LEVEL       3

/* UART interface */
/* huart1 -> RS232
 * huart2 -> RS485
 * huart3 -> DEV  */
#define CFG_UART_INTERFACE  huart1

/* Enable or disable fan */
#define CFG_FAN_ENABLE      FALSE

/* Enable or Disable LED channel, TRUE or FALSE */
#define CFG_LED1_ENABLE     TRUE
#define CFG_LED2_ENABLE     TRUE
#define CFG_LED3_ENABLE     TRUE
#define CFG_LED4_ENABLE     TRUE
#define CFG_LED5_ENABLE     TRUE
#define CFG_LED6_ENABLE     TRUE
#define CFG_LED7_ENABLE     TRUE
#define CFG_LED8_ENABLE     TRUE
#define CFG_LED9_ENABLE     TRUE
#define CFG_LED10_ENABLE    TRUE
#define CFG_LED11_ENABLE    TRUE
#define CFG_LED12_ENABLE    TRUE
#define CFG_LED13_ENABLE    TRUE
#define CFG_LED14_ENABLE    TRUE
#define CFG_LED15_ENABLE    TRUE
#define CFG_LED16_ENABLE    TRUE
#define CFG_LED17_ENABLE    TRUE
#define CFG_LED18_ENABLE    TRUE

#endif /* __CONFIG_H__ */
