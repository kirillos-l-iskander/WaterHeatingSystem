#include "WaterHeater.h"

typedef enum
{
    OffMode = 0,
    OperationMode,
    NormalMode,
    TempSetMode,
    ResetMode
}HeaterState_t;

typedef struct
{
    SW_ID_t sSwId;
    SW_ID_t mSwId;
    SW_ID_t pSwId;
    TEMPSNSR_ID_t xTempsnsrId;
    TEMPCTRL_ID_t xTempctrlId;
    LED_ID_t xLedId;
    SSD_ID_t aSsdId;
    SSD_ID_t bSsdId;
    HeaterState_t state;
    HeaterState_t preState;
    uint8_t avgTemp;
    uint8_t targetTemp;
    uint16_t counter;
    uint8_t passwordFlag;
    uint8_t passwordWrite[ PASSWORD_LENGTH ];
    uint8_t passwordRead[ PASSWORD_LENGTH ];
}Heater_t;

static Heater_t heater[ HEATER_ID_MAX ];

void Heater_init( HEATER_ID_t id, SW_ID_t sSwId, SW_ID_t mSwId, SW_ID_t pSwId, TEMPSNSR_ID_t xTempsnsrId,
                  TEMPCTRL_ID_t xTempctrlId, LED_ID_t xLedId, SSD_ID_t aSsdId, SSD_ID_t bSsdId )
{
    size_t index = 0;
    Eeprom_init();
    heater[ id ].sSwId = sSwId;
    heater[ id ].mSwId = mSwId;
    heater[ id ].pSwId = pSwId;
    heater[ id ].xTempsnsrId = xTempsnsrId;
    heater[ id ].xTempctrlId = xTempctrlId;
    heater[ id ].xLedId = xLedId;
    heater[ id ].aSsdId = aSsdId;
    heater[ id ].bSsdId = bSsdId;
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

void Heater_update( void *paramter )
{
    HEATER_ID_t id = (HEATER_ID_t) paramter;
    switch( heater[ id ].state )
    {
        case OffMode:
        {
            if( Switch_getState( heater[ id ].sSwId ) == SWITCH_STATE_PRESSED )
            {
                heater[ id ].state = OperationMode;
            }
            break;
        }
        case OperationMode:
        {
            heater[ id ].avgTemp = Tempsnsr_getState( heater[ id ].xTempsnsrId );
            if( heater[ id ].avgTemp <= ( heater[ id ].targetTemp - 5 ) )
            {
                Tempctrl_setState( heater[ id ].xTempctrlId, TEMPCTRL_STATE_HEAT );
                Led_setState( heater[ id ].xLedId, LED_STATE_ON, LED_BLINK_1000MS );
            }else if( heater[ id ].avgTemp >= ( heater[ id ].targetTemp + 5 ) )
            {
                Tempctrl_setState( heater[ id ].xTempctrlId, TEMPCTRL_STATE_COOL );
                Led_setState( heater[ id ].xLedId, LED_STATE_ON, LED_BLINK_0MS );
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
            Ssd_setState( heater[ id ].aSsdId, SSD_STATE_ON, SSD_BLINK_0MS );
            Ssd_setState( heater[ id ].bSsdId, SSD_STATE_ON, SSD_BLINK_0MS );
            Ssd_setSymbol( heater[ id ].aSsdId, heater[ id ].avgTemp % 10 );
            Ssd_setSymbol( heater[ id ].bSsdId, ( heater[ id ].avgTemp / 10 ) % 10 );
            if( Switch_getState( heater[ id ].mSwId ) || Switch_getState( heater[ id ].pSwId ) )
            {
                heater[ id ].state = TempSetMode;
            }else if( Switch_getState( heater[ id ].sSwId ) )
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
            Ssd_setState( heater[ id ].aSsdId, SSD_STATE_ON, SSD_BLINK_1000MS );
            Ssd_setState( heater[ id ].bSsdId, SSD_STATE_ON, SSD_BLINK_1000MS );
            Ssd_setSymbol( heater[ id ].aSsdId, heater[ id ].targetTemp % 10 );
            Ssd_setSymbol( heater[ id ].bSsdId, ( heater[ id ].targetTemp / 10 ) % 10 );
            if( Switch_getState( heater[ id ].pSwId ) && heater[ id ].targetTemp <= 70 )
            {
                heater[ id ].targetTemp += 5;
                heater[ id ].counter = 0;
            }
            if( Switch_getState( heater[ id ].mSwId ) && heater[ id ].targetTemp >= 40 )
            {
                heater[ id ].targetTemp -= 5;
                heater[ id ].counter = 0;
            }
            if( Switch_getState( heater[ id ].sSwId ) )
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
            Tempctrl_setState( heater[ id ].xTempctrlId, TEMPCTRL_STATE_OFF );
            Led_setState( heater[ id ].xLedId, LED_STATE_OFF, LED_BLINK_0MS );
            Ssd_setState( heater[ id ].aSsdId, SSD_STATE_OFF, SSD_BLINK_0MS );
            Ssd_setState( heater[ id ].bSsdId, SSD_STATE_OFF, SSD_BLINK_0MS );
            Eeprom_write( EEPROM_DATA_ADDRESS, heater[ id ].targetTemp );
            heater[ id ].counter = 0;
            heater[ id ].state = OffMode;
            heater[ id ].preState = heater[ id ].state;
            break;
        }
    }
}
