#include "SwitchTask.h"

typedef struct
{
    uint8_t lock;
    uint8_t counter;
    uint8_t state;
}SwitchTask_t;

static SwitchTask_t switchTask[ SWITCH_NUMBER ];

void SwitchTask_init( Id_t id, Id_t xGpioId, uint8_t xPin )
{
    switchTask[ id ].lock = 0;
    switchTask[ id ].counter = 0;
    switchTask[ id ].state = LOW;
    Switch_init( id, xGpioId, xPin );
}

uint8_t SwitchTask_getState( Id_t id )
{
    uint8_t buffer = switchTask[ id ].state;
    switchTask[ id ].state = LOW;
    return buffer;
}

void SwitchTask_update( void *paramter )
{
    Id_t id = (Id_t) paramter;
    if( switchTask[ id ].lock )
    {
        switchTask[ id ].lock--;
    }else if( !Switch_getState( id ) )
    {
        switchTask[ id ].counter++;
        if( switchTask[ id ].counter == MS_TO_TICKS( 20 ) / MS_TO_TICKS( 10 ) )
        {
            switchTask[ id ].lock = MS_TO_TICKS( 500 ) / MS_TO_TICKS( 10 );
            switchTask[ id ].counter = 0;
            switchTask[ id ].state = HIGH;
        }
    }else
    {
        switchTask[ id ].counter = 0;
    }
}
