#include "TEMP.h"
#include "ADC.h"

volatile static TEMP_t TEMP_G[1];

void TEMP_Init(void)
{
    uint8_t Index = 0;
    for(Index = 0; Index < 10; Index++)
        TEMP_G[0].Array[Index] = 0;
    TEMP_G[0].Index = 0;
    TEMP_G[0].AvgFlag = 0;
}

void TEMP_Update(void)
{
    TEMP_G[0].Array[TEMP_G[0].Index++] = ADC_GetState();
    if(TEMP_G[0].Index == 10)
    {
        TEMP_G[0].Index = 0;
        TEMP_G[0].AvgFlag = 1;
    }
}

uint8_t TEMP_GetAverage(void)
{
    uint8_t Index = 0;
    uint16_t AvgTemp = 0;
    if(TEMP_G[0].AvgFlag)
    {
        for(Index = 0; Index < 10; Index++)
        {
            AvgTemp += TEMP_G[0].Array[Index];
        }
        AvgTemp /= 10;
    }
    return (uint8_t) AvgTemp;
}
