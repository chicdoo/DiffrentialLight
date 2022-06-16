/* ------------------------------------------------------------------------------ *
 * @file        inc/dac.h
 * @author      Eungdoo Kim
 * @version     v0.0
 * @date        2022-06-14
 * @brief       Control DAC(BU2505FV).
 * ------------------------------------------------------------------------------ *
 * @reference
 * ------------------------------------------------------------------------------ */


#include "spi.h"
#include "log.h"

#define DAC_ADDR  0x01



typedef struct {

  uint16_t data[5];
} DAC_Data;


void DAC_BU2505FV_Init();
void DAC_SetData(uint8_t ch, uint16_t data);
