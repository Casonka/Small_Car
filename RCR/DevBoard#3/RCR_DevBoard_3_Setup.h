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
/*!
*   @note [RCR] Configuration Development Board #3
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
    InitPeriph;         \
    InitTimers;         \
    InitUSART;          }

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

#define InitTimers {\
    TimPWMConfigure(TIM1,0x1,0x1,1,1,0,0);\
    TimPWMConfigure(TIM2,0x1,0x1,1,1,1,1);\
    TimEncoderConfigure(TIM4);\
    TimPIDConfigure(TIM3,0x1,0x1);}

#define InitInterrupts {\
    NVIC_EnableIRQ(TIM3_IRQn);}

#define InitUSART {\
    USARTBothConfigure(USART1,9600, 0, 1); \
    USARTTransmitterConfigure(USART6, 115200, 0);}


#endif /*STM32F401xx*/
