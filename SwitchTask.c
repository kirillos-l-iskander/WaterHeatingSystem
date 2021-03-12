#include "SwitchTask.h"

typedef struct
{
    uint8_t Lock;
    uint8_t Counter;
    uint8_t State;
}SwitchTask_t;

static SwitchTask_t SwitchTask[ SWITCH_TASK_NUMBER ];

void SwitchTask_Init( Id_t Id, Id_t GpioId, uint8_t Pin )
{
    SwitchTask[ Id ].Lock = 0;
    SwitchTask[ Id ].Counter = 0;
    SwitchTask[ Id ].State = LOW;
    Switch_Init( Id, GpioId, Pin );
}

uint8_t SwitchTask_GetState( Id_t Id )
{
    uint8_t Buffer = SwitchTask[ Id ].State;
    SwitchTask[ Id ].State = LOW;
    return Buffer;
}

void SwitchTask_Update( void *Paramter )
{
    Id_t Id = (Id_t) Paramter;
    if( SwitchTask[ Id ].Lock )
    {
        SwitchTask[ Id ].Lock--;
    }else if( !Switch_GetState( Id ) )
    {
        SwitchTask[ Id ].Counter++;
        if( SwitchTask[ Id ].Counter == C_MS_TO_TICKS( 20 ) / C_MS_TO_TICKS( 10 ) )
        {
            SwitchTask[ Id ].Lock = C_MS_TO_TICKS( 500 ) / C_MS_TO_TICKS( 10 );
            SwitchTask[ Id ].Counter = 0;
            SwitchTask[ Id ].State = HIGH;
        }
    }else
    {
        SwitchTask[ Id ].Counter = 0;
    }
}
