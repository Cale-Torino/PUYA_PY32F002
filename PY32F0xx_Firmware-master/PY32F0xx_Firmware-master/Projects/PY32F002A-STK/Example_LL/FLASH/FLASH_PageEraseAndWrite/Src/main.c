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
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_FlashErase(void);
static void APP_FlashProgram(void);
static void APP_FlashBlank(void);
static void APP_FlashVerify(void);

/**
  * @brief  应用程序入口函数.
  * @param  无
  * @retval int
  */
int main(void)
{
  /*时钟初始化,配置系统时钟为HSI*/
  APP_SystemClockConfig();

  /*初始化按键PB2*/
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  /*等待按键按下，防止每次上电都擦写FLASH*/
  while (BSP_PB_GetState(BUTTON_USER));

  /*初始化LED灯PA2*/
  BSP_LED_Init(LED_GREEN);

  /*解锁FLASH*/
  LL_FLASH_Unlock(FLASH);

  LL_FLASH_TIMMING_SEQUENCE_CONFIG_24M();

  /*擦除FLASH*/
  APP_FlashErase();

  /*查空FLASH*/
  APP_FlashBlank();

  /*写FLASH*/
  APP_FlashProgram();

  /*锁定FLASH*/
  LL_FLASH_Lock(FLASH);

  /*校验FLASH*/
  APP_FlashVerify();
  
  BSP_LED_On(LED_GREEN);

  while (1)
  {

  }
}
/**
  * @brief  擦除FLASH
  * @param  无
  * @retval 无
  */
static void APP_FlashErase(void)
{
  uint32_t flash_program_start = FLASH_USER_START_ADDR ;                /* flash写起始地址 */
  uint32_t flash_program_end = (FLASH_USER_START_ADDR + sizeof(DATA));  /* flash写结束地址 */
  
  while (flash_program_start < flash_program_end)
  {
    while(LL_FLASH_IsActiveFlag_BUSY(FLASH)==1);
    LL_FLASH_EnablePageErase(FLASH);
    LL_FLASH_SetEraseAddress(FLASH,flash_program_start);
    while(LL_FLASH_IsActiveFlag_BUSY(FLASH)==1);
    LL_FLASH_DisablePageErase(FLASH);
    flash_program_start += FLASH_PAGE_SIZE;                             /* flash起始指针指向下一个page */
  }
}

/**
  * @brief  写FLASH
  * @param  无
  * @retval 无
  */
static void APP_FlashProgram(void)
{
  uint32_t flash_program_start = FLASH_USER_START_ADDR ;                 /* flash写起始地址 */
  uint32_t flash_program_end = (FLASH_USER_START_ADDR + sizeof(DATA));   /* flash写结束地址 */
  uint32_t *src = (uint32_t *)DATA;                                      /* 数组指针 */

  while (flash_program_start < flash_program_end)
  {
    while(LL_FLASH_IsActiveFlag_BUSY(FLASH)==1);
    LL_FLASH_EnablePageProgram(FLASH);
    LL_FLASH_PageProgram(FLASH,flash_program_start,src);
    while(LL_FLASH_IsActiveFlag_BUSY(FLASH)==1);
    LL_FLASH_DisablePageProgram(FLASH);
    flash_program_start += FLASH_PAGE_SIZE;                              /* flash起始指针指向下一个page */
    src += FLASH_PAGE_SIZE / 4;                                          /* 更新数据指针 */
  }
}
/**
  * @brief  查空FLASH
  * @param  无
  * @retval 无
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
  * @brief  校验FLASH
  * @param  无
  * @retval 无
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
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
static void APP_SystemClockConfig(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  /* 设置HSI时钟：24MHz */
  LL_RCC_HSI_SetCalibFreq(LL_RCC_HSICALIBRATION_24MHz);
  /* 使能HSI */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* 设置 AHB 分频*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* 配置HSISYS作为系统时钟源 */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  /* 设置 APB1 分频*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(24000000);

  /* 更新系统时钟全局变量SystemCoreClock(也可以通过调用SystemCoreClockUpdate函数更新) */
  LL_SetSystemCoreClock(24000000);
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void APP_ErrorHandler(void)
{
  /* 无限循环 */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  输出产生断言错误的源文件名及行号
  * @param  file：源文件名指针
  * @param  line：发生断言错误的行号
  * @retval 无
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* 用户可以根据需要添加自己的打印信息,
     例如: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* 无限循环 */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
