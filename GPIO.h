#ifndef GPIO_H
#define GPIO_H

#include "CONFIG.h"
#include "PORT.h"
#include "SCH_CONFIG.h"
#include "SCH.h"
#include "TIM.h"
#include "GPIO.h"
#include "LED.h"

#include "SW.h"
#include "ADC.h"
#include "TEMP.h"
#include "HCU.h"
#include "SSD.h"
#include "DISP.h"
#include "I2C.h"
#include "EEPROM.h"
#include "WH.h"

#define INPUT (1)
#define OUTPUT (0)
#define LOW (0)
#define HIGH (1)

#define GPIOA ((GPIO_TypeDef*)&PORTA)
#define GPIOB ((GPIO_TypeDef*)&PORTB)
#define GPIOC ((GPIO_TypeDef*)&PORTC)
#define GPIOD ((GPIO_TypeDef*)&PORTD)
#define GPIOE ((GPIO_TypeDef*)&PORTE)

typedef struct
{
	uint8_t PORT;
	uint8_t PAD[127];
	uint8_t TRIS;
}GPIO_TypeDef;

void GPIO_InitPin(GPIO_TypeDef* GPIOx, uint8_t PINx, uint8_t Mode);
void GPIO_SetPinState(GPIO_TypeDef* GPIOx, uint8_t PINx, uint8_t State);
uint8_t GPIO_GetPinState(GPIO_TypeDef* GPIOx, uint8_t PINx);
void GPIO_SetPortState(GPIO_TypeDef* GPIOx, uint8_t PINx, uint8_t State);
uint8_t GPIO_GetPortState(GPIO_TypeDef* GPIOx);

#endif /* GPIO_H */
