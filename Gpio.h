#ifndef GPIO_H
#define GPIO_H

#include "SchedulerConfig.h"

#define INPUT       ( 1 )
#define OUTPUT      ( 0 )
#define OUTPUT_AF   ( 0 )
#define LOW         ( 0 )
#define HIGH        ( 1 )

typedef enum
{
	GPIOA_ID,
	GPIOB_ID,
	GPIOC_ID,
	GPIOD_ID,
	GPIOE_ID
}GPIO_t;

void Gpio_initPin( Id_t Id, UBaseType_t Pin, UBaseType_t Mode );
void Gpio_setPinState( Id_t Id, UBaseType_t Pin, UBaseType_t State );
UBaseType_t Gpio_getPinState( Id_t Id, UBaseType_t Pin );
void Gpio_setPortState( Id_t Id, UBaseType_t Pins, UBaseType_t State );
UBaseType_t Gpio_getPortState( Id_t Id, UBaseType_t Pins );

#endif /* GPIO_H */
