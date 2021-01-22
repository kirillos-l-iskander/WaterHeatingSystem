#ifndef SSD_H
#define	SSD_H

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

#define SSD_Num 2

#define SSD_ON (1)
#define SSD_OFF (0)

typedef struct
{
    uint8_t State;
    uint8_t Symbol;
}SSD_t;

void SSD_Init(void);
void SSD_Update(void);
void SSD_SetState(uint8_t SSDx, uint8_t State);
uint8_t SSD_GetState(uint8_t SSDx);
void SSD_SetSymbol(uint8_t SSDx, uint8_t Symbol);
uint8_t SSD_GetSymbol(uint8_t SSDx);

#endif	/* SSD_H */
