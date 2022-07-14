#include "TIM.h"

void CalcTimStatus(TIM_TypeDef *TIMx)
{
    CalcClocksRCC();
    TIMStatus.DutyCH1 = ((uint32_t)(TIMx->CCR1 / TIMx->ARR * 100));
    TIMStatus.DutyCH2 = ((uint32_t)(TIMx->CCR2 / TIMx->ARR * 100));
    TIMStatus.DutyCH3 = ((uint32_t)(TIMx->CCR3 / TIMx->ARR * 100));
    TIMStatus.DutyCH4 = ((uint32_t)(TIMx->CCR4 / TIMx->ARR * 100));
#if defined(STM32F401xx)
    if(TIMx == TIM1 || TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11)
    {
        TIMStatus.Frequency = (Clocks.CurrentAPB2 / ((TIMx->PSC + 1) * TIMx->ARR));
    }
    else if(TIMx == TIM2 || TIMx == TIM3 || TIMx == TIM4 || TIMx == TIM5)
    {
        TIMStatus.Frequency = (Clocks.CurrentAPB1 / ((TIMx->PSC + 1) * TIMx->ARR));
    }
#elif defined(STM32F40_41xxx)
    if(TIMx == TIM1 || TIMx == TIM8 || TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11)
    {
        TIMStatus.Frequency = (Clocks.CurrentAPB2 / ((TIMx->PSC + 1) * TIMx->ARR));
    }
    else if(TIMx == TIM2 || TIMx == TIM3 || TIMx == TIM4 || TIMx == TIM5 || TIMx == TIM6 || TIMx == TIM7 || TIMx == TIM12 || TIMx == TIM13 || TIMx == TIM14)
    {
        TIMStatus.Frequency = (Clocks.CurrentAPB1 / ((TIMx->PSC + 1) * TIMx->ARR));
    }
#endif
}
