#include "Eeprom.h"

#define EEPROM_Address_W 0xA0
#define EEPROM_Address_R 0xA1

void Eeprom_Init( void )
{
    I2c_MasterInit( 100000 );
    Gpio_InitPin(I2C_REG, SDA, INPUT);
    Gpio_InitPin(I2C_REG, SCL, INPUT);
}

void Eeprom_Write( uint8_t Address, uint8_t Buffer )
{
    I2c_MasterStart();
    //Wait Until EEPROM Is IDLE
    while( I2c_MasterWrite( EEPROM_Address_W ) )
    {
        I2c_MasterRepeatedStart();
    }
    I2c_MasterWrite( Address );
    I2c_MasterWrite( Buffer );
    I2c_MasterStop();
}

void Eeprom_WritePage( uint8_t Address, uint8_t *Buffer, uint8_t Length )
{
    I2c_MasterStart();
    //Wait Until EEPROM Is IDLE
    while( I2c_MasterWrite( EEPROM_Address_W ) )
    {
        I2c_MasterRepeatedStart();
    }
    I2c_MasterWrite( Address );
    for( unsigned int i = 0; i< Length; i++ )
    {
        I2c_MasterWrite( Buffer[ i ] );
    }
    I2c_MasterStop();
}

uint8_t Eeprom_Read( uint8_t Address )
{
    uint8_t Buffer;
    I2c_MasterStart();
    //Wait Until EEPROM Is IDLE
    while( I2c_MasterWrite( EEPROM_Address_W ) )
    {
        I2c_MasterRepeatedStart();
    }
    I2c_MasterWrite( Address );
    I2c_MasterStart();
    I2c_MasterWrite( EEPROM_Address_R );
    Buffer = I2c_Read();
    I2c_NACK();
    I2c_MasterStop();
    return Buffer;
}

void Eeprom_ReadPage( uint8_t Address, uint8_t *Buffer, uint8_t Length )
{
    I2c_MasterStart();
    //Wait Until EEPROM Is IDLE
    while( I2c_MasterWrite( EEPROM_Address_W ) )
    {
        I2c_MasterRepeatedStart();
    }
    I2c_MasterWrite( Address );
    I2c_MasterStart();
    I2c_MasterWrite( EEPROM_Address_R );
    for( unsigned int i = 0; i < Length; i++ )
    {
        Buffer[i] = I2c_Read();
        I2c_ACK();
    }
    I2c_MasterStop();
}
