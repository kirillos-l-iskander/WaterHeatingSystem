#ifndef WH_H
#define	WH_H

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

#define LED_UPDATE 5
#define SW_UPDATE 10
#define ADC_UPDATE 100
#define TEMP_UPDATE 100
#define HCU_UPDATE 100
#define DISP_UPDATE 100
#define SSD_UPDATE 5
#define WH_UPDATE 100

typedef enum
{
    OffMode,
    OperationMode,
    NormalMode,
    TempSetMode,
    ResetMode
}WH_t;

void WH_Init(void);
void WH_Task(void);
void WH_OffMode(void);
void WH_OperationMode(void);
void WH_NormalMode(void);
void WH_TempSetMode(void);
void WH_PostTempSetMode(void);
void WH_ResetMode(void);

#endif	/* WH_H */
