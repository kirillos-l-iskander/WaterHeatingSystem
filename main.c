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
    SwitchTask_Init( 0, GPIOB_ID, 0 );
    SwitchTask_Init( 1, GPIOB_ID, 1 );
    SwitchTask_Init( 2, GPIOB_ID, 2 );
    
    TempSensorTask_Init( 0, GPIOA_ID, 2, 0 );

    TempControlTask_Init( 0, GPIOC_ID, 5, GPIOC_ID, 2 );
    
    LedTask_Init( 0, GPIOB_ID, 6 );
    LedTask_Init( 1, GPIOB_ID, 7 );
   
    SsdTask_Init( 0, GPIOA_ID, 5, GPIOD_ID, 0 );
    SsdTask_Init( 1, GPIOA_ID, 4, GPIOD_ID, 0 );
    
    HeaterTask_Init( 0 );
    
    DELAY_US(1000);
    
    Scheduler_init();
    Scheduler_addTask( SwitchTask_Update, (void *) 0, 0, C_MS_TO_TICKS( 10 ) );
    Scheduler_addTask( SwitchTask_Update, (void *) 1, 0, C_MS_TO_TICKS( 10 ) );
    Scheduler_addTask( SwitchTask_Update, (void *) 2, 0, C_MS_TO_TICKS( 10 ) );
    Scheduler_addTask( TempSensorTask_Update, (void *) 0, 0, C_MS_TO_TICKS( 100 ) );
    Scheduler_addTask( HeaterTask_Update, (void *) 0, 0, C_MS_TO_TICKS( 100 ) );
    Scheduler_addTask( TempControlTask_Update, (void *) 0, 0, C_MS_TO_TICKS( 100 ) );
    Scheduler_addTask( LedTask_Update, (void *) 0, 0, C_MS_TO_TICKS( 100 ) );
    Scheduler_addTask( LedTask_Update, (void *) 1, 0, C_MS_TO_TICKS( 100 ) );
    Scheduler_addTask( SsdTask_Update, (void *) 0, 0, C_MS_TO_TICKS( 5 ) );
    Scheduler_addTask( SsdTask_Update, (void *) 1, 0, C_MS_TO_TICKS( 5 ) );
    //systickInterrupt = Scheduler_update;
    Scheduler_start();
    while( 1 )
    {
        Scheduler_dispatchTasks();
    }
    return SCH_RETURN_NORMAL;
}
