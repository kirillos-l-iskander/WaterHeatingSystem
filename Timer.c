#include "Timer.h"

void Timer0_init( TIMER_MODE_t mode, TIMER_PERIOD_t period, TIMER_CHANNEL_t channel, TIMER_EVENT_t event );
void Timer1_init( TIMER_MODE_t mode, TIMER_PERIOD_t period, TIMER_CHANNEL_t channel, TIMER_EVENT_t event );
void Timer2_init( TIMER_MODE_t mode, TIMER_PERIOD_t period, TIMER_CHANNEL_t channel, TIMER_EVENT_t event );

void Timer_init( TIMER_ID_t id, TIMER_MODE_t mode, TIMER_PERIOD_t period, TIMER_CHANNEL_t channel, TIMER_EVENT_t event )
{
    switch( id )
    {
        case TIMER_ID_0:
            Timer0_init( mode, period, channel, event );
            break;
        case TIMER_ID_1:
            Timer1_init( mode, period, channel, event );
            break;
        case TIMER_ID_2:
            break;
        default:
            break;
    }
}

void Timer_enableInterrupt( TIMER_ID_t id )
{
    switch( id )
    {
        case TIMER_ID_0:
            INTCON |= 0x60;
            break;
        case TIMER_ID_1:
            INTCON |= 0x40;
            PIE1 |= 0x04;
            break;
        case TIMER_ID_2:
            INTCON |= 0x40;
            PIE1 |= 0x02;
            break;
        default:
            break;
    }
}
void Timer0_init( TIMER_MODE_t mode, TIMER_PERIOD_t period, TIMER_CHANNEL_t channel, TIMER_EVENT_t event )
{
    //OPTION_REG &= ~0x3F;

    TMR0 = 	( uint8_t )( ( ( ( ( SCH_CPU_F / SCH_CPU_INSTRUCTION ) / 256 ) / 1000 ) * period ) - 1 );

    OPTION_REG |= 0x07;
}

void Timer1_init( TIMER_MODE_t mode, TIMER_PERIOD_t period, TIMER_CHANNEL_t channel, TIMER_EVENT_t event )
{
    //T1CON &= ~0xFF;
    
    //TMR1 = 0;
    CCPR1 = ( uint16_t )( ( ( ( ( SCH_CPU_F / SCH_CPU_INSTRUCTION ) / 1 ) / 1000 ) * period ) - 1 );

    //CCP1CON &= 0x0F;
    CCP1CON |= event;

    T1CON |= 0x01;

    INTCON |= 0x40;
    PIE1 |= 0x04;
}
