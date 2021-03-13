/*
 * Configuration bits setting
 */

#ifndef CONFIG_H
#define CONFIG_H

// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "SchedulerConfig.h"

#define _XTAL_FREQ ( 16000000 )

#define GIE() ei()
#define GID() di()

typedef uint8_t                     Id_t;
#define SWITCH_NUMBER               ( 3 )
#define TEMP_SENSOR_NUMBER          ( 1 )
#define TEMP_CONTROL_NUMBER         ( 1 )
#define LED_NUMBER                  ( 2 )
#define SSD_NUMBER                  ( 2 )
#define HEATER_NUMBER               ( 1 )

#define EEPROM_PASSWORD_ADDRESS 0
#define PASSWORD_LENGTH 8
#define EEPROM_DATA_ADDRESS 8

//I2C---------------------
#define I2C_REG ( GPIOC_ID )
#define SCL ( 3 )
#define SDA ( 4 )
//I2C---------------------

//SW---------------------
#define SW_REG ( GPIOB_ID )
#define SW0 ( 0 )
#define SW1 ( 1 )
#define SW2 ( 2 )
//SW---------------------

//LED---------------------
#define LED_REG ( GPIOB_ID )
#define LED0 ( 7 )
#define LED1 ( 6 )
//LED---------------------

//SSD---------------------
#define SSD_DAT_REG ( GPIOD_ID )
#define D0 ( 0 )
#define D1 ( 1 )
#define D2 ( 2 )
#define D3 ( 3 )
#define D4 ( 4 )
#define D5 ( 5 )
#define D6 ( 6 )
#define D7 ( 7 )

#define SSD_ENA_REG ( GPIOA_ID )
#define SSD0 ( 5 )
#define SSD1 ( 4 )
#define SSD2 ( 3 )
#define SSD3 ( 2 )
//SSD---------------------

//HCU---------------------
#define HCU_REG ( GPIOC_ID )
#define HU ( 5 )
#define CU ( 2 )
//HCU---------------------

#endif /* CONFIG_H */
