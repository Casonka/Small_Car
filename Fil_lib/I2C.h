    /*!
    *   --------------------------------------------------------------------------
    *                       ///I2C initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 01/08/2022 - last update version I2C
    *
    *       @note [FIL:I2C] Configuration file I2C
    */
#include "FilConfig.h"

#if(configUSE_I2C == 1)

#define ConfTimPSC(TIM,PRESCALER)     { TIM->PSC = ((uint32_t)(TIM->PSC & ((uint32_t)(~0xFFFFFFFF))) | ((uint32_t)PRESCALER));}

#endif /*configUSE_I2C*/
