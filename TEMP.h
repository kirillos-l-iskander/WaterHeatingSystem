#ifndef TEMP_H
#define	TEMP_H

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
    uint8_t Array[10];
    uint8_t Index;
    uint8_t AvgFlag;
}TEMP_t;

void TEMP_Init(void);
void TEMP_Update(void);
uint8_t TEMP_GetAverage(void);

#endif	/* TEMP_H */
