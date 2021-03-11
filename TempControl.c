#include "TempControl.h"

typedef struct
{
    Id_t GpioIdH;
	uint8_t PinH;
    Id_t GpioIdC;
	uint8_t PinC;
}TempControl_t;

static TempControl_t TempControl[ TEMP_CONTROL_NUMBER ];

void TempControl_Init( void )
{
    size_t Id = 0;
    for( Id = 0; Id < TEMP_CONTROL_NUMBER; Id++ )
    {
        Gpio_InitPin( TempControl[ Id ].GpioIdH, TempControl[ Id ].PinH, OUTPUT );
        Gpio_InitPin( TempControl[ Id ].GpioIdC, TempControl[ Id ].PinC, OUTPUT );
    }
}

void TempControl_SetState( Id_t Id, uint8_t State )
{
	Gpio_SetPinState( TempControl[ Id ].GpioIdH, TempControl[ Id ].PinH, State & 0x01 );
	Gpio_SetPinState( TempControl[ Id ].GpioIdC, TempControl[ Id ].PinC, ( State & 0x02 ) >> 1 );
}

void TempControl_SetGpioH( Id_t Id, Id_t GpioId, uint8_t Pin )
{
    TempControl[ Id ].GpioIdH = GpioId;
    TempControl[ Id ].PinH = Pin;
}

void TempControl_SetGpioC( Id_t Id, Id_t GpioId, uint8_t Pin )
{
    TempControl[ Id ].GpioIdC = GpioId;
    TempControl[ Id ].PinC = Pin;
}
