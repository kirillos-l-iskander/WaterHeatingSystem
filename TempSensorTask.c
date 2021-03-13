#include "TempSensorTask.h"

typedef struct
{
    uint8_t array[ 10 ];
    uint8_t index;
    uint8_t avgFlag;
    uint16_t avgTemp;
}TempSensorTask_t;

static TempSensorTask_t tempSensorTask[ TEMP_SENSOR_NUMBER ];

void TempSensorTask_init( Id_t id, Id_t xGpioId, uint8_t xPin, Id_t xAdcId )
{
    size_t index = 0;
    for( index = 0; index < 10; index++ )
    {
        tempSensorTask[ id ].array[ index ] = 0;
    }
    tempSensorTask[ id ].index = 0;
    tempSensorTask[ id ].avgFlag = 0;
    tempSensorTask[ id ].avgTemp = 0;
    TempSensor_init( id, xGpioId, xPin, xAdcId );
}

uint8_t TempSensorTask_getAverage( Id_t id )
{
    return ( uint8_t ) tempSensorTask[ id ].avgTemp;
}

void TempSensorTask_update( void *paramter )
{
    Id_t id = (Id_t) paramter;
    size_t index = 0;
    tempSensorTask[ id ].array[ tempSensorTask[ id ].index++ ] = TempSensor_getState( id );
    if( tempSensorTask[ id ].index == 10 )
    {
        tempSensorTask[ id ].index = 0;
        tempSensorTask[ id ].avgFlag = 1;
    }
    if( tempSensorTask[ id ].avgFlag )
    {
        for( index = 0; index < 10; index++ )
        {
            tempSensorTask[ id ].avgTemp += tempSensorTask[ id ].array[ index ];
        }
        tempSensorTask[ id ].avgTemp /= 10;
    }
}
