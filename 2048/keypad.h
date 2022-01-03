#define KEYPAD_WIDTH 4
#define KEYPAD_HEIGHT 4

/*
    PA2 - Col_0
    PA3 - Col_1
    PA4 - Col_2
    PA5 - Col_3

    PD0 - Row_0
    PD1 - Row_1
    PD2 - Row_2
    PD3 - Row_3
*/

void keypad_init(void);
char keypad_read();
void keypad_clear_interrupt();
void keypad_Time_Handler(void);
