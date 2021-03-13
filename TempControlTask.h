#ifndef TEMP_CONTROL_TASK_H
#define	TEMP_CONTROL_TASK_H

#include "SchedulerConfig.h"
#include "TempControl.h"

void TempControlTask_init( Id_t id, Id_t hGpioId, uint8_t hPin, Id_t cGpioId, uint8_t cPin );
void TempControlTask_setState( Id_t id, uint8_t state );
void TempControlTask_update( void *paramter );

#endif	/* TEMP_CONTROL_TASK_H */
