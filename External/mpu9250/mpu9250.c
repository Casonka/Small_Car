#include "mpu9250.h"

#if(EXTERNAL_MPU9250 == 1)

#define MPU_Reconnect_it    (100)
static uint32_t MPU_Timeout;

/*!
*   @brief Initialization MPU9250
*       @arg status - errors with connection to device
*       @value 1 - Start success, no errors
*       @value 2 - power resetting done
*       @value 3 - Verification complete
*       @value 4 - MPU_Connect done
*       @value 5 - begin connection
*/
uint8_t MPU_Init(uint8_t aScale, uint8_t gScale)
{
    if(I2CBusBusyEvent(__configEXTMPU_SOURCE))  I2C_RestoreConnection(I2C1);

    I2CSimpleConfigure(__configEXTMPU_SOURCE,I2C_Fast);
    bool connect = false;

    connect = MPU_Connect(__configEXTMPU_SOURCE,true);
    if(!connect) return 1;

    uint8_t Data;
    Data = I2C_MemoryReadSingle(__configEXTMPU_SOURCE,MPU9250_ADDR,MPUWHO_AM_I);
    if((Data) != MPUWHO_AM_I_9250) return 1;
#if(CALC_I2C_SCANNING == 1)
    MPU9250.MPUstatus = 3;
#endif/*CALC_I2C_SCANNING*/
    delay_ms(50);
    (void)I2C_MemoryWriteSingle(__configEXTMPU_SOURCE,MPU9250_ADDR,MPUPWR_MGMT_1,0x00);
    delay_ms(50);
#if(CALC_I2C_SCANNING == 1)
    MPU9250.MPUstatus = 2;
#endif/*CALC_I2C_SCANNING*/
#if(__configEXTMPU_Calibration == 1)
    MPU_ScaleCalibration(__configEXTMPU_SOURCE,aScale,gScale);
    delay_ms(50);
    AK8963_Init();
#endif /*__configEXTMPU_Calibration*/

#if(CALC_I2C_SCANNING == 1)
    MPU9250.MPUstatus = 1;
#endif/*CALC_I2C_SCANNING*/

return 0;
}

/*!
*   @brief Initialization Magnetometer AK8963
*       @arg status - errors with connection to device
*       @value 1 - Start success, no errors
*       @value 2 - power resetting done
*       @value 3 - Begin initialization
*/
void AK8963_Init(void)
{
#if(CALC_I2C_SCANNING == 1)
    MPU9250.AK8963status = 3;
#endif/*CALC_I2C_SCANNING*/
    __attribute__((unused)) uint8_t REG;
    uint8_t REGbuf[3];

    // Power mode OFF
    REG = AK8963_WriteRegister(AK8963_CTRL1, 0x00, 1);
    delay_ms(50);

    // Enable FUSE access mode
    REG = AK8963_WriteRegister(AK8963_CTRL1, 0xF, 1);
    delay_ms(50);

    (void)AK8963_ReadRegisters(AK8963_ASAX, REGbuf, 3);
    MPU9250.MagnetometerScaleFactor[0] = ((((float)REGbuf[0]) - 128.0)/ 256.0 + 1.0)* 4912.0 / 32760.0;
    MPU9250.MagnetometerScaleFactor[1] = ((((float)REGbuf[1]) - 128.0)/ 256.0 + 1.0)* 4912.0 / 32760.0;
    MPU9250.MagnetometerScaleFactor[2] = ((((float)REGbuf[2]) - 128.0)/ 256.0 + 1.0)* 4912.0 / 32760.0;

    REG = AK8963_WriteRegister(AK8963_CTRL1, 0x00, 1);
    delay_ms(50);

    REG = AK8963_WriteRegister(AK8963_CTRL1, 0x16, 1);
    delay_ms(50);

//    uint8_t* mPoint = (uint8_t *)(MPU9250.Raw_Data + );
//    (void)AK8963_ReadRegisters(AK8963_HXL, mPoint, 6);

#if(CALC_I2C_SCANNING == 1)
    MPU9250.AK8963status = 2;
#endif/*CALC_I2C_SCANNING*/
}

uint8_t AK8963_ReadRegisters(uint8_t Register, uint8_t* Buffer, uint8_t Length)
{
    uint8_t REG, SuccessRead;
    // Send to MPU AK8963 slave address
    REG = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE, MPU9250_ADDR, MPUI2C_SLV0_ADDR, (AK8963_ADDR | 0x80));
    if(REG == 0) return 0;
    delay_ms(50);
    //Send to MPU AK8963 register to Read
    REG = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE, MPU9250_ADDR, MPUI2C_SLV0_REG, Register);
    if(REG == 0) return 0;
    delay_ms(50);
    //Send to MPU enable bits for new slave device
    REG = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE, MPU9250_ADDR, MPUI2C_SLV0_CTRL, (Length | 0x80));
    if(REG == 0) return 0;
    delay_ms(50);

    SuccessRead = I2C_MemoryReadMultiple(__configEXTMPU_SOURCE, MPU9250_ADDR, Register,
                                         Buffer, Length);
    if(SuccessRead != Length) return 0;

return SuccessRead;
}

uint8_t AK8963_WriteRegister(uint8_t Register, uint8_t Value, uint8_t Length)
{
    uint8_t REG;
    //Send to MPU AK8963 slave address
    REG = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE, MPU9250_ADDR, MPUI2C_SLV0_ADDR, AK8963_ADDR);
    if(REG == 0) return 0;
    delay_ms(50);
    //Send to MPU AK8963 register to Write
    REG = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE, MPU9250_ADDR, MPUI2C_SLV0_REG, Register);
    if(REG == 0) return 0;
    delay_ms(50);
    //Send Value to Data Output register of device
    REG = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE, MPU9250_ADDR, MPUI2C_SLV0_DO, Value);
    if(REG == 0) return 0;
    delay_ms(50);
    //Send to MPU enable bits for new slave device
    REG = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE, MPU9250_ADDR, MPUI2C_SLV0_CTRL, (0x80 | Length));
    if(REG == 0) return 0;
    delay_ms(50);

    REG = AK8963_ReadRegister(Register, 1);
    if(REG != Value) return 0;

return REG;
}

uint8_t AK8963_ReadRegister(uint8_t Register, uint8_t Length)
{
    uint8_t REG;
    // Send to MPU AK8963 slave address
    REG = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE, MPU9250_ADDR, MPUI2C_SLV0_ADDR, (AK8963_ADDR | 0x80));
    if(REG == 0) return 0;
    delay_ms(50);
    //Send to MPU AK8963 register to Read
    REG = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE, MPU9250_ADDR, MPUI2C_SLV0_REG, Register);
    if(REG == 0) return 0;
    delay_ms(50);
    //Send to MPU enable bits for new slave device
    REG = I2C_MemoryWriteSingle(__configEXTMPU_SOURCE, MPU9250_ADDR, MPUI2C_SLV0_CTRL, (Length | 0x80));
    if(REG == 0) return 0;
    delay_ms(50);

    REG = I2C_MemoryReadSingle(__configEXTMPU_SOURCE, MPU9250_ADDR, MPUEXT_SENS_DATA_00);

return REG;
}

void MPU_ScaleCalibration(I2C_TypeDef* I2Cx, uint8_t aScale, uint8_t gScale)
{
//--------------------Accelerometer Scale Configuration--------------------------//
    switch(aScale)
    {
        case AFSR_2G:
        MPU9250.aScaleFactor = 16384.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUACCEL_CONFIG,0x00);
        break;

        case AFSR_4G:
        MPU9250.aScaleFactor = 8192.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUACCEL_CONFIG,0x08);
        break;

        case AFSR_8G:
        MPU9250.aScaleFactor = 4096.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUACCEL_CONFIG,0x10);
        break;

        case AFSR_16G:
        MPU9250.aScaleFactor = 2048.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUACCEL_CONFIG,0x18);
        break;

        default:
        MPU9250.aScaleFactor = 8192.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUACCEL_CONFIG,0x08);
        break;
    }
//-------------------------------------------------------------------------------//
//--------------------Gyroscope Scale Configuration------------------------------//
    switch(gScale)
    {
        case GFSR_250DPS:
        MPU9250.gScaleFactor = 131.0;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUGYRO_CONFIG,0x00);
        break;

        case GFSR_500DPS:
        MPU9250.gScaleFactor = 65.5;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUGYRO_CONFIG,0x08);
        break;

        case GFSR_1000DPS:
        MPU9250.gScaleFactor = 32.8;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUGYRO_CONFIG,0x10);
        break;

        case GFSR_2000DPS:
        MPU9250.gScaleFactor = 16.4;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUGYRO_CONFIG,0x18);
        break;

        default:
        MPU9250.gScaleFactor = 65.5;
        (void)I2C_MemoryWriteSingle(I2Cx,MPU9250_ADDR,MPUGYRO_CONFIG,0x08);
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
        int delay = 300;
        while(--delay > 0) {}
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
#if(CALC_I2C_SCANNING == 1)
        MPU9250.MPUstatus = 5;
#endif/*CALC_I2C_SCANNING*/

        I2C_ClearAllStats(I2Cx);

        SetI2CPeriphEnable(I2Cx);
        I2CStart(I2Cx);

        MPU_Timeout = __configI2C_TIMEOUT;
        while (!I2CStartBitEvent(I2Cx)) {
            if (--MPU_Timeout == 0x00)
            {
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
                break;
            }
        }
        if(!(I2Cx->SR1 & I2C_SR1_ADDR)) continue;
#if(CALC_I2C_SCANNING == 1)
        MPU9250.MPUstatus = 4;
#endif/*CALC_I2C_SCANNING*/

        I2CStop(I2Cx);

        return true;
    }

return false;
}
uint8_t Bus[20];
bool MPU_ReadRawData(I2C_TypeDef* I2Cx)
{
    uint8_t* MPU_data = Bus;
    //uint8_t* AK8963_data = MPU_data + 14;

    uint16_t DataItems = I2C_MemoryReadMultiple(I2Cx,MPU9250_ADDR,MPUACCEL_XOUT_H, (uint8_t *)MPU_data, 14);
    if(DataItems != 14) return false;
    MPU9250.MPUstatus = 0;
//    DataItems = I2C_MemoryReadMultiple(I2Cx,MPU9250_ADDR,EXT_SENS_DATA_00,(uint8_t *)AK8963_data, 6);
//    if(DataItems != 6) return false;

    MPU9250.Raw_Data[0] = Bus[0] << 8 | Bus[1];     //ax
    MPU9250.Raw_Data[1] = Bus[2] << 8 | Bus[3];     //ay
    MPU9250.Raw_Data[2] = Bus[4] << 8 | Bus[5];     //az
    MPU9250.Raw_Data[3] = Bus[6] << 8 | Bus[7];     //temperature
    MPU9250.Raw_Data[4] = Bus[8] << 8 | Bus[9];     //gx
    MPU9250.Raw_Data[5] = Bus[10] << 8 | Bus[11];   //gy
    MPU9250.Raw_Data[6] = Bus[12] << 8 | Bus[13];   //gz
//    MPU9250.Raw_Data[7] = Bus[15] << 8 | Bus[14];   //mx
//    MPU9250.Raw_Data[8] = Bus[17] << 8 | Bus[16];   //my
//    MPU9250.Raw_Data[9] = Bus[19] << 8 | Bus[18];   //mz

    MPU9250.Accelerometer[0] = MPU9250.Raw_Data[0] / MPU9250.aScaleFactor;
    MPU9250.Accelerometer[1] = MPU9250.Raw_Data[1] / MPU9250.aScaleFactor;
    MPU9250.Accelerometer[2] = MPU9250.Raw_Data[2] / MPU9250.aScaleFactor;

    MPU9250.Gyroscope[0] = (MPU9250.Raw_Data[4] - MPU9250.GyroCal[0]) / MPU9250.gScaleFactor;
    MPU9250.Gyroscope[1] = (MPU9250.Raw_Data[5] - MPU9250.GyroCal[1]) / MPU9250.gScaleFactor;
    MPU9250.Gyroscope[2] = (MPU9250.Raw_Data[6] - MPU9250.GyroCal[2]) / MPU9250.gScaleFactor;
    //DataItems = I2C_MemoryReadMultiple(I2Cx,MPU9250_ADDR,Magnet_XOUT_L, Bus1, 6);
    //if(DataItems != 6) return false;

//    MPU9250.Compass[0] = Bus1[1] << 8 | Bus1[0];
//    MPU9250.Compass[1] = Bus1[3] << 8 | Bus1[2];
//    MPU9250.Compass[2] = Bus1[5] << 8 | Bus1[4];

return true;
}

#endif /*EXTERNAL_MPU9250*/
