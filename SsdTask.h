#ifndef SSD_TASK_H
#define	SSD_TASK_H

#include "SchedulerConfig.h"
#include "Ssd.h"

void SsdTask_Init( void );
void SsdTask_SetState( Id_t Id, uint8_t State, uint16_t Period );
void SsdTask_SetSymbol( Id_t Id, uint8_t Symbol );
void SsdTask_Update( void *Paramter );

#endif	/* SSD_TASK_H */
