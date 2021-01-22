#include "DISP.h"
#include "LED.h"
#include "SSD.h"

volatile static DISP_t DISP_G[2];

void DISP_Init()
{
    DISP_G[0].State = 0;
    DISP_G[0].Blink = 0;
    DISP_G[0].Counter = 0;
    DISP_G[1].State = 0;
    DISP_G[1].Blink = 0;
    DISP_G[1].Counter = 0;
    LED_SetState(LED1, LED_OFF);
    SSD_SetState(SSD0, SSD_OFF);
    SSD_SetState(SSD1, SSD_OFF);
}

void DISP_Update()
{
    if(DISP_G[0].State)
    {
        if(DISP_G[0].Blink)
        {
            DISP_G[0].Counter++;
        }else
        {
            DISP_G[0].Counter = 0;
        }
        if(DISP_G[0].Counter <= 1000/DISP_UPDATE)
        {
            LED_SetState(LED1, LED_ON);
        }else if(DISP_G[0].Counter <= 2000/DISP_UPDATE)
        {
            LED_SetState(LED1, LED_OFF);
        }else
        {
            DISP_G[0].Counter = 0;
        }
    }else
    {
        LED_SetState(LED1, LED_OFF);
    }
    if(DISP_G[1].State)
    {
        if(DISP_G[1].Blink)
        {
            DISP_G[1].Counter++;
        }else
        {
            DISP_G[1].Counter = 0;
        }
        if(DISP_G[1].Counter <= 1000/DISP_UPDATE)
        {
            SSD_SetState(SSD0, SSD_ON);
            SSD_SetState(SSD1, SSD_ON);
        }else if(DISP_G[1].Counter <= 2000/DISP_UPDATE)
        {
            SSD_SetState(SSD0, SSD_OFF);
            SSD_SetState(SSD1, SSD_OFF);
        }else
        {
            DISP_G[1].Counter = 0;
        }
    }else
    {
        SSD_SetState(SSD0, SSD_OFF);
        SSD_SetState(SSD1, SSD_OFF);
    }
}

void DISP_SetState(uint8_t DISPx, uint8_t State)
{
    switch(DISPx)
    {
        case DISP0_STATE:
            DISP_G[0].State = State;
            break;
        case DISP0_BLINK:
            DISP_G[0].Blink = State;
            break;
        case DISP1_STATE:
            DISP_G[1].State = State;
            break;
        case DISP1_BLINK:
            DISP_G[1].Blink = State;
            break;
    }
}

uint8_t DISP_GetState(uint8_t DISPx)
{
    uint8_t State;
    switch(DISPx)
    {
        case DISP0_STATE:
            State = DISP_G[0].State;
            break;
        case DISP0_BLINK:
            State = DISP_G[0].Blink;
            break;
        case DISP1_STATE:
            State = DISP_G[1].State;
            break;
        case DISP1_BLINK:
            State = DISP_G[1].Blink;
            break;
    }
    return State;
}
