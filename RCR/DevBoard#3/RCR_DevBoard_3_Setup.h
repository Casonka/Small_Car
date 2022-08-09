/*!
    *   --------------------------------------------------------------------------
    *                       ///RCR Main Board Configuration file #3\\
    *   --------------------------------------------------------------------------
    *   @file RCR_DevBoard_3_Setup.h
    *   @note [RCR] Setup pins, interfaces for Development Board #3
    *   @author RCR group developers - Caska, Evgeny Garanin
    *   @date   02/08/2022 - last update
    *
*/
#pragma once

#include "FilConfig.h"
#include "RCR_DevBoard_3.h"

#if defined(STM32F401xx)
//-----------------------------------------------------------------//
/*!
*   @note [RCR] Configuration Development Board #3
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

#define __config_TIM5_PSC        (420 - 1)
#define __config_TIM5_ARR        (4000)
#define __config_TIM5_CH1        1
#define __config_TIM5_CH2        0
#define __config_TIM5_CH3        0
#define __config_TIM5_CH4        0

#define MAX_PWM         __config_TIM1_ARR
#define MAX_PWM_SERVO   __config_TIM5_ARR

/*!
*   @note [RCR] Regulator configuration { Car's engine }
*/
#define __config_Regulator_ON           (1)
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
#define __config_USART6_Baudrate    (115200)

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
#define __configMAP_Multiplexor         (8)
/////////////////////////////////////////////////
#define __configUSE_SENSOR_1            __configMAP_Potentiometer
#define __configUSE_SENSOR_2            __configMAP_Multiplexor
#define __configUSE_SENSOR_3            (-1)
#define __configUSE_SENSOR_4            (-1)
#define __configUSE_SENSOR_5            (-1)
#define __configUSE_SENSOR_6            (-1)
#define __configUSE_SENSOR_7            (-1)
#define __configUSE_SENSOR_8            (-1)
#define __configUSE_SENSOR_9            (-1)
#define __configUSE_SENSOR_10           (-1)

#define __configADC_InterruptRequest    (1)
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
*       @arg ADC_480_CYCLES - 480[cycles]
*       @arg ADC_144_CYCLES - 144[cycles]
*       @arg ADC_112_CYCLES - 112[cycles]
*       @arg ADC_84_CYCLES  -  84[cycles]
*       @arg ADC_56_CYCLES  -  56[cycles]
*       @arg ADC_28_CYCLES  -  28[cycles]
*       @arg ADC_15_CYCLES  -  15[cycles]
*       @arg ADC_3_CYCLES   -   3[cycles]
*/
#define __configADC_CYCLES              (ADC_480_CYCLES)

/*!
*   @info Supported divider for ADC bus
*   @note [RCR] ADC Freq = APB2(example 84 MHz) / __configADC_DIVIDER
*       @arg 0 - divided by 2
*       @arg 1 - divided by 4
*       @arg 2 - divided by 6
*       @arg 3 - divided by 8
*/
#define __configADC_DIVIDER             (3)
/*!
*   @note [RCR] IIC(I2C) configuration
*/
#define MPU9250_ADDR                (0x34)     // Gyro Accelerometer Magnetometer
#define SSD1305_ADDR                (0x00)     // LCD monitor
//-----------------------------------------------------------------//
/*!
*   @brief General Initialization. This sector is custom adding by author.
*          You can modify and use some new functions that you need.
*/
#define Board_Config       {\
    SetPWR;                 \
    SetGPIOA;               \
    SetGPIOB;               \
    SetGPIOC;               \
    SetTIM1;                \
    SetTIM3;                \
    SetTIM4;                \
    SetTIM5;                \
    SetDMA2;                \
    SetADC1;                \
    SetUSART1;              \
    SetUSART6;              \
    SetI2C1;                \
    SetSYSCFG;              \
    InitPeriph;             \
    InitTimers;             \
    InitUSART;              \
    InitInterrupts;         \
    SysTick_Config(__config_SysTick_Counter);}

/*!
*   @brief Initialization pins
*/
#define InitPeriph {\
    conf_pin(BTN1_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(MULPLXA_PIN,  GENERAL, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(MULPLXB_PIN,  GENERAL, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(MULPLXC_PIN,  GENERAL, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(INT_PIN,  GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(LED_PIN,  GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(ADC_TOP, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(POT_PIN, ANALOG, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(EXTI1_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(EXTI2_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(EXTI3_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(EXTI4_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(EXTI5_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(BTN1_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_af(BTN1_PWM_PIN, AF1);\
    conf_pin(BTN2_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_af(BTN2_PWM_PIN, AF1);\
    conf_pin(ENCODER1A_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_af(ENCODER1A_PIN, AF2);\
    conf_pin(ENCODER1B_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_af(ENCODER1B_PIN, AF2);\
    conf_pin(ENCODER2A_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP);\
    conf_af(ENCODER2A_PIN, AF2);\
    conf_pin(ENCODER2B_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP);\
    conf_af(ENCODER2B_PIN, AF2);\
    conf_pin(I2C_SDA_PIN, ALTERNATE, PUSH_PULL, FAST_S, PULL_UP);\
    conf_af(I2C_SDA_PIN, AF4);\
    conf_pin(I2C_SCL_PIN, ALTERNATE, PUSH_PULL, FAST_S, PULL_UP);\
    conf_af(I2C_SCL_PIN, AF4);}

/*!
*   @brief Initialization timers
*       @arg TIM1 - Wheels engine
*       @arg TIM5 - Servo management
*       @arg TIM3 - PID Calculating (Interrupt)
*           @attention check interrupts file for TIM
*               @file TIM.c
*       @arg TIM4 - Encoder monitoring
*/
#define InitTimers                                                                                                                     {\
    TimPWMConfigure(TIM1,__config_TIM1_PSC,__config_TIM1_ARR,__config_TIM1_CH1,__config_TIM1_CH2,__config_TIM1_CH3,__config_TIM1_CH4);  \
    TimPWMConfigure(TIM5,__config_TIM5_PSC,__config_TIM5_ARR,__config_TIM5_CH1,__config_TIM5_CH2,__config_TIM5_CH3,__config_TIM5_CH4);  \
    TimEncoderConfigure(TIM4);                                                                                                          \
    TimPIDConfigureAutomatic(TIM3,__config_Regulator_FREQ);                                                                             }

/*!
*   @brief Initialization interrupts
*/
#define InitInterrupts {\
    NVIC_EnableIRQ(TIM3_IRQn);\
    NVIC_EnableIRQ(ADC_IRQn);}

/*!
*   @brief Initialization uart/usart
*/
#define InitUSART {\
    USARTBothConfigure(USART1,__config_USART1_Baudrate, 0, 0); \
    USARTTransmitterConfigure(USART6, __config_USART6_Baudrate, 0);}

#endif /*STM32F401xx*/
