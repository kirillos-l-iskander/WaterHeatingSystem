#ifndef SWITCHH_TASK_H
#define	SWITCHH_TASK_H

#include "SchedulerConfig.h"
#include "Switch.h"

void SwitchTask_Init( void );
uint8_t SwitchTask_GetState( Id_t Id );
void SwitchTask_Update( void *Paramter );

#endif	/* SWITCHH_TASK_H */
