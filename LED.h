#ifndef LED_H
#define	LED_H

#include "CONFIG.h"
#include "PORT.h"
#include "SCH_CONFIG.h"
#include "SCH.h"
#include "TIM.h"
#include "GPIO.h"
#include "LED.h"

#include "SW.h"
#include "ADC.h"
#include "TEMP.h"
#include "HCU.h"
#include "SSD.h"
#include "DISP.h"
#include "I2C.h"
#include "EEPROM.h"
#include "WH.h"

#define LED_ON (1)
#define LED_OFF (0)

typedef struct
{
    uint8_t State;
}LED_t;

void LED_Init(void);
void LED_Update(void);
void LED_SetState(uint8_t LEDx, uint8_t State);

#endif	/* LED_H */
