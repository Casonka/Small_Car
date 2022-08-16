#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx.h"

#include "FilConfig.h"

#ifdef INCLUDED_I2C
#include "fonts.h"
#include "images.h"
#include "ssd1306.h"
#include "ssd1306_i2c.h"
#include "mpu9250.h"
#endif /*INCLUDED_I2C*/

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H_INCLUDED */
