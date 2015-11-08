/* Define to prevent recursive inclusion ----------------------------------------------------------------------*/
#ifndef __BSP_LED_H
#define __BSP_LED_H




#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ---------------------------------------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"


/* Exported constants -----------------------------------------------------------------------------------------*/
/* Exported macro ---------------------------------------------------------------------------------------------*/


/* Exported types ---------------------------------------------------------------------------------------------*/
/* List of LEDs                                                                                                */ 
typedef enum
{
    LED_GREEN = 0, 
}Enum_LedName;

/* Status of LED                                                                                               */
typedef enum
{
    LED_ON  = 0,
    LED_OFF = 1
}Enum_LedStatus;

typedef struct 
{
  Enum_LedName   LED_NAME;    /* LED Name                                                                      */
  GPIO_TypeDef*  LED_PORT;    /* The Port the LED in                                                           */
  const uint16_t LED_PIN;     /* The Pin the LED in                                                            */
  Enum_LedStatus LED_INIT;    /* Initial status of the LED                                                     */
}Struct_LedInit;

/* Exported functions -----------------------------------------------------------------------------------------*/
extern void bsp_LedInit(void);
extern void bsp_LedOn(Enum_LedName ledName);
extern void bsp_LedOff(Enum_LedName ledName);
extern void bsp_LedToggle(Enum_LedName ledName);
extern void bsp_GPIOxClockEnable(GPIO_TypeDef* gpioPort);


#ifdef __cplusplus
}
#endif    /* __cplusplus                                                                                       */

#endif    /* __BSP_LED_H                                                                                       */
/*************************************************END OF FILE***************************************************/
