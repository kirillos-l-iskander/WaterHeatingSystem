#ifndef SWITCH_H
#define	SWITCH_H

#include "SchedulerConfig.h"
#include "Gpio.h"

void Switch_Init( Id_t Id, Id_t GpioId, uint8_t Pin );
uint8_t Switch_GetState( Id_t Id );
void Switch_SetGpio( Id_t Id, Id_t GpioId, uint8_t Pin );

#endif	/* SWITCH_H */
