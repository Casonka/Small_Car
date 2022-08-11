    /*!
    *   --------------------------------------------------------------------------
    *                       ///I2C initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 01/08/2022 - last update version I2C
    *
    *       @note [FIL:I2C] Configuration file I2C
    */
#pragma once
#include "FilConfig.h"

#if(FIL_I2C == 1)

    /*!
    *   @brief I2CMasterConfigure(I2C,SPEED) - configuration I2C in master mode
    *       @arg I2C - number of I2C interface
    *       @arg SPEED - speed mode interface (SLOW or FAST)
    *           @list I2C_Slow - slow mode I2C
    *                 I2C_Fast - fast mode I2C
    *       @arg
    *       @arg
    */
#define I2CMasterConfigure(I2C, SPEED, ADDRESS)                {\
    ConfI2CFreq(I2C,I2CDefaultFREQ);                            \
    ConfI2CCCR(I2C, SPEED);                                     \
    ResetI2CPeriphEnable(I2C);                                  \
    if(SPEED == I2C_Slow) { SetI2CMasterModeSlow(I2C);          \
                           ConfI2CTrise(I2C,RiseTimeDefaultSM);}\
    if(SPEED == I2C_Fast) {ConfI2CTrise(I2C,RiseTimeDefaultFM); \
                          SetI2CMasterModeFast(I2C);}           \
    SetI2CPeriphEnable(I2C);                                    \
    ConfI2CAddress(I2C, ADDRESS);                               }

    /*!
    *   @brief I2CSlaveConfigure() -
    *       @arg
    *       @arg
    *       @arg
    *       @arg
    */
#define I2CSlaveConfigure(I2C, SPEED, ADDRESS)

//-----------------------Simple commands reset and set the state-------------------------------------------------------------------------------------------------------------//
#define I2CDefaultFREQ      ((uint16_t)(0x2A))  // 42MHz -> APB1 bus
#define ConfI2CFreq(I2C,FREQ)         { I2C->CR2 = ((uint32_t)(I2C->CR2 & ((uint32_t)(~I2C_CR2_FREQ))) | ((uint32_t)FREQ));}

#define RiseTimeDefaultSM   ((uint16_t)(0x34))
#define RiseTimeDefaultFM   ((uint16_t)(0x12))
#define ConfI2CTrise(I2C,vTRISE)       { I2C->TRISE = ((uint32_t)(I2C->TRISE & ((uint32_t)(~I2C_TRISE_TRISE))) | ((uint32_t)vTRISE));}

#define ConfI2CAddress(I2C, ADDRESS)  { I2C->OAR1 = ((uint32_t)(I2C->OAR1 & ((uint32_t)(~I2C_OAR1_ADD1_7))) | ((uint32_t)(ADDRESS << 1)));}

#define I2C_Slow            (420)
#define I2C_Fast            (105)
#define ConfI2CCCR(I2C,SPEED)           { I2C->CCR = ((uint32_t)(I2C->CCR & ((uint32_t)(~I2C_CCR_CCR))) | ((uint32_t)SPEED));}

//----------------------------------------Set state----------------------------------------------------//
#define SetI2CMasterModeFast(I2C) { I2C->CCR |= I2C_CCR_FS;}
#define SetI2CPeriphEnable(I2C)   { I2C->CR1 |= I2C_CR1_PE;}
#define I2CStart(I2C)             { I2C->CR1 |= I2C_CR1_START;}
//---------------------------------------Reset state---------------------------------------------------//
#define SetI2CMasterModeSlow(I2C) { I2C->CCR &= (~I2C_CCR_FS);}
#define ResetI2CPeriphEnable(I2C) { I2C->CR1 &= (~I2C_CR1_PE);}
//---------------------------------------Status flags---------------------------------------------------//
#define I2CBusyEvent(I2C)              ((I2C->SR2 & I2C_SR2_BUSY) == 1)
#define I2CStartBitEvent(I2C)          ((I2C->SR1 & I2C_SR1_SB) == 1)
#define I2CAddressSentEvent(I2C)       ((I2C->SR1 & I2C_SR1_ADDR) == 1)
#define I2CMasterModeEvent(I2C)        ((I2C->SR2 & I2C_SR2_MSL) == 1)
#define I2CDataEmptyEvent(I2C)         ((I2C->SR1 & I2C_SR1_TXE) == 1)

#ifndef __configI2C_TIMEOUT
#define __configI2C_TIMEOUT					20000
#endif
#endif /*FIL_I2C*/
