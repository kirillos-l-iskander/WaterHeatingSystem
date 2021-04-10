#include "Eeprom.h"

#define EEPROM_Address_W 0xA0
#define EEPROM_Address_R 0xA1

void Eeprom_init( void )
{
    I2c_initMaster( 100000 );
    Gpio_initPin(GPIO_ID_C, GPIO_PIN_3, GPIO_MODE_INPUT, GPIO_TYPE_FLOATING );
    Gpio_initPin(GPIO_ID_C, GPIO_PIN_4, GPIO_MODE_INPUT, GPIO_TYPE_FLOATING );
}

void Eeprom_write( uint8_t address, uint8_t buffer )
{
    I2c_startMaster();
    //Wait Until EEPROM Is IDLE
    while( I2c_writeMaster( EEPROM_Address_W ) )
    {
        I2c_repeatedStartMaster();
    }
    I2c_writeMaster( address );
    I2c_writeMaster( buffer );
    I2c_stopMaster();
}

void Eeprom_writePage( uint8_t address, uint8_t *buffer, uint8_t length )
{
    I2c_startMaster();
    //Wait Until EEPROM Is IDLE
    while( I2c_writeMaster( EEPROM_Address_W ) )
    {
        I2c_repeatedStartMaster();
    }
    I2c_writeMaster( address );
    for( size_t i = 0; i< length; i++ )
    {
        I2c_writeMaster( buffer[ i ] );
    }
    I2c_stopMaster();
}

uint8_t Eeprom_read( uint8_t address )
{
    uint8_t buffer;
    I2c_startMaster();
    //Wait Until EEPROM Is IDLE
    while( I2c_writeMaster( EEPROM_Address_W ) )
    {
        I2c_repeatedStartMaster();
    }
    I2c_writeMaster( address );
    I2c_startMaster();
    I2c_writeMaster( EEPROM_Address_R );
    buffer = I2c_read();
    I2c_nack();
    I2c_stopMaster();
    return buffer;
}

void Eeprom_readPage( uint8_t address, uint8_t *buffer, uint8_t length )
{
    I2c_startMaster();
    //Wait Until EEPROM Is IDLE
    while( I2c_writeMaster( EEPROM_Address_W ) )
    {
        I2c_repeatedStartMaster();
    }
    I2c_writeMaster( address );
    I2c_startMaster();
    I2c_writeMaster( EEPROM_Address_R );
    for( size_t i = 0; i < length; i++ )
    {
        buffer[i] = I2c_read();
        I2c_ack();
    }
    I2c_stopMaster();
}
