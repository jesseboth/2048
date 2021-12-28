//TODO: Table 5-7 System Control Register Map

#define SYSCTL 0x400FE000   // System Control Base Address
#define RCGCGPIO 0x608      // Clock

#define PortA 0x40004000	
#define PortB 0x40005000
#define PortC 0x40006000
#define PortD 0x40007000
#define PortE 0x40024000
#define PortF 0x40025000

#define GPIODATA 0x3fC      // GPIO Data
#define GPIODIR 0x400       // GPIO Direction
#define GPIOIS 0x404        // GPIO Interrupt Sense
#define GPIOIBE 0x408       // GPIO Interrupt Both Edges
#define GPIOIEV 0x40C       // GPIO Interrupt Even
#define GPIOIM 0x410        // GPIO Interrupt Mask
#define GPIORIS 0x414       // GPIO Raw Interrupt Status
#define GPIOMIS 0x418       // GPIO Masked Interrupt Status
#define GPIOICR 0x41C       // GPIO Interrupt Clear
#define GPIOAFSEL 0x420     // GPIO Alternate Function Select
#define GPIODR2R 0x500      // GPIO 2-mA Drive Select
#define GPIODR4R 0x504      // GPIO 4-mA Drive Select
#define GPIODR8R 0x508      // GPIO 8-mA Drive Select
#define GPIOODR 0x50C       // GPIO Open Drain Select
#define GPIOPUR 0x510       // GPIO Pull-Up Select
#define GPIOPDR 0x514       // GPIO Pull-Down Select
#define GPIOSLR 0x518       // GPIO Slew Rate Control Select
#define GPIODEN 0x51C       // GPIO Digital Enable
#define GPIOLOCK 0x520      // GPIO Lock
#define GPIOCR 0x524        // GPIO Commit
#define GPIOAMSEL 0x528     // GPIO Analog Mode Select
#define GPIOPCTL 0x52C      // GPIO Port Control
#define GPIOADCCTL 0x530    // GPIO ADC Control
#define GPIODMACTL 0x534    // GPIO DMA Control
#define GPIOPeriphlD4 0xFD0 // GPIO Peripheral Identification 4
#define GPIOPeriphlD5 0xFD4 // GPIO Peripheral Identification 5
#define GPIOPeriphlD6 0xFD8 // GPIO Peripheral Identification 6
#define GPIOPeriphlD7 0xFDC // GPIO Peripheral Identification 7
#define GPIOPeriphlD0 0xFE0 // GPIO Peripheral Identification 0
#define GPIOPeriphlD1 0xFE4 // GPIO Peripheral Identification 1
#define GPIOPeriphlD2 0xFE8 // GPIO Peripheral Identification 2
#define GPIOPeriphlD3 0xFEC // GPIO Peripheral Identification 3
#define GPIOPCellID0 0xFF0  // GPIO PrimeCell Identification 0
#define GPIOCellID1 0xFF4   // GPIO PrimeCell Identification 1
#define GPIOCellID2 0xFF8   // GPIO PrimeCell Identification 2
#define GPIOCellID3 0xFFC   // GPIO PrimeCell Identification 3