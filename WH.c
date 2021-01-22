#include "WH.h"

#define EEPROM_PASSWORD_ADDRESS 0
#define PASSWORD_LENGTH 8
#define EEPROM_DATA_ADDRESS 8

volatile static WH_t WH_State_G = OffMode;
volatile static WH_t WH_PreState_G = OffMode;

volatile static uint8_t WH_EEPROMPassword_G[PASSWORD_LENGTH] = {'#','P','w','r','U','p','_','1'};
volatile static uint8_t WH_PasswordRead_G[PASSWORD_LENGTH] = {0};
volatile static uint8_t WH_PasswordFlag_G = 1;

volatile static uint8_t WH_TargetTemp_G = 60;
volatile static uint8_t WH_AvgTemp_G = 0;
volatile static uint16_t WH_Counter_G = 0;

void WH_Init(void)
{
    uint8_t Index = 0;
    EEPROM_Init();
    //Check if power up for first time
    EEPROM_ReadPage(EEPROM_PASSWORD_ADDRESS, WH_PasswordRead_G, PASSWORD_LENGTH);
    for(Index = 0; Index < PASSWORD_LENGTH; Index++)
    {
        if(WH_EEPROMPassword_G[Index] != WH_PasswordRead_G[Index])
        {
            WH_PasswordFlag_G = 0;
            break;
        }
    }
    if(WH_PasswordFlag_G)
    {
        WH_TargetTemp_G = EEPROM_Read(EEPROM_DATA_ADDRESS);
    }else
    {
        EEPROM_WritePage(EEPROM_PASSWORD_ADDRESS, WH_EEPROMPassword_G, PASSWORD_LENGTH);
        Delay_ms(10);
        EEPROM_Write(EEPROM_DATA_ADDRESS, WH_TargetTemp_G);
    }
}

void WH_Task(void)
{
    switch(WH_State_G)
    {
        case OffMode:
            WH_OffMode();
            break;
        case OperationMode:
            WH_OperationMode();
            break;
        case NormalMode:
            WH_NormalMode();
            break;
        case TempSetMode:
            WH_TempSetMode();
            break;
        case ResetMode:
            WH_ResetMode();
            EEPROM_Write(EEPROM_DATA_ADDRESS, WH_TargetTemp_G);
            break;
    }
}

void WH_OffMode(void)
{
    if(SW_GetState(SW0))
    {
        DISP_SetState(DISP0_STATE, DISP_ON);
        DISP_SetState(DISP1_STATE, DISP_ON);
        WH_State_G = OperationMode;
    }
}

void WH_OperationMode(void)
{
    WH_AvgTemp_G = TEMP_GetAverage();
    if(WH_AvgTemp_G <= (WH_TargetTemp_G - 5))
    {
        HCU_SetState(HU, HCU_ON);
        HCU_SetState(CU, HCU_OFF);
        DISP_SetState(DISP0_BLINK, DISP_ON);
    }else if(WH_AvgTemp_G >= (WH_TargetTemp_G + 5))
    {
        HCU_SetState(HU, HCU_OFF);
        HCU_SetState(CU, HCU_ON);
        DISP_SetState(DISP0_BLINK, DISP_OFF);
    }
    if(WH_PreState_G == TempSetMode)
    {
        WH_State_G = TempSetMode;
    }else
    {
        WH_State_G = NormalMode;
    }
}

void WH_NormalMode(void)
{
    WH_PreState_G = WH_State_G;
    SSD_SetSymbol(SSD0, WH_AvgTemp_G%10);
    SSD_SetSymbol(SSD1, (WH_AvgTemp_G/10)%10);
    if(SW_GetState(SW2) || SW_GetState(SW1))
    {
        WH_State_G = TempSetMode;
    }else if((SW_GetState(SW0)))
    {
        WH_State_G = ResetMode;
    }else
    {
        WH_State_G = OperationMode;
    }
}

void WH_TempSetMode(void)
{
    WH_PreState_G = WH_State_G;
    DISP_SetState(DISP1_BLINK, DISP_ON);
    SSD_SetSymbol(SSD0, WH_TargetTemp_G%10);
    SSD_SetSymbol(SSD1, (WH_TargetTemp_G/10)%10);
    if(SW_GetState(SW2) && WH_TargetTemp_G <= 70)
    {
        WH_TargetTemp_G += 5;
        WH_Counter_G = 0;
    }
    if(SW_GetState(SW1) && WH_TargetTemp_G >= 40)
    {
        WH_TargetTemp_G -= 5;
        WH_Counter_G = 0;
    }
    if(SW_GetState(SW0))
    {
        WH_State_G = ResetMode;
    }else
    {
        WH_State_G = OperationMode;
    }
    if(WH_Counter_G++ >= 5000/(WH_UPDATE*2))
    {
        WH_Counter_G = 0;
        DISP_SetState(DISP1_BLINK, DISP_OFF);
        EEPROM_Write(EEPROM_DATA_ADDRESS, WH_TargetTemp_G);
        WH_State_G = NormalMode;
    }
}

void WH_ResetMode(void)
{
    HCU_SetState(HU, HCU_OFF);
    HCU_SetState(CU, HCU_OFF);
    DISP_SetState(DISP0_STATE, DISP_OFF);
    DISP_SetState(DISP0_BLINK, DISP_OFF);
    DISP_SetState(DISP1_STATE, DISP_OFF);
    DISP_SetState(DISP1_BLINK, DISP_OFF);
    WH_State_G = OffMode;
}
