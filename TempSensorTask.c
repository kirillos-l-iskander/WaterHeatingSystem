#include "TempSensorTask.h"

typedef struct
{
    uint8_t Array[ 10 ];
    uint8_t Index;
    uint8_t AvgFlag;
    uint16_t AvgTemp;
}TempSensorTask_t;

static TempSensorTask_t TempSensorTask[ TEMP_SENSOR_TASK_NUMBER ];

void TempSensorTask_Init( Id_t Id, Id_t GpioId, uint8_t Pin, Id_t AdcId )
{
    size_t Index = 0;
    for( Index = 0; Index < 10; Index++ )
    {
        TempSensorTask[ Id ].Array[ Index ] = 0;
    }
    TempSensorTask[ Id ].Index = 0;
    TempSensorTask[ Id ].AvgFlag = 0;
    TempSensorTask[ Id ].AvgTemp = 0;
    TempSensor_Init( Id, GpioId, Pin, AdcId );
}

uint8_t TempSensorTask_GetAverage( Id_t Id )
{
    return ( uint8_t ) TempSensorTask[ Id ].AvgTemp;
}

void TempSensorTask_Update( void *Paramter )
{
    Id_t Id = (Id_t) Paramter;
    size_t Index = 0;
    TempSensorTask[ Id ].Array[ TempSensorTask[ Id ].Index++ ] = TempSensor_GetState( Id );
    if( TempSensorTask[ Id ].Index == 10 )
    {
        TempSensorTask[ Id ].Index = 0;
        TempSensorTask[ Id ].AvgFlag = 1;
    }
    if( TempSensorTask[ Id ].AvgFlag )
    {
        for( Index = 0; Index < 10; Index++ )
        {
            TempSensorTask[ Id ].AvgTemp += TempSensorTask[ Id ].Array[ Index ];
        }
        TempSensorTask[ Id ].AvgTemp /= 10;
    }
}
