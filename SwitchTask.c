#include "SwitchTask.h"

typedef struct
{
    uint8_t Lock;
    uint8_t Counter;
    uint8_t State;
}SwitchTask_t;

static SwitchTask_t SwitchTask[ SWITCH_TASK_NUMBER ];

void SwitchTask_Init( void )
{
    size_t Id = 0;
    for( Id = 0; Id < SWITCH_TASK_NUMBER; Id++ )
    {
        SwitchTask[ Id ].Lock = 0;
        SwitchTask[ Id ].Counter = 0;
        SwitchTask[ Id ].State = LOW;
    }
    Switch_Init();
}

uint8_t SwitchTask_GetState( Id_t Id )
{
    uint8_t Buffer = SwitchTask[ Id ].State;
    SwitchTask[ Id ].State = LOW;
    return Buffer;
}

void SwitchTask_Update( void *Paramter )
{
    size_t Id = 0;
    for( Id = 0; Id < SWITCH_TASK_NUMBER; Id++ )
    {
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
}
