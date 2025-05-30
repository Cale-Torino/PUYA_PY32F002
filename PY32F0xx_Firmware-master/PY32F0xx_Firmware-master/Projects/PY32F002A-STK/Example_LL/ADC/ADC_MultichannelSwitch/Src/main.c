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
#include "py32f002xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
#define ADC_CALIBRATION_TIMEOUT_MS       ((uint32_t) 1)

/* Private variables ---------------------------------------------------------*/
__IO uint16_t AdcValue;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_AdcEnable(void);
static void APP_AdcConfig(void);
static void APP_AdcCalibrate(void);
static uint32_t APP_AdcConvert(uint32_t channel);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Configure system clock */
  APP_SystemClockConfig();
  
  /* Initialize UART */
  BSP_USART_Config();

  /*Reset ADC*/
  LL_ADC_Reset(ADC1);

  /* Enable ADC module clock */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_ADC1);

  /* ADC calibration */
  APP_AdcCalibrate();

  /* Configure ADC parameters */
  APP_AdcConfig();

  while (1)
  {
    AdcValue = APP_AdcConvert(LL_ADC_CHANNEL_5);
    printf("CH5:%u \r\n",(unsigned int) AdcValue);
    
    AdcValue = APP_AdcConvert(LL_ADC_CHANNEL_4);
    printf("CH4:%u \r\n",(unsigned int) AdcValue);
    LL_mDelay(1000);
  }
}

/**
  * @brief  ADC convert function
  * @param  channel: channel is selected to be converted
  * @retval None
  */
static uint32_t APP_AdcConvert(uint32_t channel)
{
  uint16_t AdcConvertValue;

  /* Clear all channels */
  WRITE_REG(ADC1->CHSELR,0);
  
  /* Set channel as conversion channel */
  LL_ADC_REG_SetSequencerChannels(ADC1, channel);
  
  /* Enable ADC */
  APP_AdcEnable();

  /* Start ADC conversion */
  LL_ADC_REG_StartConversion(ADC1);
  
  /* Wait for ADC conversion to complete */
  while(LL_ADC_IsActiveFlag_EOC(ADC1)==0);
  
  /* Clear eoc flag */
  LL_ADC_ClearFlag_EOC(ADC1);
  
  /* Get conversion value */
  AdcConvertValue = LL_ADC_REG_ReadConversionData12(ADC1);
  
  /* Clear all channels */
  WRITE_REG(ADC1->CHSELR,0);
  
  return (uint32_t)AdcConvertValue; 
}

/**
  * @brief  ADC configuration function
  * @param  None
  * @retval None
  */
void APP_AdcConfig(void)
{
  /* Enable GPIOA clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* Configure pin 4 as analog input */
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_ANALOG);
  
  /* Configure pin 5 as analog input */
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_ANALOG);

  /* ADC channel and clock source should be configured when ADEN=0, others should be configured when ADSTART=0 */
  /* Configure internal conversion channel */
  LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_NONE);

  /* Setting the ADC Clock */
  LL_ADC_SetClock(ADC1, LL_ADC_CLOCK_SYNC_PCLK_DIV4);

  /* Set 12-bit resolution */
  LL_ADC_SetResolution(ADC1, LL_ADC_RESOLUTION_12B);

  /* Set data alignment to right */
  LL_ADC_SetDataAlignment(ADC1, LL_ADC_DATA_ALIGN_RIGHT);

  /* Set low power mode */
  LL_ADC_SetLowPowerMode(ADC1, LL_ADC_LP_AUTOWAIT);

  /* Set channel conversion time */
  LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_41CYCLES_5);

  /* ADC regular group conversion trigger by software */
  LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);

  /* Set ADC conversion mode to single mode: one conversion per trigger */
  LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);

  /* Set overrun management mode to data overwritten */
  LL_ADC_REG_SetOverrun(ADC1, LL_ADC_REG_OVR_DATA_OVERWRITTEN);

  /* Set discontinuous mode to disabled */
  LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_DISABLE);

}

/**
  * @brief  ADC calibration function
  * @param  None
  * @retval None
  */
static void APP_AdcCalibrate(void)
{

#if (USE_TIMEOUT == 1)
  uint32_t Timeout = 0; /* Variable used for timeout management */
#endif /* USE_TIMEOUT */

  if (LL_ADC_IsEnabled(ADC1) == 0)
  {
    /* Enable calibration */
    LL_ADC_StartCalibration(ADC1);

#if (USE_TIMEOUT == 1)
    Timeout = ADC_CALIBRATION_TIMEOUT_MS;
#endif /* USE_TIMEOUT */

    while (LL_ADC_IsCalibrationOnGoing(ADC1) != 0)
    {
#if (USE_TIMEOUT == 1)
      /* Check if calibration is timeout */
      if (LL_SYSTICK_IsActiveCounterFlag())
      {
        if(Timeout-- == 0)
        {

        }
      }
#endif /* USE_TIMEOUT */
    }

    /* Delay between ADC calibration end and ADC enable: minimum 4 ADC Clock cycles */
    LL_mDelay(1);
  }
}

/**
  * @brief  ADC enable function
  * @param  None
  * @retval None
  */
static void APP_AdcEnable(void)
{
  /* Enable ADC */
  LL_ADC_Enable(ADC1);

    /* ADC stabilization time, minimum 8 ADC Clock cycles */
  LL_mDelay(1);
}

/**
  * @brief  System clock configuration
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  /* Enable HSI */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /*Configure HSISYS as system clock source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(8000000);

  /* Update system clock global variable SystemCoreClock (can also be updated by calling SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(8000000);
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
