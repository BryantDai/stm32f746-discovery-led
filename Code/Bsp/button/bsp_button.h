/* Define to prevent recursive inclusion ----------------------------------------------------------------------*/
#ifndef __BSP_BUTTON_H
#define __BSP_BUTTON_H




#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ---------------------------------------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"


/* Exported constants -----------------------------------------------------------------------------------------*/
/* Exported macro ---------------------------------------------------------------------------------------------*/
#define USER_BUTTON1_PORT         GPIOI
#define USER_BUTTON1_PIN          GPIO_PIN_11
#define USER_BUTTON1_VALUE        USER_BUTTON1_PORT->IDR

#define BUTTON_LONG_TIME          100   /* Continue 2s view as long press event                                */


/* Exported types ---------------------------------------------------------------------------------------------*/
/* Define the name of each button                                                                              */
typedef enum
{
  USER_BUTTON1 = 0,                     /* User button in stm32f746-discovery                                  */
}BUTTON_IDTypeDef;


/* Status of the buttons                                                                                       */
typedef enum
{
  USER_BUTTON_NONE   = 0,

  USER_BUTTON_DOWN   = 1,               /* Button click event happen                                           */ 
  USER_BUTTON_DOUBLE = 2,               /* Button double click event happen                                    */
  USER_BUTTON_LONG   = 3,               /* Button long click event happen                                      */
}BUTTON_StatusTypeDef;

/* Button initialization structure                                                                             */
typedef struct
{
  GPIO_TypeDef*    buttonPort;
  BUTTON_IDTypeDef buttonName;
  GPIO_PinState    buttonInitStatus;
  uint16_t         buttonPin ;
  uint32_t         buttonPull;  
}BUTTON_InitTypeDef;


/* Define for specific operation of button(each button correspond with one of this)                            */
typedef struct 
{   
  uint8_t  count;                       /* Filter counter(Eliminate buttons jitter)                            */
  uint8_t  state;                       /* Button current state(Down or Up or Long)                            */
  uint16_t longTime;                    /* Button depress time(0 for not detect long depress)                  */
  BUTTON_IDTypeDef buttonName;
}BUTTON_TypeDef;



typedef enum
{
  BUTTON_STATE0 = 0,
  BUTTON_STATE1 = 1,
  BUTTON_STATE2 = 2,
  BUTTON_STATE3 = 3
}BUTTON_StateTypeDef;

/* Exported functions -----------------------------------------------------------------------------------------*/
extern void bsp_ButtonInit(void);
extern uint8_t bsp_ButtonScan(void);



#ifdef __cplusplus
}
#endif    /* __cplusplus                                                                                       */



#endif   /* __BSP_BUTTON_H                                                                                     */


/*************************************************END OF FILE***************************************************/

