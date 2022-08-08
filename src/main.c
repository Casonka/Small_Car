#include "main.h"

int main(void)
{
    Board_Config;
    //SetServo(&Servo1,BIG_BLACK_SERVA,180,TIM2->CCR1,TIM2->ARR,2.2);
    //SetServoAngle(&Servo1, 20);
    TIM1->CCR1 = 64;
    TIM5->CCR1 = 125;
    //TIM5->CCR1 = 0x200;
    //ADC_Init(ADC1);
    //init_PID_Regulator();
    while(1)
    {

    }
}

