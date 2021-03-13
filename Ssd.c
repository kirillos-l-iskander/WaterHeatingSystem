#include "Ssd.h"

typedef struct
{
    Id_t cGpioId;
    uint8_t cPin;
    Id_t dGpioId;
    uint8_t dPin;
}Ssd_t;

static Ssd_t ssd[ SSD_NUMBER ];
static uint8_t ssdSymbolPattern[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void Ssd_init( Id_t id, Id_t cGpioId, uint8_t cPin, Id_t dGpioId, uint8_t dPin )
{
    size_t pin = 0;
    ssd[ id ].cGpioId = cGpioId;
    ssd[ id ].cPin = cPin;
    ssd[ id ].dGpioId = dGpioId;
    ssd[ id ].dPin = dPin;
    Gpio_initPin( ssd[ id ].cGpioId, ssd[ id ].cPin, OUTPUT );
    for ( pin = ssd[ id ].dPin; pin < ( ssd[ id ].dPin + 8 ); pin++ )
    {
        Gpio_initPin( ssd[ id ].dGpioId, pin, OUTPUT );
    }
}

void Ssd_setState( Id_t id, uint8_t state )
{
    Gpio_setPinState( ssd[ id ].cGpioId, ssd[ id ].cPin, state );
}

void Ssd_setSymbol( Id_t id, uint8_t symbol )
{
	Gpio_setPortState( ssd[ id ].dGpioId, ( 0xFF << ssd[ id ].dPin ), ssdSymbolPattern[ symbol ] );
}
