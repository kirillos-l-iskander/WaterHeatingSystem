#include "TempSensor.h"

typedef struct
{
    Id_t xGpioId;
	uint8_t xPin;
    Id_t xAdcId;
    uint8_t channel;
    uint32_t voltMulti;
    uint32_t voltDivide;
    uint8_t result;
}TempSensor_t;

static TempSensor_t tempSensor[ TEMP_SENSOR_NUMBER ];

void TempSensor_init( Id_t id, Id_t xGpioId, uint8_t xPin, Id_t xAdcId )
{
    tempSensor[ id ].xGpioId = xGpioId;
    tempSensor[ id ].xPin = xPin;
    tempSensor[ id ].xAdcId = xAdcId;
    tempSensor[ id ].channel = 2;
    tempSensor[ id ].voltMulti = 488281;
    tempSensor[ id ].voltDivide = 1000000;
    tempSensor[ id ].result = 0;
    Gpio_initPin( tempSensor[ id ].xGpioId, tempSensor[ id ].xPin, INPUT );
    Adc_init( tempSensor[ id ].xAdcId );
}

uint8_t TempSensor_getState( Id_t id )
{
    return ( ( Adc_getState( tempSensor[ id ].xAdcId ) * tempSensor[ id ].voltMulti ) / tempSensor[ id ].voltDivide );
}
