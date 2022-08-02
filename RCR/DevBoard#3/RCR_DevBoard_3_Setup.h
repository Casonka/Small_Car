#pragma once
#include "FilConfig.h"
#include "RCR_DevBoard_3.h"
/*!
*
*   @file RCR_DevBoard_3_Setup.h
*   @note [RCR] Setup pins, interfaces for Development Board #3
*   @author RCR group developers - Caska, Evgeny Garanin
*   @date   02/08/2022 - last update
*
*/

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

#define __config_TIM2_PSC        (420 - 1)
#define __config_TIM2_ARR        (2000)
#define __config_TIM2_CH1        1
#define __config_TIM2_CH2        0
#define __config_TIM2_CH3        0
#define __config_TIM2_CH4        0

#define MAX_PWM         __config_TIM1_ARR
#define MAX_PWM_SERVO   __config_TIM2_ARR

/*!
*   @note [RCR] Regulator configuration { Car's engine }
*/
#define __config_Regulator_ON           (1)
#define __config_Regulator_FREQ         (100)
#define __config_Regulator_P_K          (0.0)
#define __config_Regulator_I_K          (0.0)
#define __config_Regulator_D_K          (0.0)
#define __config_MAX_SUM_ERROR          (0.0)
#define __config_OUTPUT_END             (50.0)
#define __config_Regulator_ERROR_END    (0.0)
#define __config_MAX_OUTPUT             (1.0)
#define __config_MIN_OUTPUT             (0.01)

#define PI                              (3.14157)
#define REDUCTION_ENGINE                (150)
#define REDUCTION_DIFF                  (1.2)
#define REDUCTION_SUM                   (REDUCTION_ENGINE + REDUCTION_DIFF)
#define R_WHEEL                         (0.09)
#define DISKETS_ON_ROTATE               (32400)
#define WHEEL_LENGTH                    (2 * PI * R_WHEEL)
#define TIME                            (1 / __config_Regulator_FREQ)
/*!
*   @note [RCR] UART/USART configuration
*/
#define __config_USART1_Baudrate    (9600)
#define __config_USART6_Baudrate    (115200)

/*!
*   @note [RCR] IIC(I2C) configuration
*/
#define MPU9250_ADDR                (0x34)     // Gyro Accelerometer Magnetometer
#define SSD1305_ADDR                (0x00)
//-----------------------------------------------------------------//
/*!
*   @brief General Initialization
*/
#define Board_Config       {\
    SetPWR;                 \
    SetGPIOA;               \
    SetGPIOB;               \
    SetGPIOC;               \
    SetTIM1;                \
    SetTIM2;                \
    SetTIM3;                \
    SetTIM4;                \
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
    SysTick_Config(__config_SysTick_Counter);  }

/*!
*   @brief Initialization pins
*/
#define InitPeriph {\
    conf_pin(BTN1_DIR_PIN, GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(MULPLXA_PIN,  GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(MULPLXB_PIN,  GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(MULPLXC_PIN,  GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(INT_PIN,  GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(LED_PIN,  GENERAL, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(ADC_TOP, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(POT_PIN, ANALOG, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_pin(EXTI1_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(EXTI2_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(EXTI3_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(EXTI4_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(EXTI5_PIN, INPUT, PUSH_PULL, FAST_S, PULL_DOWN);\
    conf_pin(BTN1_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_af(BTN1_PWM_PIN, AF1);\
    conf_pin(BTN2_PWM_PIN, ALTERNATE, PUSH_PULL, FAST_S, NO_PULL_UP);\
    conf_af(BTN2_PWM_PIN, AF1);\
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
*       @arg TIM2 - Servo management
*       @arg TIM3 - PID Calculating (Interrupt)
*           @attention check interrupts file for TIM
*               @file TIM.c
*       @arg TIM4 - Encoder monitoring
*/
#define InitTimers {\
    TimPWMConfigure(TIM1,__config_TIM1_PSC,__config_TIM1_ARR,1,1,0,0);\
    TimPWMConfigure(TIM2,__config_TIM2_PSC,0x1,1,1,1,1);\
    TimEncoderConfigure(TIM3);\
    TimPIDConfigureAutomatic(TIM4,__config_Regulator_FREQ);}

/*!
*   @brief Initialization interrupts
*/
#define InitInterrupts {\
    NVIC_EnableIRQ(TIM4_IRQn);}

/*!
*   @brief Initialization uart/usart
*/
#define InitUSART {\
    USARTBothConfigure(USART1,__config_USART1_Baudrate, 0, 0); \
    USARTTransmitterConfigure(USART6, __config_USART6_Baudrate, 0);}

/*!
*   @brief Initialization servomotors
*/
#define InitServo   setServo(&Servo1, BIG_BLACK_SERVA, 20, 0x500, 0x100, 20)

#endif /*STM32F401xx*/
