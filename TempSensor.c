#include "TempSensor.h"

typedef struct
{
    Id_t GpioId;
	uint8_t Pin;
    Id_t AdcId;
    uint8_t Channel;
    uint32_t VoltMulti;
    uint32_t VoltDivide;
    uint8_t Result;
}TempSensor_t;

static TempSensor_t TempSensor[ TEMP_SENSOR_NUMBER ];

void TempSensor_Init( void )
{
    size_t Id = 0;
    for( Id = 0; Id < TEMP_SENSOR_NUMBER; Id++ )
    {
        TempSensor[ Id ].Channel = 2;
        TempSensor[ Id ].VoltMulti = 488281;
        TempSensor[ Id ].VoltDivide = 1000000;
        TempSensor[ Id ].Result = 0;
        Gpio_InitPin( TempSensor[ Id ].GpioId, TempSensor[ Id ].Pin, INPUT );
        Adc_Init( TempSensor[ Id ].AdcId );
    }
}

uint8_t TempSensor_GetState( Id_t Id )
{
    return ( ( Adc_GetState( TempSensor[ Id ].AdcId ) * TempSensor[ Id ].VoltMulti ) / TempSensor[ Id ].VoltDivide );
}

void TempSensor_SetGpio( Id_t Id, Id_t GpioId, uint8_t Pin )
{
    TempSensor[ Id ].GpioId = GpioId;
    TempSensor[ Id ].Pin = Pin;
}

void TempSensor_SetAdc( Id_t Id, Id_t AdcId )
{
    TempSensor[ Id ].AdcId = AdcId;
}
