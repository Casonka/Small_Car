#pragma once


/////////////////////////////////////////////////////////////////////////////
//________________________________BTN PWM_______________________________//
/////////////////////////////////////////////////////////////////////////////
#define BTN1_PWM_PIN            pin_id(PORTD,12)
#define BTN2_PWM_PIN            pin_id(PORTD,13)

#define BTN1_CCR                ((uint32_t *)&(TIM4->CCR1))
#define BTN2_CCR                ((uint32_t *)&(TIM4->CCR2))
/////////////////////////////////////////////////////////////////////////////
//_____________________________BTN directions___________________________//
/////////////////////////////////////////////////////////////////////////////
#define BTN1_DIR_PIN          pin_id(PORTC,14)          //
#define BTN2_DIR_PIN          pin_id(PORTC,15)          //
/////////////////////////////////////////////////////////////////////////////
//________________________________Encoders_________________________________//
/////////////////////////////////////////////////////////////////////////////
#define ENCODER1A_PIN           pin_id(PORTC,6)
#define ENCODER1B_PIN           pin_id(PORTC,7)
#define ENCODER2A_PIN           pin_id(PORTA,15)
#define ENCODER2B_PIN           pin_id(PORTB,3)

#define  ENCODER1_CNT           ((uint32_t *)&(TIM8->CNT))
#define  ENCODER2_CNT           ((uint32_t *)&(TIM2->CNT))
/////////////////////////////////////////////////////////////////////////////
//_____________________________GENERAL_PIN_________________________________//
/////////////////////////////////////////////////////////////////////////////
#define GENERAL_PIN_0            pin_id(PORTA,0)                //ADC12_IN0//
#define GENERAL_PIN_1            pin_id(PORTA,1)                //ADC12_IN1//
#define GENERAL_PIN_2            pin_id(PORTA,2)                //ADC12_IN2//
#define GENERAL_PIN_3            pin_id(PORTA,3)                //ADC12_IN3//
#define GENERAL_PIN_4            pin_id(PORTB,0)                //ADC12_IN8//
#define GENERAL_PIN_5            pin_id(PORTB,1)                //ADC12_IN9//
#define GENERAL_PIN_6            pin_id(PORTC,1)                //ADC12_IN11//
#define GENERAL_PIN_7            pin_id(PORTC,2)                //ADC12_IN12//
#define GENERAL_PIN_8            pin_id(PORTC,4)                //ADC12_IN14//
#define GENERAL_PIN_9            pin_id(PORTC,5)                //ADC12_IN15//

/////////////////////////////////////////////////////////////////////////////
//__________________________________USART__________________________________//
/////////////////////////////////////////////////////////////////////////////
//USART3 in stm32, USART1 as PCB header. AF7
#define TX1_PIN                  pin_id(PORTC,10)
#define RX1_PIN                  pin_id(PORTC,11)
//USART1 in stm32, USART2 as PCB header. AF7
#define TX2_PIN                  pin_id(PORTB,6)
#define RX2_PIN                  pin_id(PORTB,7)

#define USB_Switch_ON            pin_id(PORTC,0)
/////////////////////////////////////////////////////////////////////////////
//____________________________External interrupts__________________________//
/////////////////////////////////////////////////////////////////////////////
#define EXTI1_PIN               pin_id(PORTD,0)         // ׀אחתול EXTI1 // HALL_SENSOR_1
#define EXTI2_PIN               pin_id(PORTD,1)         // ׀אחתול EXTI2 // HALL_SENSOR_2
#define EXTI3_PIN               pin_id(PORTD,2)         // ׀אחתול EXTI3 //
#define EXTI4_PIN               pin_id(PORTD,3)         // ׀אחתול EXTI4 //
#define EXTI5_PIN               pin_id(PORTE,4)         // ׀אחתול EXTI5 //
#define EXTI6_PIN               pin_id(PORTD,6)         // ׀אחתול EXTI6 //
#define EXTI7_PIN               pin_id(PORTD,7)         // ׀אחתול EXTI7 //
#define EXTI8_PIN               pin_id(PORTD,8)         // ׀אחתול EXTI8 //
#define EXTI9_PIN               pin_id(PORTD,9)         // ׀אחתול EXTI9 //
#define EXTI10_PIN              pin_id(PORTD,10)        // ׀אחתול EXTI10 //
/////////////////////////////////////////////////////////////////////////////
//________________________________I2C2 pins________________________________//
/////////////////////////////////////////////////////////////////////////////
//I2C2 in stm32; I1,I2 as PCB headers
#define I2C_SDA_PIN             pin_id(PORTB,11)                  //I2C_SDA//
#define I2C_SCL_PIN             pin_id(PORTB,10)                  //I2C_SCL//
/////////////////////////////////////////////////////////////////////////////
//_________________________________+12V_PINS_______________________________//
/////////////////////////////////////////////////////////////////////////////
#define PIN6_12V	        pin_id(PORTB, 4)
#define PIN5_12V	        pin_id(PORTB, 5)
#define PIN4_12V	        pin_id(PORTD, 11)
#define PIN3_12V	        pin_id(PORTA, 5)
#define PIN2_12V	        pin_id(PORTC, 9)
#define PIN1_12V	        pin_id(PORTC, 8)
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//_________________________________Other Pins_______________________________//
/////////////////////////////////////////////////////////////////////////////
#define DYNAMIXEL_IO_CONTROL	        pin_id(PORTB,12)        /// DRUM_DX
/////////////////////////////////////////////////////////////////////////////
#endif /*Configuration pins for STM32F40_41xxx*/

