#pragma once
#include "FilConfig.h"
#if(EXTERNAL_MPU9250 == 1)

#include "stdbool.h"
struct {
    char status;
    int16_t Raw_Data[6];
    float SensorData[6];
    float Gyroscope[3];
    float Altitude[3];

}MPU9250;

/*!
*   @brief This function is reconnect to device MPUXX50
*       @note [MPU] if this function on too long then have problem on bus I2C and reconnect_it is much
*/
bool MPU_Connect(I2C_TypeDef* I2Cx, bool IsWrite);

/*!
*   @brief This function is writing new value to device MPUXX50
*       @note [MPU] if end value if false then have problem with bus or device
*/
uint8_t MPU_WriteRegistry(I2C_TypeDef* I2Cx, uint8_t Register, uint8_t Value);

uint8_t MPU_ReadRegistry(I2C_TypeDef* I2Cx, uint8_t Register);

bool MPU_ReadRawData(I2C_TypeDef* I2Cx);

/*!
*   @brief Main Init Function for MPUxx50
*       @note [RCR] MPU9250 currently used
*/

/*!
*   @note [MPU] Registry
*/
#define WHO_AM_I_6050     0x68
#define WHO_AM_I_9250     0x71
#define WHO_AM_I          0x75
#define AD0_LOW           0x68
#define AD0_HIGH          0x69
#define GYRO_CONFIG       0x1B
#define ACCEL_CONFIG      0x1C
#define PWR_MGMT_1        0x6B
#define ACCEL_XOUT_H      0x3B

uint8_t MPU_Init(I2C_TypeDef* I2Cx, uint8_t aScale, uint8_t gScale);

#endif/*EXTERNAL_MPU9250*/
