#include "TIM.h"

    /*!
    *   @brief CalcTimStatus(TIM_TypeDef *TIMx) - Calculating Timer Status
    *       @arg TIMx - number of timer
    *           @note [FIL:TIM] Функция позволяет получить текущий статус таймера, заполнения ШИМ и частоту работы
    */
void CalcTimStatus(TIM_TypeDef *TIMx)
{
    CalcTimClockSourse(TIMx);
    TIMStatus.DutyCH1 = ((uint32_t)(((float)TIMx->CCR1) / TIMx->ARR * 100));
    TIMStatus.DutyCH2 = ((uint32_t)(((float)TIMx->CCR2) / TIMx->ARR * 100));
    TIMStatus.DutyCH3 = ((uint32_t)(((float)TIMx->CCR3) / TIMx->ARR * 100));
    TIMStatus.DutyCH4 = ((uint32_t)(((float)TIMx->CCR4) / TIMx->ARR * 100));
    TIMStatus.Frequency = (TIMStatus.SourseClock / ((TIMx->PSC + 1) * TIMx->ARR));
}
    /*!
    *   @brief CalcTimPIDFrequency(TIM_TypeDef *TIMx, uint16_t freq) - Calculating Timer frequency
    *       @arg TIMx - number of timer
    *       @arg freq - necessary frequency
    *           @note [FIL:TIM] Функция для расчета частоты работы прерывания по таймеру. Можно использовать для различных расчетов
    */
void CalcTimPIDFrequency(TIM_TypeDef *TIMx, uint16_t freq)
{
    CalcTimClockSourse(TIMx);

    TIMx->PSC = (freq >= 100) ? ((uint32_t)(TIMStatus.SourseClock / 1000000)) :
                (freq >= 10000) ? ((uint32_t)(TIMStatus.SourseClock / 10000)) : ((uint32_t)(TIMStatus.SourseClock / 100000));
    TIMx->ARR = ((uint32_t)(TIMStatus.SourseClock / ((TIMx->PSC)* freq)));
    TIMx->PSC -= 1;
}

    /*!
    *   @brief CalcTimClockSourse(TIM_TypeDef *TIMx) - Calculating Timer Clock Sourse
    *       @arg TIMx - number of timer
    *       @note [FIL:TIM] Функция вычисляет ресурс, используемый таймером, базовый расчет.
    */
void CalcTimClockSourse(TIM_TypeDef *TIMx)
{
    CalcRCCClocks();
#if defined(STM32F401xx)
    if(TIMx == TIM1 || TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11)
    {
        TIMStatus.SourseClock = Clocks.CurrentAPB2;
    }
    else if(TIMx == TIM2 || TIMx == TIM3 || TIMx == TIM4 || TIMx == TIM5)
    {
        TIMStatus.SourseClock = Clocks.CurrentAPB1;
    }
#elif defined(STM32F40_41xxx)
    if(TIMx == TIM1 || TIMx == TIM8 || TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11)
    {
        TIMStatus.SourseClock = Clocks.CurrentAPB2;
    }
    else if(TIMx == TIM2 || TIMx == TIM3 || TIMx == TIM4 || TIMx == TIM5 || TIMx == TIM6 || TIMx == TIM7 || TIMx == TIM12 || TIMx == TIM13 || TIMx == TIM14)
    {
        TIMStatus.SourseClock = Clocks.CurrentAPB1;
    }
#endif
}
