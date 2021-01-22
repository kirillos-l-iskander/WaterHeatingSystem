#ifndef TIM_H
#define	TIM_H

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

#define TIM0_RELOAD() (TMR0 = 6)
#define TIM0_CLR_INT_FLAG() (INTCON = INTCON & (~0x04))
#define TIM0_CHECK_INT_FLAG() (INTCON & 0x04)
#define TIM1_MAX (65536)
#define TIM1_CLR_INT_FLAG() (PIR1 = PIR1 & (~0x04))

void TIM0_Init(void);
void TIM1_Init(uint16_t Ticks_N);

#endif	/* TIM_H */
