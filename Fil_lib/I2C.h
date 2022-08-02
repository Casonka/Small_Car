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

#if(configUSE_I2C == 1)

    /*!
    *   @brief I2CMasterReceiverConfigure(I2C,SPEED) - configuration I2C for receiving messages
    *       @arg I2C - number of I2C interface
    *       @arg SPEED - speed mode interface (SLOW or FAST)
    *           @list I2C_Slow - slow mode I2C
    *                 I2C_Fast - fast mode I2C
    *       @arg
    *       @arg
    */
#define I2CMasterReceiverConfigure(I2C, SPEED, ADDRESS)        {\
    ConfI2CFreq(I2C,I2CDefaultFREQ);                            \
    ConfI2CCCR(I2C, SPEED);                                     \
    SetI2CPeriphEnable(I2C);                                    \
    (SPEED == I2C_Slow) ? SetI2CMasterModeFast(I2C) :           \
                          SetI2CMasterModeSlow(I2C);            \
    (SPEED == I2C_Slow) ? ConfI2CTrise(I2C,RiseTimeDefaultSM):  \
                          ConfI2CTrise(I2C,RiseTimeDefaultFM);  \
    ConfI2CAddress(I2C, ADDRESS);                               }

    /*!
    *   @brief I2CMasterTransmitterConfigure() -
    *       @arg
    *       @arg
    *       @arg
    *       @arg
    */
#define I2CMasterTransmitterConfigure()

    /*!
    *   @brief I2CSlaveReceiverConfigure() -
    *       @arg
    *       @arg
    *       @arg
    *       @arg
    */
#define I2CSlaveReceiverConfigure()

    /*!
    *   @brief I2CSlaveTransmitterConfigure() -
    *       @arg
    *       @arg
    *       @arg
    *       @arg
    */
#define I2CSlaveTransmitterConfigure()

//-----------------------Simple commands reset and set the state-------------------------------------------------------------------------------------------------------------//
#define I2CDefaultFREQ      ((uint16_t)(0x2A))  // 42MHz -> APB1 bus
#define ConfI2CFreq(I2C,FREQ)         { I2C->CR2 = ((uint32_t)(I2C->CR2 & ((uint32_t)(~I2C_CR2_FREQ))) | ((uint32_t)FREQ));}

#define RiseTimeDefaultSM   ((uint16_t)(0x2B))
#define RiseTimeDefaultFM   ((uint16_t)(0x11))
#define ConfI2CTrise(I2C,TRISE)       { I2C->TRISE = ((uint32_t)(I2C->TRISE & ((uint32_t)(~I2C_TRISE_TRISE))) | ((uint32_t)TRISE));}

#define ConfI2CAddress(I2C, ADDRESS)  { I2C->OAR1 = ((uint32_t)(I2C->OAR1 & ((uint32_t)(~I2C_OAR1_ADD1_7))) | ((uint32_t)(ADDRESS << 1)));}

#define I2C_Slow            (420)
#define I2C_Fast            (105)
#define ConfI2CCCR(I2C,CCR)           { I2C->CCR = ((uint32_t)(I2C->CCR & ((uint32_t)(~0x3F))) | ((uint32_t)CCR));}

//----------------------------------------Set state----------------------------------------------------//
#define SetI2CMasterModeFast(I2C) { I2C->CCR |= I2C_CCR_FS;}
#define SetI2CPeriphEnable(I2C)   { I2C->CR1 |= I2C_CR1_PE;}
#define I2CStart(I2C)             { I2C->CR1 |= I2C_CR1_START;}
//---------------------------------------Reset state---------------------------------------------------//
#define SetI2CMasterModeSlow(I2C) { I2C->CCR &= (~I2C_CCR_FS);}


#endif /*configUSE_I2C*/
