#include "main.h"
//Servomotor Servo1;
int main(void)
{
    Board_Config;
    SSD1306_Init();
    SSD1306_GotoXY(1, 5); //������������� ������ � ������� 0;44. ������� �� �����������, ����� ���������.
    SSD1306_Puts("RCR-DSTU RobotV1.0", &Font_7x10, SSD1306_COLOR_WHITE); //����� ������� � ������������ ������� ������� "Font_7x10" ����� ������.
//    ssd1306_image(logo_RCR_40x40, 40, 40, 80, 20);
//    ssd1306_image(logo_DSTU_40x40, 40, 40, 5, 20);
    SSD1306_UpdateScreen();
    ADC_Init(ADC1);
    //ServoInit(&Servo1,PDI6225MG_300,TIM5,20);
    //ServoSetRange(&Servo1, 0, 60);
    //SetServoAngle(&Servo1,0);
    //init_PID_Regulator();
    while(1)
    {

    }
}

