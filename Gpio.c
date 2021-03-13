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

static Gpio_t *gpio[ 5 ] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE };

void Gpio_initPin( Id_t Id, UBaseType_t Pin, UBaseType_t Mode )
{
	gpio[ Id ]->TRIS = ( gpio[ Id ]->TRIS & ~( 1 << Pin ) ) | ( Mode << Pin );
}

void Gpio_setPinState( Id_t Id, UBaseType_t Pin, UBaseType_t State )
{
	gpio[ Id ]->PORT = ( gpio[ Id ]->PORT & ~( 1 << Pin ) ) | ( State << Pin);
}

UBaseType_t Gpio_getPinState( Id_t Id, UBaseType_t Pin )
{
	return ( gpio[ Id ]->PORT & ( 1 << Pin ) ) >> Pin;
}

void Gpio_setPortState( Id_t Id, UBaseType_t Pins, UBaseType_t State )
{
	gpio[ Id ]->PORT = ( gpio[ Id ]->PORT & ~Pins ) | ( State & Pins );
}

UBaseType_t Gpio_getPortState( Id_t Id, UBaseType_t Pins )
{
	return ( gpio[ Id ]->PORT & ~Pins );
}
