#ifndef TEMP_CONTROL_TASK_H
#define	TEMP_CONTROL_TASK_H

#include "SchedulerConfig.h"
#include "TempControl.h"

void TempControlTask_Init( Id_t Id, Id_t hGpioId, uint8_t hPin, Id_t cGpioId, uint8_t cPin );
void TempControlTask_SetState( Id_t Id, uint8_t State );
void TempControlTask_Update( void *Paramter );

#endif	/* TEMP_CONTROL_TASK_H */
