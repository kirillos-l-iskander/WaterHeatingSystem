#include "WaterHeater.h"

typedef enum
{
    OffMode,
    OperationMode,
    NormalMode,
    TempSetMode,
    ResetMode
}HeaterState_t;

typedef struct
{
    HeaterState_t state;
    HeaterState_t preState;
    uint8_t avgTemp;
    uint8_t targetTemp;
    uint16_t counter;
    uint8_t passwordFlag;
    uint8_t passwordWrite[ PASSWORD_LENGTH ];
    uint8_t passwordRead[ PASSWORD_LENGTH ];
}Heater_t;

static Heater_t heater[ HEATER_NUMBER ];

void HeaterTask_init( Id_t id )
{
    size_t index = 0;
    Eeprom_init();
    heater[ id ].state = OffMode;
    heater[ id ].preState = heater[ id ].state;
    heater[ id ].avgTemp = 0;
    heater[ id ].targetTemp = 60;
    heater[ id ].counter = 0;
    heater[ id ].passwordFlag = 1;
    heater[ id ].passwordWrite[ 0 ] = '#';
    heater[ id ].passwordWrite[ 1 ] = 'P';
    heater[ id ].passwordWrite[ 2 ] = 'w';
    heater[ id ].passwordWrite[ 3 ] = 'r';
    heater[ id ].passwordWrite[ 4 ] = 'U';
    heater[ id ].passwordWrite[ 5 ] = 'p';
    heater[ id ].passwordWrite[ 6 ] = '_';
    heater[ id ].passwordWrite[ 7 ] = '1';
    heater[ id ].passwordRead[ 0 ] = 0;
    heater[ id ].passwordRead[ 1 ] = 0;
    heater[ id ].passwordRead[ 2 ] = 0;
    heater[ id ].passwordRead[ 3 ] = 0;
    heater[ id ].passwordRead[ 4 ] = 0;
    heater[ id ].passwordRead[ 5 ] = 0;
    heater[ id ].passwordRead[ 6 ] = 0;
    heater[ id ].passwordRead[ 7 ] = 0;
    //Check if power up for first time
    Eeprom_readPage( EEPROM_PASSWORD_ADDRESS, heater[ id ].passwordRead, PASSWORD_LENGTH );
    for( index = 0; index < PASSWORD_LENGTH; index++)
    {
        if( heater[ id ].passwordWrite[ index ] != heater[ id ].passwordRead[ index ] )
        {
            heater[ id ].passwordFlag = 0;
            break;
        }
    }

    if( heater[ id ].passwordFlag )
    {
        heater[ id ].targetTemp = Eeprom_read( EEPROM_DATA_ADDRESS );
    }else
    {
        Eeprom_writePage( EEPROM_PASSWORD_ADDRESS, heater[ id ].passwordWrite, PASSWORD_LENGTH );
        DELAY_MS( 10 );
        Eeprom_write( EEPROM_DATA_ADDRESS, heater[ id ].targetTemp );
    }
}

void HeaterTask_update( void *paramter )
{
    Id_t id = (Id_t) paramter;
    switch( heater[ id ].state )
    {
        case OffMode:
        {
            if( SwitchTask_getState( id*3 ) )
            {
                heater[ id ].state = OperationMode;
            }
            break;
        }
        case OperationMode:
        {
            heater[ id ].avgTemp = TempSensorTask_getAverage( id );
            if( heater[ id ].avgTemp <= ( heater[ id ].targetTemp - 5 ) )
            {
                TempControlTask_setState( id, 1 );
                LedTask_setState( id, HIGH, 1000 );
            }else if( heater[ id ].avgTemp >= ( heater[ id ].targetTemp + 5 ) )
            {
                TempControlTask_setState( id, 2 );
                LedTask_setState( id, HIGH, 0 );
            }
            if( heater[ id ].preState == TempSetMode )
            {
                heater[ id ].state = TempSetMode;
            }else
            {
                heater[ id ].state = NormalMode;
            }
            break;
        }
        case NormalMode:
        {
            heater[ id ].preState = heater[ id ].state;
            SsdTask_setState( id*2, HIGH, 0 );
            SsdTask_setState( id*2 + 1, HIGH, 0 );
            SsdTask_setSymbol( id*2, heater[ id ].avgTemp % 10 );
            SsdTask_setSymbol( id*2 + 1, ( heater[ id ].avgTemp / 10 ) % 10 );
            if( SwitchTask_getState( id*3 + 2 ) || SwitchTask_getState( id*3 + 1 ) )
            {
                heater[ id ].state = TempSetMode;
            }else if( SwitchTask_getState( id*3 ) )
            {
                heater[ id ].state = ResetMode;
            }else
            {
                heater[ id ].state = OperationMode;
            }
            break;
        }
        case TempSetMode:
        {
            heater[ id ].preState = heater[ id ].state;
            SsdTask_setState( id*2, HIGH, 1000 );
            SsdTask_setState( id*2 + 1, HIGH, 1000 );
            SsdTask_setSymbol( id*2, heater[ id ].targetTemp % 10 );
            SsdTask_setSymbol( id*2 + 1, ( heater[ id ].targetTemp / 10 ) % 10 );
            if( SwitchTask_getState( id*3 + 2 ) && heater[ id ].targetTemp <= 70 )
            {
                heater[ id ].targetTemp += 5;
                heater[ id ].counter = 0;
            }
            if( SwitchTask_getState( id*3 + 1 ) && heater[ id ].targetTemp >= 40 )
            {
                heater[ id ].targetTemp -= 5;
                heater[ id ].counter = 0;
            }
            if( SwitchTask_getState( id*3 ) )
            {
                heater[ id ].state = ResetMode;
            }else
            {
                heater[ id ].state = OperationMode;
            }
            if( heater[ id ].counter++ >= ( MS_TO_TICKS( 5000 ) / MS_TO_TICKS( 200 ) ) )
            {
                heater[ id ].counter = 0;
                Eeprom_write( EEPROM_DATA_ADDRESS, heater[ id ].targetTemp );
                heater[ id ].state = NormalMode;
            }
            break;
        }
        case ResetMode:
        {
            TempControlTask_setState( id, 0 );
            LedTask_setState( id, LOW, 0 );
            SsdTask_setState( id*2, 0x00, 0 );
            SsdTask_setState( id*2 + 1, 0x00, 0 );
            Eeprom_write( EEPROM_DATA_ADDRESS, heater[ id ].targetTemp );
            heater[ id ].counter = 0;
            heater[ id ].state = OffMode;
            heater[ id ].preState = heater[ id ].state;
            break;
        }
    }
}
