#include "I2c.h"

void I2c_MasterInit( uint32_t BaudRate )
{
    SSPSTAT = 0;
    SSPCON = SSPCON | 0x28;
    SSPCON2 = 0;
    SSPADD = ( ( SCH_CPU_F / SCH_CPU_INSTRUCTION ) / BaudRate ) - 1;
}

void I2c_MasterWait( void )
{
    while ( ( SSPSTAT & 0x04 ) || ( SSPCON2 & 0x1F ) );
}

void I2c_MasterStart( void )
{
    I2c_MasterWait();
    SSPCON2 = SSPCON2 | 0x01;
}

void I2c_MasterRepeatedStart( void )
{
    I2c_MasterWait();
    SSPCON2 = SSPCON2 | 0x02;
}

void I2c_MasterStop( void )
{
    I2c_MasterWait();
    SSPCON2 = SSPCON2 | 0x04; 
}

uint8_t I2c_MasterWrite( uint8_t Buffer )
{
    I2c_MasterWait();
    SSPBUF = Buffer;
    while( !( PIR1 & 0x08 ) );
    PIR1 = PIR1 & ~0x08;
    return ( SSPCON2 & 0x40 );
}

uint8_t I2c_Read( void )
{
    I2c_MasterWait();
    SSPCON2 = SSPCON2 | 0x08;
    while( !( PIR1 & 0x08 ) );
    PIR1 = PIR1 & ~0x08;
    I2c_MasterWait();
    return SSPBUF;
}

void I2c_ACK( void )
{
    SSPCON2 = SSPCON2 & ~0x20;
    I2c_MasterWait();
    SSPCON2 = SSPCON2 | 0x10;
}

void I2c_NACK( void )
{
    SSPCON2 = SSPCON2 | 0x20;
    I2c_MasterWait();
    SSPCON2 = SSPCON2 | 0x10;
}
