#include "mpu9250.h"

#if(EXTERNAL_MPU9250 == 1)

#define MPU_Reconnect_it    (100)
static uint32_t MPU_Timeout;

/*!
*   @brief Initialization MPU9250
*/
uint8_t MPU_Init(I2C_TypeDef* I2Cx, uint8_t aScale, uint8_t gScale)
{
    MPU9250.status = 5;
    I2CSimpleConfigure(I2Cx,I2C_Fast);
    bool connect = false;

    connect = MPU_Connect(I2Cx,true);
    if(!connect) return 1;

#if(CALC_I2C_SCANNING == 1)
    MPU9250.status = 1;
#endif/*CALC_I2C_SCANNING*/
    uint8_t Data;
    Data = I2C_MemoryReadSingle(I2Cx,MPU9250_ADDR,WHO_AM_I);

    if((Data) != WHO_AM_I_9250) return 1;

    (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,PWR_MGMT_1,0x00);

    MPU_ScaleCalibration(I2Cx,aScale,gScale);

return 0;
}

void MPU_ScaleCalibration(I2C_TypeDef* I2Cx, uint8_t aScale, uint8_t gScale)
{
//--------------------Accelerometer Scale Configuration--------------------------//
    switch(aScale)
    {
        case AFSR_2G:
        MPU9250.aScaleFactor = 16384.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,ACCEL_CONFIG,0x00);
        break;

        case AFSR_4G:
        MPU9250.aScaleFactor = 8192.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,ACCEL_CONFIG,0x08);
        break;

        case AFSR_8G:
        MPU9250.aScaleFactor = 4096.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,ACCEL_CONFIG,0x10);
        break;

        case AFSR_16G:
        MPU9250.aScaleFactor = 2048.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,ACCEL_CONFIG,0x18);
        break;

        default:
        MPU9250.aScaleFactor = 8192.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,ACCEL_CONFIG,0x08);
        break;
    }
//-------------------------------------------------------------------------------//
//--------------------Gyroscope Scale Configuration------------------------------//
    switch(gScale)
    {
        case GFSR_250DPS:
        MPU9250.gScaleFactor = 131.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,GYRO_CONFIG,0x00);
        break;

        case GFSR_500DPS:
        MPU9250.gScaleFactor = 65.5;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,GYRO_CONFIG,0x08);
        break;

        case GFSR_1000DPS:
        MPU9250.gScaleFactor = 32.8;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,GYRO_CONFIG,0x10);
        break;

        case GFSR_2000DPS:
        MPU9250.gScaleFactor = 16.4;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,GYRO_CONFIG,0x18);
        break;

        default:
        MPU9250.gScaleFactor = 65.5;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,GYRO_CONFIG,0x08);
        break;
    }
//-------------------------------------------------------------------------------//
}

void MPU_GyroscopeCalibration(I2C_TypeDef* I2Cx, uint16_t CalPoints)
{
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;

    if(CalPoints == 0) CalPoints = 1;

    for(int i = 0; i < CalPoints; i++)
    {
        x += MPU9250.Raw_Data[4];
        y += MPU9250.Raw_Data[5];
        z += MPU9250.Raw_Data[6];
        int z = 300;
        while(--z > 0) {}
    }

    MPU9250.GyroCal[0] = (float)x / (float)CalPoints;
    MPU9250.GyroCal[1] = (float)y / (float)CalPoints;
    MPU9250.GyroCal[2] = (float)z / (float)CalPoints;
}

/*!
*   @brief Connect to MPU9250
*/
bool MPU_Connect(I2C_TypeDef* I2Cx, bool IsWrite)
{

    for(int i = 0; i < MPU_Reconnect_it; i++)
    {
        SetI2CPeriphDisable(I2Cx);
        MPU9250.status = 5;

        I2C_ClearAllStats(I2Cx);

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
        if(!I2CStartBitEvent(I2Cx)) continue;

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

        I2CStop(I2Cx);

        return true;
    }

return false;
}

bool MPU_ReadRawData(I2C_TypeDef* I2Cx)
{
    uint8_t Bus[14];

    uint16_t DataItems = I2C_MemoryReadMultiple(I2Cx,MPU9250_ADDR,ACCEL_XOUT_H, Bus, 14);
    if(DataItems != 14) return false;

    MPU9250.Raw_Data[0] = Bus[0] << 8 | Bus[1]; //ax
    MPU9250.Raw_Data[1] = Bus[2] << 8 | Bus[3]; //ay
    MPU9250.Raw_Data[2] = Bus[4] << 8 | Bus[5]; //az
    MPU9250.Raw_Data[3] = Bus[6] << 8 | Bus[7]; //temperature
    MPU9250.Raw_Data[4] = Bus[8] << 8 | Bus[9];     //gx
    MPU9250.Raw_Data[5] = Bus[10] << 8 | Bus[11];   //gy
    MPU9250.Raw_Data[6] = Bus[12] << 8 | Bus[13];   //gz

    MPU9250.SensorData[0] = MPU9250.Raw_Data[0] / MPU9250.aScaleFactor;
    MPU9250.SensorData[1] = MPU9250.Raw_Data[1] / MPU9250.aScaleFactor;
    MPU9250.SensorData[2] = MPU9250.Raw_Data[2] / MPU9250.aScaleFactor;

    MPU9250.Gyroscope[0] = (MPU9250.Raw_Data[4] - MPU9250.GyroCal[0]) / MPU9250.gScaleFactor;
    MPU9250.Gyroscope[1] = (MPU9250.Raw_Data[5] - MPU9250.GyroCal[1]) / MPU9250.gScaleFactor;
    MPU9250.Gyroscope[2] = (MPU9250.Raw_Data[6] - MPU9250.GyroCal[2]) / MPU9250.gScaleFactor;

    uint8_t Bus1[6];

    DataItems = I2C_MemoryReadMultiple(I2Cx,MPU9250_ADDR,Magnet_XOUT_L, Bus1, 6);
    if(DataItems != 6) return false;

    MPU9250.Compass[0] = Bus1[1] << 8 | Bus1[0];
    MPU9250.Compass[1] = Bus1[3] << 8 | Bus1[2];
    MPU9250.Compass[2] = Bus1[5] << 8 | Bus1[4];

return true;
}

#endif /*EXTERNAL_MPU9250*/
