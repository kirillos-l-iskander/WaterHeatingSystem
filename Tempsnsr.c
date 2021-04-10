#include "Tempsnsr.h"

typedef struct
{
    GPIO_ID_t gpioId;
	GPIO_PIN_t gpioPin;
    ADC_ID_t adcId;
    ADC_CHANNEL_t adcChannel;
    uint32_t voltMulti;
    uint32_t voltDivide;
    uint8_t array[ 10 ];
    uint8_t index;
    uint8_t avgFlag;
    TEMPSNSR_STATE_t avgTemp;
}   TempSensor_t;

static TempSensor_t tempsnsr[ TEMPSNSR_ID_MAX ];

void initTempsnsrHardware( TEMPSNSR_ID_t id );
TEMPSNSR_STATE_t getTempsnsrHarwareState( TEMPSNSR_ID_t id );
TEMPSNSR_STATE_t getAvgTemp( TEMPSNSR_ID_t id );

void Tempsnsr_init( TEMPSNSR_ID_t id, GPIO_ID_t gpioId, GPIO_PIN_t gpioPin, ADC_ID_t adcId, ADC_CHANNEL_t adcChannel )
{
    size_t index = 0;
    tempsnsr[ id ].gpioId = gpioId;
    tempsnsr[ id ].gpioPin = gpioPin;
    tempsnsr[ id ].adcId = adcId;
    tempsnsr[ id ].adcChannel = adcChannel;
    tempsnsr[ id ].voltMulti = 488281;
    tempsnsr[ id ].voltDivide = 1000000;
    for( index = 0; index < 10; index++ )
    {
        tempsnsr[ id ].array[ index ] = 0;
    }
    tempsnsr[ id ].index = 0;
    tempsnsr[ id ].avgFlag = 0;
    tempsnsr[ id ].avgTemp = 0;
    initTempsnsrHardware( id );
}

void Tempsnsr_update( void *paramter )
{
    TEMPSNSR_ID_t id = (TEMPSNSR_ID_t) paramter;
    tempsnsr[ id ].array[ tempsnsr[ id ].index ] = getTempsnsrHarwareState( id );
    tempsnsr[ id ].index++;
	if( tempsnsr[ id ].index == 10 )
    {
        tempsnsr[ id ].index = 0;
        tempsnsr[ id ].avgFlag = 1;
    }
    if( tempsnsr[ id ].avgFlag )
    {
        tempsnsr[ id ].avgTemp = getAvgTemp( id );
    }
}

TEMPSNSR_STATE_t Tempsnsr_getState( TEMPSNSR_ID_t id )
{
    return tempsnsr[ id ].avgTemp;
}

void initTempsnsrHardware( TEMPSNSR_ID_t id )
{
    Gpio_initPin( tempsnsr[ id ].gpioId, tempsnsr[ id ].gpioPin, GPIO_MODE_INPUT, GPIO_TYPE_FLOATING );
    Adc_init( tempsnsr[ id ].adcId );
}

TEMPSNSR_STATE_t getTempsnsrHarwareState( TEMPSNSR_ID_t id )
{
    return (TEMPSNSR_STATE_t)
    		( ( Adc_getState( tempsnsr[ id ].adcId, tempsnsr[ id ].adcChannel ) * tempsnsr[ id ].voltMulti ) / tempsnsr[ id ].voltDivide );
}

TEMPSNSR_STATE_t getAvgTemp( TEMPSNSR_ID_t id )
{
    size_t index = 0;
    uint32_t temp = 0;
    for( index = 0; index < 10; index++ )
    {
    	temp += tempsnsr[ id ].array[ index ];
    }
    temp /= 10;
    return temp;
}
