#include "LCD.h"
#include "gpio.h"

// initialize LCD controller
void LCD_init(void) {
    PORTS_init();

    delayMs(20);                // LCD controller reset sequence
    LCD_nibble_write(0x30, 0);
    delayMs(5);
    LCD_nibble_write(0x30, 0);
    delayMs(1);
    LCD_nibble_write(0x30, 0);
    delayMs(1);

    LCD_nibble_write(0x20, 0);      // use 4-bit data mode
    delayMs(1);
    LCD_command(LCD_FUNCTIONSET);   // set 4-bit data, 2-line, 5x7 font
    LCD_command(0x06);              // Set Entry
    LCD_command(LCD_CLEARDISPLAY);  // clear screen, move cursor to home
    LCD_command(LCD_DISPLAYCONTROL | LCD_DISPLAYON); //LCD on, no blink
}

/* PA2-PA5 for LCD D4-D7, respectively. 
 * PE0 for LCD R/S
 * PC6 for LCD EN
 */
void PORTS_init(void) {
    (*((volatile uint32_t *)(SYSCTL+RCGCGPIO))) |= 0x1D;    // enable ports

    // PORTA 5-2 LCD D7-D4
    (*((volatile uint32_t *)(PortA+GPIOAMSEL))) &= ~0x3C;   // turn off analog of PORTA 5-2
    (*((volatile uint32_t *)(PortA+GPIODATA))) &= ~0x3C;    // PORTA 5-2 output low
    (*((volatile uint32_t *)(PortA+GPIODIR))) |= 0x3C;      // PORTA 5-2 as GPIO output pins
    (*((volatile uint32_t *)(PortA+GPIODEN))) |= 0x3C;      // PORTA 5-2 as digital pins
    
    
    // PORTE 0 for LCD R/S
    (*((volatile uint32_t *)(PortE+GPIOAMSEL))) &= ~0x01;   // disable analog
    (*((volatile uint32_t *)(PortE+GPIODIR))) |= 0x01;      // set PORTE 0 as output for CS
    (*((volatile uint32_t *)(PortE+GPIODEN))) |= 0x01;      // set PORTE 0 as digital pins
    (*((volatile uint32_t *)(PortE+GPIODATA))) |= 0x01;     // set PORTE 0 idle high

    // PORTC 6 for LCD EN
    (*((volatile uint32_t *)(PortC+GPIOAMSEL))) &= ~0x40;   // disable analog
    (*((volatile uint32_t *)(PortC+GPIODIR))) |= 0x40;      // set PORTC 6 as output for CS
    (*((volatile uint32_t *)(PortC+GPIODEN))) |= 0x40;      // set PORTC 6 as digital pins
    (*((volatile uint32_t *)(PortC+GPIODATA))) &= ~0x40;   // set PORTC 6 idle low

    (*((volatile uint32_t *)(PortD+GPIOAMSEL))) &= ~0x80;   // disable analog
    (*((volatile uint32_t *)(PortD+GPIODIR))) |= 0x80;      // set PORTD 7 as output for CS
    (*((volatile uint32_t *)(PortD+GPIODEN))) |= 0x80;      // set PORTD 7 as digital pins
    (*((volatile uint32_t *)(PortD+GPIODATA))) |= 0x80;     // set PORTD 7 idle high
}

void LCD_nibble_write(char data, unsigned char control) {
    /* populate data bits */
    (*((volatile uint32_t *)(PortA+GPIODIR))) |= 0x3C;                  // PORTA 5-2 as GPIO output pins
    (*((volatile uint32_t *)(PortA+GPIODATA))) &= ~0x3C;                // clear data bits
    (*((volatile uint32_t *)(PortA+GPIODATA))) |= (data & 0xF0) >> 2;   // set data bits

    /* set R/S bit */
    if (control & RS)
        (*((volatile uint32_t *)(PortE+GPIODATA))) |= 1;
    else
        (*((volatile uint32_t *)(PortE+GPIODATA))) &= ~1;
    
    /* pulse E */
    (*((volatile uint32_t *)(PortC+GPIODATA))) |= 1 << 6;
    delayMs(0);
    (*((volatile uint32_t *)(PortC+GPIODATA))) &= ~(1 << 6);
    
    (*((volatile uint32_t *)(PortA+GPIODIR))) &= ~0x3C;                 // PORTA 5-2 as GPIO input pins
}

void LCD_command(unsigned char command) {
    LCD_nibble_write(command & 0xF0, 0);    // upper nibble first
    LCD_nibble_write(command << 4, 0);      // then lower nibble

    if (command < 4)
        delayMs(2);         // command 1 and 2 needs up to 1.64ms
    else
        delayMs(1);         // all others 40 us
}

void LCD_data(char data) {
    LCD_nibble_write(data & 0xF0, RS);      // upper nibble first
    LCD_nibble_write(data << 4, RS);        // then lower nibble

    delayMs(1);
}

void LCD_setCursor(uint8_t col, uint8_t row)
{
  uint8_t row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if ( row >= 2 ) 
  {
    row = 0;  //write to first line if out off bounds
  }
  
  LCD_command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void LCD_print(char *str) {
    int i = 0;
    while(str[i] != 0){
        LCD_data(str[i]);
        i++;
    }
}

/* delay n milliseconds (50 MHz CPU clock) */
void delayMs(int n) {
    int i, j;
    for(i = 0 ; i< n; i++)
        for(j = 0; j < 6265; j++)
            {}  /* do nothing for 1 ms */
}
