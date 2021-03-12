#include "Led.h"

typedef struct
{
	Id_t GpioId;
	uint8_t Pin;
	uint8_t State;
}Led_t;

static Led_t Led[ LED_NUMBER ];

void Led_Init( Id_t Id, Id_t GpioId, uint8_t Pin )
{
	Led[ Id ].GpioId = GpioId;
	Led[ Id ].Pin = Pin;
    Led[ Id ].State = LOW;
    Gpio_InitPin( Led[ Id ].GpioId, Led[ Id ].Pin, OUTPUT );
}

void Led_SetState( uint8_t Id, uint8_t State )
{
    Led[ Id ].State = State;
	Gpio_SetPinState( Led[ Id ].GpioId, Led[ Id ].Pin, Led[ Id ].State );
}
