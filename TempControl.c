#include "TempControl.h"

typedef struct
{
    Id_t GpioIdH;
	uint8_t PinH;
    Id_t GpioIdC;
	uint8_t PinC;
}TempControl_t;

static TempControl_t TempControl[ TEMP_CONTROL_NUMBER ];

void TempControl_Init( Id_t Id, Id_t hGpioId, uint8_t hPin, Id_t cGpioId, uint8_t cPin )
{
    TempControl[ Id ].GpioIdH = hGpioId;
    TempControl[ Id ].PinH = hPin;
    TempControl[ Id ].GpioIdC = cGpioId;
    TempControl[ Id ].PinC = cPin;
    Gpio_InitPin( TempControl[ Id ].GpioIdH, TempControl[ Id ].PinH, OUTPUT );
    Gpio_InitPin( TempControl[ Id ].GpioIdC, TempControl[ Id ].PinC, OUTPUT );
}

void TempControl_SetState( Id_t Id, uint8_t State )
{
	Gpio_SetPinState( TempControl[ Id ].GpioIdH, TempControl[ Id ].PinH, State & 0x01 );
	Gpio_SetPinState( TempControl[ Id ].GpioIdC, TempControl[ Id ].PinC, ( State & 0x02 ) >> 1 );
}
