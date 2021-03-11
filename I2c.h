#ifndef I2C_H
#define	I2C_H

#include "SchedulerConfig.h"
#include "Gpio.h"

void I2c_MasterInit( uint32_t BaudRate );
void I2c_MasterWait( void );
void I2c_MasterStart( void );
void I2c_MasterRepeatedStart( void );
void I2c_MasterStop( void );
void I2c_ACK( void );
void I2c_NACK( void );
uint8_t I2c_MasterWrite( uint8_t Buffer );
uint8_t I2c_Read( void );

#endif	/* I2C_H */
