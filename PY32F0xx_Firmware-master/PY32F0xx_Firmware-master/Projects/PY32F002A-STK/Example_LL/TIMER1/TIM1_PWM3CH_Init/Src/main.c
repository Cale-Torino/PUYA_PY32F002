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
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigPWMChannel(void);
static void APP_ConfigTIM1(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Configure system clock */
  APP_SystemClockConfig();
 /*Enable TIM1 and GPIO clock*/
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  
  /*Initialize button*/
  BSP_PB_Init(BUTTON_USER,BUTTON_MODE_GPIO);
  
  /*Wait for button press*/
  while(BSP_PB_GetState(BUTTON_USER) != 0)
  {}
  
  /*Configure TIM1 PWM channels and PWM mode*/
  APP_ConfigPWMChannel();
  
  /*Configure and enable TIM1 PWM mode*/
  APP_ConfigTIM1();
  while (1)
  {
  }
}
/**
  * @brief  Configure TIM1 PWM related GPIO
  * @param  None
  * @retval None
  */
static void APP_ConfigPWMChannel(void)
{
  LL_GPIO_InitTypeDef TIM1CH1MapInit= {0};
  LL_TIM_OC_InitTypeDef TIM_OC_Initstruct ={0};

  /* Configure PA3/PA13/PA0 as TIM1_CH1/TIM1_CH2/TIM1_CH3 */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_3|LL_GPIO_PIN_13|LL_GPIO_PIN_0;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_13; 
  TIM1CH1MapInit.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1CH1MapInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  TIM1CH1MapInit.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA,&TIM1CH1MapInit);
  
  TIM_OC_Initstruct.OCMode        = LL_TIM_OCMODE_PWM2;       /* Mode: PWM2       */
  TIM_OC_Initstruct.OCState       = LL_TIM_OCSTATE_ENABLE;    /* Channel enable       */
  TIM_OC_Initstruct.OCPolarity    = LL_TIM_OCPOLARITY_HIGH;   /* Active polarity: high level */
  TIM_OC_Initstruct.OCIdleState   = LL_TIM_OCIDLESTATE_LOW;   /* Complementary channel active polarity: low level */
  /*Channel 1 compare value: 250*/
  TIM_OC_Initstruct.CompareValue  = 250;
  /* Configure channel 1 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH1,&TIM_OC_Initstruct);
  /* Channel 2 compare value: 500 */
  TIM_OC_Initstruct.CompareValue  = 500;
  /* Configure channel 2 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH2,&TIM_OC_Initstruct);
  /* Channel 3 compare value: 750 */
  TIM_OC_Initstruct.CompareValue  = 750;
  /* Configure channel 3 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH3,&TIM_OC_Initstruct);
}

/**
  * @brief  Configure TIM1.
  * @param  None
  * @retval int
  */
static void APP_ConfigTIM1(void)
{
  /*Configure TIM1*/
  LL_TIM_InitTypeDef TIM1CountInit = {0};
  
  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1;/* No clock division             */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;    /* Up-counting mode */
  TIM1CountInit.Prescaler           = 2400-1;                   /* Prescaler value: 2400   */
  TIM1CountInit.Autoreload          = 1000-1;                   /* Auto-reload value */
  TIM1CountInit.RepetitionCounter   = 0;                        /* Repetition counter value: 0      */
  
  /*Initialize TIM1*/
  LL_TIM_Init(TIM1,&TIM1CountInit);
  
  /*Enable main output*/
  LL_TIM_EnableAllOutputs(TIM1);

  /*Enable TIM1 counter*/
  LL_TIM_EnableCounter(TIM1);
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
  LL_RCC_HSI_SetCalibFreq(LL_RCC_HSICALIBRATION_24MHz);
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
  LL_Init1msTick(24000000);
  
  /* Update system clock global variable SystemCoreClock (can also be updated by calling SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(24000000);
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
