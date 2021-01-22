#ifndef EEPROM_H
#define	EEPROM_H

#include "CONFIG.h"
#include "PORT.h"
#include "SCH_CONFIG.h"
#include "SCH.h"
#include "TIM.h"
#include "GPIO.h"
#include "LED.h"

#include "SW.h"
#include "ADC.h"
#include "TEMP.h"
#include "HCU.h"
#include "SSD.h"
#include "DISP.h"
#include "I2C.h"
#include "EEPROM.h"
#include "WH.h"

void EEPROM_Init(void);
void EEPROM_Write(uint8_t Address, uint8_t Data);
void EEPROM_WritePage(uint8_t Address, uint8_t* Data_P, uint8_t Length);
uint8_t EEPROM_Read(uint8_t Address);
void EEPROM_ReadPage(uint8_t Address, uint8_t* Data_P, uint8_t Length);

#endif	/* EEPROM_H */
