/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "stm32l4xx_ll_adc.h"
#include "stm32l4xx_ll_dma.h"
#include "stm32l4xx_ll_crs.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_cortex.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_pwr.h"
#include "stm32l4xx_ll_rtc.h"
#include "stm32l4xx_ll_spi.h"
#include "stm32l4xx_ll_tim.h"
#include "stm32l4xx_ll_usart.h"
#include "stm32l4xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DEBUG_LED2_Pin LL_GPIO_PIN_2
#define DEBUG_LED2_GPIO_Port GPIOE
#define DEBUG_LED3_Pin LL_GPIO_PIN_3
#define DEBUG_LED3_GPIO_Port GPIOE
#define DEBUG_LED4_Pin LL_GPIO_PIN_4
#define DEBUG_LED4_GPIO_Port GPIOE
#define DEBUG_LED5_Pin LL_GPIO_PIN_5
#define DEBUG_LED5_GPIO_Port GPIOE
#define EN_5V_BOOST_PM_Pin LL_GPIO_PIN_2
#define EN_5V_BOOST_PM_GPIO_Port GPIOB
#define EN_5V_PM_Pin LL_GPIO_PIN_7
#define EN_5V_PM_GPIO_Port GPIOE
#define EN_UNREG1_PM_Pin LL_GPIO_PIN_8
#define EN_UNREG1_PM_GPIO_Port GPIOE
#define EN_UNREG2_PM_Pin LL_GPIO_PIN_9
#define EN_UNREG2_PM_GPIO_Port GPIOE
#define EN_3V3_1_PM_Pin LL_GPIO_PIN_14
#define EN_3V3_1_PM_GPIO_Port GPIOE
#define EN_3V3_2_BUCK_PM_Pin LL_GPIO_PIN_15
#define EN_3V3_2_BUCK_PM_GPIO_Port GPIOE
#define EN_MCU_3V3_PM_Pin LL_GPIO_PIN_8
#define EN_MCU_3V3_PM_GPIO_Port GPIOD
#define EN_MCU_BUCK_PM_Pin LL_GPIO_PIN_9
#define EN_MCU_BUCK_PM_GPIO_Port GPIOD
#define EN_3V3_2_PM_Pin LL_GPIO_PIN_10
#define EN_3V3_2_PM_GPIO_Port GPIOD
#define EN_3V3_1_BUCK_PM_Pin LL_GPIO_PIN_11
#define EN_3V3_1_BUCK_PM_GPIO_Port GPIOD
#define DONE_Pin LL_GPIO_PIN_8
#define DONE_GPIO_Port GPIOC
#define WAKE_Pin LL_GPIO_PIN_9
#define WAKE_GPIO_Port GPIOC
#define DEBUG_LED1_Pin LL_GPIO_PIN_1
#define DEBUG_LED1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
