#ifndef SWITCH_H
#define	SWITCH_H

#include "Config.h"
#include "Gpio.h"

typedef enum
{
	SWITCH_ID_1 = 0,
	SWITCH_ID_2,
	SWITCH_ID_3,
	SWITCH_ID_MAX,
}   SW_ID_t;

typedef enum
{
	SWITCH_STATE_RELEASED = 0,
	SWITCH_STATE_PRESSED,
	SWITCH_STATE_ERROR,
}   SW_STATE_t;

void Switch_init( SW_ID_t id, GPIO_ID_t gpioId, GPIO_PIN_t gpioPin );
void Switch_update( void *paramter );
SW_STATE_t Switch_getState( SW_ID_t id );

#endif	/* SWITCH_H */
