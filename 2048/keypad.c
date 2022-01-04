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

#include "keypad.h"
#include "gpio.h"

int col[1];     // active column
int wait[1];    // time to wait

char keys[KEYPAD_HEIGHT][KEYPAD_WIDTH] = {  {'1', '2', '3', 'A'}, 
                                            {'4', '5', '6', 'B'},
                                            {'7', '8', '9', 'C'},
                                            {'*', '0', '#', 'D'} };

/** Initialize the keypad ports and interrupts */
void keypad_init(void){
    *col = 0;

    /* enable portA */
    *((Reg)(SYSCTL+RCGCGPIO))   |= 0x9;         //Enable Port A and D
    
    *((Reg)(PortA+GPIOAMSEL))   &= ~0x3C;       // turn off analog of GPIOA PA2-PA5
    *((Reg)(PortA+GPIODATA))    &= ~0x3C;       // PA2-PA5 output low
    *((Reg)(PortA+GPIODIR))     |= 0x3C;        // PA2-PA5 as GPIO output pins
    *((Reg)(PortA+GPIODEN))     |= 0x3C;        // PA2-PA5 as digital pins

    /* Enable portD */
    *((Reg)(PortD+GPIOAMSEL))   &= ~0xF;        // turn off analog of GPIOD PD0-PD3
    *((Reg)(PortD+GPIODATA))    &= ~0xF;        // PD0-PD3 output low
    *((Reg)(PortD+GPIODIR))     &= ~0xF;        // PD0-PD3 as GPIO input pins
    *((Reg)(PortD+GPIODEN))     |= 0xF;         // PD0-PD3 as digital pins

    /* set up portD interrupt */
    *((Reg)(Interrupt+EN0))     |= InterruptD;  // Enable GPIOD interrupt
    *((Reg)(PortD+GPIOIS))      &= ~0xF;        // Edge sensitive on Pins PD0-PD3
    *((Reg)(PortD+GPIOIBE))     &= ~0xF;        // Not rising & falling
    *((Reg)(PortD+GPIOIEV))     |= 0xF;         // Rising Edge
    *((Reg)(PortD+GPIOIM))      |= 0xF;         // Enable Interrupt 

    /* Enable Timer1 A Interrupt to scroll through columns */
    *((Reg)(SYSCTL+RCGCTIMER))  |= 0x2;         // Enable T1
    *((Reg)(Timer1+GPTMCTL))    &= ~0x1;        // Disable timer T1 TAEN
    *((Reg)(Timer1+GPTMCFG))    &= ~0x7;        // 32 bit mode
    *((Reg)(Timer1+GPTMTAMR))   |= 0x2;         // Periodic mode
    // *((Reg)(Timer1+GPTMTAILR))  &= 0x27100;     // interrupt every 10ms
    *((Reg)(Timer1+GPTMTAILR))  &= 0x3E80;      // interrupt every 1ms
    *((Reg)(Timer1+GPTMIMR))    |= 0x1;         // 32 bit mode
    *((Reg)(Interrupt+EN0))     |= InterruptT1A;// Enable T1 A timer interrupt
    *((Reg)(Timer1+GPTMCTL))    |= 0x1;         // Enable timer T1 TAEN
}

/** Determines which key was pressed on the keypad */
char keypad_read(){
    char check = *((Reg)(PortD+GPIODATA));
    int i = 0;
    while(i<KEYPAD_HEIGHT){
        if((check & 0xF) == (1<<i)){
            wait[0] = KEYPAD_WAIT;
            return keys[i][*col];
        }
        i++;
    }
    return 0;
}

/** Used to check if the keypad should be read from 
     @returns true or false              
*/
int keypad_wait(){
    return wait[0] == 0;
}

/** Clear the keypad interrupt */
void keypad_clear_interrupt(){
    *((Reg)(PortD+GPIOICR))  |= 0xF;   // clear interrupt GPIOD PD0-PD3
}

/** Scans the keypad columns */
void keypad_Time_Handler(void){
    *((Reg)(Timer1+GPTMICR)) |= 0x1;  // Clear interrupt
    col[0]++;
    col[0] %= 4;
    wait[0] -= wait[0] > 0;
    *((Reg)(PortA+GPIODIR))     |= 0x3C;        // PA2-PA5 as GPIO output pins
    *((Reg)(PortA+GPIODATA)) &= ~0x3C;          // PA2-PA5 output low
    *((Reg)(PortA+GPIODATA)) |= (1<<(col[0]+2));// col high
}
