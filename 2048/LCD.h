#include "gpio.h"
#define RS 1    // BIT0 mask for reg select
#define EN 2    // BIT1 mask for E

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x28
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE    0x10
#define LCD_4BITMODE    0x00
#define LCD_JAPANESE    0x00
#define LCD_EUROPEAN_I  0x01
#define LCD_RUSSIAN     0x02
#define LCD_EUROPEAN_II 0x03

void LCD_init(void);
void LCD_setCursor(uint8_t col, uint8_t row);
void LCD_print(char *str);
void LCD_clear(void);
void LCD_home(void);
void LCD_enable(void);
void LCD_disable(void);
void PORTS_init(void);
void LCD_nibble_write(char data, unsigned char control);
void LCD_command(unsigned char command);
void LCD_data(char data);
void delayMs(int n);
