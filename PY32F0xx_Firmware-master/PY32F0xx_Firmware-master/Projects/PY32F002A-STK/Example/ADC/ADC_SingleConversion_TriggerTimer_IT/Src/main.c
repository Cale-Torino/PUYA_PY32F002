/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
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
ADC_HandleTypeDef             AdcHandle;
ADC_ChannelConfTypeDef        sConfig;
volatile uint16_t             aADCxConvertedData;
TIM_HandleTypeDef             TimHandle;
TIM_MasterConfigTypeDef       sMasterConfig;

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void APP_ADCConfig(void);
void APP_Tim1Config(void);
/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();

  /* Initialize UART */
  BSP_USART_Config();

  /* Configure TIM */
  APP_Tim1Config();

  /* Configure ADC*/
  APP_ADCConfig();

  /* infinite loop */
  while (1)
  {
    
  }
}

/**
  * @brief  ADC configuration function
  * @param  None
  * @retval None
  */
void APP_ADCConfig(void)
{
  __HAL_RCC_ADC_CLK_ENABLE();                                                     /* Enable ADC clock */

  /* Reset ADC */
  __HAL_RCC_ADC_FORCE_RESET();
  __HAL_RCC_ADC_RELEASE_RESET();
  __HAL_RCC_ADC_CLK_ENABLE();                                                     /* Enable ADC clock */

  AdcHandle.Instance = ADC1;
  if (HAL_ADCEx_Calibration_Start(&AdcHandle) != HAL_OK)                          /* ADC calibration */
  {
    APP_ErrorHandler();
  }
  
  AdcHandle.Instance                   = ADC1;                                    /* ADC*/
  AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;                /* Set ADC clock*/
  AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;                      /* 12-bit resolution for converted data*/
  AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;                     /* Right-alignment for converted data */
  AdcHandle.Init.ScanConvMode          = ADC_SCAN_DIRECTION_BACKWARD;             /* Scan sequence direction */
  AdcHandle.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;                     /* Single sampling*/
  AdcHandle.Init.LowPowerAutoWait      = ENABLE;                                  /* Enable wait for conversion mode */
  AdcHandle.Init.ContinuousConvMode    = DISABLE;                                 /* Single conversion mode */
  AdcHandle.Init.DiscontinuousConvMode = ENABLE;                                  /* Enable discontinuous mode */
  AdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_TRGO;            /* Set the external trigger for conversion start event to TIM1_TRGO */
  AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_RISING;         /* Trigger on rising edges */
  AdcHandle.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;                /* When an overload occurs, overwrite the previous value*/
  AdcHandle.Init.SamplingTimeCommon    = ADC_SAMPLETIME_239CYCLES_5;              /* Set sampling time */
  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)                                         /* ADC initialization*/
  {
    APP_ErrorHandler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                                 /* Set whether to sample */
  sConfig.Channel      = ADC_CHANNEL_0;                                           /* Setting the sampling channel */
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)                      /* Configuring ADC Channels */
  {
    APP_ErrorHandler();
  }
 
  if (HAL_ADC_Start_IT(&AdcHandle) != HAL_OK)                                      /* Enable ADC and enable interrupts */
  {
    APP_ErrorHandler();
  }

}
/**
  * @brief  TIM configuration function
  * @param  None
  * @retval None
  */
void APP_Tim1Config(void)
{
  __HAL_RCC_TIM1_CLK_ENABLE();                                        /*Enable TIM1 clock*/
  TimHandle.Instance = TIM1;                                          /*TIM1*/
  TimHandle.Init.Period            = 8000 - 1;                        /*TIM1 reload value*/
  TimHandle.Init.Prescaler         = 100 - 1;                         /*Prescaler value*/
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;          /*Clock not divided*/
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;              /*Up-counting mode*/
  TimHandle.Init.RepetitionCounter = 0;                               /*No repetition*/
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;  /*Auto-reload register not buffered*/
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                        /*Initialize TIM1*/
  {
    APP_ErrorHandler();
  }
  /*Configure TIM1 as master mode*/
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;                /*Select update event as trigger source*/
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;        /*No effect in master/slave mode*/
  HAL_TIMEx_MasterConfigSynchronization(&TimHandle, &sMasterConfig);  /*Configure TIM1*/
  if (HAL_TIM_Base_Start(&TimHandle) != HAL_OK)                       /*Enable TIM1*/
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  ADC transfer complete callback function
  * @param  None
  * @retval None
  */
 void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  aADCxConvertedData = HAL_ADC_GetValue(hadc);
  printf("ADC: %d\r\n", aADCxConvertedData);

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
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
