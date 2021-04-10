#ifndef ADC_H
#define	ADC_H

#include "Config.h"

typedef enum
{
	ADC_ID_0 = 0,
}   ADC_ID_t;

typedef enum
{
	ADC_CHANNEL_1 = 0,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7,
	ADC_CHANNEL_8,
}   ADC_CHANNEL_t;

void Adc_init( ADC_ID_t id );
uint16_t Adc_getState( ADC_ID_t id, ADC_CHANNEL_t channel );

#endif	/* ADC_H */
