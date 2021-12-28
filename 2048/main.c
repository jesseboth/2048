

/**
 * main.c
 */
#include "LCD.h"
extern void output_string(char *str);
extern void init(void);

int main(void) {
	init();


	// initialize LCD controller
	LCD_init();
	LCD_command(1);

	// Write "HELLO" on LCD
	LCD_data('H');
	LCD_data('E');
	LCD_data('L');
	LCD_data('L');
	LCD_data('O');
//	delayMs(1000);


	output_string((char *)"Did it do it?\n\r");
	return 0;
}
