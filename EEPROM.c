#include "EEPROM.h"
#include "I2C.h"

#define EEPROM_Address_W 0xA0
#define EEPROM_Address_R 0xA1

void EEPROM_Init(void)
{
    I2C_Master_Init(100000);
}

void EEPROM_Write(uint8_t Address, uint8_t Data)
{
    I2C_Master_Start();
    //Wait Until EEPROM Is IDLE
    while(I2C_Master_Write(EEPROM_Address_W))
        I2C_Master_RepeatedStart();
    I2C_Master_Write(Address);
    I2C_Master_Write(Data);
    I2C_Master_Stop();
}

void EEPROM_WritePage(uint8_t Address, uint8_t* Data_P, uint8_t Length)
{
    I2C_Master_Start();
    //Wait Until EEPROM Is IDLE
    while(I2C_Master_Write(EEPROM_Address_W))
        I2C_Master_RepeatedStart();
    I2C_Master_Write(Address);
    for(unsigned int i=0; i<Length; i++)
        I2C_Master_Write(Data_P[i]);
    I2C_Master_Stop();
}

uint8_t EEPROM_Read(uint8_t Address)
{
    uint8_t Data;
    I2C_Master_Start();
    //Wait Until EEPROM Is IDLE
    while(I2C_Master_Write(EEPROM_Address_W))
        I2C_Master_RepeatedStart();
    I2C_Master_Write(Address);
    I2C_Master_Start();
    I2C_Master_Write(EEPROM_Address_R);
    Data = I2C_Read();
    I2C_NACK();
    I2C_Master_Stop();
    return Data;
}

void EEPROM_ReadPage(uint8_t Address, uint8_t* Data_P, uint8_t Length)
{
    I2C_Master_Start();
    //Wait Until EEPROM Is IDLE
    while(I2C_Master_Write(EEPROM_Address_W))
        I2C_Master_RepeatedStart();
    I2C_Master_Write(Address);
    I2C_Master_Start();
    I2C_Master_Write(EEPROM_Address_R);
    for(unsigned int i=0; i<Length; i++)
    {
        Data_P[i] = I2C_Read();
        I2C_ACK();
    }
    I2C_Master_Stop();
}
