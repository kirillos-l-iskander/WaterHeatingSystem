#ifndef EEPROM_H
#define	EEPROM_H

#include "SchedulerConfig.h"
#include "I2c.h"

void Eeprom_Init( void );
void Eeprom_Write( uint8_t Address, uint8_t Buffer );
void Eeprom_WritePage( uint8_t Address, uint8_t *Buffer, uint8_t Length );
uint8_t Eeprom_Read( uint8_t Address );
void Eeprom_ReadPage( uint8_t Address, uint8_t *Buffer, uint8_t Length );

#endif	/* EEPROM_H */
