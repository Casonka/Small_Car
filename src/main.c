#include "main.h"

int main(void)
{
    Board_Config;
    SetI2C1;
    MPU_Init(I2C1,AFSR_4G,GFSR_500DPS);
    MPU_ReadRawData(I2C1);
    MPU_GyroscopeCalibration(I2C1,1500);
    while(1)
    {
    MPU_ReadRawData(I2C1);
    }
}
