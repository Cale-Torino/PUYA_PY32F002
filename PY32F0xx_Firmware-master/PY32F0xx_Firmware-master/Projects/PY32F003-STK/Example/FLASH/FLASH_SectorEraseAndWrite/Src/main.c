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
#include "py32f003xx_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
#define FLASH_USER_START_ADDR     0x08003000

/* Private variables ---------------------------------------------------------*/
const uint32_t DATA[64] =
{
  0x01010101, 0x23456789, 0x3456789A, 0x456789AB, 0x56789ABC, 0x6789ABCD, 0x789ABCDE, 0x89ABCDEF,
  0x9ABCDEF0, 0xABCDEF01, 0xBCDEF012, 0xCDEF0123, 0xDEF01234, 0xEF012345, 0xF0123456, 0x01234567,
  0x01010101, 0x23456789, 0x3456789A, 0x456789AB, 0x56789ABC, 0x6789ABCD, 0x789ABCDE, 0x89ABCDEF,
  0x9ABCDEF0, 0xABCDEF01, 0xBCDEF012, 0xCDEF0123, 0xDEF01234, 0xEF012345, 0xF0123456, 0x01234567,
  0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA,
  0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA,
  0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA,
  0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA, 0x55555555, 0x23456789, 0xAAAAAAAA,
};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_FlashErase(void);
static void APP_FlashProgram(void);
static void APP_FlashBlank(void);
static void APP_FlashVerify(void);

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
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  /* Wait for button press to prevent flash programming on every power-up */
  while (BSP_PB_GetState(BUTTON_USER))
  {
  }

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Configure system clock */
  APP_SystemClockConfig();

  /* Unlock FLASH */
  HAL_FLASH_Unlock();

  /* Erase FLASH */
  APP_FlashErase();

  /* Check if FLASH is blank*/
  APP_FlashBlank();

  /* program FLASH */
  APP_FlashProgram();

  /* Lock FLASH */
  HAL_FLASH_Lock();

  /* Verify FLASH */
  APP_FlashVerify();

  BSP_LED_On(LED_GREEN);

  while (1)
  {
  }
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

  /* Configure HSI, HSE, LSI clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                      /* Enable HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                                      /* HSI prescaler */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_24MHz;             /* Set HSI output clock as 24MHz, the library will set the calibration value */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                                     /* Disable HSE */
  RCC_OscInitStruct.HSEFreq =  RCC_HSE_16_32MHz;                                /* HSE frequency range */
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                                     /* Disable LSI */

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Initialize AHB, and APB bus clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;                        /* SYSCLK source is HSI */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                            /* Setting the AHB prescaler */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                             /* Setting the APB1 prescaler */

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  Erase FLASH
  * @param  None
  * @retval None
  */
static void APP_FlashErase(void)
{
  uint32_t SECTORError = 0;
  FLASH_EraseInitTypeDef EraseInitStruct = {0};

  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_SECTORERASE;      /* Erase type: FLASH_TYPEERASE_PAGEERASE = erase by page, FLASH_TYPEERASE_SECTORERASE = erase by sector */
  EraseInitStruct.SectorAddress = FLASH_USER_START_ADDR;          /* Erase start address */
  EraseInitStruct.NbSectors  = 1;                                 /* Number of sectors to erase */
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)/* Perform sector erase, SECTORError returns the sector with erase error, 0xFFFFFFFF indicates successful erase */
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  Program FLASH
  * @param  None
  * @retval None
  */
static void APP_FlashProgram(void)
{
  uint32_t flash_program_start = FLASH_USER_START_ADDR ;                /* Start address for flash program */
  uint32_t flash_program_end = (FLASH_USER_START_ADDR + sizeof(DATA));  /* End address for flash program */
  uint32_t *src = (uint32_t *)DATA;                                     /* Pointer to the array */
  while (flash_program_start < flash_program_end)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_PAGE, flash_program_start, src) == HAL_OK)/* Execute Program */
    {
      flash_program_start += FLASH_PAGE_SIZE; /* Set flash start pointer to the first page */
      src += FLASH_PAGE_SIZE / 4;             /* Update the data pointer */
    }
  }
}

/**
  * @brief  Check if Flash is blank
  * @param  None
  * @retval None
  */
static void APP_FlashBlank(void)
{
  uint32_t addr = 0;

  while (addr < sizeof(DATA))
  {
    if (0xFFFFFFFF != HW32_REG(FLASH_USER_START_ADDR + addr))
    {
      APP_ErrorHandler();
    }
    addr += 4;
  }
}

/**
  * @brief  Check if Flash is blank
  * @param  None
  * @retval None
  */
static void APP_FlashVerify(void)
{
  uint32_t addr = 0;

  while (addr < sizeof(DATA))
  {
    if (DATA[addr / 4] != HW32_REG(FLASH_USER_START_ADDR + addr))
    {
      APP_ErrorHandler();
    }
    addr += 4;
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
