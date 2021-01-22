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

#define _XTAL_FREQ (16000000)

#define GIE() ei()
#define GID() di()

//--------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------------------------------------------------------------

#define CPU_F (16000000)
#define CPU_INSTRUCTION (4)

#define SCH_MAX_TASKS (8)
#define SCH_TICK_PERIOD_MS (5)
#define SCH_SYSTICK_MAX (65536)

#ifndef TRUE
#define FALSE (0)
#define TRUE (!FALSE)
#endif

#define RETURN_ERROR (0)
#define RETURN_NORMAL (!RETURN_ERROR)

#define ERROR_SCH_TOO_MANY_TASKS (1)
#define ERROR_SCH_CANNOT_DELETE_TASK (2)

#define ERROR_SCH_WAITING_FOR_SLAVE_TO_ACK (0xAA)
#define ERROR_SCH_WAITING_FOR_START_COMMAND_FROM_MASTER (0xAA)

#define ERROR_SCH_ONE_OR_MORE_SLAVES_DID_NOT_START (0xA0)
#define ERROR_SCH_LOST_SLAVE (0x80)

//--------------------------------------------------------------------------------------------------------------------

#define _BV(n) (1<<n)
#define SET_BIT(reg,bit) (reg |= (1<<bit))
#define CLEAR_BIT(reg,bit) (reg &= ~(1<<bit))
#define TOGGLE_BIT(reg,bit) (reg ^= (1<<bit))
#define ROR(reg,bit) (reg = (reg>>bit | reg<<8-bit))
#define ROL(reg,bit) (reg = (reg<<bit | reg>>8-bit))
#define BIT_IS_SET(reg,bit) (reg & (1<<bit))
#define BIT_IS_CLEAR(reg,bit) (!(reg & (1<<bit)))

#define Delay_ms(t) SW_Delay_ms(t)
#define Delay_us(t) SW_Delay_us(t)

//--------------------------------------------------------------------------------------------------------------------

typedef signed char         int8_t;
typedef signed short        int16_t;
typedef signed long         int32_t;
typedef signed long long    int64_t;
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned long       uint32_t;
typedef unsigned long long  uint64_t;

typedef union
{
    struct
    {
        uint8_t BIT0:1;
        uint8_t BIT1:1;
        uint8_t BIT2:1;
        uint8_t BIT3:1;
        uint8_t BIT4:1;
        uint8_t BIT5:1;
        uint8_t BIT6:1;
        uint8_t BIT7:1;
    }BITS_t;
    uint8_t BYTE:8;
}REG_t;

//--------------------------------------------------------------------------------------------------------------------

#endif /* CONFIG_H */
