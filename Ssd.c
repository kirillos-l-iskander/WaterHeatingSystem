#include "Ssd.h"

typedef struct
{
    GPIO_ID_t gpioIdC;
    GPIO_PIN_t gpioPinC;
    GPIO_ID_t gpioIdD;
    GPIO_PIN_t gpioPinD;
    SSD_ID_t counter;
    uint8_t symbol;
    SSD_STATE_t state;
	SSD_STATE_t blink;
	SSD_BLINK_t period;
	SSD_BLINK_t delay;
}   Ssd_t;

static Ssd_t ssd[ SSD_ID_MAX ];
static uint8_t ssdSymbolPattern[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void initSsdHardware( SSD_ID_t id );
void setSsdHardwareState( SSD_ID_t id, SSD_STATE_t state );
void setSsdHardwareSymbol( SSD_ID_t id, SSD_SYMBOL_t symbol );

void Ssd_init( SSD_ID_t id, GPIO_ID_t gpioIdC, GPIO_PIN_t gpioPinC, GPIO_ID_t gpioIdD, GPIO_PIN_t gpioPinD )
{
    ssd[ id ].gpioIdC = gpioIdC;
    ssd[ id ].gpioPinC = gpioPinC;
    ssd[ id ].gpioIdD = gpioIdD;
    ssd[ id ].gpioPinD = gpioPinD;
    ssd[ id ].counter = id;
    ssd[ id ].symbol = 0;
    ssd[ id ].state = SSD_STATE_OFF;
    ssd[ id ].blink = 0;
    ssd[ id ].period = 0;
    ssd[ id ].delay = 0;
    initSsdHardware( id );
}

void Ssd_update( void *paramter )
{
    SSD_ID_t id = (SSD_ID_t) paramter;
    if( ssd[ id ].delay )
    {
        ssd[ id ].delay--;
    }else if( ssd[ id ].period )
    {
        ssd[ id ].blink ^= ssd[ id ].state;
        ssd[ id ].delay = ssd[ id ].period;
    }else
    {
        ssd[ id ].blink = 0;
    }
    setSsdHardwareState( id, SSD_STATE_OFF );
    if( ssd[ id ].counter == 0 )
    {
        setSsdHardwareSymbol( id, ssd[ id ].symbol );
        setSsdHardwareState( id, ssd[ id ].state & !ssd[ id ].blink );
    }
    ssd[ id ].counter++;
    if( ssd[ id ].counter == SSD_ID_MAX )
    {
        ssd[ id ].counter = 0;
    }
}

void Ssd_setState( SSD_ID_t id, SSD_STATE_t state, SSD_BLINK_t period )
{
    ssd[ id ].state = state;
	ssd[ id ].period = MS_TO_TICKS( period ) / MS_TO_TICKS( 5 );
}

void Ssd_setSymbol( SSD_ID_t id, SSD_SYMBOL_t symbol )
{
    ssd[ id ].symbol = symbol;
}

void initSsdHardware( SSD_ID_t id )
{
    Gpio_initPin( ssd[ id ].gpioIdC, ssd[ id ].gpioPinC, GPIO_MODE_OUTPUT_DHZ, GPIO_TYPE_GP_PP );
    for( size_t i = 0; i < 8; i++ )
    {
        Gpio_initPin( ssd[ id ].gpioIdD, ssd[ id ].gpioPinD + i, GPIO_MODE_OUTPUT_DHZ, GPIO_TYPE_GP_PP );
    }
}

void setSsdHardwareState( SSD_ID_t id, SSD_STATE_t state )
{
    if( state == SSD_STATE_ON )
    {
        Gpio_setPinState( ssd[ id ].gpioIdC, ssd[ id ].gpioPinC, GPIO_STATE_HIGH );
    }else if( state == SSD_STATE_OFF )
    {
        Gpio_setPinState( ssd[ id ].gpioIdC, ssd[ id ].gpioPinC, GPIO_STATE_LOW );
    }else
    {
        
    }
}

void setSsdHardwareSymbol( SSD_ID_t id, SSD_SYMBOL_t symbol )
{
	Gpio_setPortState( ssd[ id ].gpioIdD, ( 0xFF << ssd[ id ].gpioPinD ), ssdSymbolPattern[ symbol ] );
}
