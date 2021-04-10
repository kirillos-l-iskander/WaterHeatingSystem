#include "Gpio.h"

#define GPIOA ( ( Gpio_t * ) &PORTA )
#define GPIOB ( ( Gpio_t * ) &PORTB )
#define GPIOC ( ( Gpio_t * ) &PORTC )
#define GPIOD ( ( Gpio_t * ) &PORTD )
#define GPIOE ( ( Gpio_t * ) &PORTE )

typedef struct
{
	uint8_t PORT;
	uint8_t PAD[127];
	uint8_t TRIS;
}Gpio_t;

static Gpio_t *gpio[ GPIO_ID_MAX ] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE };

void Gpio_initPin( GPIO_ID_t id, GPIO_PIN_t pin, GPIO_MODE_t mode, GPIO_TYPE_t type )
{
    if( id == GPIO_ID_E && pin > GPIO_PIN_3)
    {
        return;
    }
	gpio[ id ]->TRIS = ( gpio[ id ]->TRIS & ~( 1 << pin ) ) | ( mode << pin );
    OPTION_REG = ( OPTION_REG & ( 1 << 7 ) ) | ( type << 7 );
}

void Gpio_setPinState( GPIO_ID_t id, GPIO_PIN_t pin, GPIO_STATE_t state )
{
    state &= 0x1;
	gpio[ id ]->PORT = ( gpio[ id ]->PORT & ~( 1 << pin ) ) | ( state << pin );
}

GPIO_STATE_t Gpio_getPinState( GPIO_ID_t id, GPIO_PIN_t pin )
{
	return ( gpio[ id ]->PORT & ( 1 << pin ) ) >> pin;
}

void Gpio_setPortState( GPIO_ID_t id, GPIO_PIN_t pins, GPIO_STATE_t state )
{
    state &= pins;
	gpio[ id ]->PORT = ( gpio[ id ]->PORT & ~pins ) | ( state );
}

GPIO_STATE_t Gpio_getPortState( GPIO_ID_t id, GPIO_PIN_t pins )
{
	return ( gpio[ id ]->PORT & ~pins );
}
