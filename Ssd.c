#include "Ssd.h"

typedef struct
{
    Id_t GpioIdCtrl;
    uint8_t PinCtrl;
    Id_t GpioIdD0;
    uint8_t PinD0;
}Ssd_t;

static Ssd_t Ssd[ SSD_NUMBER ];
static uint8_t SsdSymbolPattern[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void Ssd_Init( void )
{
    size_t Id = 0;
    size_t Pin = 0;
	for ( Id = 0; Id < SSD_NUMBER; Id++ )
    {
        Gpio_InitPin( Ssd[ Id ].GpioIdCtrl, Ssd[ Id ].PinCtrl, OUTPUT );
    	for ( Pin = Ssd[ Id ].PinD0; Pin < ( Ssd[ Id ].PinD0 + 8 ); Pin++ )
        {
            Gpio_InitPin( Ssd[ Id ].GpioIdD0, Pin, OUTPUT );
        }
    }
}

void Ssd_SetState( Id_t Id, uint8_t State )
{
    Gpio_SetPinState( Ssd[ Id ].GpioIdCtrl, Ssd[ Id ].PinCtrl, State );
}

void Ssd_SetSymbol( Id_t Id, uint8_t Symbol )
{
	Gpio_SetPortState( Ssd[ Id ].GpioIdD0, ( 0xFF << Ssd[ Id ].PinD0 ), SsdSymbolPattern[ Symbol ] );
}

void Ssd_SetGpioCtrl( Id_t Id, Id_t GpioId, uint8_t Pin )
{
    Ssd[ Id ].GpioIdCtrl = GpioId;
    Ssd[ Id ].PinCtrl = Pin;
}

void Ssd_SetGpioD0( Id_t Id, Id_t GpioId, uint8_t Pin )
{
    Ssd[ Id ].GpioIdD0 = GpioId;
    Ssd[ Id ].PinD0 = Pin;
}
