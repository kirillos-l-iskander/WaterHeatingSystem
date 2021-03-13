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
    SwitchTask_init( SWITCH1_ID, GPIOB_ID, 0 );
    SwitchTask_init( SWITCH2_ID, GPIOB_ID, 1 );
    SwitchTask_init( SWITCH3_ID, GPIOB_ID, 2 );
    TempSensorTask_init( TEMP_SENSOR1_ID, GPIOA_ID, 2, 0 );
    TempControlTask_init( TEMP_CONTROL1_ID, GPIOC_ID, 5, GPIOC_ID, 2 );
    LedTask_init( LED1_ID, GPIOB_ID, 6 );
    LedTask_init( LED2_ID, GPIOB_ID, 7 );
    SsdTask_init( SSD1_ID, GPIOA_ID, 5, GPIOD_ID, 0 );
    SsdTask_init( SSD2_ID, GPIOA_ID, 4, GPIOD_ID, 0 );
    HeaterTask_init( HEATER1_ID );
    
    DELAY_US(1000);
    
    Scheduler_init();
    Scheduler_addTask( SwitchTask_update, (void *) SWITCH1_ID, 0, MS_TO_TICKS( 10 ) );
    Scheduler_addTask( SwitchTask_update, (void *) SWITCH1_ID, 0, MS_TO_TICKS( 10 ) );
    Scheduler_addTask( SwitchTask_update, (void *) SWITCH1_ID, 0, MS_TO_TICKS( 10 ) );
    Scheduler_addTask( TempSensorTask_update, (void *) TEMP_SENSOR1_ID, 0, MS_TO_TICKS( 100 ) );
    Scheduler_addTask( HeaterTask_update, (void *) HEATER1_ID, 0, MS_TO_TICKS( 100 ) );
    Scheduler_addTask( TempControlTask_update, (void *) TEMP_CONTROL1_ID, 0, MS_TO_TICKS( 100 ) );
    Scheduler_addTask( LedTask_update, (void *) LED1_ID, 0, MS_TO_TICKS( 100 ) );
    Scheduler_addTask( LedTask_update, (void *) LED2_ID, 0, MS_TO_TICKS( 100 ) );
    Scheduler_addTask( SsdTask_update, (void *) SSD1_ID, 0, MS_TO_TICKS( 5 ) );
    Scheduler_addTask( SsdTask_update, (void *) SSD2_ID, 0, MS_TO_TICKS( 5 ) );
    //systickInterrupt = Scheduler_update;
    Scheduler_start();
    while( 1 )
    {
        Scheduler_dispatchTasks();
    }
    return SCH_RETURN_NORMAL;
}
