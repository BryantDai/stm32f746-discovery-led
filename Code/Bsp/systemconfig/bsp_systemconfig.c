/* Includes ----------------------------------------------------------------------------------------------------------------------*/
#include "bsp_systemconfig.h"


/* Private typedef ---------------------------------------------------------------------------------------------------------------*/
/* Private define ----------------------------------------------------------------------------------------------------------------*/
/* Private macro -----------------------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------------------*/

/* Private function prototypes ---------------------------------------------------------------------------------------------------*/
/* Private functions -------------------------------------------------------------------------------------------------------------*/





 /*********************************************************************************************************************************
  * Function Name   : bsp_SystemClockConfig
  * Description     : System Clock Configuration
  * Input Variable  : None
  * Return Variable : None
  * Author          : Bryant
  * Create Date     : Nov-07-2015
  * Call            : Outside
***********************************************************************************************************************************/
void bsp_SystemClockConfig(void)
{
  /* The system Clock is configured as follow : 
   * System Clock source            = PLL (HSE)
   * SYSCLK(Hz)                     = 216000000
   * HCLK(Hz)                       = 216000000
   * AHB Prescaler                  = 1
   * APB1 Prescaler                 = 4
   * APB2 Prescaler                 = 2
   * HSE Frequency(Hz)              = 25000000
   * PLL_M                          = 25    (f(PLL input) = f(HSE) / PLLM      )  
   * PLL_N                          = 432   (f(VCO)       = f(PLL input) * PLLN)
   * PLL_P                          = 2     (f(PLLCLK)    = f(VCO) / PLLP      )
   * PLL_Q                          = 9     (f(USB OTG FS)= f(VCO) / PLLQ      )  
   * VDD(V)                         = 3.3
   * Main regulator output voltage  = Scale1 mode
   * Flash Latency(WS)              = 7
  */
  RCC_OscInitTypeDef RCC_OscInitStructure;
  RCC_ClkInitTypeDef RCC_ClkInitStructure;
  HAL_StatusTypeDef  halStatus;    

  /* Select PLL source and select PLL factor to enable PLL to get a new frequency of the system clock                             */
  RCC_OscInitStructure.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStructure.HSEState       = RCC_HSE_ON;
  RCC_OscInitStructure.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
  RCC_OscInitStructure.PLL.PLLState   = RCC_PLL_ON;
  RCC_OscInitStructure.PLL.PLLM       = 25;
  RCC_OscInitStructure.PLL.PLLN       = 432;
  RCC_OscInitStructure.PLL.PLLP       = RCC_PLLP_DIV2;
  RCC_OscInitStructure.PLL.PLLQ       = 9;
  halStatus = HAL_RCC_OscConfig  (&RCC_OscInitStructure);
  if (halStatus != HAL_OK)                                      /* Error occur at enabling the HSE clock, capture the error here  */
  {
    while(1)
    {;}
  }

  /* The maximum value of f(HCLK) is 180MHz. It can be extended to 216MHz by activating the over-drive mode                       */  
  halStatus = HAL_PWREx_EnableOverDrive();
  if (halStatus != HAL_OK)                                      /* Error occur at enabling Over Driver, capture the error here    */
  {
    while(1)
    {;}
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers                                    */
  RCC_ClkInitStructure.ClockType      = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStructure.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStructure.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStructure.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStructure.APB2CLKDivider = RCC_HCLK_DIV2;
  
  halStatus = HAL_RCC_ClockConfig(&RCC_ClkInitStructure, FLASH_LATENCY_7);
  if (halStatus != HAL_OK)                                      /* Error occur at configure clocks dividers,capture the error here*/
  {
    while(1)
    {;}
  }

  /* Enables the Clock Security System when use HSE as PLL source clock and PLL clock as system clock                             */
  HAL_RCC_EnableCSS(); 
  
}



 /*********************************************************************************************************************************
  * Function Name   : bsp_HsiToHseSwitch
  * Description     : Switch the PLL source from HSI to HSE , and select the PLL as SYSCLK source.
  * Input Variable  : None
  * Return Variable : None
  * Author          : Bryant
  * Create Date     : Nov-08-2015
  * Call            : Outside
***********************************************************************************************************************************/
void bsp_HsiToHseSwitch(void)
{
  RCC_OscInitTypeDef RCC_OscInitStructure;
  
  /* Enable HSE as source clock of PLL divide the PLL clock to AHB, APB1 and APB2                                                 */
  bsp_SystemClockConfig();
  
  /* -4- Optional: Disable HSI Oscillator (if the HSI is no more needed by the application)*/
  RCC_OscInitStructure.OscillatorType  = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStructure.HSIState        = RCC_HSI_OFF;
  RCC_OscInitStructure.PLL.PLLState    = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStructure) != HAL_OK)
  {
    while(1)
    {;}
  }
  
}

/*********************************************************************************************************************************
 * Function Name   : bsp_HseToHsiSwitch
 * Description     : Switch the PLL source from HSE  to HSI , and select the PLL as SYSCLK source.
 * Input Variable  : None
 * Return Variable : None
 * Author          : Bryant
 * Create Date     : Nov-08-2015
 * Call            : Outside
***********************************************************************************************************************************/
void bsp_HseToHsiSwitch(void)
{
  /* The system Clock is configured as follow : 
   * System Clock source            = PLL (HSI)
   * SYSCLK(Hz)                     = 216000000
   * HCLK(Hz)                       = 216000000
   * AHB Prescaler                  = 1
   * APB1 Prescaler                 = 4
   * APB2 Prescaler                 = 2
   * HSE Frequency(Hz)              = 16000000
   * PLL_M                          = 16    (f(PLL input) = f(HSE) / PLLM      )  
   * PLL_N                          = 432   (f(VCO)       = f(PLL input) * PLLN)
   * PLL_P                          = 2     (f(PLLCLK)    = f(VCO) / PLLP      )
   * PLL_Q                          = 9     (f(USB OTG FS)= f(VCO) / PLLQ      )  
   * VDD(V)                         = 3.3
   * Main regulator output voltage  = Scale1 mode
   * Flash Latency(WS)              = 7
   */
  RCC_OscInitTypeDef RCC_OscInitStructure = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStructure = {0}; 

  /* -1- Select HSE  as system clock source to allow modification of the PLL configuration                                        */
  RCC_ClkInitStructure.ClockType          = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStructure.SYSCLKSource       = RCC_SYSCLKSOURCE_HSE;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStructure, FLASH_LATENCY_1) != HAL_OK)
  {
    /* Initialization Error                                                                                                       */
    while(1)
    {;}
  }

  /* -2- Enable HSI Oscillator, select it as PLL source and finally activate the PLL                                              */
  RCC_OscInitStructure.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStructure.HSIState            = RCC_HSI_ON;
  RCC_OscInitStructure.HSICalibrationValue = 16;
  RCC_OscInitStructure.PLL.PLLState        = RCC_PLL_ON;
  RCC_OscInitStructure.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
  RCC_OscInitStructure.PLL.PLLM            = 16;
  RCC_OscInitStructure.PLL.PLLN            = 432;
  RCC_OscInitStructure.PLL.PLLP            = RCC_PLLP_DIV2;
  RCC_OscInitStructure.PLL.PLLQ            = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStructure) != HAL_OK)
  {
    /* Initialization Error                                                                                                       */
    while(1)
    {;}
  }
 
  /* - Activate the Over Drive feature to reach 216 MHz as system clock frequency                                                 */
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    /* Initialization Error                                                                                                       */
    while(1)
    {;}
  }

  /* -3- Select the PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers                            */
  RCC_ClkInitStructure.ClockType       = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStructure.SYSCLKSource    = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStructure.AHBCLKDivider   = RCC_SYSCLK_DIV1;
  RCC_ClkInitStructure.APB1CLKDivider  = RCC_HCLK_DIV4;
  RCC_ClkInitStructure.APB2CLKDivider  = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStructure, FLASH_LATENCY_7) != HAL_OK)
  {
    /* Initialization Error                                                                                                       */
    while(1)
    {;}
  }

  /* -4- Optional: Disable HSE  Oscillator (if the HSE  is no more needed by the application) */
  RCC_OscInitStructure.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStructure.HSEState        = RCC_HSE_OFF;
  RCC_OscInitStructure.PLL.PLLState    = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStructure) != HAL_OK)
  {
    /* Initialization Error                                                                                                       */
    while(1)
    {;};
  }
}



/*********************************************************************************************************************************
 * Function Name   : bsp_CpuCacheEnable
 * Description     : CPU L1-Cache enable
 * Input Variable  : None
 * Return Variable : None
 * Author          : Bryant
 * Create Date     : Nov-08-2015
 * Call            : Outside
***********************************************************************************************************************************/
void bsp_CpuCacheEnable(void)
{
  /* Enable I-Cache                                                                                                               */
  SCB_EnableICache();

  /* Enable D-Cache                                                                                                               */
  SCB_EnableDCache();
}

/*********************************************************END OF FILE**************************************************************/


