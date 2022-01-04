/** Contains keypad related functions
 *  keypad interrupt name: Keypad_Handler
 *  Interrupt steps:
 *                  check keypad_wait()
 *                      if false -  keypad_clear_interrupt()
 *                                  exit
 *                  get char keypad_read
 *                  (operations)
 *                  keypad_clear_interrupt()
*/

#define KEYPAD_WIDTH 4
#define KEYPAD_HEIGHT 4

#define KEYPAD_WAIT 500
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
int keypad_waiting();
void keypad_clear_interrupt();
void keypad_Time_Handler(void);
