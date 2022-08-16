#pragma once
#include "main.h"
#include "BoardSelection.h"

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
bool MPU_WriteRegistry(I2C_TypeDef* I2Cx, uint8_t Register, uint8_t Value);

bool MPU_ReadRawData(I2C_TypeDef* I2Cx);

/*!
*   @brief Main Init Function for MPUxx50
*       @note [RCR] MPU9250 currently used
*/
/*!
*   @note [MPU] Registry
*/
#define MPU9250_PWR             0x6B
#define MPU9250_Gyro_Conf       0x1B
#define MPU9250_Accel_Conf      0x1C
#define MPU9250_Accel_XoutH     0x3B

uint8_t MPU_Init(I2C_TypeDef* I2Cx);


