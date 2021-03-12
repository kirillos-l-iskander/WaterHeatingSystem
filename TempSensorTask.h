#ifndef TEMP_SENSOR_TASK_H
#define	TEMP_SENSOR_TASK_H

#include "SchedulerConfig.h"
#include "TempSensor.h"

void TempSensorTask_Init( Id_t Id, Id_t GpioId, uint8_t Pin, Id_t AdcId );
uint8_t TempSensorTask_GetAverage( Id_t Id );
void TempSensorTask_Update( void *Paramter );

#endif	/* TEMP_SENSOR_TASK_H */
