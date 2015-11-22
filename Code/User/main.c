/***************************************************************************************************************
 * File               : main.c
 * Description        :        
 * CPU                : Stm32f746G
 * ST Library Version : V1.0.1
 * Author             : Bryant Dai 
 * Create Date        : Sep-25-2015
****************************************************************************************************************/	

/* Includes ---------------------------------------------------------------------------------------------------*/
#include "bsp_led.h"
#include "bsp_button.h"
#include "bsp_systemconfig.h"

/* Private typedef --------------------------------------------------------------------------------------------*/
/* Private define ---------------------------------------------------------------------------------------------*/
/* Private macro ----------------------------------------------------------------------------------------------*/
/* Private variables ------------------------------------------------------------------------------------------*/
__IO uint8_t g_10msFlag = 0u;
/* Private function prototypes --------------------------------------------------------------------------------*/
/* Private functions ------------------------------------------------------------------------------------------*/





 /**************************************************************************************************************
  * Function Name   : main
  * Description     : main application function
  * Input Variable  : None
  * Return Variable : None
  * Author          : Bryant
  * Create Date     : Jun-17-2015
  * Call            : Outside
****************************************************************************************************************/

int main(void)
{
  uint8_t buttonEvent = USER_BUTTON_NONE;
  uint8_t i = 0u;
  
  /* Enable the CPU Cache                                                                                      */
  bsp_CpuCacheEnable();

  
  /* STM32F7xx HAL library initialization:
   - Configure the Flash ART accelerator on ITCM interface
   - Systick timer is configured by default as source of time base, but user 
     can eventually implement his proper time base source (a general purpose 
     timer for example or other time source), keeping in mind that Time base 
     duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
     handled in milliseconds basis.
   - Set NVIC Group Priority to 4
   - Low Level Initialization
  */
  HAL_Init();
  
  /* Enable the PWR Clock                                                                                      */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* Enable HSE oscillator and configure the PLL to reach the max system frequency 
     (216 MHz) when using HSE oscillator as PLL clock source. 
   */
  bsp_SystemClockConfig();

  bsp_LedInit();
  
  bsp_ButtonInit();
  
  while(1)
  {
    if (g_10msFlag == 1u)
    {
      g_10msFlag = 0u;

      buttonEvent = bsp_ButtonScan();
      if (buttonEvent == USER_BUTTON_DOWN)
      {
        for (i = 0u;i < 8u;i++)
        {
          bsp_LedToggle(LED_GREEN);
          HAL_Delay(100u);
        }
      }
      else if (buttonEvent == USER_BUTTON_DOUBLE)
      {
        for (i = 0u;i < 8u;i++)
        {
          bsp_LedToggle(LED_GREEN);
          HAL_Delay(500u);
        }
      }
      else if (buttonEvent == USER_BUTTON_LONG)
      {
        for (i = 0u;i < 8u;i++)
        {
          bsp_LedToggle(LED_GREEN);
          HAL_Delay(1000u);
        }
      }
    }
  }
}


/*************************************************END OF FILE***************************************************/

