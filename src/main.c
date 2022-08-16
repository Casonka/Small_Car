#include "main.h"
//Servomotor Servo1;

int main(void)
{
    Board_Config;
    //set_pin(INT_PIN);
    MPU_Init(__configI2C_MPU_SOURCE);
    (void)MPU_ReadRawData(I2C1);
//
//    I2C1->CR1 |= I2C_CR1_ACK;
//
//    I2CStart(I2C1);
//    I2C1->DR = (0x68 << 1);

    //finds = I2CFindDevices(I2C1);
    //I2CFindDevices();
    //SSD1306_Init();
    //SSD1306_GotoXY(1, 5);
    //ssd1306_image(Heart_50x50, 50, 50, 30, 15);
//    SSD1306_Puts("RCR-DSTU Small Car", &Font_7x10, SSD1306_COLOR_WHITE);
//    ssd1306_image(logo_RCR_40x40, 40, 40, 80, 20);
//    ssd1306_image(logo_DSTU_40x40, 40, 40, 5, 20);
    //SSD1306_UpdateScreen();
    //ADC_Init(ADC1);
    //ServoInit(&Servo1,PDI6225MG_300,TIM5,20);
    //ServoSetRange(&Servo1, 0, 60);
    //SetServoAngle(&Servo1,0);
    //init_PID_Regulator();
    while(1)
    {

    }
}

