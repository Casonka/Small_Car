#pragma once
#if (configUSE_FREERTOS == 1)

#include "FilConfig.h"
/*!
*   @brief vBlinkTest(void *pvParameters) - ���� ���������� ������ ������������ ������� FreeRTOS
*       @arg nothing
*       @note [FIL:FreeRTOS] ����� �������� ������������ � ������������� �� ���� https://www.freertos.org/features.html
*/
xTaskHandle xBlinkHandle;
void vBlinkTest(void *pvParameters);

#endif /*configUSE_FREERTOS*/
