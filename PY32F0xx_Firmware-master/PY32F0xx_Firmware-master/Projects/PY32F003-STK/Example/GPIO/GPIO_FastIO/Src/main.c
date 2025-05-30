/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
#define APP_GPIO_TOGGLE()  {GPIOB->BSRR = u32High;\
                            GPIOB->BSRR = u32Low; \
                            GPIOB->BSRR = u32High;\
                            GPIOB->BSRR = u32Low; \
                            GPIOB->BSRR = u32High;\
                            GPIOB->BSRR = u32Low; \
                            GPIOB->BSRR = u32High;\
                            GPIOB->BSRR = u32Low; \
                            GPIOB->BSRR = u32High;\
                            GPIOB->BSRR = u32Low;}

/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_GpioInit(void);
static void APP_SystemClockConfig(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* PB5 */
  uint32_t u32High = 0x00000020;
  uint32_t u32Low  = 0x00200000;
  
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();  
  
  /* Initialize GPIO */
  APP_GpioInit();                                 
  
  /* Configure system clock */
  APP_SystemClockConfig();                         
  
  while (1)
  {
    /* Toggle LED output approximately 12MHz */
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
    APP_GPIO_TOGGLE();
  }
}

/**
  * @brief  Initialize GPIO
  * @param  None
  * @retval None
  */
static void APP_GpioInit()
{
  GPIO_InitTypeDef  GPIO_InitStruct = {0};

  __HAL_RCC_GPIOB_CLK_ENABLE();                          /* Enable GPIOB clock */

  /* Initialize GPIO PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;            /* Push-pull output */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* Pull-up */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     /* GPIO speed */
  /* Initialize GPIO */
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);                
}

/**
  * @brief  Configure system clock
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* Configure clock source HSI */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                                       /* Enable HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                                                       /* No HSI division */
  /* RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_4MHz; */                         /* Configure HSI output clock as 4MHz */
  /* RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz; */                         /* Configure HSI output clock as 8MHz */
  /* RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_16MHz; */                        /* Configure HSI output clock as 16MHz */
  /* RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_22p12MHz; */                     /* Configure HSI output clock as 22.12MHz */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_24MHz;                              /* Configure HSI output clock as 24MHz */

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)                                           /* Initialize RCC oscillators */
  {
    APP_ErrorHandler();
  }

  /* Initialize CPU, AHB, APB bus clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;  /* RCC system clock types */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;                                          /* SYSCLK source is HSI */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                              /* AHB clock not divided */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                                               /* APB clock not divided */

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)                         /* Initialize RCC system clock (FLASH_LATENCY_0=up to 24MHz; FLASH_LATENCY_1=up to 48MHz) */
  {
    APP_ErrorHandler();
  }
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  /* infinite loop */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line)  */
  /* infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
