#ifndef TEMP_CONTROL_H
#define	TEMP_CONTROL_H

#include "SchedulerConfig.h"
#include "Gpio.h"

void TempControl_Init( Id_t Id, Id_t hGpioId, uint8_t hPin, Id_t cGpioId, uint8_t cPin );
void TempControl_SetState( Id_t Id, uint8_t State );
void TempControl_SetGpioH( Id_t Id, Id_t GpioId, uint8_t Pin );
void TempControl_SetGpioC( Id_t Id, Id_t GpioId, uint8_t Pin );

#endif	/* TEMP_CONTROL_H */
