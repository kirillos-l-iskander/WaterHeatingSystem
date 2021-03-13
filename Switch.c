#include "Switch.h"

typedef struct
{
    Id_t xGpioId;
    uint8_t xPin;
}Switch_t;

static Switch_t sw[ SWITCH_NUMBER ];

void Switch_init( Id_t id, Id_t xGpioId, uint8_t xPin )
{
    sw[ id ].xGpioId = xGpioId;
    sw[ id ].xPin = xPin;
    Gpio_initPin( sw[ id ].xGpioId, sw[ id ].xPin, INPUT );
}

uint8_t Switch_getState( Id_t id )
{
    return Gpio_getPinState( sw[ id ].xGpioId, sw[ id ].xPin );
}
