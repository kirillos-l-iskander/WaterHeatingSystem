#ifndef SSD_TASK_H
#define	SSD_TASK_H

#include "SchedulerConfig.h"
#include "Ssd.h"

void SsdTask_init( Id_t id, Id_t cGpioId, uint8_t cPin, Id_t dGpioId, uint8_t dPin );
void SsdTask_setState( Id_t id, uint8_t state, uint16_t period );
void SsdTask_setSymbol( Id_t id, uint8_t symbol );
void SsdTask_update( void *paramter );

#endif	/* SSD_TASK_H */
