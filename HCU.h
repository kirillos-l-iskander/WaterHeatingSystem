#ifndef HCU_H
#define	HCU_H

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

#define HCU_ON (1)
#define HCU_OFF (0)

typedef struct
{
    uint8_t State;
}HCU_t;

void HCU_Init(void);
void HCU_Update(void);
void HCU_SetState(uint8_t HCUx, uint8_t State);

#endif	/* HCU_H */
