/** Contains important gpio base addresses and offsets 
 * System Control
 * GPIO
 * NVIC
 * Timer
*/

#include <stdint.h>

typedef volatile uint32_t *     Reg;

/* ------------------------ System Control ----------------------- */
/* Table 5-7 System Control Register Map */
#define SYSCTL 0x400FE000       // System Control Base Address
#define RCGCTIMER 0x604         // TImer Clock
#define RCGCGPIO 0x608          // GPIO Clock
/* ------------------------ System Control ----------------------- */

/* -------------------------- GPIO Ports -------------------------- */
#define PortA 0x40004000	
#define PortB 0x40005000
#define PortC 0x40006000
#define PortD 0x40007000
#define PortE 0x40024000
#define PortF 0x40025000
    
#define GPIODATA 0x3fC          // GPIO Data
#define GPIODIR 0x400           // GPIO Direction
#define GPIOIS 0x404            // GPIO Interrupt Sense
#define GPIOIBE 0x408           // GPIO Interrupt Both Edges
#define GPIOIEV 0x40C           // GPIO Interrupt Even
#define GPIOIM 0x410            // GPIO Interrupt Mask
#define GPIORIS 0x414           // GPIO Raw Interrupt Status
#define GPIOMIS 0x418           // GPIO Masked Interrupt Status
#define GPIOICR 0x41C           // GPIO Interrupt Clear
#define GPIOAFSEL 0x420         // GPIO Alternate Function Select
#define GPIODR2R 0x500          // GPIO 2-mA Drive Select
#define GPIODR4R 0x504          // GPIO 4-mA Drive Select
#define GPIODR8R 0x508          // GPIO 8-mA Drive Select
#define GPIOODR 0x50C           // GPIO Open Drain Select
#define GPIOPUR 0x510           // GPIO Pull-Up Select
#define GPIOPDR 0x514           // GPIO Pull-Down Select
#define GPIOSLR 0x518           // GPIO Slew Rate Control Select
#define GPIODEN 0x51C           // GPIO Digital Enable
#define GPIOLOCK 0x520          // GPIO Lock
#define GPIOCR 0x524            // GPIO Commit
#define GPIOAMSEL 0x528         // GPIO Analog Mode Select
#define GPIOPCTL 0x52C          // GPIO Port Control
#define GPIOADCCTL 0x530        // GPIO ADC Control
#define GPIODMACTL 0x534        // GPIO DMA Control
#define GPIOPeriphlD4 0xFD0     // GPIO Peripheral Identification 4
#define GPIOPeriphlD5 0xFD4     // GPIO Peripheral Identification 5
#define GPIOPeriphlD6 0xFD8     // GPIO Peripheral Identification 6
#define GPIOPeriphlD7 0xFDC     // GPIO Peripheral Identification 7
#define GPIOPeriphlD0 0xFE0     // GPIO Peripheral Identification 0
#define GPIOPeriphlD1 0xFE4     // GPIO Peripheral Identification 1
#define GPIOPeriphlD2 0xFE8     // GPIO Peripheral Identification 2
#define GPIOPeriphlD3 0xFEC     // GPIO Peripheral Identification 3
#define GPIOPCellID0 0xFF0      // GPIO PrimeCell Identification 0
#define GPIOCellID1 0xFF4       // GPIO PrimeCell Identification 1
#define GPIOCellID2 0xFF8       // GPIO PrimeCell Identification 2
#define GPIOCellID3 0xFFC       // GPIO PrimeCell Identification 3
/* -------------------------- GPIO Ports -------------------------- */

/* ----------------------------- NVIC ----------------------------- */
#define Interrupt 0xE000E000    // Base address for interrupts
#define EN0 0x100               // NVIC EN0 bits 0-31 used for ports 

/* Table 2-9 */
#define InterruptA (1<<0)       // Interrupt EN0 bit for Port A
#define InterruptB (1<<1)       // Interrupt EN0 bit for Port B
#define InterruptC (1<<2)       // Interrupt EN0 bit for Port C
#define InterruptD (1<<3)       // Interrupt EN0 bit for Port D
#define InterruptE (1<<4)       // Interrupt EN0 bit for Port E
#define InterruptT0A (1<<19)    // Interrupt EN0 bit for T0 A
#define InterruptT0B (1<<20)    // Interrupt EN0 bit for T0 B
#define InterruptT1A (1<<21)    // Interrupt EN0 bit for T1 A
#define InterruptT1B (1>>22)    // Interrupt EN0 bit for T1 B
#define InterruptT2A (1<<23)    // Interrupt EN0 bit for T2 A
#define InterruptT2B (1>>24)    // Interrupt EN0 bit for T2 B
#define InterruptF (1<<30)      // Interrupt EN0 bit for Port F
/* ----------------------------- NVIC ----------------------------- */

/* ----------------------------- Timer ---------------------------- */
/* Timer information 11.5-11.6 */
#define Timer0 0x40030000       // T0 Base
#define Timer1 0x40031000       // T1 Base
#define Timer2 0x40032000       // T2 Base
#define Timer3 0x40033000       // T3 Base
#define Timer4 0x40034000       // T4 Base
#define Timer5 0x40035000       // T5 Base

/* Timer offsets */
#define GPTMCFG 0x000
#define GPTMTAMR 0x004
#define GPTMTBMR 0x008
#define GPTMCTL 0x00C
#define GPTMSYNC 0x010
#define GPTMIMR 0x018
#define GPTMRIS 0x01C
#define GPTMMIS 0x020
#define GPTMICR 0x024
#define GPTMTAILR 0x028
#define GPTMTBILR 0x02C
#define GPTMTAMATCHR 0x030
#define GPTMTBMATCHR 0x034
#define GPTMTAPR 0x038
#define GPTMTBPR 0x03C
#define GPTMTAPMR 0x040
#define GPTMTBPMR 0x044
#define GPTMTAR 0x048
#define GPTMTBR 0x04C
#define GPTMTAV 0x050
#define GPTMTBV 0x054
#define GPTMRTCPD 0x058
#define GPTMTAPS 0x05C
#define GPTMTBPS 0x060
#define GPTMTAPV 0x064
#define GPTMTBPV 0x068
#define GPTMPP 0xFc0
/* ----------------------------- Timer ---------------------------- */

