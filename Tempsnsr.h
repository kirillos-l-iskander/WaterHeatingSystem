#ifndef TEMPSNSR_H
#define	TEMPSNSR_H

#include "Config.h"
#include "Gpio.h"
#include "Adc.h"

typedef enum
{
	TEMPSNSR_ID_1 = 0,
	TEMPSNSR_ID_MAX,
}   TEMPSNSR_ID_t;

typedef enum
{
	TEMPSNSR_STATE_MIN = 0,
	TEMPSNSR_STATE_MAX = 100,
}   TEMPSNSR_STATE_t;

void Tempsnsr_init( TEMPSNSR_ID_t id, GPIO_ID_t gpioId, GPIO_PIN_t gpioPin, ADC_ID_t adcId, ADC_CHANNEL_t adcChannel );
void Tempsnsr_update( void *paramter );
TEMPSNSR_STATE_t Tempsnsr_getState( TEMPSNSR_ID_t id );

#endif	/* TEMPSNSR_H */
