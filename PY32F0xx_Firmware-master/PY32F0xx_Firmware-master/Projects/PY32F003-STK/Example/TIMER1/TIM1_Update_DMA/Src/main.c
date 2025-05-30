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
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle;
TIM_OC_InitTypeDef sConfig;
uint32_t Arr_DMA[3] = {1600, 3200, 4800};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_GpioPortInit(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  /* System clock configuration */
  APP_SystemClockConfig(); 

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* GPIOA0初始化 */
  APP_GpioPortInit();
  
  TimHandle.Instance = TIM1;                                           /* Select TIM1 */
  TimHandle.Init.Period            = 6400 - 1;                         /* Auto-reload value */
  TimHandle.Init.Prescaler         = 1000 - 1;                         /* Prescaler */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;           /* No clock division */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;               /* Up counting */
  TimHandle.Init.RepetitionCounter = 1 - 1;                            /* No repetition counting */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;    /* Enable auto-reload register preload */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                         /* Initialize TIM1 */
  {
    APP_ErrorHandler();
  }
  __HAL_TIM_ENABLE_DMA(&TimHandle, TIM_DMA_UPDATE);                    /* Enable specified DMA request */
  
  if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)                     /* Start the TIM Base generation in interrupt mode */
  {
    APP_ErrorHandler();
  }
  
  while (1)
  {
  }
}

/**
  * @brief  Initialize GPIO PA0
  * @param  None
  * @retval None
  */
static void APP_GpioPortInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct = {0};
  __HAL_RCC_GPIOA_CLK_ENABLE();                   /* Enable GPIOA clock */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;     /* Push-pull output */
  GPIO_InitStruct.Pull = GPIO_NOPULL;             /* 无上拉和下拉 */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);         /* Initialize GPIO */
}

/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim：TIM
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
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

  /* Oscillator configuration */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                                       /* Enable HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                                                       /* HSI not divided */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_16MHz;                              /* Configure HSI output clock as 16MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                                                      /* Disable HSE */
  RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz;                                                  /* HSE frequency range 16M~32M */
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                                                      /* Disable LSI */

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Initialize CPU, AHB, and APB bus clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* RCC system clock types */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;                                         /* SYSCLK source is HSI */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                             /* AHB clock not divided */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                                              /* APB clock not divided */

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)                        /* Initialize RCC system clock (FLASH_LATENCY_0=up to 24MHz; FLASH_LATENCY_1=up to 48MHz) */
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
