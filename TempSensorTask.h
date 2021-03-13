#ifndef TEMP_SENSOR_TASK_H
#define	TEMP_SENSOR_TASK_H

#include "SchedulerConfig.h"
#include "TempSensor.h"

void TempSensorTask_init( Id_t id, Id_t xGpioId, uint8_t xPin, Id_t xAdcId );
uint8_t TempSensorTask_getAverage( Id_t id );
void TempSensorTask_update( void *paramter );

#endif	/* TEMP_SENSOR_TASK_H */
