#include "SsdTask.h"

typedef struct
{
	uint8_t Counter;
    uint8_t Symbol;
    uint8_t State;
	uint8_t Blink;
	uint16_t Period;
	uint16_t Delay;
}SsdTask_t;

static SsdTask_t SsdTask[ SSD_TASK_NUMBER ];

void SsdTask_Init( void )
{
    size_t Id = 0;
	for ( Id = 0; Id < SSD_TASK_NUMBER; Id++ )
    {
        SsdTask[ Id ].Counter = Id;
        SsdTask[ Id ].Symbol = 0;
        SsdTask[ Id ].State = LOW;
        SsdTask[ Id ].Blink = 0;
        SsdTask[ Id ].Period = 0;
        SsdTask[ Id ].Delay = 0;
    }
    Ssd_Init();
}

void SsdTask_SetState( Id_t Id, uint8_t State, uint16_t Period )
{
    SsdTask[ Id ].State = State;
	SsdTask[ Id ].Period = C_MS_TO_TICKS( Period ) / C_MS_TO_TICKS( 5 );
}

void SsdTask_SetSymbol( Id_t Id, uint8_t Symbol )
{
    SsdTask[ Id ].Symbol = Symbol;
}

void SsdTask_Update( void *Paramter )
{
    size_t Id = 0;
	for ( Id = 0; Id < SSD_TASK_NUMBER; Id++ )
    {
        if( SsdTask[ Id ].Delay )
        {
            SsdTask[ Id ].Delay--;
        }else if( SsdTask[ Id ].Period )
        {
            SsdTask[ Id ].Blink ^= SsdTask[ Id ].State;
            SsdTask[ Id ].Delay = SsdTask[ Id ].Period;
        }else
        {
            SsdTask[ Id ].Blink = 0;
        }
        Ssd_SetState( Id, LOW );
        if( SsdTask[ Id ].Counter == 0 )
        {
            Ssd_SetSymbol( Id, SsdTask[ Id ].Symbol );
            Ssd_SetState( Id, SsdTask[ Id ].State & !SsdTask[ Id ].Blink );
        }
        SsdTask[ Id ].Counter++;
        if( SsdTask[ Id ].Counter == SSD_NUMBER )
        {
            SsdTask[ Id ].Counter = 0;
        }
    }
}
