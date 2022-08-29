#include "main.h"

int main(void)
{
    Board_Config;
    RTC_Calibration;
//
//    RTC->ISR |= RTC_ISR_INIT;
//    while((RTC->ISR & RTC_ISR_INITF) == 0) {}
//
//    RTC->CR |= RTC_CR_FMT;
//
//    RTC->TR = 0;
//    RTC->TR |= (RTC_TR_HT_0 | RTC_TR_HU_3 | RTC_TR_HU_0);
//    RTC->TR |= (RTC_TR_MNT_1);
//
//    RTC->ISR &= (RTC->ISR & (~RTC_ISR_INIT));
    while(1)
    {
    RTC_GetStatus;

    }
}
