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

int main(void)
{
    SCH_Init();
    LED_Init();
    SW_Init();
    ADC_Init();
    TEMP_Init();
    HCU_Init();
    DISP_Init();
    SSD_Init();
    WH_Init();
    SCH_Add_Task(LED_Update, 0/SCH_TICK_PERIOD_MS, LED_UPDATE/SCH_TICK_PERIOD_MS);
    SCH_Add_Task(SW_Update, 0/SCH_TICK_PERIOD_MS, SW_UPDATE/SCH_TICK_PERIOD_MS);
    SCH_Add_Task(ADC_Update, 0/SCH_TICK_PERIOD_MS, ADC_UPDATE/SCH_TICK_PERIOD_MS);
    SCH_Add_Task(TEMP_Update, 0/SCH_TICK_PERIOD_MS, TEMP_UPDATE/SCH_TICK_PERIOD_MS);
    SCH_Add_Task(HCU_Update, 0/SCH_TICK_PERIOD_MS, HCU_UPDATE/SCH_TICK_PERIOD_MS);
    SCH_Add_Task(DISP_Update, 0/SCH_TICK_PERIOD_MS, DISP_UPDATE/SCH_TICK_PERIOD_MS);
    SCH_Add_Task(SSD_Update, 0/SCH_TICK_PERIOD_MS, SSD_UPDATE/SCH_TICK_PERIOD_MS);
    SCH_Add_Task(WH_Task, 0/SCH_TICK_PERIOD_MS, WH_UPDATE/SCH_TICK_PERIOD_MS);
    SCH_Start();
    while(1)
    {
        SCH_Dispatch_Tasks();
    }
    return RETURN_NORMAL;
}
