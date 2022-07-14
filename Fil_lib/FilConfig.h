    /*!
    *   --------------------------------------------------------------------------
    *                ///Fast Initialization Library Configuration File\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska, Evgeny Garanin.
    *   @date 12/06/2022 - last update version FIL STM32
    *
    */

/*!
*   FIL STM32 Driver
*   @file <FilConfig.h>
*   @note [FIL:Configuration] This file include driver Fast Initialization Library(FIL) for STM32 controllers
*/

#pragma once
#include "main.h"

/*!
*   @arg 1 - RCR Development Board #1
*   @arg 2 - RCR Development Board #2
*   @arg 3 - RCR Development Board #3
*/
#define _configUSEBoards                3

#define configUSE_RCC                   1
#define configUSE_GPIO                  1
#define configUSE_TIM                   1
#define configUSE_I2C                   0
#define configUSE_DMA                   1
#define configUSE_ADC                   0
#define configUSE_EXTI                  0
#define configUSE_RTC                   0
#define configUSE_USART                 1
#define configUSE_FREERTOS              0
#define configUSE_DeprecatedFunctions   0

#define _configCALC_RCC                 1
#define _configCALC_TIM                 1
#define _configCALC_USART               1
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

#if (_configUSEBoards != 0 )
    #if (_configUSEBoards == 1) // Development Board №1
// none
    #endif /*Development Board №1*/
    #if (_configUSEBoards == 2) // Development Board №2
// none
    #endif /*Development Board №2*/
    #if (_configUSEBoards == 3) // Development Board №3
        #include "RCR_DevBoard_3.h"
        #include "RCR_DevBoard_3_Setup.h"
    #endif /*Development Board №3*/
    #if ((_configUSEBoards < 0) || (_configUSEBoards > 3))
        #error Invalid argument of Development Board
    #endif /*_configUSEBoards*/
#endif /*_configUSEBoards*/

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
#if(configUSE_I2C == 1)
    #include "I2C.h"
#endif /*configUSE_I2C*/
#if(configUSE_USART == 1)
    #include "USART.h"
#endif /*configUSE_USART*/
#if(configUSE_DMA == 1)
    #include "DMA.h"
    #include "DMA_FIFOBuffers.h"
#endif /*configUSE_DMA*/
