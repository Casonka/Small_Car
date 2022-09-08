#include "main.h"

int main(void)
{
    Board_Config;
    I2CSimpleConfigure(I2C1,I2C_Fast);
    MPU_Init(AFSR_4G,GFSR_500DPS);

    MPU_ReadRawData();
    MPU_GyroscopeCalibration(I2C1,1500);
    while(1)
    {
        MPU_ReadRawData();
    }
}
