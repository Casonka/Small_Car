#include "main.h"

uint16_t ADC1_Data[ADC1_NUMB];
int main(void)
{
Board_Config;
    ADCAddRegularChannel(ADC1,0,ADC_480_CYCLES);
    ADCAddRegularChannel(ADC1,1,ADC_480_CYCLES);
    ConnectADCTODMA(HIGH_P,ADC1_Data,0);
    ADCSimpleConfigure(ADC1);
    SetTIM4;
    TimPIDConfigureAutomatic(TIM4,10);
    NVIC_EnableIRQ(TIM4_IRQn);
    while(1)
    {



    }
}



