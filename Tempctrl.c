#include "Tempctrl.h"

typedef struct
{
    GPIO_ID_t gpioIdH;
	GPIO_PIN_t gpioPinH;
    GPIO_ID_t gpioIdC;
	GPIO_PIN_t gpioPinC;
    TEMPCTRL_STATE_t state;
}   TempControl_t;

static TempControl_t tempctrl[ TEMPCTRL_ID_MAX ];

void initTempctrlHardware( TEMPCTRL_ID_t id );
void setTempctrlHardwareState( TEMPCTRL_ID_t id, TEMPCTRL_STATE_t state );

void Tempctrl_init( TEMPCTRL_ID_t id, GPIO_ID_t gpioIdH, GPIO_PIN_t gpioPinH, GPIO_ID_t gpioIdC, GPIO_PIN_t gpioPinC )
{
    tempctrl[ id ].gpioIdH = gpioIdH;
    tempctrl[ id ].gpioPinH = gpioPinH;
    tempctrl[ id ].gpioIdC = gpioIdC;
    tempctrl[ id ].gpioPinC = gpioPinC;
    tempctrl[ id ].state = TEMPCTRL_STATE_OFF;
    initTempctrlHardware( id );
}

void Tempctrl_update( void *paramter )
{
    TEMPCTRL_ID_t id = (TEMPCTRL_ID_t) paramter;
    setTempctrlHardwareState( id, tempctrl[ id ].state );
}

void Tempctrl_setState( TEMPCTRL_ID_t id, TEMPCTRL_STATE_t state )
{
    tempctrl[ id ].state = state;
}

void initTempctrlHardware( TEMPCTRL_ID_t id )
{
    Gpio_initPin( tempctrl[ id ].gpioIdH, tempctrl[ id ].gpioPinH, GPIO_MODE_OUTPUT_DHZ, GPIO_TYPE_GP_PP );
    Gpio_initPin( tempctrl[ id ].gpioIdC, tempctrl[ id ].gpioPinC, GPIO_MODE_OUTPUT_DHZ, GPIO_TYPE_GP_PP );
}

void setTempctrlHardwareState( TEMPCTRL_ID_t id, TEMPCTRL_STATE_t state )
{
    if( state == TEMPCTRL_STATE_OFF )
    {
        Gpio_setPinState( tempctrl[ id ].gpioIdH, tempctrl[ id ].gpioPinH, GPIO_STATE_LOW );
        Gpio_setPinState( tempctrl[ id ].gpioIdC, tempctrl[ id ].gpioPinC, GPIO_STATE_LOW );
    }else if( state == TEMPCTRL_STATE_HEAT )
    {
        Gpio_setPinState( tempctrl[ id ].gpioIdH, tempctrl[ id ].gpioPinH, GPIO_STATE_HIGH );
        Gpio_setPinState( tempctrl[ id ].gpioIdC, tempctrl[ id ].gpioPinC, GPIO_STATE_LOW );
    }else if( state == TEMPCTRL_STATE_COOL )
    {
        Gpio_setPinState( tempctrl[ id ].gpioIdH, tempctrl[ id ].gpioPinH, GPIO_STATE_LOW );
        Gpio_setPinState( tempctrl[ id ].gpioIdC, tempctrl[ id ].gpioPinC, GPIO_STATE_HIGH );
    }else
    {
    }
}
