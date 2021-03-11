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
    HeaterState_t State;
    HeaterState_t PreState;
    uint8_t AvgTemp;
    uint8_t TargetTemp;
    uint16_t Counter;
    uint8_t PasswordFlag;
    uint8_t PasswordWrite[ PASSWORD_LENGTH ];
    uint8_t PasswordRead[ PASSWORD_LENGTH ];
}Heater_t;

static Heater_t Heater[ HEATER_NUMBER ];

void HeaterTask_Init( void )
{
    size_t Id = 0;
	for ( Id = 0; Id < HEATER_NUMBER; Id++ )
    {
        size_t Index = 0;
        Eeprom_Init();
        Heater[ Id ].State = OffMode;
        Heater[ Id ].PreState = Heater[ Id ].State;
        Heater[ Id ].AvgTemp = 0;
        Heater[ Id ].TargetTemp = 60;
        Heater[ Id ].Counter = 0;
        Heater[ Id ].PasswordFlag = 1;
        Heater[ Id ].PasswordWrite[ 0 ] = '#';
        Heater[ Id ].PasswordWrite[ 1 ] = 'P';
        Heater[ Id ].PasswordWrite[ 2 ] = 'w';
        Heater[ Id ].PasswordWrite[ 3 ] = 'r';
        Heater[ Id ].PasswordWrite[ 4 ] = 'U';
        Heater[ Id ].PasswordWrite[ 5 ] = 'p';
        Heater[ Id ].PasswordWrite[ 6 ] = '_';
        Heater[ Id ].PasswordWrite[ 7 ] = '1';
        Heater[ Id ].PasswordRead[ 0 ] = 0;
        Heater[ Id ].PasswordRead[ 1 ] = 0;
        Heater[ Id ].PasswordRead[ 2 ] = 0;
        Heater[ Id ].PasswordRead[ 3 ] = 0;
        Heater[ Id ].PasswordRead[ 4 ] = 0;
        Heater[ Id ].PasswordRead[ 5 ] = 0;
        Heater[ Id ].PasswordRead[ 6 ] = 0;
        Heater[ Id ].PasswordRead[ 7 ] = 0;

        //Check if power up for first time
        Eeprom_ReadPage( EEPROM_PASSWORD_ADDRESS, Heater[ Id ].PasswordRead, PASSWORD_LENGTH );
        for( Index = 0; Index < PASSWORD_LENGTH; Index++)
        {
            if( Heater[ Id ].PasswordWrite[ Index ] != Heater[ Id ].PasswordRead[ Index ] )
            {
                Heater[ Id ].PasswordFlag = 0;
                break;
            }
        }

        if( Heater[ Id ].PasswordFlag )
        {
            Heater[ Id ].TargetTemp = Eeprom_Read( EEPROM_DATA_ADDRESS );
        }else
        {
            Eeprom_WritePage( EEPROM_PASSWORD_ADDRESS, Heater[ Id ].PasswordWrite, PASSWORD_LENGTH );
            DELAY_MS( 10 );
            Eeprom_Write( EEPROM_DATA_ADDRESS, Heater[ Id ].TargetTemp );
        }
    }
}

void HeaterTask_Update( void *Paramter )
{
    size_t Id = 0;
	for ( Id = 0; Id < HEATER_NUMBER; Id++ )
    {
        switch( Heater[ Id ].State )
        {
            case OffMode:
            {
                if( SwitchTask_GetState( Id*3 ) )
                {
                    Heater[ Id ].State = OperationMode;
                }
                break;
            }
            case OperationMode:
            {
                Heater[ Id ].AvgTemp = TempSensorTask_GetAverage( Id );
                if( Heater[ Id ].AvgTemp <= ( Heater[ Id ].TargetTemp - 5 ) )
                {
                    TempControlTask_SetState( Id, 1 );
                    LedTask_SetState( Id, HIGH, 1000 );
                }else if( Heater[ Id ].AvgTemp >= ( Heater[ Id ].TargetTemp + 5 ) )
                {
                    TempControlTask_SetState( Id, 2 );
                    LedTask_SetState( Id, HIGH, 0 );
                }
                if( Heater[ Id ].PreState == TempSetMode )
                {
                    Heater[ Id ].State = TempSetMode;
                }else
                {
                    Heater[ Id ].State = NormalMode;
                }
                break;
            }
            case NormalMode:
            {
                Heater[ Id ].PreState = Heater[ Id ].State;
                SsdTask_SetState( Id*2, HIGH, 0 );
                SsdTask_SetState( Id*2 + 1, HIGH, 0 );
                SsdTask_SetSymbol( Id*2, Heater[ Id ].AvgTemp % 10 );
                SsdTask_SetSymbol( Id*2 + 1, ( Heater[ Id ].AvgTemp / 10 ) % 10 );
                if( SwitchTask_GetState( Id*3 + 2 ) || SwitchTask_GetState( Id*3 + 1 ) )
                {
                    Heater[ Id ].State = TempSetMode;
                }else if( SwitchTask_GetState( Id*3 ) )
                {
                    Heater[ Id ].State = ResetMode;
                }else
                {
                    Heater[ Id ].State = OperationMode;
                }
                break;
            }
            case TempSetMode:
            {
                Heater[ Id ].PreState = Heater[ Id ].State;
                SsdTask_SetState( Id*2, HIGH, 1000 );
                SsdTask_SetState( Id*2 + 1, HIGH, 1000 );
                SsdTask_SetSymbol( Id*2, Heater[ Id ].TargetTemp % 10 );
                SsdTask_SetSymbol( Id*2 + 1, ( Heater[ Id ].TargetTemp / 10 ) % 10 );
                if( SwitchTask_GetState( Id*3 + 2 ) && Heater[ Id ].TargetTemp <= 70 )
                {
                    Heater[ Id ].TargetTemp += 5;
                    Heater[ Id ].Counter = 0;
                }
                if( SwitchTask_GetState( Id*3 + 1 ) && Heater[ Id ].TargetTemp >= 40 )
                {
                    Heater[ Id ].TargetTemp -= 5;
                    Heater[ Id ].Counter = 0;
                }
                if( SwitchTask_GetState( Id*3 ) )
                {
                    Heater[ Id ].State = ResetMode;
                }else
                {
                    Heater[ Id ].State = OperationMode;
                }
                if( Heater[ Id ].Counter++ >= ( C_MS_TO_TICKS( 5000 ) / C_MS_TO_TICKS( 200 ) ) )
                {
                    Heater[ Id ].Counter = 0;
                    Eeprom_Write( EEPROM_DATA_ADDRESS, Heater[ Id ].TargetTemp );
                    Heater[ Id ].State = NormalMode;
                }
                break;
            }
            case ResetMode:
            {
                TempControlTask_SetState( Id, 0 );
                LedTask_SetState( Id, LOW, 0 );
                SsdTask_SetState( Id*2, 0x00, 0 );
                SsdTask_SetState( Id*2 + 1, 0x00, 0 );
                Eeprom_Write( EEPROM_DATA_ADDRESS, Heater[ Id ].TargetTemp );
                Heater[ Id ].Counter = 0;
                Heater[ Id ].State = OffMode;
                Heater[ Id ].PreState = Heater[ Id ].State;
                break;
            }
        }
    }
}
