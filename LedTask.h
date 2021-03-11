#ifndef LED_TASK_H
#define	LED_TASK_H

#include "SchedulerConfig.h"
#include "Led.h"

#define BLINK_Period ( 0 )

void LedTask_Init( void );
void LedTask_SetState( Id_t Id, uint8_t State, uint16_t Period );
void LedTask_Update( void *Paramter );

#endif	/* LED_TASK_H */
