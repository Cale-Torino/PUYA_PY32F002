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
#include "py32f030xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
#define TXSTARTMESSAGESIZE    (COUNTOF(aTxStartMessage) - 1)
#define TXENDMESSAGESIZE      (COUNTOF(aTxEndMessage) - 1)

/* Private variables ---------------------------------------------------------*/
uint8_t aRxBuffer[12] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
uint8_t aTxStartMessage[] = "\n\r USART Hyperterminal communication based on polling \n\r Enter 12 characters using keyboard :\n\r";
uint8_t aTxEndMessage[] = "\n\r Example Finished\n\r";

uint8_t *TxBuff = NULL;
__IO uint16_t TxCount = 0;

uint8_t *RxBuff = NULL;
__IO uint16_t RxCount = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigUsart(USART_TypeDef *USARTx);
static void APP_UsartTransmit(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size);
static void APP_UsartReceive(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Configure system clock */
  APP_SystemClockConfig();

  /* Configure LED */
  BSP_LED_Init(LED_GREEN);
  
  /* Configure USART */
  APP_ConfigUsart(USART1);
  
  /* Start the transmission process */
  APP_UsartTransmit(USART1, (uint8_t*)aTxStartMessage, TXSTARTMESSAGESIZE);

  /* receive data */
  APP_UsartReceive(USART1, (uint8_t *)aRxBuffer, 12);

  /* Transmit data */
  APP_UsartTransmit(USART1, (uint8_t*)aRxBuffer, 12);
  
  /* Send the End Message  */
  APP_UsartTransmit(USART1, (uint8_t*)aTxEndMessage, TXENDMESSAGESIZE);
  
  /* Turn on LED if test passes then enter infinite loop */
  BSP_LED_On(LED_GREEN);
  
  /* Infinite loop */
  while (1)
  {

  }
}

/**
  * @brief  System clock configuration function
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

  /* Set AHB prescaler */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Configure HSISYS as system clock source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  /* Set APB1 prescaler */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(8000000);

  /* Update system clock global variable SystemCoreClock (can also be updated by calling SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(8000000);
}

/**
  * @brief  USART configuration function
  * @param  USARTx：USART module, can be USART1 or USART2
  * @retval None
  */
static void APP_ConfigUsart(USART_TypeDef *USARTx)
{
  /* Enable clock and initialize pins */
  if (USARTx == USART1) 
  {
    /* Enable GPIOA clock */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    /* Enable USART1 clock */
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_USART1);
    
    /* GPIOA configuration */
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* Select pin 2 */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
    /* Select alternate function mode */
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    /* Select output speed */
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    /* Select push-pull output mode */
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    /* Select pull-up */
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    /* Select USART1 function */
    GPIO_InitStruct.Alternate = LL_GPIO_AF1_USART1;
    /* Initialize GPIOA */
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    /* Select pin 3 */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
    /* Select USART1 function */
    GPIO_InitStruct.Alternate = LL_GPIO_AF1_USART1;
    /* Initialize GPIOA */
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
  }
  else if (USARTx == USART2)
  {
    /* Enable GPIOA clock */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    /* Enable USART1 clock */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
    
    /* GPIOA configuration */
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* Select pin 2 */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
    /* Select alternate function mode */
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    /* Select output speed */
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    /* Select push-pull output mode */
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    /* Select pull-up */
    GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
    /* Select USART2 function */
    GPIO_InitStruct.Alternate = LL_GPIO_AF4_USART2;
    /* Initialize GPIOA */
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    /* Select pin 3 */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
    /* Select USART2 function */
    GPIO_InitStruct.Alternate = LL_GPIO_AF4_USART2;
    /* Initialize GPIOA */
    LL_GPIO_Init(GPIOA,&GPIO_InitStruct);
  }
  
  /* USART configuration */
  LL_USART_InitTypeDef USART_InitStruct = {0};
  /* Set baud rate */
  USART_InitStruct.BaudRate = 9600;
  /* Set data width */
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  /* Set stop bits */
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  /* Set parity */
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  /* Initialize USART */
  LL_USART_Init(USARTx, &USART_InitStruct);
  
  /* Configure as full duplex asynchronous mode */
  LL_USART_ConfigAsyncMode(USARTx);
  
  /* Enable UART module */
  LL_USART_Enable(USARTx);
}

/**
  * @brief  USART transmit function
  * @param  USARTx：USART module, can be USART1 or USART2
  * @param  pData：transmit buffer
  * @param  Size：Size of the transmit buffer
  * @retval None
  */
static void APP_UsartTransmit(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size)
{
  TxBuff = pData;
  TxCount = Size;
  
  /* Send data */
  while (TxCount > 0)
  {
    /* Wait for TXE flag to be set */
    while(LL_USART_IsActiveFlag_TXE(USARTx) != 1);
    /* Send data */
    LL_USART_TransmitData8(USARTx, *TxBuff);
    TxBuff++;
    TxCount--;
  }
  
  /* Wait for TC flag to be set */
  while(LL_USART_IsActiveFlag_TC(USARTx) != 1);
}

/**
  * @brief  USART receive function
  * @param  USARTx：USART module, can be USART1 or USART2
  * @param  pData：receive buffer
  * @param  Size：Size of the receive buffer
  * @retval None
  */
static void APP_UsartReceive(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size)
{
  RxBuff = pData;
  RxCount = Size;
  
  /* Receive data */
  while (RxCount > 0)
  {
    /* Wait for RXNE flag to be set */
    while(LL_USART_IsActiveFlag_RXNE(USARTx) != 1);
    /* Receive data */
    *RxBuff = LL_USART_ReceiveData8(USARTx);
    RxBuff++;
    RxCount--;
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  /* Infinite loop */
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
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
