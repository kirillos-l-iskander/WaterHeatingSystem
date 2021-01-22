#ifndef _SW_H
#define	_SW_H

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

#define SW_THRES 2

typedef struct
{
    uint8_t State;
    uint8_t Counter;
    uint8_t Lock;
}SW_t;

void SW_Init(void);
void SW_Update(void);
uint8_t SW_GetState(uint8_t SWx);

#endif	/* _SW_H */
