#ifndef SSD_H
#define	SSD_H

#include "SchedulerConfig.h"
#include "Gpio.h"

void Ssd_Init( void );
void Ssd_SetState( Id_t Id, uint8_t State );
void Ssd_SetSymbol( Id_t Id, uint8_t Symbol );
void Ssd_SetGpioCtrl( Id_t Id, Id_t GpioId, uint8_t Pin );
void Ssd_SetGpioD0( Id_t Id, Id_t GpioId, uint8_t Pin );
void Ssd_SetGpioD1( Id_t Id, Id_t GpioId, uint8_t Pin );
void Ssd_SetGpioD2( Id_t Id, Id_t GpioId, uint8_t Pin );
void Ssd_SetGpioD3( Id_t Id, Id_t GpioId, uint8_t Pin );
void Ssd_SetGpioD4( Id_t Id, Id_t GpioId, uint8_t Pin );
void Ssd_SetGpioD5( Id_t Id, Id_t GpioId, uint8_t Pin );
void Ssd_SetGpioD6( Id_t Id, Id_t GpioId, uint8_t Pin );
void Ssd_SetGpioD7( Id_t Id, Id_t GpioId, uint8_t Pin );

#endif	/* SSD_H */
