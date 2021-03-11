#include "TempControlTask.h"

typedef struct
{
    uint8_t State;
}TempControlTask_t;

static TempControlTask_t TempControlTask[ TEMP_CONTROL_TASK_NUMBER ];

void TempControlTask_Init( void )
{
    size_t Id = 0;
    for( Id = 0; Id < TEMP_CONTROL_TASK_NUMBER; Id++ )
    {
        TempControlTask[ Id ].State = 0;
    }
    TempControl_Init();
}

void TempControlTask_SetState( Id_t Id, uint8_t State )
{
    TempControlTask[ Id ].State = State;
}

void TempControlTask_Update( void *Paramter )
{
    size_t Id = 0;
    for( Id = 0; Id < TEMP_CONTROL_TASK_NUMBER; Id++ )
    {
        TempControl_SetState( Id, TempControlTask[ Id ].State );
    }
}
