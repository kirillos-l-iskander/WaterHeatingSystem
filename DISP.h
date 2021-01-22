#ifndef DISP_H
#define	DISP_H

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

#define DISP0_STATE 0
#define DISP0_BLINK 1
#define DISP1_STATE 2
#define DISP1_BLINK 3
#define DISP_ON 1
#define DISP_OFF 0

typedef struct
{
    uint8_t State;
    uint8_t Blink;
    uint16_t Counter;
}DISP_t;

void DISP_Init(void);
void DISP_Update(void);
void DISP_SetState(uint8_t DISPx, uint8_t State);
uint8_t DISP_GetState(uint8_t DISPx);

#endif	/* DISP_H */
