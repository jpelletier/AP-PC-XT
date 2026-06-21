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
#include "stm32f4xx_hal.h"

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
#define nDACK2_Pin GPIO_PIN_2
#define nDACK2_GPIO_Port GPIOE
#define nDACK3_Pin GPIO_PIN_3
#define nDACK3_GPIO_Port GPIOE
#define TC_Pin GPIO_PIN_5
#define TC_GPIO_Port GPIOE
#define nAEN_Pin GPIO_PIN_13
#define nAEN_GPIO_Port GPIOC
#define D0_Pin GPIO_PIN_0
#define D0_GPIO_Port GPIOC
#define D1_Pin GPIO_PIN_1
#define D1_GPIO_Port GPIOC
#define D2_Pin GPIO_PIN_2
#define D2_GPIO_Port GPIOC
#define D3_Pin GPIO_PIN_3
#define D3_GPIO_Port GPIOC
#define D4_Pin GPIO_PIN_4
#define D4_GPIO_Port GPIOC
#define D5_Pin GPIO_PIN_5
#define D5_GPIO_Port GPIOC
#define IO_RDY_Pin GPIO_PIN_0
#define IO_RDY_GPIO_Port GPIOB
#define nIO_CHK_Pin GPIO_PIN_1
#define nIO_CHK_GPIO_Port GPIOB
#define DRQ1_Pin GPIO_PIN_7
#define DRQ1_GPIO_Port GPIOE
#define DRQ2_Pin GPIO_PIN_8
#define DRQ2_GPIO_Port GPIOE
#define DRQ3_Pin GPIO_PIN_9
#define DRQ3_GPIO_Port GPIOE
#define A16_Pin GPIO_PIN_12
#define A16_GPIO_Port GPIOE
#define A17_Pin GPIO_PIN_13
#define A17_GPIO_Port GPIOE
#define A18_Pin GPIO_PIN_14
#define A18_GPIO_Port GPIOE
#define A19_Pin GPIO_PIN_15
#define A19_GPIO_Port GPIOE
#define IRQ2_Pin GPIO_PIN_10
#define IRQ2_GPIO_Port GPIOB
#define IRQ3_Pin GPIO_PIN_11
#define IRQ3_GPIO_Port GPIOB
#define IRQ4_Pin GPIO_PIN_12
#define IRQ4_GPIO_Port GPIOB
#define IRQ5_Pin GPIO_PIN_13
#define IRQ5_GPIO_Port GPIOB
#define IRQ6_Pin GPIO_PIN_14
#define IRQ6_GPIO_Port GPIOB
#define IRQ7_Pin GPIO_PIN_15
#define IRQ7_GPIO_Port GPIOB
#define A8_Pin GPIO_PIN_8
#define A8_GPIO_Port GPIOD
#define A9_Pin GPIO_PIN_9
#define A9_GPIO_Port GPIOD
#define A10_Pin GPIO_PIN_10
#define A10_GPIO_Port GPIOD
#define A11_Pin GPIO_PIN_11
#define A11_GPIO_Port GPIOD
#define A12_Pin GPIO_PIN_12
#define A12_GPIO_Port GPIOD
#define A13_Pin GPIO_PIN_13
#define A13_GPIO_Port GPIOD
#define A14_Pin GPIO_PIN_14
#define A14_GPIO_Port GPIOD
#define A15_Pin GPIO_PIN_15
#define A15_GPIO_Port GPIOD
#define D6_Pin GPIO_PIN_6
#define D6_GPIO_Port GPIOC
#define D7_Pin GPIO_PIN_7
#define D7_GPIO_Port GPIOC
#define nMEMW_Pin GPIO_PIN_8
#define nMEMW_GPIO_Port GPIOC
#define nMEMR_Pin GPIO_PIN_9
#define nMEMR_GPIO_Port GPIOC
#define nIOW_Pin GPIO_PIN_10
#define nIOW_GPIO_Port GPIOC
#define nIOR_Pin GPIO_PIN_11
#define nIOR_GPIO_Port GPIOC
#define ALE_Pin GPIO_PIN_12
#define ALE_GPIO_Port GPIOC
#define A0_Pin GPIO_PIN_0
#define A0_GPIO_Port GPIOD
#define A1_Pin GPIO_PIN_1
#define A1_GPIO_Port GPIOD
#define A2_Pin GPIO_PIN_2
#define A2_GPIO_Port GPIOD
#define A3_Pin GPIO_PIN_3
#define A3_GPIO_Port GPIOD
#define A4_Pin GPIO_PIN_4
#define A4_GPIO_Port GPIOD
#define A5_Pin GPIO_PIN_5
#define A5_GPIO_Port GPIOD
#define A6_Pin GPIO_PIN_6
#define A6_GPIO_Port GPIOD
#define A7_Pin GPIO_PIN_7
#define A7_GPIO_Port GPIOD
#define RESET_Pin GPIO_PIN_9
#define RESET_GPIO_Port GPIOB
#define nDACK0_Pin GPIO_PIN_0
#define nDACK0_GPIO_Port GPIOE
#define nDACK1_Pin GPIO_PIN_1
#define nDACK1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
