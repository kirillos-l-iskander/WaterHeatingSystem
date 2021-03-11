#include "Gpio.h"

#define GPIOA ( ( Gpio_t * ) &PORTA )
#define GPIOB ( ( Gpio_t * ) &PORTB )
#define GPIOC ( ( Gpio_t * ) &PORTC )
#define GPIOD ( ( Gpio_t * ) &PORTD )
#define GPIOE ( ( Gpio_t * ) &PORTE )

typedef struct
{
	UBaseType_t PORT;
	UBaseType_t PAD[127];
	UBaseType_t TRIS;
}Gpio_t;

static Gpio_t *Gpio[ 5 ] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE };

void Gpio_InitPin( Id_t Id, UBaseType_t Pin, UBaseType_t Mode )
{
	Gpio[ Id ]->TRIS = ( Gpio[ Id ]->TRIS & ~( 1 << Pin ) ) | ( Mode << Pin );
}

void Gpio_SetPinState( Id_t Id, UBaseType_t Pin, UBaseType_t State )
{
	Gpio[ Id ]->PORT = ( Gpio[ Id ]->PORT & ~( 1 << Pin ) ) | ( State << Pin);
}

UBaseType_t Gpio_GetPinState( Id_t Id, UBaseType_t Pin )
{
	return ( Gpio[ Id ]->PORT & ( 1 << Pin ) ) >> Pin;
}

void Gpio_SetPortState( Id_t Id, UBaseType_t Pins, UBaseType_t State )
{
	Gpio[ Id ]->PORT = ( Gpio[ Id ]->PORT & ~Pins ) | ( State & Pins );
}

UBaseType_t Gpio_GetPortState( Id_t Id, UBaseType_t Pins )
{
	return ( Gpio[ Id ]->PORT & ~Pins );
}
