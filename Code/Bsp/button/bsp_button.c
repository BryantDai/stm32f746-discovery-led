/* Includes ---------------------------------------------------------------------------------------------------*/
#include "bsp_button.h"
#include "bsp_led.h"


/* Private typedef --------------------------------------------------------------------------------------------*/
/* Private define ---------------------------------------------------------------------------------------------*/
/* Private macro ----------------------------------------------------------------------------------------------*/
/* Private variables ------------------------------------------------------------------------------------------*/
BUTTON_InitTypeDef g_buttonInit[] = {
   /* Name      ,InitStatus     ,Pin            pull register, Port                                            */
  {USER_BUTTON1_PORT,USER_BUTTON1,GPIO_PIN_RESET,USER_BUTTON1_PIN,GPIO_NOPULL},
};
static uint8_t g_buttonNum = sizeof(g_buttonInit)/sizeof(g_buttonInit[0]);



/* Private function prototypes --------------------------------------------------------------------------------*/
static uint8_t bsp_IsButtonDown(BUTTON_IDTypeDef buttonName);
static uint8_t bsp_ButtonDetect(BUTTON_IDTypeDef buttonName);


/* Private functions ------------------------------------------------------------------------------------------*/




 /**************************************************************************************************************
  * Function Name   : bsp_ButtonGpioConfig
  * Description     : Configure Pins connected to key and initialize the state of a button
  * Input Variable  : None
  * Return Variable : None
  * Author          : Bryant
  * Create Date     : Nov-22-2015
  * Call            : Outside
****************************************************************************************************************/
void bsp_ButtonInit(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  BUTTON_IDTypeDef buttonName;

  for (buttonName = USER_BUTTON1;buttonName < g_buttonNum;buttonName++)
  {
    /* Enable PORT clock                                                                                       */
    bsp_GPIOxClockEnable((GPIO_TypeDef *)g_buttonInit[buttonName].buttonPort);

    /* GPIO config                                                                                             */
    GPIO_InitStruct.Pin   = g_buttonInit[buttonName].buttonPin;
    GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull  = g_buttonInit[buttonName].buttonPull;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init  (g_buttonInit[buttonName].buttonPort,&GPIO_InitStruct);  
  }
}



/**************************************************************************************************************
 * Function Name   : bsp_ButtonScan
 * Description     : Scan all the button(Call in each systick interrupt(each 10ms))
 * Input Variable  : None
 * Return Variable : The button status
 * Author          : Bryant
 * Create Date     : Nov-22-2015
 * Call            : Outside
****************************************************************************************************************/
uint8_t bsp_ButtonScan(void)
{
  BUTTON_IDTypeDef buttonName;
  uint8_t buttonStatus = USER_BUTTON_NONE;
  static uint8_t s_countTime = 0u;
  uint8_t buttonTemp = USER_BUTTON_NONE;
  static uint8_t s_buttonStep = BUTTON_STATE0;  

  /* Go through all the buttons                                                                                */
  for (buttonName = USER_BUTTON1;buttonName < g_buttonNum;buttonName++)
  {
    buttonTemp = bsp_ButtonDetect(buttonName);
    
    switch (s_buttonStep)
    {
      case BUTTON_STATE0 : 
           if (buttonTemp == USER_BUTTON_DOWN)
           {
             s_buttonStep = BUTTON_STATE1;
             s_countTime = 0u;
           }
           else if (buttonTemp == USER_BUTTON_LONG) /* Long depress event happen                               */
           {
             buttonStatus = USER_BUTTON_LONG;
           }
      break;

      case BUTTON_STATE1 :
           if (buttonTemp == USER_BUTTON_DOWN)
           {
              buttonStatus = USER_BUTTON_DOUBLE;
              s_buttonStep = BUTTON_STATE0;
           }        
           else 
           {
             if (++s_countTime >= 50)
              { /* Another click in less than 500ms become double click event                                     */
                buttonStatus = USER_BUTTON_DOWN;

                s_buttonStep = BUTTON_STATE0;
              }
           }
           
      break;

    } /* End of switch (s_buttonState)                                                                         */
  } /* End of for (buttonName = USER_BUTTON1;buttonName < g_buttonNum;buttonName++)                            */
  return buttonStatus;
}

/***************************************************************************************************************
 * Function Name   : bsp_ButtonDetect
 * Description     : Check if specific button depressed
 * Input Variable  : buttonName : the button name
 * Return Variable : The button status
 * Author          : Bryant
 * Create Date     : Nov-22-2015
 * Call            : Inside
****************************************************************************************************************/
static uint8_t bsp_ButtonDetect(BUTTON_IDTypeDef buttonName)
{
  uint8_t isButtonDepress = 0u;
  uint8_t buttonStatus = USER_BUTTON_NONE;
  static uint8_t s_buttonState = BUTTON_STATE0;  
  static uint8_t s_timeCount = 0u;
  
  isButtonDepress = bsp_IsButtonDown(buttonName);

  switch (s_buttonState)
  {
    case BUTTON_STATE0 : 
         if (isButtonDepress)
           s_buttonState = BUTTON_STATE1;
    break;
    case BUTTON_STATE1 : 
         if (isButtonDepress)                    /* Button do depressed then begin to 'count' the depress time */
         {
           s_timeCount = 0u;
           s_buttonState = BUTTON_STATE2;
         }
         else
         {
           s_buttonState = BUTTON_STATE0;        /* Button already up, then back to initialize state           */
         }
    break;
    case BUTTON_STATE2 : 
         if (!isButtonDepress)                   /* Button has release, then a click event happen              */
         {
           buttonStatus = USER_BUTTON_DOWN;
           s_buttonState = BUTTON_STATE0;
         }
         else
         { /* Button depress time long than define time, than a long click event happen                        */
           if (++s_timeCount > BUTTON_LONG_TIME)
           {
             buttonStatus = USER_BUTTON_LONG;
             s_buttonState = BUTTON_STATE0;
           }
         }
    break;
  }
  return buttonStatus;
}


/***************************************************************************************************************
 * Function Name   : bsp_IsButtonDown
 * Description     : Check if specific key depressed
 * Input Variable  : buttonName : button want to check
 * Return Variable : 1          : if depressed
 *                   0          : if not depressed
 * Author          : Bryant
 * Create Date     : Nov-22-2015
 * Call            : Inside
****************************************************************************************************************/
static uint8_t bsp_IsButtonDown(BUTTON_IDTypeDef buttonName)
{
  /* Basic on the schematics, when user button depressed, the pin connect with it will become high level       */
  if (HAL_GPIO_ReadPin(g_buttonInit[buttonName].buttonPort,g_buttonInit[buttonName].buttonPin) == GPIO_PIN_SET)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}







/*************************************************END OF FILE***************************************************/




