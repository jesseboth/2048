/* Initialize LCD controller and flash "HELLO" on the LCD.
 *
 * The connections between the LCD controller of EduPad 
 * board and the Tiva LaunchPad are
 * 
 * PA2-PA5 for LCD D4-D7, respectively. 
 * PE0 for LCD R/S
 * PC6 for LCD EN
 *
 * For simplicity, all delay below 1 ms uses 1 ms.
 *
 * Built and tested with Keil MDK-ARM v5.24a and TM4C_DFP v1.1.0
 */


#define RS 1    // BIT0 mask for reg select
#define EN 2    // BIT1 mask for E

void delayMs(int n);
void LCD_nibble_write(char data, unsigned char control);
void LCD_command(unsigned char command);
void LCD_data(char data);
void LCD_init(void);
void PORTS_init(void);