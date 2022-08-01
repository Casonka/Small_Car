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
#if (configUSE_ADC_Manually == 0)
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
        SetADCSWStart(ADC);                                                         }

#else /*configUSE_ADC_Manually == 1*/
//----------------------------------------ADC check channel--------------------------------------------------//
    /*!
    *   @brief  AddADCChannel(ADC,CHANNEL,CYCLES) - Adding new channel to conversions ADC
    *       @arg ADC - Number of ADC
    *       @arg CHANNEL - Number of target channel
    *       @arg CYCLES - Sample time selection
    *
    */
    #define AddADCChannel(ADC,CHANNEL,CYCLES)                                              {\
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


#endif /*configUSE_ADC_Manually*/

//----------------------------------------ADC ID Selection----------------------------------------------------------//
#if defined(STM32F40_41xxx)
#define ADCID(ADC)      {(ADC == ADC1) ? ADC1_BASE : (ADC == ADC2) ? ADC2_BASE : (ADC == ADC3) ? ADC3_BASE : 0x00;}
#elif defined (STM32F401xx)
#define ADCID(ADC)      {(ADC == ADC1) ? ADC1_BASE : 0x00;}
#endif /*STM32F40_41xxx, STM32F401xx*/
//----------------------------------------Set state----------------------------------------------------------------------------------------------------------------------------//
    #define SetADCSMP1(ADC,CYCLES)          (* (uint32_t *)(((ADCID(ADC)) + 0x0C)) |= ADCSmpr1(CYCLES))
    #define SetADCSMP2(ADC,CYCLES)          (* (uint32_t *)(((ADCID(ADC)) + 0x10)) |= ADCSmpr2(CYCLES))
    #define SetADCLength(ADC,LENGTH)        (* (uint32_t *)(((ADCID(ADC)) + 0x2C)) |= (LENGTH << 20))
    #define SetADCSQ1(ADC,CH1,CH2,CH3,CH4)  (* (uint32_t *)(((ADCID(ADC)) + 0x2C)) |= ADCSQ1(CH1,CH2,CH3,CH4))
    #define SetADCSQ2(ADC,CH5,CH6,CH7,CH8,CH9,CH10) (* (uint32_t *)(((ADCID(ADC)) + 0x30)) |= ADCSQ2(CH5,CH6,CH7,CH8,CH9,CH10))
    #define SetADCSQ3(ADC,CH11,CH12,CH13,CH14,CH15,CH16) (* (uint32_t *)(((ADCID(ADC)) + 0x34)) |= ADCSQ3(CH11,CH12,CH13,CH14,CH15,CH16))
    #define SetADCScan(ADC)                 (* (uint32_t *)(((ADCID(ADC)) + 0x04)) |= (1 << 8))
    #define SetADCResolution(ADC,RES)       (* (uint32_t *)(((ADCID(ADC)) + 0x04)) |= (RES << 28))
    #define SetADCDMA(ADC)                  (* (uint32_t *)(((ADCID(ADC)) + 0x08)) |= (1 << 8))
    #define SetADCCont(ADC)                 (* (uint32_t *)(((ADCID(ADC)) + 0x08)) |= (1 << 1))
    #define SetADCDDS(ADC)                  (* (uint32_t *)(((ADCID(ADC)) + 0x08)) |= (1 << 9))
    #define SetADCAdon(ADC)                 (* (uint32_t *)(((ADCID(ADC)) + 0x08)) |= (1))
    #define SetADCSWStart(ADC)              (* (uint32_t *)(((ADCID(ADC)) + 0x08)) |= (1 << 30))

//---------------------------Simple commands reset and set the state-------------------------------------------------------------------------------------------------------------//
#if (configUSE_ADC_Manually == 0)

    #define ConfADCLength(ADC,LENGTH)                       {* ((uint32_t *)(((ADCID(ADC)) + 0x2C))) = ((* ((uint32_t *)(((ADCID(ADC)) + 0x2C)))&(~(0xF)))|ADCLength(LENGTH));}
    #define ConfADCSQ1(ADC,CH1,CH2,CH3,CH4)                 {* ((uint32_t *)(((ADCID(ADC)) + 0x2C))) = ((* ((uint32_t *)(((ADCID(ADC)) + 0x2C)))&(~(0xFFFFF)))|ADCSQ1(CH1,CH2,CH3,CH4));}
    #define ConfADCSQ2(ADC,CH5,CH6,CH7,CH8,CH9,CH10)        {* ((uint32_t *)(((ADCID(ADC)) + 0x30))) = ((* ((uint32_t *)(((ADCID(ADC)) + 0x30)))&(~(0x3FFFFFFF)))|ADCSQ2(CH5,CH6,CH7,CH8,CH9,CH10));}
    #define ConfADCSQ3(ADC,CH11,CH12,CH13,CH14,CH15,CH16)   {* ((uint32_t *)(((ADCID(ADC)) + 0x34))) = ((* ((uint32_t *)(((ADCID(ADC)) + 0x34)))&(~(0x3FFFFFFF)))|ADCSQ3(CH11,CH12,CH13,CH14,CH15,CH16));}
    #define ConfADCSmpr1(ADC,CYCLES)                        {* ((uint32_t *)(((ADCID(ADC)) + 0x0C))) = ((* ((uint32_t *)(((ADCID(ADC)) + 0x0C)))&(~(0x7FFFFFF)))|ADCSmpr1(CYCLES));}
    #define ConfADCSmpr2(ADC,CYCLES)                        {* ((uint32_t *)(((ADCID(ADC)) + 0x10))) = ((* ((uint32_t *)(((ADCID(ADC)) + 0x10)))&(~(0x3FFFFFFF)))|ADCSmpr2(CYCLES));}
    #define ConfADCSmpr(ADC,NUMBER,CYCLES)         {\
        if(NUMBER > 0) ConfADCSmpr2(ADC,CYCLES);    \
        if(NUMBER > 10) ConfADCSmpr1(ADC,CYCLES);   }

    #define ADCSQ1(CH1,CH2,CH3,CH4)                             ((uint32_t)(CH1 << 15) | (CH2 << 10) | (CH3 << 5)  | (CH4))
    #define ADCSQ2(CH5,CH6,CH7,CH8,CH9,CH10)                    ((uint32_t)(CH5 << 25) | (CH6 << 20) | (CH7 << 15) | (CH8 << 10) | (CH9 << 5)  | (CH10))
    #define ADCSQ3(CH11,CH12,CH13,CH14,CH15,CH16)               ((uint32_t)(CH11 << 25) | (CH12 << 20) | (CH13 << 15) | (CH14 << 10) | (CH15 << 5)  | (CH16))
    #define ADCSmpr1(CYCLES)                                    ((uint32_t)(CYCLES << 24) | (CYCLES << 21) | (CYCLES << 18) | (CYCLES << 15) | (CYCLES << 12) | (CYCLES << 9) | (CYCLES << 6) | (CYCLES << 3) | (CYCLES))
    #define ADCSmpr2(CYCLES)                                    ((uint32_t)(CYCLES << 27) | (CYCLES << 24) | (CYCLES << 21) | (CYCLES << 18) | (CYCLES << 15) | (CYCLES << 12) | (CYCLES << 9) | (CYCLES << 6) | (CYCLES << 3) | (CYCLES))
#endif /*configUSE_ADC_Manually*/
#endif /*_DefaultSectorIncludeHandler*/
