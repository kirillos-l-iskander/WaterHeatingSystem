#ifndef TEMP_SENSOR_H
#define	TEMP_SENSOR_H

#include "SchedulerConfig.h"
#include "Gpio.h"
#include "Adc.h"

void TempSensor_Init( Id_t Id, Id_t GpioId, uint8_t Pin, Id_t AdcId );
uint8_t TempSensor_GetState( Id_t Id );
void TempSensor_SetGpio( Id_t Id, Id_t GpioId, uint8_t Pin );
void TempSensor_SetAdc( Id_t Id, Id_t AdcId );

#endif	/* TEMP_SENSOR_H */
