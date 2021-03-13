#ifndef TEMP_SENSOR_H
#define	TEMP_SENSOR_H

#include "SchedulerConfig.h"
#include "Gpio.h"
#include "Adc.h"

typedef enum
{
	TEMP_SENSOR1_ID
}TEMP_SENSOR_t;

void TempSensor_init( Id_t id, Id_t xGpioId, uint8_t xPin, Id_t xAdcId );
uint8_t TempSensor_getState( Id_t id );

#endif	/* TEMP_SENSOR_H */
