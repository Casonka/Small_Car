#pragma once
#include "FilConfig.h"
#if(EXTERNAL_MPU9250 == 1)
#include <math.h>
#include "stdbool.h"

/*!
*   @note [MPU] MPU9250 Registry
*/
#define MPU9250_ADDR        (0x68)   // Gyro Accelerometer
#define MPU9250_ADDR_AD0    (0x69)

#define MPUACCEL_CONFIG        0x1C
#define MPUGYRO_CONFIG         0x1B
#define MPUI2C_SLV0_ADDR       0x25
#define MPUI2C_SLV0_REG        0x26
#define MPUI2C_SLV0_CTRL       0x27
#define MPUACCEL_XOUT_H        0x3B
#define MPUEXT_SENS_DATA_00    0x49
#define MPUI2C_SLV0_DO         0x63
#define MPUWHO_AM_I_6050       0x68
#define MPUPWR_MGMT_1          0x6B
#define MPUWHO_AM_I_9250       0x71
#define MPUWHO_AM_I            0x75

/*!
*   @note [MPU] AK8963 Registry
*/
#define AK8963_ADDR     0x0C    //Slave address of magnetometer

#define AK8963_HXL             0x03
#define AK8963_CTRL1           0x0A
#define AK8963_CTRL2           0x0B
#define AK8963_ASAX            0x10

struct {
    char MPUstatus;
    char AK8963status;
    float Altitude[3];
    int16_t Compass[3];
    float AnglePosition[3];
    float Accelerometer[3];
    float Gyroscope[3];
    float Magnetometer[3];
    float GyroCal[3];
    float aScaleFactor;
    float gScaleFactor;
    float MagnetometerScaleFactor[3];
    int16_t Raw_Data[10];
}MPU9250;

enum accelerometerFullScaleRange
{
    AFSR_2G,
    AFSR_4G,
    AFSR_8G,
    AFSR_16G
};

enum gyroscopeFullScaleRange
{
    GFSR_250DPS,
    GFSR_500DPS,
    GFSR_1000DPS,
    GFSR_2000DPS
};

/*!
*   @brief This function is reconnect to device MPUXX50
*       @note [MPU] if this function on too long then have problem on bus I2C and reconnect_it is much
*/
bool MPU_Connect(I2C_TypeDef* I2Cx, bool IsWrite);
uint8_t AK8963_WriteRegister(uint8_t Register, uint8_t Value, uint8_t Length);
uint8_t AK8963_ReadRegisters(uint8_t Register, uint8_t* Buffer, uint8_t Length);
uint8_t AK8963_ReadRegister(uint8_t Register, uint8_t Length);
void MPU_ScaleCalibration(I2C_TypeDef* I2Cx, uint8_t aScale, uint8_t gScale);
void MPU_GyroscopeCalibration(I2C_TypeDef* I2Cx, uint16_t CalPoints);
/*!
*   @brief This function is writing new value to device MPUXX50
*       @note [MPU] if end value if false then have problem with bus or device
*/
uint8_t MPU_WriteRegistry(I2C_TypeDef* I2Cx, uint8_t Register, uint8_t Value);

uint8_t MPU_ReadRegistry(I2C_TypeDef* I2Cx, uint8_t Register);

bool MPU_ReadRawData(I2C_TypeDef* I2Cx);
void MPU_parseData(void);
/*!
*   @brief Main Init Function for MPUxx50
*       @note [RCR] MPU9250 currently used
*/
#define RAD2DEG     57.2957795131
void AK8963_Init(void);
uint8_t MPU_Init(uint8_t aScale, uint8_t gScale);

#endif/*EXTERNAL_MPU9250*/
