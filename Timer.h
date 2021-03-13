#ifndef TIMER_H
#define	TIMER_H

#include "SchedulerConfig.h"

#define TIM0_RELOAD() ( TMR0 = 6 )
#define TIM0_CLR_INT_FLAG() ( INTCON = INTCON & ~0x04 )
#define TIM0_CHECK_INT_FLAG() ( INTCON & 0x04 )
#define TIM1_MAX ( 65536 )
#define TIM1_CLR_INT_FLAG() ( PIR1 = PIR1 & ~0x04 )

typedef enum
{
	TIMER0_ID,
	TIMER1_ID,
	TIMER2_ID
}TIMER_t;

void Timer0_init( void );
void Timer1_init( uint16_t tickNumber );

#endif	/* TIMER_H */
