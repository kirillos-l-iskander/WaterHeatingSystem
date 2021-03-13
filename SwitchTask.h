#ifndef SWITCHH_TASK_H
#define	SWITCHH_TASK_H

#include "SchedulerConfig.h"
#include "Switch.h"

void SwitchTask_init( Id_t id, Id_t xGpioId, uint8_t xPin );
uint8_t SwitchTask_getState( Id_t id );
void SwitchTask_update( void *paramter );

#endif	/* SWITCHH_TASK_H */
