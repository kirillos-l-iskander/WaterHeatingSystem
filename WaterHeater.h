#ifndef WH_H
#define	WH_H

#include "Config.h"

#include "Gpio.h"
#include "Adc.h"
#include "Timer.h"
#include "Switch.h"
#include "Tempsnsr.h"
#include "Tempctrl.h"
#include "Led.h"
#include "Ssd.h"

#include "I2c.h"
#include "Eeprom.h"
#include "WaterHeater.h"

typedef enum
{
	HEATER_ID_1 = 0,
	HEATER_ID_MAX,
}   HEATER_ID_t;

void Heater_init( HEATER_ID_t id, SW_ID_t sSwId, SW_ID_t mSwId, SW_ID_t pSwId, TEMPSNSR_ID_t xTempsnsrId,
                  TEMPCTRL_ID_t xTempctrlId, LED_ID_t xLedId, SSD_ID_t aSsdId, SSD_ID_t bSsdId );
void Heater_update( void *paramter );

#endif	/* WH_H */
