#include "HCU.h"

volatile static HCU_t HCU_G[2];

void HCU_Init(void)
{
    HCU_G[0].State = 0;
    HCU_G[1].State = 0;
    GPIO_InitPin(HCU_REG, HU, OUTPUT);
    GPIO_InitPin(HCU_REG, CU, OUTPUT);
}

void HCU_Update(void)
{
    GPIO_SetPinState(HCU_REG, HU, HCU_G[0].State);
    GPIO_SetPinState(HCU_REG, CU, HCU_G[1].State);
}

void HCU_SetState(uint8_t HCUx, uint8_t State)
{
    switch(HCUx)
    {
        case HU:
            HCU_G[0].State = State;
            break;
        case CU:
            HCU_G[1].State = State;
            break;
    }
}
