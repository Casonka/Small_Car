
    /*!
    *   --------------------------------------------------------------------------
    *                       ///TIM Source file\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska, Evgeny Garanin
    *   @date 13/07/2022 - last update version TIM
    *
    *       @note [FIL:TIM] TIM Source file.
    */

#include "TIM.h"

//---------------------------------------------------------//
//----------------------Timer Interrupts-------------------//
//---------------------------------------------------------//

void TIM1_IRQHandler(void)
{

ResetTimSR(TIM1);
}

void TIM2_IRQHandler(void)
{

ResetTimSR(TIM2);
}

void TIM3_IRQHandler(void)
{

ResetTimSR(TIM3);
}

void TIM4_IRQHandler(void)
{

ResetTimSR(TIM4);
}

void TIM5_IRQHandler(void)
{

ResetTimSR(TIM5);
}

#if defined(STM32F40_41xxx) /*--------------STM32F407------------------*/
void TIM6_DAC_IRQHandler(void)
{

ResetTimSR(TIM6);
}


void TIM7_IRQHandler(void)
{

ResetTimSR(TIM7);
}

void TIM8_UP_TIM13_IRQHandler(void)
{

ResetTimSR(TIM13);
}
#endif /*STM32F40_41xxx*/

    /*!
    *   @brief CalcTimStatus(TIM_TypeDef *TIMx) - Calculating Timer Status
    *       @arg TIMx - number of timer
    *           @note [FIL:TIM] ������� ��������� �������� ������� ������ �������, ���������� ��� � ������� ������
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
    *           @note [FIL:TIM] ������� ��� ������� ������� ������ ���������� �� �������. ����� ������������ ��� ��������� ��������
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
    *       @note [FIL:TIM] ������� ��������� ������, ������������ ��������, ������� ������.
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

    /*!
    *   @brief SetPWM(CCR_Pin,Duty) - ���������� ���������� �� ���������
    *       @arg CCR_Pin - selecting channel of timer
    *       @arg Duty - duty value
    *       @note [FIL:TIM] ������� ������������� ��� ������������ ���������� ���.
    */
    static bool SetPWM(uint32_t *CCR_Pin,float Duty)
    {
        if(Duty > 1.0) Duty = 1.0;
        if(Duty < -1.0) Duty = -1.0;
        if(Duty >= 0)
        {
            *CCR_Pin = ((int32_t) (Duty * MAX_PWM));
            return true;
        }
        else
        {
            *CCR_Pin = ((int32_t)(MAX_PWM +  (Duty * MAX_PWM)));
            return true;
        }
        return false;
    }

    /*!
    *   @brief SetVoltage(Motor, Duty) - ���������� ���������� �� ���������
    *       @arg Motor - number of Motor
    *       @arg Duty - duty value
    *       @note [FIL:TIM] ������� ������������� ��� ���������� ����������� ����������� ����.
    */
    bool SetVoltage(float Duty)
    {
        if(Duty >= 0)
        {
            reset_pin(BTN1_DIR_PIN);
            SetPWM(BTN1_CCR,Duty);
            return true;
        }
        else
        {
            set_pin(BTN1_DIR_PIN);
            SetPWM(BTN1_CCR,Duty);
            return true;
        }
        return false;
    }

    void SetServo(Servomotor* Servo, char servoType, uint8_t mAngle, uint32_t CCR, uint32_t ARR, uint16_t ms)
    {
        Servo->maxAngle = mAngle;
        *Servo->CCR = CCR;
        Servo->ARR = ARR;
        Servo->ms = ms;

        if(servoType == BIG_BLACK_SERVA)
        {
            (*Servo).min_ms = 0.8;
            (*Servo).max_ms = 2.2;
        }
        else if(servoType == SMALL_BLUE_SERVA)
        {
            (*Servo).min_ms = 0.4;
            (*Servo).max_ms = 2.45;
        }
    }


    void SetServoAngle(Servomotor* Servo, uint8_t angle)
    {
        if(angle > (*Servo).maxAngle) angle = (*Servo).maxAngle;
        if(angle < 0)   angle = 0;

        float min_PWM = (float)(((*Servo).ARR * (*Servo).min_ms) / (*Servo).ms);
        float max_PWM = (float)(((*Servo).ARR * (*Servo).max_ms) / (*Servo).ms);

        *(*Servo).CCR = (uint32_t)(angle * ((max_PWM - min_PWM) / (*Servo).maxAngle) + min_PWM);
    }


