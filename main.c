#include "SchedulerConfig.h"
#include "Scheduler.h"
#include "Config.h"

#include "Gpio.h"
#include "Adc.h"
#include "Timer.h"
#include "Switch.h"
#include "Tempsnsr.h"
#include "Tempctrl.h"
#include "Led.h"
#include "Ssd.h"

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
    Switch_init( SWITCH_ID_1, GPIO_ID_B, GPIO_PIN_0 );
    Switch_init( SWITCH_ID_2, GPIO_ID_B, GPIO_PIN_1 );
    Switch_init( SWITCH_ID_3, GPIO_ID_B, GPIO_PIN_2 );
    Tempsnsr_init( TEMPSNSR_ID_1, GPIO_ID_A, GPIO_PIN_2, ADC_ID_0, ADC_CHANNEL_1 );
    Tempctrl_init( TEMPCTRL_ID_1, GPIO_ID_C, GPIO_PIN_5, GPIO_ID_C, GPIO_PIN_2 );
    Led_init( LED_ID_1, GPIO_ID_B, GPIO_PIN_7 );
    Led_init( LED_ID_2, GPIO_ID_B, GPIO_PIN_6 );
    Ssd_init( SSD_ID_1, GPIO_ID_A, GPIO_PIN_5, GPIO_ID_D, GPIO_PIN_0 );
    Ssd_init( SSD_ID_2, GPIO_ID_A, GPIO_PIN_4, GPIO_ID_D, GPIO_PIN_0 );
    Heater_init( HEATER_ID_1, SWITCH_ID_1, SWITCH_ID_2, SWITCH_ID_3, TEMPSNSR_ID_1,
                 TEMPCTRL_ID_1, LED_ID_2, SSD_ID_1, SSD_ID_2 );
    
    DELAY_US( 1000 );
    
    Scheduler_init();
    Scheduler_addTask( Switch_update, (void *) SWITCH_ID_1, 0, MS_TO_TICKS( 10 ) );
    Scheduler_addTask( Switch_update, (void *) SWITCH_ID_2, 0, MS_TO_TICKS( 10 ) );
    Scheduler_addTask( Switch_update, (void *) SWITCH_ID_3, 0, MS_TO_TICKS( 10 ) );
    Scheduler_addTask( Tempsnsr_update, (void *) TEMPSNSR_ID_1, 0, MS_TO_TICKS( 100 ) );
    Scheduler_addTask( Heater_update, (void *) HEATER_ID_1, 1, MS_TO_TICKS( 100 ) );
    Scheduler_addTask( Tempctrl_update, (void *) TEMPCTRL_ID_1, 1, MS_TO_TICKS( 100 ) );
    Scheduler_addTask( Led_update, (void *) LED_ID_1, 1, MS_TO_TICKS( 100 ) );
    Scheduler_addTask( Led_update, (void *) LED_ID_2, 1, MS_TO_TICKS( 100 ) );
    Scheduler_addTask( Ssd_update, (void *) SSD_ID_1, 1, MS_TO_TICKS( 5 ) );
    Scheduler_addTask( Ssd_update, (void *) SSD_ID_2, 1, MS_TO_TICKS( 5 ) );
    //systickInterrupt = Scheduler_update;
    Scheduler_start();
    while( 1 )
    {
        Scheduler_dispatchTasks();
    }
    return SCH_RETURN_NORMAL;
}
