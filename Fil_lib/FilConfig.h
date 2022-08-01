    /*!
    *   --------------------------------------------------------------------------
    *                ///Fast Initialization Library Configuration File\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska, Evgeny Garanin.
    *   @date 28/06/2022 - last update version FIL STM32
    *
    */

/*!
*   FIL STM32 Driver
*   @file <FilConfig.h>
*   @note [FIL:Configuration] This file include driver Fast Initialization Library(FIL) for STM32 controllers
*/

#pragma once
#include "main.h"

#define configUSE_RCC                   1
#define configUSE_GPIO                  1
#define configUSE_TIM                   1
#define configUSE_USART                 1
#define configUSE_DMA                   0
#define configUSE_I2C                   0
#define configUSE_ADC                   1
#define configUSE_ADC_Manually          0
#define configUSE_EXTI                  1
#define configUSE_RTC                   0
#define configUSE_FREERTOS              1
#define configUSE_DeprecatedFunctions   0

#define _configCALC_RCC                 1
#define _configCALC_TIM                 1
#define _configCALC_USART               1
#define _configCALC_Regulators          0
#define _configCALC_Matrix              0
/*!
*   Version control
*
*/
#if  !defined(STM32F40_41xxx) && !defined(STM32F401xx)
    #error Not supported on another devices
    #pragma message "Supported devices:"
    #pragma message "STM32F407VGT6, STM32F407VET6"
    #pragma message "STM32F401CCU6"
#endif /*Supporting device securing end*/

/*!
*   @note [FIL:FreeRTOS] Include FreeRTOS in project
*/
#if(configUSE_FREERTOS == 1)
    /*!
    *   @note [FIL:FreeRTOS] Настройка отвечает за подключение операционной системы в проект
    *   Содержит все файлы необходимые для работы многопоточного приложения
    *   Только для опытных пользователей
    */
    #include "FreeRTOS.h"       // main FreeRTOS kernel file
    #include "FreeRTOSConfig.h" // main configuration file
    #include "task.h"           //file for initialization tasks
    #include "queue.h"  /// работа с очередями
    #include "semphr.h" /// работа с отложенным прерыванием(семафорами)
    #include "croutine.h" /// работа с сопрограммами
    #include "timers.h" /// работа с программными таймерами
    #include "event_groups.h" // работа с группами событий
    #include "stream_buffer.h" // работа с потоками сообщений
    //-----------------------------------------------------------------
    // custom files
    #include "robot_tasks.h"    // tasks list
    //-----------------------------------------------------------------
#endif /*configUSE_FREERTOS*/

#if(configUSE_RCC == 1)
    #include "RCC.h"
#endif /*configUSE_RCC*/
#if(configUSE_GPIO == 1)
    #include "GPIO.h"
#endif /*configUSE_GPIO*/
#if(configUSE_TIM == 1)
    #include "TIM.h"
#endif /*configUSE_TIM*/
#if(configUSE_USART == 1)
    #include "USART.h"
#endif /*configUSE_USART*/
#if(configUSE_DMA == 1)
    #include "DMA.h"
    #include "DMA_FIFOBuffers.h"
#endif /*configUSE_DMA*/
#if(configUSE_ADC == 1)
    #include "ADC.h"
#endif /*configUSE_ADC*/
#if(configUSE_I2C == 1)
    #include "I2C.h"
#endif /*configUSE_I2C*/
#if(configUSE_EXTI == 1)
    #include "EXTI.h"
#endif /*configUSE_EXTI*/

