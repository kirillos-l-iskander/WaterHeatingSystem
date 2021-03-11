#include "SchedulerConfig.h"
#include "Scheduler.h"

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

//static void (*systickInterrupt)( void );

void SysTick_Handler( void ) __interrupt()
{
    TIM1_CLR_INT_FLAG();
    Scheduler_update();
    //(*systickInterrupt)();
}

int main( void )
{
    Switch_SetGpio( 0, GPIOB_ID, 0 );
    Switch_SetGpio( 1, GPIOB_ID, 1 );
    Switch_SetGpio( 2, GPIOB_ID, 2 );
    Switch_Init();
    SwitchTask_Init();
    
    TempSensor_SetGpio( 0, GPIOA_ID, 2 );
    TempSensor_Init();
    TempSensorTask_Init();

    TempControl_SetGpioH( 0, GPIOC_ID, 5 );
    TempControl_SetGpioC( 0, GPIOC_ID, 2 );
    TempControl_Init();
    TempControlTask_Init();
    
    Led_SetGpio( 0, GPIOB_ID, 6 );
    Led_SetGpio( 1, GPIOB_ID, 7 );
    Led_Init();
    LedTask_Init();
   
    Ssd_SetGpioCtrl( 0, GPIOA_ID, 5 );
    Ssd_SetGpioD0( 0, GPIOD_ID, 0 );
    Ssd_SetGpioCtrl( 1, GPIOA_ID, 4 );
    Ssd_SetGpioD0( 1, GPIOD_ID, 0 );
    Ssd_Init();
    SsdTask_Init();
    
    HeaterTask_Init();
    
    DELAY_US(1000);
    
    Scheduler_init();
    Scheduler_addTask( SwitchTask_Update, NULL, 0, C_MS_TO_TICKS( 10 ) );
    Scheduler_addTask( TempSensorTask_Update, NULL, 0, C_MS_TO_TICKS( 100 ) );
    Scheduler_addTask( TempControlTask_Update, NULL, 0, C_MS_TO_TICKS( 100 ) );
    Scheduler_addTask( LedTask_Update, NULL, 0, C_MS_TO_TICKS( 100 ) );
    Scheduler_addTask( SsdTask_Update, NULL, 0, C_MS_TO_TICKS( 5 ) );
    Scheduler_addTask( HeaterTask_Update, NULL, 0, C_MS_TO_TICKS( 100 ) );
    //systickInterrupt = Scheduler_update;
    Scheduler_start();
    while( 1 )
    {
        Scheduler_dispatchTasks();
    }
    return SCH_RETURN_NORMAL;
}
