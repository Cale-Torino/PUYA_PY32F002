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
PWR_StopModeConfigTypeDef PwrStopModeConf = {0};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_ExtiConfig(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();       

  /* Initialize button */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Configure external interrupt */
  APP_ExtiConfig();                             
 
  /* USART configuration */
  DEBUG_USART_Config();                         

  /* Turn on the LED */
  BSP_LED_On(LED_GREEN);

  /* Wait for button press */
  while (BSP_PB_GetState(BUTTON_USER))
  {
  }

  /* Turn off the LED */
  BSP_LED_Off(LED_GREEN);

  /* print "STOP MODE!" */
  printf("STOP MODE!\n\n");

  /* Suspend Systick interrupt */
  HAL_SuspendTick();     

  /* VCORE = 1.0V  when enter stop mode */
  PwrStopModeConf.LPVoltSelection       =  PWR_STOPMOD_LPR_VOLT_SCALE2;
  PwrStopModeConf.FlashDelay            =  PWR_WAKEUP_FLASH_DELAY_5US;
  PwrStopModeConf.WakeUpHsiEnableTime   =  PWR_WAKEUP_HSIEN_AFTER_MR;
  PwrStopModeConf.RegulatorSwitchDelay  =  PWR_WAKEUP_LPR_TO_MR_DELAY_2US;
  PwrStopModeConf.SramRetentionVolt     =  PWR_SRAM_RETENTION_VOLT_VOS;
  HAL_PWR_ConfigStopMode(&PwrStopModeConf);

  /* Enter STOP mode */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

  /* print "WAKEUP OK!" */
  printf("WAKEUP OK!\n\n");

  /* Resume the SysTick interrupt */
  HAL_ResumeTick();    

  while (1)
  {
    BSP_LED_Toggle(LED_GREEN);
    HAL_Delay(200);
  }
}

/**
  * @brief  Interrupt configuration function
  * @param  None
  * @retval None
  */
static void APP_ExtiConfig(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();                  /* Enable GPIOA clock */

  GPIO_InitStruct.Mode  = GPIO_MODE_IT_FALLING;  /* GPIO mode set to falling edge interrupt */
  GPIO_InitStruct.Pull  = GPIO_PULLUP;           /* Pull-up */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;  /* High-speed  */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  /* Initialize GPIO */
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);             /* Enable EXTI interrupt */
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);     /* Configure interrupt priority */
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
