    /*!
    *   --------------------------------------------------------------------------
    *                       ///ADC initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 18/07/2022 - last update version ADC
    *
    *       @note [FIL:ADC] Configuration file ADC
    */
#pragma once
#include "FilConfig.h"

#if(configUSE_ADC == 1)
//----------------------------------------ADC Length-------------------------------------------------------------//
#define ADC_3_CYCLES    0
#define ADC_15_CYCLES   1
#define ADC_28_CYCLES   2
#define ADC_56_CYCLES   3
#define ADC_84_CYCLES   4
#define ADC_112_CYCLES  5
#define ADC_144_CYCLES  6
#define ADC_480_CYCLES  7

#define ADC_IN_0    __configUSE_SENSOR_1
#define ADC_IN_1    __configUSE_SENSOR_2
#define ADC_IN_2    __configUSE_SENSOR_3
#define ADC_IN_3    __configUSE_SENSOR_4
#define ADC_IN_4    __configUSE_SENSOR_5
#define ADC_IN_5    __configUSE_SENSOR_6
#define ADC_IN_6    __configUSE_SENSOR_7
#define ADC_IN_7    __configUSE_SENSOR_8
#define ADC_IN_8    __configUSE_SENSOR_9
#define ADC_IN_9    __configUSE_SENSOR_10

#if(__configADC_RESOLUTION == 12)
    #define K_RESOLUTION    4096.0
#elif(__configADC_RESOLUTION == 10)
    #define K_RESOLUTION    1024.0
#elif(__configADC_RESOLUTION == 8)
    #define K_RESOLUTION    256.0
#elif(__configADC_RESOLUTION == 6)
    #define K_RESOLUTION    64.0
#endif /*__configADC_RESOLUTION*/
//----------------------------------------ADC Functions----------------------------------------------------------//
    /*!
    *   @brief  ADCScanConfigure(ADC,IsDMA) - Simple configuration ADC (Scan mode without adding channels)
    *       @arg ADC - Number of ADC
    *       @arg IsDMA - DMA mode: 0 - DMA off
    *                              1 - DMA on
    *
    */
    #define ADCScanConfigure(ADC)             {\
        SetADCScan(ADC);                       \
        SetADCDMA(ADC);                        \
        SetADCCont(ADC);                       \
        SetADCAdon(ADC);                       }

    /*!
    *   @brief  ADCAllScanConfigure(ADC,LENGTH,
    *           CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8,CH9,CH10,CH11,CH12,CH13,CH14,CH15,CH16,
    *           CYCLES) - Configuration all channels ADC (Scan mode)
    *       @arg ADC - Number of ADC
    *       @arg LENGTH - Regular channel sequence length
    *       @arg CHx - Connect ADC_IN pins to conversion queue
    *       @arg NUMBER - NUMBER of ADC_IN active pins
    *       @arg CYCLES - Sample time selection
    *
    */
    #define ADCAllScanConfigure(ADC,LENGTH,                                         \
            CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8,CH9,CH10,CH11,CH12,CH13,CH14,CH15,CH16, \
            CYCLES)                                                                {\
        SetADCLength(ADC,LENGTH);                                                   \
        ConfADCSQ1(ADC,CH1,CH2,CH3,CH4);                                            \
        ConfADCSQ2(ADC,CH5,CH6,CH7,CH8,CH9,CH10);                                   \
        ConfADCSQ3(ADC,CH11,CH12,CH13,CH14,CH15,CH16);                              \
        ConfADCSmpr(ADC,LENGTH,CYCLES);                                             \
        SetADCScan(ADC);                                                            \
        SetADCDDS(ADC);                                                             \
        SetADCDMA(ADC);                                                             \
        SetADCCont(ADC);                                                            \
        SetADCAdon(ADC);                                                            \
        ADCStartRegular(ADC);                                                       }

    /*!
    *   @brief  ADCSimpleConfigure(ADC) - Configuration ADC simple
    *       @arg ADC - Number of ADC
    *
    */
    #define ADCSimpleConfigure(ADC)                                            {\
        SetADCAdon(ADC);                                                        \
        SetADCCont(ADC);                                                        \
        ADCStartRegular(ADC);                                                   \
        if(CheckADCJStart(ADC) == 1) ADCStartInjected(ADC);                     \
        (__configADC_InterruptRequest == 1) ? SetADCRegularInterrupt(ADC) :     \
                                              ResetADCRegularInterrupt(ADC);    }
//----------------------------------------REGULAR----------------------------------------------------------------//
    /*!
    *   @brief  ADCAddRegularChannel(ADC,CHANNEL,CYCLES) - Adding new channel to conversions ADC
    *       @arg ADC - Number of ADC
    *       @arg CHANNEL - Number of target channel
    *       @arg CYCLES - Sample time selection
    *
    */
    #define ADCAddRegularChannel(ADC,CHANNEL,CYCLES)                                       {\
                        static char CH;                                                     \
                        ADC->SQR1 &= ~(0xF << 20);                                          \
                        ADC->SQR1 |= CH << 20;                                              \
                        *(&ADC->SQR3 - (CH / 6)) |= CHANNEL << ((CH * 5) % 30);             \
                        *(&ADC->SMPR2 - ((CH / 10)*0x4)) |= CYCLES << ((CH * 3) % 30);      \
                        CH++;                                                               }

    /*!
    *   @brief  AddADCSingleChannel(ADC,CHANNEL,CYCLES) - Adding single channel to conversions ADC
    *       @arg ADC - Number of ADC
    *       @arg CHANNEL - Number of target channel
    *       @arg CYCLES - Sample time selection
    *           @attention This function delete old channel from ADC list before writing new target channel
    */
    #define ADCAddSingleChannel(ADC,CHANNEL,CYCLES)                                        {\
                        ADC->CR2 &= ~ADC_CR2_ADON;                                          \
                        ADC->SQR3 &= ~(0x1F);                                               \
                        ADC->SMPR2 &= ~(0x7);                                               \
                        ADC->SQR3 |= CHANNEL;                                               \
                        ADC->SMPR2 |= CYCLES;                                               \
                        ADC->CR1 &= ~ADC_CR1_SCAN;                                          \
                        ADC->CR2 |= (ADC_CR2_ADON | ADC_CR2_CONT);                          }

//----------------------------------------INJECTED----------------------------------------------------------------//
    /*!
    *   @brief  ADCAddInjectedChannel(ADC,CHANNEL,CYCLES) - Adding new injected channel to conversions ADC
    *       @arg ADC - Number of ADC
    *       @arg CHANNEL - Number of target injected channel
    *       @arg CYCLES - Sample time selection
    *
    */
    #define ADCAddInjectedChannel(ADCx,CHANNEL,CYCLES)                                             {\
                        static char JCH;                                                            \
                        ADCx->JSQR &= ~(0xF << 20);                                                 \
                        ADCx->JSQR |= (JCH << 20);                                                  \
                        ADCx->JSQR |= (CHANNEL << ((JCH * 5) % 30));                                \
                        *(&ADCx->SMPR2 - ((JCH / 10)*0x4)) |= (CYCLES << (JCH * 3) % 30);           \
                        JCH++;                                                                      }
    /*!
    *   @brief  ADCAddInjectedGroups(ADC,NUMBER,J1,J2,J3,J4) -
    *       @arg ADC - Number of ADC
    *       @arg NUMBER -
    *       @arg Jx -
    */
    #define ADCAddInjectedGroup(ADC,NUMBER,J1,J2,J3,J4)                                        {\
                        ADC->JSQR &= ~(0x3FFFFF);                                               \
                        ADC->JSQR |= (NUMBER << 20);                                            \
                        ADC->JSQR |= ((J1) | (J2 << 5) | (J3 << 10) | (J4 << 15));              \
                        SetADCContInjected(ADC);                                                \
                        (__configADC_InterruptRequest == 1) ? SetADCInjectedInterrupt(ADC) :    \
                                                              ResetADCInjectedInterrupt(ADC);   }

//----------------------------------------Set state----------------------------------------------------------------------------------------------------------------------------//
    #define SetADCSMP1(ADC,CYCLES)          ((ADC->SMPR1) |= ADCSmpr1(CYCLES))
    #define SetADCSMP2(ADC,CYCLES)          ((ADC->SMPR2) |= ADCSmpr2(CYCLES))
    #define SetADCLength(ADC,LENGTH)        ((ADC->SQR1) |= (LENGTH << 20))
    #define SetADCSQ1(ADC,CH1,CH2,CH3,CH4)  ((ADC->SQR1) |= ADCSQ1(CH1,CH2,CH3,CH4))
    #define SetADCSQ2(ADC,CH5,CH6,CH7,CH8,CH9,CH10) ((ADC->SQR2) |= ADCSQ2(CH5,CH6,CH7,CH8,CH9,CH10))
    #define SetADCSQ3(ADC,CH11,CH12,CH13,CH14,CH15,CH16) ((ADC->SQR3) |= ADCSQ3(CH11,CH12,CH13,CH14,CH15,CH16))
    #define SetADCScan(ADC)                 ((ADC->CR1) |= (1 << 8))
    #define SetADCDMA(ADC)                  ((ADC->CR2) |= (ADC_CR2_DMA))
    #define SetADCCont(ADC)                 ((ADC->CR2) |= (ADC_CR2_CONT))
    #define SetADCDDS(ADC)                  ((ADC->CR2) |= (ADC_CR2_DDS))
    #define SetADCAdon(ADC)                 ((ADC->CR2) |= (ADC_CR2_ADON))
    #define ADCStartRegular(ADC)            ((ADC->CR2) |= (ADC_CR2_SWSTART))
    #define ADCStartInjected(ADC)           ((ADC->CR2) |= (ADC_CR2_JSWSTART))
    #define SetADCInjectedInterrupt(ADC)    ((ADC->CR1) |= (ADC_CR1_JEOCIE))
    #define SetADCRegularInterrupt(ADC)     ((ADC->CR1) |= (ADC_CR1_EOCIE))
    #define SetADCContInjected(ADC)         ((ADC->CR1) |= (ADC_CR1_JAUTO))
//----------------------------------------Reset state----------------------------------------------------------------------------------------------------------------------------//
    #define ResetADCCont(ADC)               ((ADC->CR2) &= (~ADC_CR2_CONT))
    #define ADCStopRegular(ADC)             ((ADC->CR2) &= (~ADC_CR2_SWSTART))
    #define ResetADCEOCEvent(ADC)           ((ADC->SR) &= (~ADC_SR_EOC))
    #define ResetADCJEOCEvent(ADC)          ((ADC->SR) &= (~ADC_SR_JEOC))
    #define ResetADCOVREvent(ADC)           ((ADC->SR) &= (~ADC_SR_OVR))
    #define ResetADCInjectedInterrupt(ADC)  ((ADC->CR1) &= (~ADC_CR1_JEOCIE))
    #define ResetADCRegularInterrupt(ADC)   ((ADC->CR1) &= (~ADC_CR1_EOCIE))
//----------------------------------------Status monitoring--------------------------------------------------------------------------------------------------------------------//
    #define ADCAnalogWatchdogEvent(ADC)     (((ADC->SR) & (ADC_SR_AWD)))
    #define ADCRegularEndEvent(ADC)         (((ADC->SR) & (ADC_SR_EOC)) >> 1)
    #define ADCInjectedEndEvent(ADC)        (((ADC->SR) & (ADC_SR_JEOC)) >> 2)
    #define ADCInjectedStartEvent(ADC)      (((ADC->SR) & (ADC_SR_JSTRT)) >> 3)
    #define ADCRegularStartEvent(ADC)       (((ADC->SR) & (ADC_SR_STRT)) >> 4)
    #define ADCOverrunEvent(ADC)            (((ADC->SR) & (ADC_SR_OVR)) >> 5)
    #define CheckADCJStart(ADC)             (((ADC->CR1) & (ADC_CR1_JAUTO)) >> 10)
//---------------------------Simple commands reset and set the state-------------------------------------------------------------------------------------------------------------//
    #define ConfADCResolution(ADC,RESOLUTION)               {ADC->CR1 = (((ADC->CR1)&(~(ADC_CR1_RES)))|ADCResolution(RESOLUTION));}
    #define ConfADCLength(ADC,LENGTH)                       {ADC->SQR1 = (((ADC->SQR1)&(~(ADC_SQR1_L)))|ADCLength(LENGTH));}
    #define ConfADCSQ1(ADC,CH1,CH2,CH3,CH4)                 {ADC->SQR1 = (((ADC->SQR1)&(~(0xFFFFF)))|ADCSQ1(CH1,CH2,CH3,CH4));}
    #define ConfADCSQ2(ADC,CH5,CH6,CH7,CH8,CH9,CH10)        {ADC->SQR2 = (((ADC->SQR2)&(~(0x3FFFFFFF)))|ADCSQ2(CH5,CH6,CH7,CH8,CH9,CH10));}
    #define ConfADCSQ3(ADC,CH11,CH12,CH13,CH14,CH15,CH16)   {ADC->SQR3 = (((ADC->SQR3)&(~(0x3FFFFFFF)))|ADCSQ3(CH11,CH12,CH13,CH14,CH15,CH16));}
    #define ConfADCSmpr1(ADC,CYCLES)                        {ADC->SMPR1 = (((ADC->SMPR1)&(~(0x7FFFFFF)))|ADCSmpr1(CYCLES));}
    #define ConfADCSmpr2(ADC,CYCLES)                        {ADC->SMPR2 = (((ADC->SMPR2)&(~(0x3FFFFFFF)))|ADCSmpr2(CYCLES));}
    #define ConfADCSmpr(ADC,NUMBER,CYCLES)         {\
        if(NUMBER > 0) ConfADCSmpr2(ADC,CYCLES);    \
        if(NUMBER > 10) ConfADCSmpr1(ADC,CYCLES);   }

    #define ADCSQ1(CH1,CH2,CH3,CH4)                             ((uint32_t)(CH1 << 15) | (CH2 << 10) | (CH3 << 5)  | (CH4))
    #define ADCSQ2(CH5,CH6,CH7,CH8,CH9,CH10)                    ((uint32_t)(CH5 << 25) | (CH6 << 20) | (CH7 << 15) | (CH8 << 10) | (CH9 << 5)  | (CH10))
    #define ADCSQ3(CH11,CH12,CH13,CH14,CH15,CH16)               ((uint32_t)(CH11 << 25) | (CH12 << 20) | (CH13 << 15) | (CH14 << 10) | (CH15 << 5)  | (CH16))
    #define ADCSmpr1(CYCLES)                                    ((uint32_t)(CYCLES << 24) | (CYCLES << 21) | (CYCLES << 18) | (CYCLES << 15) | (CYCLES << 12) | (CYCLES << 9) | (CYCLES << 6) | (CYCLES << 3) | (CYCLES))
    #define ADCSmpr2(CYCLES)                                    ((uint32_t)(CYCLES << 27) | (CYCLES << 24) | (CYCLES << 21) | (CYCLES << 18) | (CYCLES << 15) | (CYCLES << 12) | (CYCLES << 9) | (CYCLES << 6) | (CYCLES << 3) | (CYCLES))
    #define ADCResolution(RES)                                  ((uint32_t)(RES << 24))

#if(__configCONVERT_Volts == 1)
struct {
    unsigned char ADCSource[4];
    float BATTERY;
    float TEMPERATURE;
    float Multiplexer1[8];
    float Multiplexer2[8];
    float adc_data[5];
}ADCStatus;
#elif (__configCONVERT_Volts == 0)
struct {
    unsigned char ADCSource[4];
    uint16_t BATTERY;
    uint16_t TEMPERATURE;
    uint16_t Multiplexer1[8];
    uint16_t Multiplexer2[8];
    uint16_t adc_data[5];
}ADCStatus;
#else
#error Invalid argument __configCONVERT_Volts
#endif /*__configCONVERT_Volts*/

#if (__configADC_Mode == 3 || __configADC_Mode == 4)

#define Multiplexer_IN_0    0x000
#define Multiplexer_IN_1    0x001
#define Multiplexer_IN_2    0x010
#define Multiplexer_IN_3    0x011
#define Multiplexer_IN_4    0x100
#define Multiplexer_IN_5    0x101
#define Multiplexer_IN_6    0x110
#define Multiplexer_IN_7    0x111

    /*!
    *   @brief ADC_Multiplexer_Get(ADC_TypeDef *ADCx) - Calculating ADC Data from multiplexor
    *       @arg TIMx - number of timer
    *
    */
    void ADC_Multiplexer_Get(ADC_TypeDef *ADCx);

#elif (__configADC_Mode == 1 || __configADC_Mode == 2)

    /*!
    *   @brief ADC_Simple_Get(ADC_TypeDef *ADCx) - Calculating ADC Data from multiplexor
    *       @arg TIMx - number of timer
    *
    */
    void ADC_Simple_Get(ADC_TypeDef *ADCx);


#elif (__configADC_Mode == 5)

#else
#error Invalig argument __configADC_Mode
#endif /*__configADC_Mode*/

    void ADC_Init(ADC_TypeDef *ADCx);

    void AnalogRead(ADC_TypeDef *ADCx);
#endif /*configUSE_ADC*/
