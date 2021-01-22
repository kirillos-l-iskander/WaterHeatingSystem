#include "I2C.h"

void I2C_Master_Init(const uint32_t BaudRate)
{
    SSPSTAT = 0;
    SSPCON = SSPCON | (0x28);
    SSPCON2 = 0;
    SSPADD = ((CPU_F/CPU_INSTRUCTION)/BaudRate)-1;
    GPIO_InitPin(I2C_REG, SDA, INPUT);
    GPIO_InitPin(I2C_REG, SCL, INPUT);
}

void I2C_Master_Wait(void)
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_Start(void)
{
    I2C_Master_Wait();
    SSPCON2 = SSPCON2 | (0x01);
}

void I2C_Master_RepeatedStart(void)
{
    I2C_Master_Wait();
    SSPCON2 = SSPCON2 | (0x02);
}

void I2C_Master_Stop(void)
{
    I2C_Master_Wait();
    SSPCON2 = SSPCON2 | (0x04); 
}

uint8_t I2C_Master_Write(uint8_t Data)
{
    I2C_Master_Wait();
    SSPBUF = Data;
    while(!(PIR1 & 0x08));
    PIR1 = PIR1 & (~0x08);
    return (SSPCON2 & 0x40);
}

uint8_t I2C_Read(void)
{
    I2C_Master_Wait();
    SSPCON2 = SSPCON2 | (0x08);
    while(!(PIR1 & 0x08));
    PIR1 = PIR1 & (~0x08);
    I2C_Master_Wait();
    return SSPBUF;
}

void I2C_ACK(void)
{
    SSPCON2 = SSPCON2 & (~0x20);
    I2C_Master_Wait();
    SSPCON2 = SSPCON2 | (0x10);
}

void I2C_NACK(void)
{
    SSPCON2 = SSPCON2 | (0x20);
    I2C_Master_Wait();
    SSPCON2 = SSPCON2 | (0x10);
}
