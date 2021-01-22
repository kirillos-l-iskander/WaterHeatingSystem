#include "ADC.h"

volatile static ADC_t ADC_G[1];

void ADC_Init(void)
{
    ADC_G[0].Channel = 2;
    ADC_G[0].VoltMulti = 488281;
    ADC_G[0].VoltDivide = 1000000;
    ADC_G[0].Result = 0;
    ADCON0 = ADCON0 | 0x41;
    ADCON1 = ADCON1 | 0xC0;
}

void ADC_Update(void)
{
    ADCON0 = ADCON0 | (ADC_G[0].Channel<<3);
    ADCON0 = ADCON0 | 0x04;
    while(ADCON0 & 0x04);
    ADC_G[0].Result = ((ADRESH<<8) + ADRESL) * ADC_G[0].VoltMulti / ADC_G[0].VoltDivide;
}

uint8_t ADC_GetState(void)
{
    return ADC_G[0].Result;
}
