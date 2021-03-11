#ifndef TIMER_H
#define	TIMER_H

#include "SchedulerConfig.h"

#define TIM0_RELOAD() ( TMR0 = 6 )
#define TIM0_CLR_INT_FLAG() ( INTCON = INTCON & ~0x04 )
#define TIM0_CHECK_INT_FLAG() ( INTCON & 0x04 )
#define TIM1_MAX ( 65536 )
#define TIM1_CLR_INT_FLAG() ( PIR1 = PIR1 & ~0x04 )

void Timer0Init( void );
void Timer1Init( uint16_t TicksNumber );

#endif	/* TIMER_H */
