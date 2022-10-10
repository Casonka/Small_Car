/*!
    *   --------------------------------------------------------------------------
    *                       ///RCR Main Board Configuration file #2\\\
    *   --------------------------------------------------------------------------
    *   @file RCR_DevBoard_2_Setup.h
    *   @note [RCR] Setup pins, interfaces for Development Board #2
    *   @author RCR group developers - Caska, Evgeny Garanin
    *   @date   02/08/2022 - last update
    *
*/
#pragma once

#include "FilConfig.h"
#include "RCR_DevBoard_2.h"

#if defined(STM32F401xx)
/*!
*   @note [RCR] This settings transport to FIL Driver
*/
#define __configUSE_RCC                   1
#define __configUSE_GPIO                  1
#define __configUSE_TIM                   1
#define __configUSE_USART                 1
#define __configUSE_DMA                   0
#define __configUSE_I2C                   1
#define __configUSE_ADC                   1
#define __configUSE_EXTI                  1
#define __configUSE_RTC                   0
#define __configUSE_FREERTOS              0

#define __configCALC_RCC                  1
#define __configCALC_TIM                  1
#define __configCALC_USART                1
#define __configCALC_Regulators           0
#define __configCALC_Matrix               0
#define __configCALC_I2C_SCANNING         1

//-----------------------------------------------------------------//
/*!
*   @note [RCR] Configuration Development Board #2
*/
//-----------------------------------------------------------------//
#define __config_SysTick_Counter        (84000)     // 1Hz

/*!
*   @note [RCR] Timers configuration
*/

#define __config_TIM1_PSC        (84 - 1)
#define __config_TIM1_ARR        (200)
#define __config_TIM1_CH1        1
#define __config_TIM1_CH2        0
#define __config_TIM1_CH3        0
#define __config_TIM1_CH4        0

#define MAX_PWM         __config_TIM1_ARR

/*!
*   @note [RCR] Regulator configuration { Car's engine }
*/
#define __config_Regulator_ON           (1)
#define __config_Regulator_Source       (TIM3)
#define __config_Regulator_FREQ         (100)
#define __config_Regulator_P_K          (5.0)
#define __config_Regulator_I_K          (1.5)
#define __config_Regulator_D_K          (0.5)
#define __config_MAX_SUM_ERROR          (6.0)
#define __config_OUTPUT_END             (50.0)
#define __config_Regulator_ERROR_END    (0.0)
#define __config_MAX_OUTPUT             (1.0)
#define __config_MIN_OUTPUT             (0.08)

#define PI2                             (6.28314)
#define REDUCTION_ENGINE                (150)
#define REDUCTION_DIFF                  (1.2)
#define REDUCTION_SUM                   (REDUCTION_ENGINE + REDUCTION_DIFF)
#define R_WHEEL                         (0.048)
#define WHEEL_LENGTH                    (PI2 * R_WHEEL)
#define DISKETS_ON_ROTATE               (41000.0)
#define COMPENSATE_VALUE                (0.9)
#define DISK_TO_REAL                    ((float)(WHEEL_LENGTH / DISKETS_ON_ROTATE * COMPENSATE_VALUE))
#define TIME                            ((float)(1.0 / __config_Regulator_FREQ))

/*!
*   @note [RCR] UART/USART configuration
*/
#define __config_USART1_Baudrate    (9600)
#define __config_USART2_Baudrate    (115200)
#define __configUSART_InterruptRequest (0)

#define __configUSE_ModBus          (0)
/*!
*   @info ModBus binary - 1; ModBus ASCII - 2
*/
#define __configMODBUS_Type         (0)
#if(__configUSE_ModBus == 1)
    #include "ModBus_conf.h"
    #include "ModBus.h"
#endif /*__configUSE_ModBus*/
/*!
*   @note [RCR] ADC configuration
*       @warning ADC Modes: 0 - ADC Off
*                           1 - ADC Simple single channel parsing
*                           2 - ADC Simple multi channel parsing
*                           3 - ADC one Multiplexer parsing
*                           4 - ADC two Multiplexer parsing(or 4 custom inputs)
*                           5 - Developer Mode (All Manually)
*/
#define __configADC_Mode                (4)
#define __configCONVERT_Volts           (0)
#define __configUSE_Battery_Charging    (0)
#define __configUSE_Temperature_Sensor  (0)
// custom variables
#define __configMAP_Potentiometer       (4)
#define __configMAP_Multiplexer1        (8)
#define __configMAP_Multiplexer2        (9)
/////////////////////////////////////////////////
#define __configUSE_SENSOR_1            __configMAP_Potentiometer
#define __configUSE_SENSOR_2            __configMAP_Multiplexer1
#define __configUSE_SENSOR_3            __configMAP_Multiplexer2
#define __configUSE_SENSOR_4            (-1)
#define __configUSE_SENSOR_5            (-1)
#define __configUSE_SENSOR_6            (-1)
#define __configUSE_SENSOR_7            (-1)
#define __configUSE_SENSOR_8            (-1)
#define __configUSE_SENSOR_9            (-1)
#define __configUSE_SENSOR_10           (-1)

#define __configADC_InterruptRequest    (0)
/*!
*   @info Supported divider ADC frequency
*       @note [RCR] ADC Freq = APB2 Clock (exmp. 84 MHz) / divider
*       @arg 0 - divided by 2
*       @arg 1 - divided by 4
*       @arg 2 - divided by 6
*       @arg 3 - divided by 8
*/
#define __configADC_Divider              (3)
/*!
*   @info Supported resolution ADC data
*       @arg 12[bit]
*       @arg 10[bit]
*       @arg 8[bit]
*       @arg 6[bit]
*/
#define __configADC_RESOLUTION          (12)        // 12-bit resolution
/*!
*   @info Supported cycles mode ADC
*       @arg 480[cycles]
*       @arg 144[cycles]
*       @arg 112[cycles]
*       @arg 84[cycles]
*       @arg 56[cycles]
*       @arg 28[cycles]
*       @arg 15[cycles]
*       @arg 3[cycles]
*/
#define __configADC_CYCLES              (ADC_480_CYCLES)
/*!
*   @note [RCR] IIC(I2C) configuration
*/
// General IIC Configuration
#define __configI2C_InterruptRequest (0)
#define __configI2C_FindListSize     (5)
#define __configI2C_TIMEOUT         (20000)

// configuration LCD
#define __configI2C_LCD_SOURCE      (I2C1)
#define __configUSE_LVGL             (0)
#define SSD1306_ADDR                (0x78)     // LCD monitor

// configuration Gyro
#define __configI2C_MPU_SOURCE      (I2C1)
#define __configMPU_USE_Calibration  (1)
#define __configMPU_Scale            (0)
#define MPU9250_ADDR                (0x68)   // Gyro Accelerometer Magnetometer

//-----------------------------------------------------------------//
/*!
*   @brief General Initialization
*/
#define Board_Config                           {\
    SetPWR;                                     \
    SetSYSCFG;                                  \
    SetGPIOA;                                   \
    SetGPIOB;                                   \
    InitPeriph;                                 \
    SetTIM1;                                    \
    SetTIM3;                                    \
    SetTIM4;                                    \
    SetTIM5;                                    \
    InitTimers;                                 \
    SetADC1;                                    \
    ADC_Init(ADC1);                             \
    SetI2C1;                                    \
    SetUSART1;                                  \
    SetUSART2;                                  \
    SysTick_Config(__config_SysTick_Counter);   \
    InitInterrupts;                             }

/*!
*   @brief Initialization pins
*/
#define InitPeriph                                                     {\
    conf_pin(BTN1_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);     \
    conf_pin(MULPLXA_PIN,  GENERAL, PUSH_PULL, FAST_S, PULL_DOWN);      \
    conf_pin(MULPLXB_PIN,  GENERAL, PUSH_PULL, FAST_S, PULL_DOWN);      \
    conf_pin(MULPLXC_PIN,  GENERAL, PUSH_PULL, FAST_S, PULL_DOWN);      \
    conf_pin(INT_PIN,  GENERAL, PUSH_PULL, FAST_S, PULL_DOWN);          \
    conf_pin(LED_PIN,  GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);         \
    conf_pin(ADC_TOP, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);           \
    conf_pin(ADC_BOTTOM, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);        \
    conf_pin(POT_PIN, ANALOG, PUSH_PULL, FAST_S, PULL_DOWN);            \
    conf_pin(EXTI1_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);           \
    conf_pin(EXTI2_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);           \
    conf_pin(EXTI3_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);           \
    conf_pin(EXTI4_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);           \
    conf_pin(EXTI5_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);           \
    conf_pin(BTN1_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);   \
    conf_af(BTN1_PWM_PIN, AF1);                                         \
    conf_pin(BTN2_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);   \
    conf_af(BTN2_PWM_PIN, AF1);                                         \
    conf_pin(ENCODER1A_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);  \
    conf_af(ENCODER1A_PIN, AF2);                                        \
    conf_pin(ENCODER1B_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);  \
    conf_af(ENCODER1B_PIN, AF2);                                        \
    conf_pin(ENCODER2A_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP);      \
    conf_af(ENCODER2A_PIN, AF2);                                        \
    conf_pin(ENCODER2B_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP);      \
    conf_af(ENCODER2B_PIN, AF2);                                        \
    conf_pin(TX2_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);        \
    conf_af(TX2_PIN,AF7);                                               \
    conf_pin(RX2_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);        \
    conf_af(RX2_PIN,AF7);                                               \
    conf_pin(TX3_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);        \
    conf_af(TX3_PIN,AF7);                                               \
    conf_pin(RX3_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);        \
    conf_af(RX3_PIN,AF7);                                               \
    conf_pin(I2C_SDA_PIN, ALTERNATE, OPEN_DRAIN, FAST_S, NO_PULL_UP);   \
    conf_af(I2C_SDA_PIN, AF4);                                          \
    conf_pin(I2C_SCL_PIN, ALTERNATE, OPEN_DRAIN, FAST_S, NO_PULL_UP);   \
    conf_af(I2C_SCL_PIN, AF4);                                          }

/*!
*   @brief Initialization timers
*       @arg TIM1 - Wheels engine
*       @arg TIM3 - Encoder#1 counter
*       @arg TIM4 - PID Calculating (Interrupt)
*           @attention check interrupts file for TIM
*               @file TIM.c
*       @arg TIM5 - Encoder#2 counter
*/
#define InitTimers                                                                                                                     {\
    TimPWMConfigure(TIM1,__config_TIM1_PSC,__config_TIM1_ARR,__config_TIM1_CH1,__config_TIM1_CH2,__config_TIM1_CH3,__config_TIM1_CH4);  \
    TimEncoderConfigure(TIM3);                                                                                                          \
    TimEncoderConfigure(TIM5);                                                                                                          \
    TimPIDConfigureAutomatic(__config_Regulator_Source,__config_Regulator_FREQ);                                                        }

/*!
*   @brief Initialization interrupts
*/
#define InitInterrupts                                                     {\
    NVIC_EnableIRQ(TIM5_IRQn);                                              \
    if(__configADC_InterruptRequest == 1) NVIC_EnableIRQ(ADC_IRQn);         \
    if(__configUSART_InterruptRequest == 1) NVIC_EnableIRQ(USART1_IRQn);    \
    if(__configUSART_InterruptRequest == 1) NVIC_EnableIRQ(USART2_IRQn);    \
    if(__configI2C_InterruptRequest == 1) NVIC_EnableIRQ(I2C1_ER_IRQn);     }

/*!
*   @brief Initialization uart/usart
*/
#define InitUSART {\
    USARTBothConfigure(USART1,__config_USART1_Baudrate, 0, 0); \
    USARTTransmitterConfigure(USART6, __config_USART6_Baudrate, 0);}


#endif /*STM32F401xx*/
