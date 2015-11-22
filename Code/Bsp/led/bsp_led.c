/* Includes ---------------------------------------------------------------------------------------------------*/
#include "bsp_led.h"



/* Private typedef --------------------------------------------------------------------------------------------*/
/* Private define ---------------------------------------------------------------------------------------------*/
/* Private macro ----------------------------------------------------------------------------------------------*/
/* Private variables ------------------------------------------------------------------------------------------*/
Struct_LedInit LED[] = {
    {LED_GREEN,GREEN_LED_PORT,GREEN_LED_PIN,LED_OFF}  /* PI1 = Green LED in stm32f7 Discovery-Board            */
};

static int g_ledNumber = sizeof(LED)/sizeof(LED[0]);  /* The number of LEDs need to config                     */
/* Private function prototypes --------------------------------------------------------------------------------*/
/* Private functions ------------------------------------------------------------------------------------------*/





 /**************************************************************************************************************
  * Function Name   : bsp_LedInit
  * Description     : Configures LED on GPIO
  * Input Variable  : None
  * Return Variable : None
  * Author          : Bryant
  * Create Date     : Sep-29-2015
  * Call            : Outside
****************************************************************************************************************/
void bsp_LedInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    Enum_LedName ledName;

    for(ledName = LED_GREEN;ledName < g_ledNumber;ledName++)
    {
        bsp_GPIOxClockEnable(LED[ledName].LED_PORT); /* Enable GPIO Port clock                                 */

        /* Config as push-pull                                                                                 */
        GPIO_InitStruct.Pin   = LED[ledName].LED_PIN;
        GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull  = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
        HAL_GPIO_Init(LED[ledName].LED_PORT,&GPIO_InitStruct);

        if (LED[ledName].LED_INIT == LED_ON)
        {
            bsp_LedOn(ledName);
        }
        else
        {
            bsp_LedOff(ledName);
        }
    }
}



 /**************************************************************************************************************
  * Function Name   : bsp_GPIOxClockEnable
  * Description     : Enable specific GPIO Port clock
  * Input Variable  : GPIO Port
  * Return Variable : None
  * Author          : Bryant
  * Create Date     : Sep-29-2015
  * Call            : Outside
****************************************************************************************************************/
void bsp_GPIOxClockEnable(GPIO_TypeDef* gpioPort)
{
  if(gpioPort==GPIOA) __GPIOA_CLK_ENABLE();
  if(gpioPort==GPIOB) __GPIOB_CLK_ENABLE();
  if(gpioPort==GPIOC) __GPIOC_CLK_ENABLE();
  if(gpioPort==GPIOD) __GPIOD_CLK_ENABLE();
  if(gpioPort==GPIOE) __GPIOE_CLK_ENABLE();
  if(gpioPort==GPIOF) __GPIOF_CLK_ENABLE();
  if(gpioPort==GPIOG) __GPIOG_CLK_ENABLE();
  if(gpioPort==GPIOH) __GPIOH_CLK_ENABLE();
  if(gpioPort==GPIOI) __GPIOI_CLK_ENABLE();
  if(gpioPort==GPIOJ) __GPIOJ_CLK_ENABLE();
  if(gpioPort==GPIOK) __GPIOK_CLK_ENABLE();
}


 /**************************************************************************************************************
  * Function Name   : bsp_LedOff
  * Description     : Turn off a specific led
  * Input Variable  : ledName
  * Return Variable : None
  * Author          : Bryant
  * Create Date     : Sep-29-2015
  * Call            : Outside
****************************************************************************************************************/
void bsp_LedOff(Enum_LedName ledName)
{
    LED[ledName].LED_PORT->BSRR = (uint32_t)LED[ledName].LED_PIN << 16;
    /* HAL_GPIO_WritePin(LED[ledName].LED_PORT,LED[ledName].LED_PIN,GPIO_PIN_RESET);                           */
}

/***************************************************************************************************************
 * Function Name   : bsp_LedOn
 * Description     : Turn on a specific led
 * Input Variable  : ledName
 * Return Variable : None
 * Author          : Bryant
 * Create Date     : Sep-29-2015
 * Call            : Outside
****************************************************************************************************************/
void bsp_LedOn(Enum_LedName ledName)
{
    LED[ledName].LED_PORT->BSRR = (uint32_t)LED[ledName].LED_PIN ;

    /* HAL_GPIO_WritePin(LED[ledName].LED_PORT,LED[ledName].LED_PIN,GPIO_PIN_SET);                             */
}

/***************************************************************************************************************
 * Function Name   : bsp_LedToggle
 * Description     : Turn on a specific led
 * Input Variable  : ledName
 * Return Variable : None
 * Author          : Bryant
 * Create Date     : Sep-29-2015
 * Call            : Outside
****************************************************************************************************************/
void bsp_LedToggle(Enum_LedName ledName)
{
    LED[ledName].LED_PORT->ODR ^= LED[ledName].LED_PIN;
    /* HAL_GPIO_TogglePin(LED[ledName].LED_PORT,LED[ledName].LED_PIN);                                         */
}

/*************************************************END OF FILE***************************************************/


