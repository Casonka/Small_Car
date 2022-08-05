    /*!
    *   --------------------------------------------------------------------------
    *                       ///ADC Source file\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 05/08/2022 - last update version ADC
    *
    *       @note [FIL:ADC] ADC Source file.
    */
#include "ADC.h"

//--------------------------------------------------------------------------------//
//---------------------------ADC Interrupts---------------------------------------//
//--------------------------------------------------------------------------------//
/*!
*   @brief ADC_IRQHandler(void)
*/
void ADC_IRQHandler(void)
{
    if(ADCRegularEndEvent(ADC1))
    {

    }
    if(ADCInjectedEndEvent(ADC1))
    {
//        ADC_Multiplexer_Get(ADC1);

        //set_pin(MULPLXC_PIN);

        //ADCStatus.BATTERY = ADC1->JDR2;
    }
}
#if(configUSE_ADC == 1)
//------------------------------------------------------------------------------------//
/*!
*   @info Prepare parameters for parsing Multiplexer
*/
//------------------------------------------------------------------------------------//
#if(__configADC_Mode == 3 || __configADC_Mode == 4)
    __attribute__((unused)) static uint16_t Multi_In[8] =    {Multiplexer_IN_0,
                                                              Multiplexer_IN_1,
                                                              Multiplexer_IN_2,
                                                              Multiplexer_IN_3,
                                                              Multiplexer_IN_4,
                                                              Multiplexer_IN_5,
                                                              Multiplexer_IN_6,
                                                              Multiplexer_IN_7};
#endif /*__configADC_Mode*/
    __attribute__((unused)) static uint8_t ADC_CurrentTabs[10] =   {ADC_IN_0,
                                                                    ADC_IN_1,
                                                                    ADC_IN_2,
                                                                    ADC_IN_3,
                                                                    ADC_IN_4,
                                                                    ADC_IN_5,
                                                                    ADC_IN_6,
                                                                    ADC_IN_7,
                                                                    ADC_IN_8,
                                                                    ADC_IN_9};
//------------------------------------------------------------------------------------//
/*!
*   @info Main initializing function
*/
//------------------------------------------------------------------------------------//
void ADC_Init(ADC_TypeDef *ADCx)
{
////////////////////////////////////////////
#if(__configADC_RESOLUTION == 12)
    ConfADCResolution(ADCx,0);
#elif(__configADC_RESOLUTION == 10)
    ConfADCResolution(ADCx,1);
#elif(__configADC_RESOLUTION == 8)
    ConfADCResolution(ADCx,2);
#elif(__configADC_RESOLUTION == 6)
    ConfADCResolution(ADCx,3);
#endif /*__configADC_RESOLUTION*/
///////////////////////////////////////////
#ifdef STM32F401xx
    // String tag the target ADC
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
#endif /*STM32F401xx*/
///////////////////////////////////////////
#if(__configADC_Mode == 1)
    if(ADC_IN_0 >= 0)
    {
        ADCAddRegularChannel(ADCx,ADC_IN_0,ADC_480_CYCLES);
        #if(__configUSE_Battery_Charging == 1)
        #undef __configUSE_Temperature_Sensor
        ADCAddInjectedGroup(ADCx,1,18,0,0,0);
        ADC_Common_TypeDef VBat;
        VBat->CCR |= (0x1 << 22);
        #endif /*__configUSE_Battery_Charging*/
        #if(__configUSE_Temperature_Sensor == 1)
        ADCAddInjectedGroup(ADCx,1,18,0,0,0);
        ADC_Common_TypeDef VTemp;
        VTemp->CCR |= (0x1 << 23);
        #endif /*__configUSE_Temperature_Sensor*/
        ADCSimpleConfigure(ADCx);
    }
///////////////////////////////////////////
#elif(__configADC_Mode == 2)

///////////////////////////////////////////
#elif(__configADC_Mode == 3 || __configADC_Mode == 4)
    ADCAddSingleChannel(ADCx,ADC_IN_0,ADC_480_CYCLES);
    if(ADC_CurrentTabs[1] >= 0)
    {
        ADCAddInjectedChannel(ADCx,ADC_IN_1,ADC_480_CYCLES);
        #if(__configADC_Mode == 4)
        if(ADC_CurrentTabs[2] != -1)
        {
            ADCAddInjectedChannel(ADCx,ADC_IN_2,ADC_480_CYCLES);
        }
        #endif /*__configADC_Mode*/
    }
    #if(__configUSE_Battery_Charging == 1)
    #undef __configUSE_Temperature_Sensor
    ADCAddInjectedChannel(ADCx,18,ADC_480_CYCLES);
    ADC_Common_TypeDef VBat;
    VBat->CCR |= (0x1 << 22);
    #endif /*__configUSE_Battery_Charging*/
    #if(__configUSE_Temperature_Sensor == 1)
    ADCAddInjectedChannel(ADCx,18,ADC_480_CYCLES);
    ADC_Common_TypeDef VTemp;
    VTemp->CCR |= (0x1 << 23);
    #endif /*__configUSE_Temperature_Sensor*/
    SetADCContInjected(ADCx);
    ADCSimpleConfigure(ADCx);
#endif /*__configADC_Mode*/
}

void AnalogRead(ADC_TypeDef *ADCx)
{
// Convert in Volts
#if(__configCONVERT_Volts == 1)
#if(__configADC_Mode == 1)
    ADCStatus.adc_data[0] = ((float)ADCx->DR) * 3.3 / K_RESOLUTION;
    #if(__configUSE_Battery_Charging == 1)
    ADCStatus.BATTERY = ((float)ADCx->JDR1) * 3.3 / K_RESOLUTION;
    #endif /*__configUSE_Battery_Charging*/
    #if(__configUSE_Temperature_Sensor == 1)
    ADCStatus.TEMPERATURE = ADCx->JDR1;
    #endif /*__configUSE_Temperature_Sensor*/
#elif(__configADC_Mode == 2)

#elif(__configADC_Mode == 3)

#elif(__configADC_Mode == 4)

#elif(__configADC_Mode == 5)

#endif /*__configADC_Mode*/
//////////////////////////////////////////////////////////////////////////
// Non convert Volts
#elif(__configCONVERT_Volts == 0)
#if(__configADC_Mode == 1)
    ADCStatus.adc_data[0] = ((float)ADCx->DR) * 3.3 / K_RESOLUTION;
    #if(__configUSE_Battery_Charging == 1)
    ADCStatus.BATTERY = ((float)ADCx->JDR1) * 3.3 / K_RESOLUTION;
    #endif /*__configUSE_Battery_Charging*/
    #if(__configUSE_Temperature_Sensor == 1)
    ADCStatus.BATTERY = ADCx->JDR1;
    #endif /*__configUSE_Temperature_Sensor*/
#elif(__configADC_Mode == 2)

#elif(__configADC_Mode == 3)

#elif(__configADC_Mode == 4)

#elif(__configADC_Mode == 5)

#endif /*__configADC_Mode*/
#endif /*__configCONVERT_Volts*/
//////////////////////////////////////////////////////////////////////////
}
/**
*   This Functions necessary for parsing Multiplexer outputs
*/
//------------------------------------------------------------------------------------//
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
//    static int NumPort = 0;
//    if(Multi_In[NumPort][1] == 0) { NumPort++; if(NumPort == 8) NumPort = 0; return; }
//    SetMulriplexer_State(Multi_In[NumPort][0]);
//    ADCStatus.Multiplexer_1[NumPort] = ADCx->JDR1;
//    if(NumPort == 8) NumPort = 0;
//    else NumPort++;
}
#endif /*__configADC_Mode*/
#endif /*configUSE_ADC*/
