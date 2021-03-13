#include "I2c.h"

void I2c_initMaster( uint32_t baudrate )
{
    SSPSTAT = 0;
    SSPCON = SSPCON | 0x28;
    SSPCON2 = 0;
    SSPADD = ( ( SCH_CPU_F / SCH_CPU_INSTRUCTION ) / baudrate ) - 1;
}

void I2c_waitMaster( void )
{
    while ( ( SSPSTAT & 0x04 ) || ( SSPCON2 & 0x1F ) );
}

void I2c_startMaster( void )
{
    I2c_waitMaster();
    SSPCON2 = SSPCON2 | 0x01;
}

void I2c_repeatedStartMaster( void )
{
    I2c_waitMaster();
    SSPCON2 = SSPCON2 | 0x02;
}

void I2c_stopMaster( void )
{
    I2c_waitMaster();
    SSPCON2 = SSPCON2 | 0x04; 
}

uint8_t I2c_writeMaster( uint8_t buffer )
{
    I2c_waitMaster();
    SSPBUF = buffer;
    while( !( PIR1 & 0x08 ) );
    PIR1 = PIR1 & ~0x08;
    return ( SSPCON2 & 0x40 );
}

uint8_t I2c_read( void )
{
    I2c_waitMaster();
    SSPCON2 = SSPCON2 | 0x08;
    while( !( PIR1 & 0x08 ) );
    PIR1 = PIR1 & ~0x08;
    I2c_waitMaster();
    return SSPBUF;
}

void I2c_ack( void )
{
    SSPCON2 = SSPCON2 & ~0x20;
    I2c_waitMaster();
    SSPCON2 = SSPCON2 | 0x10;
}

void I2c_nack( void )
{
    SSPCON2 = SSPCON2 | 0x20;
    I2c_waitMaster();
    SSPCON2 = SSPCON2 | 0x10;
}
