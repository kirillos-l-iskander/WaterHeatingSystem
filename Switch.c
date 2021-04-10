#include "Switch.h"

typedef struct
{
    GPIO_ID_t gpioId;
    GPIO_PIN_t gpioPin;
    SW_STATE_t state;
    uint8_t lock;
    uint8_t counter;
}   Switch_t;

static Switch_t sw[ SWITCH_ID_MAX ];

void initSwitchHardware( SW_ID_t id );
SW_STATE_t getSwitchHardwareState( SW_ID_t id );

void Switch_init( SW_ID_t id, GPIO_ID_t gpioId, GPIO_PIN_t gpioPin )
{
    sw[ id ].gpioId = gpioId;
    sw[ id ].gpioPin = gpioPin;
    sw[ id ].state = SWITCH_STATE_RELEASED;
    sw[ id ].lock = 0;
    sw[ id ].counter = 0;
    initSwitchHardware( id );
}

void Switch_update( void *paramter )
{
    SW_ID_t id = (SW_ID_t) paramter;
    if( sw[ id ].lock )
    {
        sw[ id ].lock--;
    }else if( getSwitchHardwareState( id ) == SWITCH_STATE_PRESSED )
    {
        sw[ id ].counter++;
        if( sw[ id ].counter == MS_TO_TICKS( 20 ) / MS_TO_TICKS( 10 ) )
        {
            sw[ id ].state = SWITCH_STATE_PRESSED;
            sw[ id ].lock = MS_TO_TICKS( 500 ) / MS_TO_TICKS( 10 );
            sw[ id ].counter = 0;
        }
    }else
    {
        sw[ id ].counter = 0;
    }
}

SW_STATE_t Switch_getState( SW_ID_t id )
{
    uint8_t buffer = sw[ id ].state;
    sw[ id ].state = SWITCH_STATE_RELEASED;
    return buffer;
}

void initSwitchHardware( SW_ID_t id )
{
    Gpio_initPin( sw[ id ].gpioId, sw[ id ].gpioPin, GPIO_MODE_INPUT, GPIO_TYPE_FLOATING );
}

SW_STATE_t getSwitchHardwareState( SW_ID_t id )
{
    if( Gpio_getPinState( sw[ id ].gpioId, sw[ id ].gpioPin ) == GPIO_STATE_HIGH )
    {
        return SWITCH_STATE_RELEASED;
    }else if( Gpio_getPinState( sw[ id ].gpioId, sw[ id ].gpioPin ) == GPIO_STATE_LOW )
    {
        return SWITCH_STATE_PRESSED;
    }else
    {
        return SWITCH_STATE_ERROR;
    }
}
