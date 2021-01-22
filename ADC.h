#ifndef ADC_H
#define	ADC_H

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

typedef struct
{
    uint8_t Channel;
    uint32_t VoltMulti;
    uint32_t VoltDivide;
    uint8_t Result;
}ADC_t;

void ADC_Init(void);
void ADC_Update(void);
uint8_t ADC_GetState(void);

#endif	/* ADC_H */
