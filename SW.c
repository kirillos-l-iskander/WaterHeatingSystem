#include "SW.h"

volatile static SW_t SW_G[3];

void SW_Init(void)
{
    SW_G[0].State = 0;
    SW_G[0].Counter = 0;
    SW_G[0].Lock = 0;
    SW_G[1].State = 0;
    SW_G[1].Counter = 0;
    SW_G[1].Lock = 0;
    SW_G[2].State = 0;
    SW_G[2].Counter = 0;
    SW_G[2].Lock = 0;
    GPIO_InitPin(SW_REG, SW0, INPUT);
    GPIO_InitPin(SW_REG, SW1, INPUT);
    GPIO_InitPin(SW_REG, SW2, INPUT);
}

void SW_Update(void)
{
    if(SW_G[0].Lock)
    {
        SW_G[0].Lock--;
    }else if(!GPIO_GetPinState(SW_REG, SW0))
    {
        SW_G[0].Counter++;
        if(SW_G[0].Counter >= SW_THRES)
        {
            SW_G[0].State = 1;
            SW_G[0].Counter = 0;
            SW_G[0].Lock = 1000/SW_UPDATE;
        }
    }else
    {
        SW_G[0].Counter = 0;
    }

    if(SW_G[1].Lock)
    {
        SW_G[1].Lock--;
    }else if(!GPIO_GetPinState(SW_REG, SW1))
    {
        SW_G[1].Counter++;
        if(SW_G[1].Counter >= SW_THRES)
        {
            SW_G[1].State = 1;
            SW_G[1].Counter = 0;
            SW_G[1].Lock = 1000/SW_UPDATE;
        }
    }else
    {
        SW_G[1].Counter = 0;
    }

    if(SW_G[2].Lock)
    {
        SW_G[2].Lock--;
    }else if(!GPIO_GetPinState(SW_REG, SW2))
    {
        SW_G[2].Counter++;
        if(SW_G[2].Counter >= SW_THRES)
        {
            SW_G[2].State = 1;
            SW_G[2].Counter = 0;
            SW_G[2].Lock = 1000/SW_UPDATE;
        }
    }else
    {
        SW_G[2].Counter = 0;
    }
}

uint8_t SW_GetState(uint8_t SWx)
{
    uint8_t State;
    switch(SWx)
    {
        case SW0:
            State = SW_G[0].State;
            SW_G[0].State = 0;
            break;
        case SW1:
            State = SW_G[1].State;
            SW_G[1].State = 0;
            break;
        case SW2:
            State = SW_G[2].State;
            SW_G[2].State = 0;
            break;
    }
    return State;
}
