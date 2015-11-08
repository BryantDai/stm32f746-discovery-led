/* Define to prevent recursive inclusion ----------------------------------------------------------------------*/
#ifndef __BSP_SYSTEM_CONFIG_H
#define __BSP_SYSTEM_CONFIG_H


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ---------------------------------------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
/* Exported constants -----------------------------------------------------------------------------------------*/
/* Exported macro ---------------------------------------------------------------------------------------------*/
/* Exported types ---------------------------------------------------------------------------------------------*/
/* Exported functions -----------------------------------------------------------------------------------------*/
extern void bsp_HsiToHseSwitch(void);
extern void bsp_HseToHsiSwitch(void);
extern void bsp_CpuCacheEnable(void);
extern void bsp_SystemClockConfig(void);


#ifdef __cplusplus
}
#endif    /* __cplusplus                                                                                       */

#endif    /* __BSP_SYSTEM_CONFIG_H                                                                             */
/*************************************************END OF FILE***************************************************/

