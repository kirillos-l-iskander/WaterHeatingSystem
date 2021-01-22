#ifndef I2C_H
#define	I2C_H

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

void I2C_Master_Init(const uint32_t BaudRate);
void I2C_Master_Wait(void);
void I2C_Master_Start(void);
void I2C_Master_RepeatedStart(void);
void I2C_Master_Stop(void);
void I2C_ACK(void);
void I2C_NACK(void);
uint8_t I2C_Master_Write(uint8_t Data);
uint8_t I2C_Read(void);

#endif	/* I2C_H */
