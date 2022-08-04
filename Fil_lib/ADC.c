    /*!
    *   --------------------------------------------------------------------------
    *                       ///ADC Source file\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 04/08/2022 - last update version ADC
    *
    *       @note [FIL:ADC] ADC Source file.
    */
#include "ADC.h"

//---------------------------------------------------------//
//----------------------ADC Interrupts---------------------//
//---------------------------------------------------------//
void ADC_IRQHandler(void)
{
    if(ADCInjectedEndEvent(ADC1))
    {
//        ADC_Multiplexer_Get(ADC1);

        set_pin(MULPLXC_PIN);
        ADCStatus.Multiplexer_1[0] = ADC1->DR;
        //ADCStatus.BATTERY = ADC1->JDR2;
    }
}
#if(configUSE_ADC == 1)

#if(__configADC_Mode == 3 || __configADC_Mode == 4)
    static uint16_t Multi_In[8][2] = {Multiplexer_IN_0,__configUSE_SENSOR_1,
                                      Multiplexer_IN_1,__configUSE_SENSOR_2,
                                      Multiplexer_IN_2,__configUSE_SENSOR_3,
                                      Multiplexer_IN_3,__configUSE_SENSOR_4,
                                      Multiplexer_IN_4,__configUSE_SENSOR_5,
                                      Multiplexer_IN_5,__configUSE_SENSOR_6,
                                      Multiplexer_IN_6,__configUSE_SENSOR_7,
                                      Multiplexer_IN_7,__configUSE_SENSOR_8};
#endif /*__configADC_Mode*/
#if(__configADC_InterruptRequest == 1)
void ADC_Init(ADC_TypeDef *ADCx)
{
    if( ADCx == ADC1)
    {
        unsigned char Buf[4] = {'A','D','C','1'};
        for(int i = 0; i <= 3; i++)
        {
            ADCStatus.ADCSource[i] = Buf[i];
        }
    }
    else
    {
        unsigned char Buf[4] = {'A','D','C','2'};
        for(int i = 0; i <= 3; i++)
        {
            ADCStatus.ADCSource[i] = Buf[i];
        }
    }
#if(__configADC_Mode == 1)

#elif(__configADC_Mode == 2)

#elif(__configADC_Mode == 3)

#elif(__configADC_Mode == 4)
    ADCAddInjectedGroups(ADCx,0x0, 0, 0, 0, 0);
#if(__configUSE_Battery_Charging == 1)
    ADCx->JSQR = ((ADCx->JSQR & ADC_JSQR_JL) + 1);
    ADCx->JSQR |= (18 << 15);
    ADC_Common_TypeDef VBat;
    VBat->CCR |= (0x1 << 22);

#endif /*__configUSE_Battery_Charging*/
#if(__configUSE_Battery_Charging == 0 && __configUSE_Temperature_Sensor == 1)
    ADCx->JSQR = ((ADCx->JSQR & ADC_JSQR_JL) + 1);
    ADCx->JSQR |= (18 << 15);
    ADC_Common_TypeDef VTemp;
    VTemp->CCR |= (0x1 << 23);
#endif /*__configUSE_Temperature_Sensor*/
    ADCScanConfigure(ADCx);
    ADCx->CR1 |= ADC_CR1_JAUTO;
    ADCx->CR1 |= ADC_CR1_JEOCIE;
    ADCx->SQR3 |= 0x8;
    ADCStartRegular(ADC1);
#endif/*__configADC_Mode*/
}
#if(__configADC_Mode == 4)

static void SetMulriplexer_State(uint16_t State)
{
    if((State&0x100) >> 2) set_pin(MULPLXC_PIN); else reset_pin(MULPLXC_PIN);
    if((State&0x010) >> 1) set_pin(MULPLXB_PIN); else reset_pin(MULPLXB_PIN);
    if((State&0x001))      set_pin(MULPLXA_PIN); else reset_pin(MULPLXA_PIN);
}
/*!
*   @brief void ADC_Multiplexer_Get()
*
*/
void ADC_Multiplexer_Get(ADC_TypeDef *ADCx)
{
    static int NumPort = 0;
    if(Multi_In[NumPort][1] == 0) { NumPort++; if(NumPort == 8) NumPort = 0; return; }
    SetMulriplexer_State(Multi_In[NumPort][0]);
    ADCStatus.Multiplexer_1[NumPort] = ADCx->JDR1;
    if(NumPort == 8) NumPort = 0;
    else NumPort++;
}
#endif /*__configADC_Mode*/
#else /*__configADC_InterruptRequest*/
void ADC_Init(ADC_TypeDef *ADCx)
{

}
#endif/*__configADC_InterruptRequest*/
#endif /*configUSE_ADC*/
