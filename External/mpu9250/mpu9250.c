#include "mpu9250.h"

#ifdef INCLUDED_I2C

#define MPU_Reconnect_it    (100)
bool connect = false;
static uint32_t MPU_Timeout;

uint8_t MPU_Init(I2C_TypeDef* I2Cx)
{
    MPU9250.status = 5;
    I2CSimpleConfigure(I2Cx,I2C_Fast);

    connect = MPU_Connect(I2Cx,true);
    if(!connect) return 1;

#if(CALC_I2C_SCANNING == 1)
    MPU9250.status = 1;
#endif/*CALC_I2C_SCANNING*/
    bool IsWrite;

    IsWrite = MPU_WriteRegistry(I2Cx,MPU9250_PWR,1);
    if(IsWrite == false) return 1;

    I2CStop(I2Cx);
return 0;
}

bool MPU_Connect(I2C_TypeDef* I2Cx, bool IsWrite)
{

for(int i = 0; i < MPU_Reconnect_it; i++)
{
    SetI2CPeriphDisable(I2Cx);
    MPU9250.status = 5;

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
        if (--MPU_Timeout == 0x00)
        {
            MPU9250.status = 4;
            break;
        }
    }
    if(!(I2Cx->SR1 & I2C_SR1_SB)) continue;

    if ((I2Cx->CR1 & I2C_CR1_ACK) == 0) SetI2CAsk(I2Cx);

    if(IsWrite) I2Cx->DR = (MPU9250_ADDR << 1) & ~I2C_OAR1_ADD0;
    else I2Cx->DR = (MPU9250_ADDR << 1) | I2C_OAR1_ADD0;

    MPU_Timeout = __configI2C_TIMEOUT;
    while(!I2CAddressSentEvent(I2Cx))
    {
        if(--MPU_Timeout == 0x00) {
            MPU9250.status = 3;
            break;
        }
    }
    if(!(I2Cx->SR1 & I2C_SR1_ADDR)) continue;

    return true;
}

return false;
}

bool MPU_WriteRegistry(I2C_TypeDef* I2Cx, uint8_t Register, uint8_t Value)
{
    bool status = false;
    if(!I2CDataEmptyEvent(I2Cx)) return false;

    status = I2C_SingleSend(I2Cx,Register,true);
    status = I2C_SingleSend(I2Cx,Value,true);

return status;
}

/*!
*   @fixme
*/
bool MPU_ReadRegistry(I2C_TypeDef* I2Cx, uint8_t Register, uint8_t Value)
{
    if(!I2CDataEmptyEvent(I2Cx)) return false;

    // Send Registry to device
    I2CSendData(I2Cx,MPU9250_PWR,0);

    MPU_Timeout = __configI2C_TIMEOUT;
    while(!I2CDataEmptyEvent(I2Cx))
    {
        if(--MPU_Timeout == 0x00) {
            MPU9250.status = 2;
            return false;
        }
    }

    //Write value
    I2CSendData(I2Cx,1,0);

    MPU_Timeout = __configI2C_TIMEOUT;
    while(!I2CDataEmptyEvent(I2Cx))
    {
        if(--MPU_Timeout == 0x00) {
            MPU9250.status = 2;
            return false;
        }
    }
return true;
}

bool MPU_ReadRawData(I2C_TypeDef* I2Cx)
{
uint8_t Buffer[14];

    ResetI2CData(I2Cx);
    (void)I2Cx->SR1;
    (void)I2Cx->SR2;

    (void)MPU_WriteRegistry(I2Cx,MPU9250_Accel_XoutH,1);

    (void)MPU_Connect(I2Cx,false);
    (void)I2Cx->SR1;
    (void)I2Cx->SR2;

    I2C_MultipleRead(I2Cx,Buffer);

    MPU9250.Raw_Data[0] = (Buffer[0] << 8) | Buffer[1];
    MPU9250.Raw_Data[1] = (Buffer[2] << 8) | Buffer[3];
    MPU9250.Raw_Data[2] = (Buffer[4] << 8) | Buffer[5];
    MPU9250.Raw_Data[3] = (Buffer[8] << 8) | Buffer[9];
    MPU9250.Raw_Data[4] = (Buffer[10] << 8) | Buffer[11];
    MPU9250.Raw_Data[5] = (Buffer[12] << 8) | Buffer[13];
return true;
}

#endif /*INCLUDED_I2C*/
