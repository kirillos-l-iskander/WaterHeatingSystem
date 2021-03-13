#include "TempControl.h"

typedef struct
{
    Id_t hGpioId;
	uint8_t hPin;
    Id_t cGpioId;
	uint8_t cPin;
}TempControl_t;

static TempControl_t tempControl[ TEMP_CONTROL_NUMBER ];

void TempControl_init( Id_t id, Id_t hGpioId, uint8_t hPin, Id_t cGpioId, uint8_t cPin )
{
    tempControl[ id ].hGpioId = hGpioId;
    tempControl[ id ].hPin = hPin;
    tempControl[ id ].cGpioId = cGpioId;
    tempControl[ id ].cPin = cPin;
    Gpio_initPin( tempControl[ id ].hGpioId, tempControl[ id ].hPin, OUTPUT );
    Gpio_initPin( tempControl[ id ].cGpioId, tempControl[ id ].cPin, OUTPUT );
}

void TempControl_setState( Id_t id, uint8_t state )
{
	Gpio_setPinState( tempControl[ id ].hGpioId, tempControl[ id ].hPin, state & 0x01 );
	Gpio_setPinState( tempControl[ id ].cGpioId, tempControl[ id ].cPin, ( state & 0x02 ) >> 1 );
}
