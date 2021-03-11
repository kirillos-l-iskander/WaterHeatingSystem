#ifndef WH_H
#define	WH_H

#include "SchedulerConfig.h"

#include "Gpio.h"
#include "Adc.h"
#include "Timer.h"
#include "Switch.h"
#include "SwitchTask.h"
#include "TempSensor.h"
#include "TempSensorTask.h"
#include "TempControl.h"
#include "TempControlTask.h"
#include "Led.h"
#include "LedTask.h"
#include "Ssd.h"
#include "SsdTask.h"

#include "I2c.h"
#include "Eeprom.h"
#include "WaterHeater.h"

#define LED_UPDATE 5
#define SW_UPDATE 10
#define ADC_UPDATE 100
#define TEMP_UPDATE 100
#define HCU_UPDATE 100
#define DISP_UPDATE 100
#define SSD_UPDATE 5
#define WH_UPDATE 100

void HeaterTask_Init( void );
void HeaterTask_Update( void *Paramter );

#endif	/* WH_H */
