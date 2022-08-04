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
//----------------------------------------ADC Functions----------------------------------------------------------//
#if(configUSE_ADC_Manually == 0)
    /*!
    *   @brief  ADCScanConfigure(ADC,LENGTH,
    *           CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8,CH9,CH10,CH11,CH12,CH13,CH14,CH15,CH16,
    *           CYCLES) - Configuration ADC (Scan mode)
    *       @arg ADC - Number of ADC
    *       @arg LENGTH - Regular channel sequence length
    *       @arg CHx - Connect ADC_IN pins to conversion queue
    *       @arg NUMBER - NUMBER of ADC_IN active pins
    *       @arg CYCLES - Sample time selection
    *
    */
    #define ADCScanConfigure(ADC,LENGTH,                                            \
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

#endif /*configUSE_ADC_Manually == 1*/
//----------------------------------------ADC check channels--------------------------------------------------//
#if(__configADC_Mode == 2)
    /*!
    *   @brief  AddADCChannel(ADC,CHANNEL,CYCLES) - Adding new channel to conversions ADC
    *       @arg ADC - Number of ADC
    *       @arg CHANNEL - Number of target channel
    *       @arg CYCLES - Sample time selection
    *
    */
    #define ADCAddChannel(ADC,CHANNEL,CYCLES)                                              {\
                        static char CH;                                                     \
                        ADC->SQR1 &= ~(0xF << 20);                                          \
                        ADC->SQR1 |= CH << 20;                                              \
                        *(&ADC->SQR3 - (CH / 6)) |= n << ((CH * 5) % 30);                   \
                        *(&ADC->SMPR2 - (CH / 10)) |= CYCLES << ((CH * 3) % 30);            \
                        CH++;                                                               }

    /*!
    *   @brief  ADCScanConfigure(ADC,IsDMA) - Configuration ADC (Scan mode without adding channels)
    *       @arg ADC - Number of ADC
    *       @arg IsDMA - DMA mode: 0 - DMA off
    *                              1 - DMA on
    *
    */
    #define ADCScanConfigure(ADC, IsDMA)      {\
        SetADCScan(ADC);                       \
        if (IsDMA == 1) SetADCDMA(ADC);        \
        SetADCCont(ADC);                       \
        SetADCAdon(ADC);                       }

#elif(__configADC_Mode == 1 || __configADC_Mode == 3)
    /*!
    *   @brief  AddADCSingleChannel(ADC,CHANNEL,CYCLES) - Adding single channel to conversions ADC
    *       @arg ADC - Number of ADC
    *       @arg CHANNEL - Number of target channel
    *       @arg CYCLES - Sample time selection
    *           @attention This function delete old channel from ADC list before writing new target channel
    */
    #define ADCAddSingleChannel(ADC,CHANNEL,CYCLES)                                        {\
                        ADC->CR2 &= ~ADC_CR2_ADON;                                          \
                        ADC->SQ3 &= ~(0x1F);                                                \
                        ADC->SMPR2 &= ~(0x7);                                               \
                        ADC->SQ3 |= CHANNEL;                                                \
                        ADC->SMP2 |= CYCLES;                                                \
                        ADC->CR1 &= ~ADC_CR1_SCAN;                                          \
                        ADC->CR2 |= (ADC_CR2_ADON | ADC_CR2_CONT);                          }

#elif(__configADC_Mode == 4)
/*!
*   @info This sector include parsing analog data with two Multiplexers or 4 inputs
*
*/

    #define ADCAddInjectedGroups(ADC,NUMBER,J1,J2,J3,J4)                           {\
                        ADC->JSQR &= ~(0x3FFFFF);                                   \
                        ADC->JSQR |= (NUMBER << 20);                                \
                        ADC->JSQR |= ((J1) | (J2 << 5) | (J3 << 10) | (J4 << 15));  }

    /*!
    *   @brief  ADCScanConfigure(ADC) - Configuration ADC (Scan mode without adding channels)
    *       @arg ADC - Number of ADC
    *
    */
    #define ADCScanConfigure(ADC)             {\
        ResetADCCont(ADC);                     \
        SetADCAdon(ADC);                       \
        SetADCCont(ADC);                       \
        ADCStartInjected(ADC);                 }

#endif /*__configADC_Mode*/

//----------------------------------------ADC ID Selection----------------------------------------------------------//
#if defined(STM32F40_41xxx)
#define ADCID(ADC)      {(ADC == ADC1) ? ADC1_BASE : (ADC == ADC2) ? ADC2_BASE : (ADC == ADC3) ? ADC3_BASE : 0x00;}
#elif defined (STM32F401xx)
#define ADCID(ADC)      {(ADC == ADC1) ? ADC1_BASE : 0x00;}
#endif /*STM32F40_41xxx, STM32F401xx*/
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
//----------------------------------------Reset state----------------------------------------------------------------------------------------------------------------------------//
    #define ResetADCCont(ADC)               ((ADC->CR2) &= (~ADC_CR2_CONT))
    #define ADCStopRegular(ADC)             ((ADC->CR2) &= (~ADC_CR2_SWSTART))
    #define ResetADCEOCEvent(ADC)           ((ADC->SR) &= (~ADC_SR_EOC))
    #define ResetADCJEOCEvent(ADC)          ((ADC->SR) &= (~ADC_SR_JEOC))
    #define ResetADCOVREvent(ADC)           ((ADC->SR) &= (~ADC_SR_OVR))
//----------------------------------------Status monitoring--------------------------------------------------------------------------------------------------------------------//
    #define ADCAnalogWatchdogEvent(ADC) (((ADC->SR) & (ADC_SR_AWD)))
    #define ADCRegularEndEvent(ADC)     (((ADC->SR) & (ADC_SR_EOC)) >> 1)
    #define ADCInjectedEndEvent(ADC)    (((ADC->SR) & (ADC_SR_JEOC)) >> 2)
    #define ADCInjectedStartEvent(ADC)  (((ADC->SR) & (ADC_SR_JSTRT)) >> 3)
    #define ADCRegularStartEvent(ADC)   (((ADC->SR) & (ADC_SR_STRT)) >> 4)
    #define ADCOverrunEvent(ADC)        (((ADC->SR) & (ADC_SR_OVR)) >> 5)
//---------------------------Simple commands reset and set the state-------------------------------------------------------------------------------------------------------------//
    #define ConfADCResolution(ADC,RESOLUTION)               {ADC->CR1 = (((ADC->CR1)&(~(ADC_CR1_RES)))|ADCResolution(RES));}
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

#if (__configADC_Mode == 3 || __configADC_Mode == 4)

#define Multiplexer_IN_0    0x000
#define Multiplexer_IN_1    0x001
#define Multiplexer_IN_2    0x010
#define Multiplexer_IN_3    0x011
#define Multiplexer_IN_4    0x100
#define Multiplexer_IN_5    0x101
#define Multiplexer_IN_6    0x110
#define Multiplexer_IN_7    0x111


struct {
    unsigned char ADCSource[4];
    uint16_t BATTERY;
    uint16_t TEMPERATURE;
    uint16_t Multiplexer_1[8];
    #if(__configADC_Mode == 4)
    uint16_t Multiplexer_2[8];
    #endif /*__configADC_Mode*/
}ADCStatus;

    /*!
    *   @brief ADC_Multiplexer_Get(ADC_TypeDef *ADCx) - Calculating ADC Data from multiplexor
    *       @arg TIMx - number of timer
    *
    */
    void ADC_Multiplexer_Get(ADC_TypeDef *ADCx);

    void ADC_Init(ADC_TypeDef *ADCx);
#elif (__configADC_Mode == 1 || __configADC_Mode == 2 || __configADC_Mode == 5)

struct {
    uint32_t ADCSource;
    uint16_t BATTERY;
    uint16_t TEMPERATURE;
    uint16_t Regular_Data[16];
    uint16_t Injected_Data[4];
}ADCStatus;

    /*!
    *   @brief ADC_Simple_Get(ADC_TypeDef *ADCx) - Calculating ADC Data from multiplexor
    *       @arg TIMx - number of timer
    *
    */
    void ADC_Simple_Get(ADC_TypeDef *ADCx);

    void ADC_Init(ADC_TypeDef *ADCx);
#endif /*__configADC_Mode*/

#endif /*configUSE_ADC*/
