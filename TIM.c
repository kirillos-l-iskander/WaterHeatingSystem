#include "TIM.h"

void TIM0_Init(void)
{
	//TIM0 Normal mode
	//OC0 Normal Port Operation
	//Prescaler CPU_F/16
    OPTION_REG = 0x03;
	//Counter Value
    TMR0 = 6;
	//TIM0 Overflow Interrupt
    //TIM0 Preferal Interrupt
    INTCON = 0x60;
}

void TIM1_Init(uint16_t Ticks_N)
{
	//Counter Value
    TMR1H = 0;
    TMR1L = 0;
    //Prescale CPU_F/1
    //TIM1 ON
    T1CON = 0x01;
    
	//Compare Match Value
    CCPR1H = Ticks_N>>8;
    CCPR1L = Ticks_N;
    //TIM1 Compare Match Mode, Reset TIM1
    CCP1CON = 0x0B;

    //TIM1 Compare Match Interrupt
    PIE1 = 0x04;
    //TIM1 Perferal Interrupt
    INTCON = 0x40;
}
