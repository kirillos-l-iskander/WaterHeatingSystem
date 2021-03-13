#include "TempControlTask.h"

typedef struct
{
    uint8_t state;
}TempControlTask_t;

static TempControlTask_t tempControlTask[ TEMP_CONTROL_NUMBER ];

void TempControlTask_init( Id_t id, Id_t hGpioId, uint8_t hPin, Id_t cGpioId, uint8_t cPin )
{
    tempControlTask[ id ].state = 0;
    TempControl_init( id, hGpioId, hPin, cGpioId, cPin );
}

void TempControlTask_setState( Id_t id, uint8_t state )
{
    tempControlTask[ id ].state = state;
}

void TempControlTask_update( void *paramter )
{
    Id_t id = (Id_t) paramter;
    TempControl_setState( id, tempControlTask[ id ].state );
}
