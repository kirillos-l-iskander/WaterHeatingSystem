#ifndef PORT_H
#define	PORT_H

//I2C---------------------
#define I2C_REG (GPIOC)
#define SCL (3)
#define SDA (4)
//I2C---------------------

//SW---------------------
#define SW_REG (GPIOB)
#define SW0 (0)
#define SW1 (1)
#define SW2 (2)
//SW---------------------

//LED---------------------
#define LED_REG (GPIOB)
#define LED0 (7)
#define LED1 (6)
//LED---------------------

//SSD---------------------
#define SSD_DAT_REG (GPIOD)
#define D0 (0)
#define D1 (1)
#define D2 (2)
#define D3 (3)
#define D4 (4)
#define D5 (5)
#define D6 (6)
#define D7 (7)

#define SSD_ENA_REG (GPIOA)
#define SSD0 (5)
#define SSD1 (4)
#define SSD2 (3)
#define SSD3 (2)
//SSD---------------------

//HCU---------------------
#define HCU_REG (GPIOC)
#define HU (5)
#define CU (2)
//HCU---------------------

#endif	/* PORT_H */
