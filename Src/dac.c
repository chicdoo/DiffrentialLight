/* ------------------------------------------------------------------------------ *
 * @file        inc/dac.c
 * @author      Eungdoo Kim
 * @version     v0.0
 * @date        2022-06-14
 * @brief       Control DAC(BU2505FV).
 * ------------------------------------------------------------------------------ *
 * @reference   See inc/dac.h
 * ------------------------------------------------------------------------------ */

#include "dac.h"


extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi3;
extern SPI_HandleTypeDef hspi4;
extern SPI_HandleTypeDef hspi5;
extern SPI_HandleTypeDef hspi6;


static DAC_Data dac_ch[6];
static int DAC_AdjustBit(uint8_t addr, uint16_t* in, uint8_t* out, int len);

/**
 * @brief   Initialize all DAC(BU2505FV) as 0v.
 */
void DAC_BU2505FV_Init()
{
  /* Address: LSB first */
  /* Data: MSB first */
  /* 14bits x 3 = 42bits = 5.25 bytes */
  /* SPI1 - 2 */
  /* SPI2 - 2 */
  /* SPI3 - 2 */
  /* SPI4 - 2 */
  /* SPI5 - 5 */
  /* SPI6 - 5 */

  uint8_t out[16] = {0, };
  int out_len = 0;

  HAL_GPIO_WritePin(LED_OFF1_GPIO_Port, LED_OFF1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF2_GPIO_Port, LED_OFF2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF3_GPIO_Port, LED_OFF3_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF4_GPIO_Port, LED_OFF4_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF5_GPIO_Port, LED_OFF5_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF6_GPIO_Port, LED_OFF6_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF7_GPIO_Port, LED_OFF7_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF8_GPIO_Port, LED_OFF8_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF9_GPIO_Port, LED_OFF9_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF10_GPIO_Port, LED_OFF10_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF11_GPIO_Port, LED_OFF11_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF12_GPIO_Port, LED_OFF12_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF13_GPIO_Port, LED_OFF13_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF14_GPIO_Port, LED_OFF14_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF15_GPIO_Port, LED_OFF15_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF16_GPIO_Port, LED_OFF16_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF17_GPIO_Port, LED_OFF17_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LED_OFF18_GPIO_Port, LED_OFF18_Pin, GPIO_PIN_RESET);

  for ( int i = 0 ; i < 6 ; i++ ) {
    for ( int j = 0 ; j < 5 ; j++ ) {
      dac_ch[i].data[j] = 0x0000;
    }
  }

  /* Set SPI1 */
  out_len = DAC_AdjustBit(DAC_ADDR, dac_ch[0].data, out, 2);
  HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi1, out, out_len, 100);
  HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_SET);

  /* Set SPI2 */
  out_len = DAC_AdjustBit(DAC_ADDR, dac_ch[1].data, out, 2);
  HAL_GPIO_WritePin(DA2_EN_GPIO_Port, DA2_EN_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2, out, out_len, 100);
  HAL_GPIO_WritePin(DA2_EN_GPIO_Port, DA2_EN_Pin, GPIO_PIN_SET);

  /* Set SPI3 */
  out_len = DAC_AdjustBit(DAC_ADDR, dac_ch[2].data, out, 2);
  HAL_GPIO_WritePin(DA3_EN_GPIO_Port, DA3_EN_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi3, out, out_len, 100);
  HAL_GPIO_WritePin(DA3_EN_GPIO_Port, DA3_EN_Pin, GPIO_PIN_SET);

  /* Set SPI4 */
  out_len = DAC_AdjustBit(DAC_ADDR, dac_ch[3].data, out, 2);
  HAL_GPIO_WritePin(DA4_EN_GPIO_Port, DA4_EN_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi4, out, out_len, 100);
  HAL_GPIO_WritePin(DA4_EN_GPIO_Port, DA4_EN_Pin, GPIO_PIN_SET);

  /* Set SPI5 */
  out_len = DAC_AdjustBit(DAC_ADDR, dac_ch[4].data, out, 5);
  HAL_GPIO_WritePin(DA5_EN_GPIO_Port, DA5_EN_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi5, out, out_len, 100);
  HAL_GPIO_WritePin(DA5_EN_GPIO_Port, DA5_EN_Pin, GPIO_PIN_SET);

  /* Set SPI6 */
  out_len = DAC_AdjustBit(DAC_ADDR, dac_ch[5].data, out, 5);
  HAL_GPIO_WritePin(DA6_EN_GPIO_Port, DA6_EN_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi6, out, out_len, 100);
  HAL_GPIO_WritePin(DA6_EN_GPIO_Port, DA6_EN_Pin, GPIO_PIN_SET);

  HAL_GPIO_WritePin(LED_OFF1_GPIO_Port, LED_OFF1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF2_GPIO_Port, LED_OFF2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF3_GPIO_Port, LED_OFF3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF4_GPIO_Port, LED_OFF4_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF5_GPIO_Port, LED_OFF5_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF6_GPIO_Port, LED_OFF6_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF7_GPIO_Port, LED_OFF7_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF8_GPIO_Port, LED_OFF8_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF9_GPIO_Port, LED_OFF9_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF10_GPIO_Port, LED_OFF10_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF11_GPIO_Port, LED_OFF11_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF12_GPIO_Port, LED_OFF12_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF13_GPIO_Port, LED_OFF13_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF14_GPIO_Port, LED_OFF14_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF15_GPIO_Port, LED_OFF15_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF16_GPIO_Port, LED_OFF16_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF17_GPIO_Port, LED_OFF17_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_OFF18_GPIO_Port, LED_OFF18_Pin, GPIO_PIN_SET);
}



/**
 * @brief   Set data each channel. Here channel range is from 1 to 18.
 */
void DAC_SetData(uint8_t ch, uint16_t data)
{
  uint8_t out[16] = {0, };
  int out_len = 0;

  LOGI("ch: %d, data: 0x%04X", ch, data);

  switch ( ch ) {

  case 1:
    dac_ch[0].data[0] = data;
    break;
  case 2:
    dac_ch[0].data[1] = data;
    break;
  case 3:
    dac_ch[1].data[0] = data;
    break;
  case 4:
    dac_ch[1].data[1] = data;
    break;
  case 5:
    dac_ch[2].data[0] = data;
    break;
  case 6:
    dac_ch[2].data[1] = data;
    break;
  case 7:
    dac_ch[3].data[0] = data;
    break;
  case 8:
    dac_ch[3].data[1] = data;
    break;
  case 9:
    dac_ch[4].data[0] = data;
    break;
  case 10:
    dac_ch[4].data[1] = data;
    break;
  case 11:
    dac_ch[4].data[2] = data;
    break;
  case 12:
    dac_ch[4].data[3] = data;
    break;
  case 13:
    dac_ch[4].data[4] = data;
    break;
  case 14:
    dac_ch[5].data[0] = data;
    break;
  case 15:
    dac_ch[5].data[1] = data;
    break;
  case 16:
    dac_ch[5].data[2] = data;
    break;
  case 17:
    dac_ch[5].data[3] = data;
    break;
  case 18:
    dac_ch[5].data[4] = data;
    break;
  }

  switch ( ch ) {

  case 1:
  case 2:
    out_len = DAC_AdjustBit(DAC_ADDR, dac_ch[0].data, out, 2);
    LOGE("%d %02X %02X %02X %02X", out_len, out[0], out[1], out[2], out[3]);
    HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, out, out_len, 100);
    HAL_GPIO_WritePin(DA1_EN_GPIO_Port, DA1_EN_Pin, GPIO_PIN_SET);
    break;

  case 3:
  case 4:
    out_len = DAC_AdjustBit(DAC_ADDR, dac_ch[1].data, out, 2);
    HAL_GPIO_WritePin(DA2_EN_GPIO_Port, DA2_EN_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi2, out, out_len, 100);
    HAL_GPIO_WritePin(DA2_EN_GPIO_Port, DA2_EN_Pin, GPIO_PIN_SET);
    break;

  case 5:
  case 6:
    out_len = DAC_AdjustBit(DAC_ADDR, dac_ch[2].data, out, 2);
    HAL_GPIO_WritePin(DA3_EN_GPIO_Port, DA3_EN_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi3, out, out_len, 100);
    HAL_GPIO_WritePin(DA3_EN_GPIO_Port, DA3_EN_Pin, GPIO_PIN_SET);
    break;

  case 7:
  case 8:
    out_len = DAC_AdjustBit(DAC_ADDR, dac_ch[3].data, out, 2);
    HAL_GPIO_WritePin(DA4_EN_GPIO_Port, DA4_EN_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi4, out, out_len, 100);
    HAL_GPIO_WritePin(DA4_EN_GPIO_Port, DA4_EN_Pin, GPIO_PIN_SET);
    break;

  case 9:
  case 10:
  case 11:
  case 12:
  case 13:
    out_len = DAC_AdjustBit(DAC_ADDR, dac_ch[4].data, out, 5);
    HAL_GPIO_WritePin(DA5_EN_GPIO_Port, DA5_EN_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi5, out, out_len, 100);
    HAL_GPIO_WritePin(DA5_EN_GPIO_Port, DA5_EN_Pin, GPIO_PIN_SET);
    break;

  case 14:
  case 15:
  case 16:
  case 17:
  case 18:
    out_len = DAC_AdjustBit(DAC_ADDR, dac_ch[5].data, out, 5);
    HAL_GPIO_WritePin(DA6_EN_GPIO_Port, DA6_EN_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi6, out, out_len, 100);
    HAL_GPIO_WritePin(DA6_EN_GPIO_Port, DA6_EN_Pin, GPIO_PIN_SET);
    break;
  }
}

/**
 * @brief   DAC packet size is 14bits. But this MUC support only 8's multi number
 *          can be sent. So here makes packing from 14bits data.
 */
static int DAC_AdjustBit(uint8_t addr, uint16_t* in, uint8_t* out, int len)
{
  uint16_t data = 0x0000;
  uint8_t rev_addr = 0x00;
  uint32_t mask = 0x01;
  int out_len = 14 * len / 8;

  if ( ((14 * len) % 8) != 0 ) {
    out_len++;
  }

  for ( int i = 0 ; i < 4 ; i++ ) {

    if ( ((uint8_t)mask << i) & addr ) {
      rev_addr += (uint8_t)mask << (4 - i - 1);
    }
  }

  for ( int i = len-1 ; i >= 0 ; --i ) {

    if ( in[i] >= ((uint16_t)mask << 10) ) {
      LOGE("Data range overflow - %d, %d", i, in[i]);
      return -1;
    }

    for ( int j = 0 ; j < out_len - 1 ; ++j ) {
      out[j] = out[j+1];
    }

    for ( int j = 0 ; j < out_len - 1 ; ++j ) {
      out[j] = ((out[j+1]&0xFC) >> 2) | (out[j] << 6);
    }

    data = ((uint16_t)rev_addr << 10) | in[i];
    out[out_len-2] = (uint8_t)((data & 0xFF00) >> 8);
    out[out_len-1] = (uint8_t)((data & 0x00FF) >> 0);
  }

  return out_len;
}
