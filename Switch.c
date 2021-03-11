#include "Switch.h"

typedef struct
{
    Id_t GpioId;
    uint8_t Pin;
}Switch_t;

static Switch_t Switch[ SWITCH_NUMBER ];

void Switch_Init( void )
{
    size_t Id = 0;
    for( Id = 0; Id < SWITCH_NUMBER; Id++ )
    {
        Gpio_InitPin( Switch[ Id ].GpioId, Switch[ Id ].Pin, INPUT );
    }
}

uint8_t Switch_GetState( Id_t Id )
{
    return Gpio_GetPinState( Switch[ Id ].GpioId, Switch[ Id ].Pin );
}

void Switch_SetGpio( Id_t Id, Id_t GpioId, uint8_t Pin )
{
    Switch[ Id ].GpioId = GpioId;
    Switch[ Id ].Pin = Pin;
}
