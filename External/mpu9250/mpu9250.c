#include "mpu9250.h"

#ifdef INCLUDED_I2C

#ifndef __configI2C_TIMEOUT
#define __configI2C_TIMEOUT     (20000)
#endif /*__configI2C_TIMEOUT*/


/*!
*   @brief This function is reconnect to device MPU9250
*       @note [MPU] if this function on too long then have problem on bus I2C
*/
#define MPU_Reconnect_it    (100)
bool MPU_Connect(I2C_TypeDef* I2Cx)
{

for(int i = 0; i <= MPU_Reconnect_it; i++)
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

        MPU_Timeout = __configI2C_TIMEOUT;
        while (!I2CStartBitEvent(I2Cx)) {
            if (--I2C_timeout == 0x00)
            {
                break;
            }
        }
        if(!(I2Cx->SR1 & I2C_SR1_SB)) continue;


        if ((I2Cx->CR1 & I2C_CR1_ACK) == 0) SetI2CAsk(I2Cx);

        I2Cx->DR = (MPU9250_ADDR << 1) & ~I2C_OAR1_ADD0;

        MPU_Timeout = __configI2C_TIMEOUT;
        while(!I2CAddressSentEvent(I2Cx))
        {
            if(--I2C_timeout == 0x00) {
                break;
            }
        }
        if(!(I2Cx->SR1 & I2C_SR1_ADDR)) continue;

        return true;
}

return false;
}

bool connect = false;
static uint32_t MPU_Timeout;
uint8_t MPU_Init(I2C_TypeDef* I2Cx)
{
    if(I2CPeriphEnableEvent(I2Cx) == 1) return 1;
    I2CSimpleConfigure(I2Cx,I2C_Fast);

    SetI2CAsk(I2Cx);
    I2CStart(I2Cx);

        connect = MPU_Connect(I2C1);

return 0;
}

#endif /*INCLUDED_I2C*/
