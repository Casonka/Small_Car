#pragma once
#include "FilConfig.h"

/*!
*
*   @file RCR_DevBoard_3_Setup.h
*   @note [RCR] Setup pins for Development Board #3
*   @author RCR group developers - Caska, Evgeny Garanin
*   @date   13/07/2022 - last update
*
*/

#if defined(STM32F401xx)
//-----------------------------------------------------------------//
/*!
*   @note [RCR] Configuration Development Board #3
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

#define __config_USART1_Baudrate    (9600)
#define __config_USART6_Baudrate    (115200)

#define MAX_PWM         __config_TIM1_ARR
#define MAX_PWM_SERVO   __config_TIM2_ARR
//-----------------------------------------------------------------//
/*!
*   @brief General Initialization
*/
#define Board_Config   {\
    SetPWR;             \
    SetGPIOA;           \
    SetGPIOB;           \
    SetGPIOC;           \
    SetTIM1;            \
    SetTIM4;            \
    SetDMA2;            \
    SetADC1;            \
    SetUSART1;          \
    SetUSART6;          \
    SetI2C1;            \
    SetSYSCFG;          \
    InitPeriph;         \
    InitTimers;         \
    InitUSART;          \
    InitInterrupts;     \
    }

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
    conf_pin(ENCODER1A_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP);\
    conf_af(ENCODER1A_PIN, AF2);\
    conf_pin(ENCODER1B_PIN, ALTERNATE, PUSH_PULL, LOW_S, PULL_UP);\
    conf_af(ENCODER1B_PIN, AF2);}

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
    TimEncoderConfigure(TIM4);\
    TimPIDConfigure(TIM3,0x1,0x1);}

/*!
*   @brief Initialization interrupts
*/
#define InitInterrupts {\
    NVIC_EnableIRQ(TIM3_IRQn);}

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
