#ifndef TEMPCTRL_H
#define	TEMPCTRL_H

#include "Config.h"
#include "Gpio.h"

typedef enum
{
	TEMPCTRL_ID_1 = 0,
	TEMPCTRL_ID_MAX,
}   TEMPCTRL_ID_t;

typedef enum
{
	TEMPCTRL_STATE_OFF = 0,
	TEMPCTRL_STATE_HEAT,
	TEMPCTRL_STATE_COOL,
}   TEMPCTRL_STATE_t;

void Tempctrl_init( TEMPCTRL_ID_t id, GPIO_ID_t hGpioId, GPIO_PIN_t hPin, GPIO_ID_t cGpioId, GPIO_PIN_t cPin );
void Tempctrl_update( void *paramter );
void Tempctrl_setState( TEMPCTRL_ID_t id, TEMPCTRL_STATE_t state );

#endif	/* TEMPCTRL_H */
