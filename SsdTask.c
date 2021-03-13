#include "SsdTask.h"

typedef struct
{
	uint8_t counter;
    uint8_t symbol;
    uint8_t state;
	uint8_t blink;
	uint16_t period;
	uint16_t delay;
}SsdTask_t;

static SsdTask_t ssdTask[ SSD_NUMBER ];

void SsdTask_init( Id_t id, Id_t cGpioId, uint8_t cPin, Id_t dGpioId, uint8_t dPin )
{
    ssdTask[ id ].counter = id;
    ssdTask[ id ].symbol = 0;
    ssdTask[ id ].state = LOW;
    ssdTask[ id ].blink = 0;
    ssdTask[ id ].period = 0;
    ssdTask[ id ].delay = 0;
    Ssd_init( id, cGpioId, cPin, dGpioId, dPin );
}

void SsdTask_setState( Id_t id, uint8_t state, uint16_t period )
{
    ssdTask[ id ].state = state;
	ssdTask[ id ].period = MS_TO_TICKS( period ) / MS_TO_TICKS( 5 );
}

void SsdTask_setSymbol( Id_t id, uint8_t symbol )
{
    ssdTask[ id ].symbol = symbol;
}

void SsdTask_update( void *paramter )
{
    Id_t id = (Id_t) paramter;
    if( ssdTask[ id ].delay )
    {
        ssdTask[ id ].delay--;
    }else if( ssdTask[ id ].period )
    {
        ssdTask[ id ].blink ^= ssdTask[ id ].state;
        ssdTask[ id ].delay = ssdTask[ id ].period;
    }else
    {
        ssdTask[ id ].blink = 0;
    }
    Ssd_setState( id, LOW );
    if( ssdTask[ id ].counter == 0 )
    {
        Ssd_setSymbol( id, ssdTask[ id ].symbol );
        Ssd_setState( id, ssdTask[ id ].state & !ssdTask[ id ].blink );
    }
    ssdTask[ id ].counter++;
    if( ssdTask[ id ].counter == SSD_NUMBER )
    {
        ssdTask[ id ].counter = 0;
    }
}
