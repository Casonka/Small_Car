    /*!
    *   --------------------------------------------------------------------------
    *                       ///I2C Source file\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska, Evgeny Garanin
    *   @date 02/08/2022 - last update version I2C
    *
    *       @note [FIL:I2C] I2C Source file.
    */
#include "I2C.h"
//---------------------------------------------------------//
//----------------------I2C Interrupts---------------------//
//---------------------------------------------------------//
#if(FIL_I2C == 1)
void I2C1_EV_IRQHandler(void)
{

}

void I2C1_ER_IRQHandler(void)
{

}

void I2C2_EV_IRQHandler(void)
{

}

void I2C2_ER_IRQHandler(void)
{

}

void I2C3_EV_IRQHandler(void)
{

}

void I2C3_ER_IRQHandler(void)
{

}

#if(CALC_I2C_SCANNING == 1)
static uint32_t I2C_timeout;
uint8_t I2CFindDevices(I2C_TypeDef* I2Cx)
{
    uint8_t IsFind = 0;
    uint8_t address = 0x01;
    uint8_t devices = 0;
    while(address <= 0x7F)
    {
        SetI2CPeriphDisable(I2Cx);

        I2Cx->CR1 = 0;
        I2Cx->DR = 0;
        (void)I2Cx->SR1;
        I2Cx->SR1 = 0;
        (void)I2Cx->SR2;
        I2Cx->SR2 = 0;

        SetI2CPeriphEnable(I2Cx);

        I2CStart(I2Cx);

        I2C_timeout = __configI2C_TIMEOUT;
        while (!I2CStartBitEvent(I2Cx)) {
            if (--I2C_timeout == 0x00)
            {
                address++;
                break;
            }
        }
        if(!(I2Cx->SR1 & I2C_SR1_SB)) continue;


        if ((I2Cx->CR1 & I2C_CR1_ACK) == 0) SetI2CAsk(I2Cx);

        I2Cx->DR = (address << 1) & ~I2C_OAR1_ADD0;

        I2C_timeout = __configI2C_TIMEOUT;
        while(!I2CAddressSentEvent(I2Cx))
        {
            if(--I2C_timeout == 0x00) {
                address++;
                break;
            }
        }
        if(!(I2Cx->SR1 & I2C_SR1_ADDR)) continue;

        if(devices > sizeof(I2CStatus.Devices)) break;
        I2CStatus.Devices[devices++] = address;
        IsFind++;
        address++;
    }
return IsFind;
}
#endif /*CALC_I2C_SCANNING*/
#endif /*FIL_I2C*/
