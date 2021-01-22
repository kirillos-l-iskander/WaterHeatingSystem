#include "SSD.h"

volatile static SSD_t SSD_G[4];
volatile static uint8_t SSD_SymbolPattern_G[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
volatile static uint8_t SSD_Num_G = 0;

void SSD_Init(void)
{
    SSD_G[0].State = 0;
    SSD_G[0].Symbol = 0;
    SSD_G[1].State = 0;
    SSD_G[1].Symbol = 0;
    SSD_G[2].State = 0;
    SSD_G[2].Symbol = 0;
    SSD_G[3].State = 0;
    SSD_G[3].Symbol = 0;
    GPIO_InitPin(SSD_DAT_REG, D0, OUTPUT);
    GPIO_InitPin(SSD_DAT_REG, D1, OUTPUT);
    GPIO_InitPin(SSD_DAT_REG, D2, OUTPUT);
    GPIO_InitPin(SSD_DAT_REG, D3, OUTPUT);
    GPIO_InitPin(SSD_DAT_REG, D4, OUTPUT);
    GPIO_InitPin(SSD_DAT_REG, D5, OUTPUT);
    GPIO_InitPin(SSD_DAT_REG, D6, OUTPUT);
    GPIO_InitPin(SSD_DAT_REG, D7, OUTPUT);
    GPIO_InitPin(SSD_ENA_REG, SSD0, OUTPUT);
    GPIO_InitPin(SSD_ENA_REG, SSD1, OUTPUT);
}

void SSD_Update(void)
{
    GPIO_SetPinState(SSD_ENA_REG, SSD0, LOW);
    GPIO_SetPinState(SSD_ENA_REG, SSD1, LOW);
    GPIO_SetPortState(SSD_DAT_REG, 0xFF, SSD_SymbolPattern_G[SSD_G[SSD_Num_G].Symbol]);
    if(SSD_Num_G == 0)
    {
        GPIO_SetPinState(SSD_ENA_REG, SSD0, SSD_G[0].State);
    }
    if(SSD_Num_G == 1)
    {
        GPIO_SetPinState(SSD_ENA_REG, SSD1, SSD_G[1].State);
    }
    SSD_Num_G++;
    if(SSD_Num_G == SSD_Num)
    {
        SSD_Num_G = 0;        
    }
}

void SSD_SetState(uint8_t SSDx, uint8_t State)
{
    switch(SSDx)
    {
        case SSD0:
            SSD_G[0].State = State;
            break;
        case SSD1:
            SSD_G[1].State = State;
            break;
        case SSD2:
            SSD_G[2].State = State;
            break;
        case SSD3:
            SSD_G[3].State = State;
            break;
    }
}

uint8_t SSD_GetState(uint8_t SSDx)
{
    uint8_t State;
    switch(SSDx)
    {
        case SSD0:
            State = SSD_G[0].State;
            break;
        case SSD1:
            State = SSD_G[1].State;
            break;
        case SSD2:
            State = SSD_G[2].State;
            break;
        case SSD3:
            State = SSD_G[3].State;
            break;
    }
    return State;
}

void SSD_SetSymbol(uint8_t SSDx, uint8_t Symbol)
{
    switch(SSDx)
    {
        case SSD0:
            SSD_G[0].Symbol = Symbol;
            break;
        case SSD1:
            SSD_G[1].Symbol = Symbol;
            break;
        case SSD2:
            SSD_G[2].Symbol = Symbol;
            break;
        case SSD3:
            SSD_G[3].Symbol = Symbol;
            break;
    }
}

uint8_t SSD_GetSymbol(uint8_t SSDx)
{
    uint8_t Symbol;
    switch(SSDx)
    {
        case SSD0:
            Symbol = SSD_G[0].Symbol;
            break;
        case SSD1:
            Symbol = SSD_G[1].Symbol;
            break;
        case SSD2:
            Symbol = SSD_G[2].Symbol;
            break;
        case SSD3:
            Symbol = SSD_G[3].Symbol;
            break;
    }
    return Symbol;
}
