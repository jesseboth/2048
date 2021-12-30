

/**
 * main.c
 */
#include "LCD.h"
extern void output_string(char *str);
extern void start(void);
extern void init(void);

int main(void) {
	init();
	LCD_init();


	LCD_setCursor(0, 0);
	LCD_print((char *)"Time: 00:00");
	LCD_setCursor(0, 1);
	LCD_print((char *)"Score: 0");

	start();


	// output_string((char *)"DONE\n\r");
	return 0;
}
