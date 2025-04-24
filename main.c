#include <lpc214x.h>

void init_pll()                  //Fosc=12Mhz,CCLK=60Mhz,PCLK=60MHz
{
    PLL0CON=0x01;
    PLL0CFG=0x24;
    PLL0FEED=0xaa;
    PLL0FEED=0x55;
    while(!(PLL0STAT&(1<<10)));
    PLL0CON=0x03;
    PLL0FEED=0xaa;
    PLL0FEED=0x55;
    VPBDIV=0x01;
}

void delay(unsigned int z)
{
    T0CTCR=0x0;                                 //Select Timer Mode
    T0TCR=0x00;                 //Timer off
    T0PR=59999;                 //Prescaler value for 1ms
    T0TCR=0x02;                 //Timer reset
    T0TCR=0x01;                 //Timer ON
			while(T0TC<z);           
    T0TCR=0x00;                 //Timer OFF
    T0TC=0;                     //Clear the TC value. This is Optional.
}

int main(void)
{
		init_pll();
    PINSEL0 &= ~(3 << 16);  // Configure P0.8 as GPIO
    IO0DIR |= (1 << 8);  // Set P0.8 as output
    
    while (1)
    {
        IO0SET = (1 << 8);  // Turn ON LED
        delay(2000);  // Delay 2s
        IO0CLR = (1 << 8);  // Turn OFF LED
        delay(2000);  // Delay 2s
    }
}

