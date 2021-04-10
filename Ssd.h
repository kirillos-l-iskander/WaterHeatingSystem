#ifndef SSD_H
#define	SSD_H

#include "Config.h"
#include "Gpio.h"

typedef enum
{
	SSD_ID_1 = 0,
	SSD_ID_2,
	SSD_ID_MAX,
}   SSD_ID_t;

typedef enum
{
	SSD_STATE_OFF = 0,
	SSD_STATE_ON,
}   SSD_STATE_t;

typedef enum
{
	SSD_BLINK_0MS = 0,
	SSD_BLINK_100MS = 100,
	SSD_BLINK_500MS = 500,
	SSD_BLINK_1000MS = 1000,
	SSD_BLINK_5000MS = 5000,
}   SSD_BLINK_t;

typedef enum
{
	SSD_SYMBOL_MIN = 0,
	SSD_SYMBOL_MAX = 9,
}   SSD_SYMBOL_t;

void Ssd_init( SSD_ID_t id, GPIO_ID_t gpioIdC, GPIO_PIN_t gpioPinC, GPIO_ID_t gpioIdD, GPIO_PIN_t gpioPinD );
void Ssd_update( void *paramter );
void Ssd_setState( SSD_ID_t id, SSD_STATE_t state, SSD_BLINK_t period );
void Ssd_setSymbol( SSD_ID_t id, SSD_SYMBOL_t symbol );

#endif	/* SSD_H */
