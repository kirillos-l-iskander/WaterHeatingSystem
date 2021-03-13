#ifndef SWITCH_H
#define	SWITCH_H

#include "SchedulerConfig.h"
#include "Gpio.h"

typedef enum
{
	SWITCH1_ID,
	SWITCH2_ID,
	SWITCH3_ID
}SWITCH_t;

void Switch_init( Id_t id, Id_t xGpioId, uint8_t xPin );
uint8_t Switch_getState( Id_t id );

#endif	/* SWITCH_H */
