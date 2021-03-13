#ifndef SSD_H
#define	SSD_H

#include "SchedulerConfig.h"
#include "Gpio.h"

typedef enum
{
	SSD1_ID,
	SSD2_ID
}SSD_t;

void Ssd_init( Id_t id, Id_t cGpioId, uint8_t cPin, Id_t dGpioId, uint8_t dPin );
void Ssd_setState( Id_t id, uint8_t state );
void Ssd_setSymbol( Id_t id, uint8_t symbol );

#endif	/* SSD_H */
