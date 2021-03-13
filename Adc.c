#include "Adc.h"

void Adc_init( Id_t id )
{
    ADCON0 = ADCON0 | 0x41;
    ADCON1 = ADCON1 | 0xC0;
}

uint16_t Adc_getState( Id_t id )
{
    ADCON0 = ADCON0 | ( 2 << 3 );
    ADCON0 = ADCON0 | 0x04;
    while( ADCON0 & 0x04 );
    return ( ( ADRESH << 8 ) + ADRESL );
}
