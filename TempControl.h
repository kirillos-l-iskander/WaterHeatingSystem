#ifndef TEMP_CONTROL_H
#define	TEMP_CONTROL_H

#include "SchedulerConfig.h"
#include "Gpio.h"

typedef enum
{
	TEMP_CONTROL1_ID
}TEMP_CONTROL_t;

void TempControl_init( Id_t id, Id_t hGpioId, uint8_t hPin, Id_t cGpioId, uint8_t cPin );
void TempControl_setState( Id_t id, uint8_t state );

#endif	/* TEMP_CONTROL_H */
