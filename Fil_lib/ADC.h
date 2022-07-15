    /*!
    *   --------------------------------------------------------------------------
    *                       ///ADC initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 15/07/2022 - last update version ADC
    *
    *       @note [FIL:ADC] Configuration file ADC
    */
#pragma once
#include "FilConfig.h"

#if(configUSE_ADC == 1)

//----------------------------------------ADC Functions----------------------------------------------------------//

    /*!
    *   @brief  ADCScanConfigure(ADC,LENGTH,
    *           CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8,CH9,CH10,CH11,CH12,CH13,CH14,CH15,CH16,
    *           NUMBER,CYCLES) - Simple configuration ADC (Scan mode)
    *       @arg ADC - Number of ADC
    *       @arg LENGTH - Regular channel sequence length
    *       @arg CHx - Connect ADC Channel to ADC_IN pins
    *       @arg NUMBER - NUMBER of ADC_IN active pins
    *       @arg CYCLES - Sample time selection
    *
    */
    #define ADCScanConfigure(ADC,LENGTH,                                            \
            CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8,CH9,CH10,CH11,CH12,CH13,CH14,CH15,CH16, \
            NUMBER,CYCLES)                                                         {\
        SetADCLength(ADC,LENGTH);                                                   \
        ConfADCSQ1(ADC,CH1,CH2,CH3,CH4);                                            \
        ConfADCSQ2(ADC,CH5,CH6,CH7,CH8,CH9,CH10);                                   \
        ConfADCSQ3(ADC,CH11,CH12,CH13,CH14,CH15,CH16);                              \
        ConfADCSmpr(ADC,NUMBER,CYCLES);                                             \
        SetADCScan(ADC);                                                            \
        SetADCDDS(ADC);                                                             \
        SetADCDMA(ADC);                                                             \
        SetADCCont(ADC);                                                            }

//----------------------------------------ADC ID Selection----------------------------------------------------------//
#if defined(STM32F40_41xxx)
#define ADCID(ADC)      {(ADC == ADC1) ? ADC1_BASE : (ADC == ADC2) ? ADC2_BASE : (ADC == ADC3) ? ADC3_BASE : 0x00;}
#elif defined (STM32F401xx)
#define ADCID(ADC)      {(ADC == ADC1) ? ADC1_BASE : 0x00;}
#endif /*STM32F40_41xxx, STM32F401xx*/

    #define SetADCSMP1(ADC,CYCLES)          (* (uint32_t *)(((ADCID(ADC)) + 0x0C)) |= ADCSmpr1(CYCLES))

    #define SetADCSMP2(ADC,CYCLES)          (* (uint32_t *)(((ADCID(ADC)) + 0x10)) |= ADCSmpr2(CYCLES))

    #define SetADCLength(ADC,LENGTH)        (* (uint32_t *)(((ADCID(ADC)) + 0x2C)) |= (LENGTH << 20))

    #define SetADCSQ1(ADC,CH1,CH2,CH3,CH4)  (* (uint32_t *)(((ADCID(ADC)) + 0x2C)) |= ADCSQ1(CH1,CH2,CH3,CH4))

    #define SetADCSQ2(ADC,CH5,CH6,CH7,CH8,CH9,CH10) (* (uint32_t *)(((ADCID(ADC)) + 0x30)) |= ADCSQ2(CH5,CH6,CH7,CH8,CH9,CH10))

    #define SetADCSQ3(ADC,CH11,CH12,CH13,CH14,CH15,CH16) (* (uint32_t *)(((ADCID(ADC)) + 0x34)) |= ADCSQ3(CH11,CH12,CH13,CH14,CH15,CH16))

    #define SetADCScan(ADC)                 (* (uint32_t *)(((ADCID(ADC)) + 0x04)) |= ADCScan(0x1))

    #define SetADCResolution(ADC,RES)       (* (uint32_t *)(((ADCID(ADC)) + 0x04)) |= ADCResolution(0x00))

    #define SetADCDMA(ADC)                  (* (uint32_t *)(((ADCID(ADC)) + 0x08)) |= ADCDMA(0x1))

    #define SetADCCont(ADC)                 (* (uint32_t *)(((ADCID(ADC)) + 0x08)) |= ADCCont(0x1))

    #define SetADCDDS(ADC)                  (* (uint32_t *)(((ADCID(ADC)) + 0x08)) |= ADCDDS(0x1))

    #define SetADCAdon(ADC)                 (* (uint32_t *)(((ADCID(ADC)) + 0x08)) |= ADCAdon(0x1))

    #define SetADCSWStart(ADC)              (* (uint32_t *)(((ADCID(ADC)) + 0x08)) |= ADCSWStart(0x1))

    #define ConfADCLength(ADC,LENGTH)                       {* ((uint32_t *)(((ADCID(ADC)) + 0x2C))) = \
                                                            ((* ((uint32_t *)(((ADCID(ADC)) + 0x2C)))&(~(0xF)))|ADCLength(LENGTH));}

    #define ConfADCSQ1(ADC,CH1,CH2,CH3,CH4)                 {* ((uint32_t *)(((ADCID(ADC)) + 0x2C))) = \
                                                            ((* ((uint32_t *)(((ADCID(ADC)) + 0x2C)))&(~(0xFFFFF)))|ADCSQ1(CH1,CH2,CH3,CH4));}

    #define ConfADCSQ2(ADC,CH5,CH6,CH7,CH8,CH9,CH10)        {* ((uint32_t *)(((ADCID(ADC)) + 0x30))) = \
                                                            ((* ((uint32_t *)(((ADCID(ADC)) + 0x30)))&(~(0x3FFFFFFF)))|ADCSQ2(CH5,CH6,CH7,CH8,CH9,CH10));}

    #define ConfADCSQ3(ADC,CH11,CH12,CH13,CH14,CH15,CH16)   {* ((uint32_t *)(((ADCID(ADC)) + 0x34))) = \
                                                            ((* ((uint32_t *)(((ADCID(ADC)) + 0x34)))&(~(0x3FFFFFFF)))|ADCSQ3(CH11,CH12,CH13,CH14,CH15,CH16));}

    #define ConfADCSmpr1(ADC,CYCLES)                        {* ((uint32_t *)(((ADCID(ADC)) + 0x0C))) = \
                                                            ((* ((uint32_t *)(((ADCID(ADC)) + 0x0C)))&(~(0x7FFFFFF)))|ADCSmpr1(CYCLES));}

    #define ConfADCSmpr2(ADC,CYCLES)                        {* ((uint32_t *)(((ADCID(ADC)) + 0x10))) = \
                                                            ((* ((uint32_t *)(((ADCID(ADC)) + 0x10)))&(~(0x3FFFFFFF)))|ADCSmpr2(CYCLES));}

    #define ConfADCSmpr(ADC,NUMBER,CYCLES) {        \
        if(NUMBER > 0) ConfADCSmpr2(ADC,CYCLES);    \
        if(NUMBER > 10) ConfADCSmpr1(ADC,CYCLES);   }

    #define ADCLength(LENGTH)              ((uint32_t)((LENGTH) << 20))

    #define ADCScan(SCAN)                  ((uint32_t)((SCAN) << 8))

    #define ADCCont(cont)                  ((uint32_t)((cont) << 1))

    #define ADCDMA(dma)                    ((uint32_t)((dma) << 8))

    #define ADCAdon(adon)                  ((uint32_t)(adon))

    #define ADCSWStart(SWS)                ((uint32_t)((SWS) << 30))

    #define ADCDDS(dds)                    ((uint32_t)((dds) << 9))

    #define ADCResolution(RES)             ((uint32_t)((RES) << 28))

    #define ADCSQ1(CH1,CH2,CH3,CH4)                             ((uint32_t)(CH1 << 15) | (CH2 << 10) |  \
                                                                (CH3 << 5)  | (CH4))


    #define ADCSQ2(CH5,CH6,CH7,CH8,CH9,CH10)                    ((uint32_t)(CH5 << 25) | (CH6 << 20) |  \
                                                                (CH7 << 15) | (CH8 << 10) |  \
                                                                (CH9 << 5)  | (CH10))


    #define ADCSQ3(CH11,CH12,CH13,CH14,CH15,CH16)               ((uint32_t)(CH11 << 25) | (CH12 << 20) |  \
                                                                (CH13 << 15) | (CH14 << 10) |  \
                                                                (CH15 << 5)  | (CH16))

    #define ADCSmpr1(CYCLES)                                    ((uint32_t)(CYCLES << 24) | (CYCLES << 21) | (CYCLES << 18) | \
                                                                (CYCLES << 15) | (CYCLES << 12) | (CYCLES << 9) | \
                                                                (CYCLES << 6) | (CYCLES << 3) | (CYCLES))

    #define ADCSmpr2(CYCLES)                                    ((uint32_t)(CYCLES << 27) | (CYCLES << 24) | (CYCLES << 21) | \
                                                                (CYCLES << 18) | (CYCLES << 15) | (CYCLES << 12) | \
                                                                (CYCLES << 9) | (CYCLES << 6) | (CYCLES << 3) | (CYCLES))

    #define ADCOverrun(ovr)                ((uint32_t)((ovr) << 5))

    #define ADCStrt(strt)                  ((uint32_t)((strt) << 4))

    #define ADCJstrt(jstrt)                ((uint32_t)((jstrt) << 3))

    #define ADCJeoc(jeoc)                  ((uint32_t)((jeoc) << 2))

    #define ADCEoc(eoc)                    ((uint32_t)((eoc) << 1))

    #define ADCAwd(awd)                    ((uint32_t)(awd))

    #define ADCOverIe(overie)              ((uint32_t)((overie) << 26))

    #define ADCRes(res)                    ((uint32_t)((res) << 24))

    #define ADCAwden(awden)                ((uint32_t)((awden) << 23))

    #define ADCJawden(jawden)              ((uint32_t)((jawden) << 22))

    #define ADCDiscnum(discnum)            ((uint32_t)((discnum) << 13))

    #define ADCJdiscen(jdiscen)            ((uint32_t)((jdiscen) << 12))

    #define ADCDiscen(discen)              ((uint32_t)((discen) << 11))

    #define ADCJauto(jauto)                ((uint32_t)((jauto) << 10))

    #define ADCAwdsgl(awdsgl)              ((uint32_t)((awdsgl) << 9))

    #define ADCJeocIe(jeocie)              ((uint32_t)((jeocie) << 7))

    #define ADCAwdIe(awdie)                ((uint32_t)((awdie) << 6))

    #define ADCEocIe(eocie)                ((uint32_t)((eocie) << 5))

    #define ADCAwdch(awdch)                ((uint32_t)(awdch))

    #define ADCExtern(exten)               ((uint32_t)((exten) << 28))

    #define ADCExtsel(extsel)              ((uint32_t)((extsetl) << 23))

    #define ADCJSWStart(jswstart)          ((uint32_t)((jswstart) << 22))

    #define ADCJiextern(jiexten)           ((uint32_t)((jiexten) << 21))

    #define ADCJiexsel(jiexsel)            ((uint32_t)((jiexsel) << 16))

    #define ADCAlign(align)                ((uint32_t)((align) << 11))

    #define ADCEocs(eocs)                  ((uint32_t)((eocs) << 10))

    #define ADCJofsset(joffset)            ((uint32_t)joffset)

    #define ADCHt(ht)                      ((uint32_t)(ht))

    #define ADCLtr(ltr)                    ((uint32_t)(ltr))

    #define ADCJl(jl)                      ((uint32_t)((jl) << 20))

    #define ADCJdata(jdata)                ((uint32_t)(jdata))

    #define ADCDR(dr)                      ((uint32_t)(dr))

    #define ADCOvr3(ovr3)                  ((uint32_t)((ovr3) << 21))

    #define ADCStrt3(strt3)                ((uint32_t)((strt3) << 20))

    #define ADCJstrt3(jstrt3)              ((uint32_t)((jstrt3) << 19))

    #define ADCJeoc3(jeoc3)                ((uint32_t)((jeoc3) << 18))

    #define ADCEoc3(eoc3)                  ((uint32_t)((eoc3) << 17))

    #define ADCAwd3(awd3)                  ((uint32_t)((awd3) << 16))

    #define ADCOvr2(ovr2)                  ((uint32_t)((ovr2) << 13))

    #define ADCStrt2(strt2)                ((uint32_t)((strt2) << 12))

    #define ADCJstrt2(jstrt2)              ((uint32_t)((jstrt2) << 11))

    #define ADCJeoc2(jeoc2)                ((uint32_t)((jeoc2) << 10))

    #define ADCEoc2(eoc2)                  ((uint32_t)((eoc2) << 9))

    #define ADCAwd2(awd2)                  ((uint32_t)((awd2) << 8))

    #define ADCOvr1(ovr1)                  ((uint32_t)((ovr1) << 5))

    #define ADCStrt1(strt1)                ((uint32_t)((strt1) << 4))

    #define ADCJstrt1(jstrt1)              ((uint32_t)((jstrt1) << 3))

    #define ADCJeoc1(jeoc1)                ((uint32_t)((jeoc1) << 2))

    #define ADCEoc1(eoc1)                  ((uint32_t)((eoc1) << 1))

    #define ADCAwd1(awd1)                  ((uint32_t)(awd1))

    #define ADCTsvrefe(tsvrefe)            ((uint32_t)((tsvrefe) << 23))

    #define ADCVbate(vbate)                ((uint32_t)((vbate) << 22))

    #define ADCAdcpre(adcpre)              ((uint32_t)((adcpre) << 16))

    #define ADCDelay(delay)                ((uint32_t)((delay) << 8))

    #define ADCMulti(multi)                ((uint32_t)(multi))

    #define ADCData1(data1)                ((uint32_t)(data1))

    #define ADCData2(data2)                ((uint32_t)((data2) << 16))

#endif /*_DefaultSectorIncludeHandler*/
