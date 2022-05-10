#include "Prototype.h"

// LCD initialization funcion
// 4-bits mode - Port B

void LCDinit(void)
{
    SYSCTL_RCGCGPIO_R |= 0x02; // enable clock to Port B
    while ((SYSCTL_PRGPIO_R & 0x02) == 0)
    {
    } // wait until port is activated

    GPIO_PORTB_DIR_R = 0xFF; // set all port B pins as output
    GPIO_PORTB_DEN_R = 0xFF; // set all port B pins as digital

    /*Initialization Sequence (test if needed)*/
    delayms(20);
    LCDnibblewrite(Wakeup, 0);
    delayms(5);
    LCDnibblewrite(Wakeup, 0);
    delayus(100);
    LCDnibblewrite(Wakeup, 0);
    delayus(40);

    LCDnibblewrite(fourbit, 0); // use 4-bit data mode
    // only instruction that can be sent in one write

    delayus(40);
    LCDcommand(fourbittwoline); // set 4-bit data, 2-line, 5x7 font
    LCDcommand(shiftright);     // move cursor right
    LCDcommand(Clear);
    LCDcommand(blink);
}