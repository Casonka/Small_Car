#pragma once
#include "main.h"
#include "BoardSelection.h"

struct {

    int16_t Raw_Data[6];
    float SensorData[6];
    float Gyroscope[3];
    float Altitude[3];

}MPU9250;

uint8_t MPU_Init(I2C_TypeDef* I2Cx);


