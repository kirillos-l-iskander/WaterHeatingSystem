#ifndef EEPROM_H
#define	EEPROM_H

#include "Config.h"
#include "I2c.h"

typedef enum
{
	EEPROM0_ID
}EEPROM_t;

void Eeprom_init( void );
void Eeprom_write( uint8_t address, uint8_t buffer );
void Eeprom_writePage( uint8_t address, uint8_t *buffer, uint8_t length );
uint8_t Eeprom_read( uint8_t address );
void Eeprom_readPage( uint8_t address, uint8_t *buffer, uint8_t length );

#endif	/* EEPROM_H */
