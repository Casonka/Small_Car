#pragma once
#include <stdbool.h>
#include "FilConfig.h"

#define PDI6225MG_300   0
#define MG996R          1

typedef struct
{
    volatile uint32_t *CCR,
                       ARR;
    uint16_t  ms;
    float     min_ms,
              max_ms;
    uint16_t maxAngle;
    uint16_t Range_min, Range_max;
} Servomotor;

bool SetVoltage(float Duty);

void ServoInit(Servomotor* Servo, char servoType, TIM_TypeDef *TIMx, uint16_t ms);

void ServoSetRange(Servomotor* Servo, uint16_t min_angle, uint16_t max_angle);

void SetServoAngle(Servomotor* Servo, uint16_t angle);
