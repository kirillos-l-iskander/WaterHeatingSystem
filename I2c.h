#ifndef I2C_H
#define	I2C_H

#include "SchedulerConfig.h"
#include "Gpio.h"

typedef enum
{
	I2C0_ID
}I2C_t;

void I2c_initMaster( uint32_t baudrate );
void I2c_waitMaster( void );
void I2c_startMaster( void );
void I2c_repeatedStartMaster( void );
void I2c_stopMaster( void );
void I2c_ack( void );
void I2c_nack( void );
uint8_t I2c_writeMaster( uint8_t buffer );
uint8_t I2c_read( void );

#endif	/* I2C_H */
