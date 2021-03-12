#include "TempControlTask.h"

typedef struct
{
    uint8_t State;
}TempControlTask_t;

static TempControlTask_t TempControlTask[ TEMP_CONTROL_TASK_NUMBER ];

void TempControlTask_Init( Id_t Id, Id_t hGpioId, uint8_t hPin, Id_t cGpioId, uint8_t cPin )
{
    TempControlTask[ Id ].State = 0;
    TempControl_Init( Id, hGpioId, hPin, cGpioId, cPin );
}

void TempControlTask_SetState( Id_t Id, uint8_t State )
{
    TempControlTask[ Id ].State = State;
}

void TempControlTask_Update( void *Paramter )
{
    Id_t Id = (Id_t) Paramter;
    TempControl_SetState( Id, TempControlTask[ Id ].State );
}
