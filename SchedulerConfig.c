#include "SchedulerConfig.h"
#include "Timer.h"
#include "LedTask.h"

void Scheduler_initSysTick( TickType_t msTickPeriod )
{
	TickType_t tickNumber = ( TickType_t )( ( ( ( ( SCH_CPU_F / SCH_CPU_INSTRUCTION ) / SCH_TIMER_PRESCALER ) / 1000 ) * msTickPeriod ) - 1 );
    Timer1_init( tickNumber );
    GIE();
}

void Scheduler_displayError( UBaseType_t errorCode )
{
	if( errorCode )
	{
		LedTask_setState( LED2_ID, LOW, 0 );
	}else
	{
		LedTask_setState( LED2_ID, HIGH, 0 );
	}
}

void Scheduler_sleepHardware( void )
{

}

void Scheduler_delayHardwareMs( volatile uint32_t msDelay )
{

}

void Scheduler_delayHardwareUs( volatile uint32_t usDelay )
{

}

void Scheduler_delaySoftwareMs( volatile uint32_t msDelay )
{
	while( msDelay-- )
	{
		Scheduler_delaySoftwareUs( 1000 );
	}
}

void Scheduler_delaySoftwareUs( volatile uint32_t usDelay )
{
	volatile uint8_t delay;
	while( usDelay-- )
	{
		delay = ( uint8_t ) ( ( SCH_CPU_F / SCH_CPU_INSTRUCTION ) / 1000000 );
		while( delay-- );
	}
}
