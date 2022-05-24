
void SW_Init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x20; // PortF clock enable
    while ((SYSCTL_PRGPIO_R & 0x20) == 0)
    {

    }                                 // Delay
    GPIO_PORTF_LOCK_R = 0x4C4F434B;   // Unlock PortF Commit register
    GPIO_PORTF_CR_R |= 0x11;          // Allow changes to PF41
    GPIO_PORTF_AMSEL_R &= ~0x11;      // Disable analog function
    GPIO_PORTF_PCTL_R &= ~0x000F000F; // GPIO clear bit PCTL
    GPIO_PORTF_AFSEL_R &= ~0x011;     // No alternate function
    GPIO_PORTF_DIR_R &= ~0x11;        // PF41 input
    GPIO_PORTF_DEN_R |= 0x11;         // Enable digital for switches
    GPIO_PORTF_PUR_R |= 0x11;
    GPIO_PORTF_DATA_R |= 0x11; // this to set sw1 , sw2 as the simulate being unclicked
}

void SW3_Init(void) // IO port initialization
{
    SYSCTL_RCGCGPIO_R |= 0x1; // activate Port A clock
    while ((SYSCTL_PRGPIO_R & 0x1) == 0)
    {
        // wait until its status bit in PR register is true
    }
    GPIO_PORTA_AMSEL_R &= ~0x4;
    GPIO_PORTA_AFSEL_R &= ~0x4;
    GPIO_PORTA_PCTL_R &= ~0xF00;
    GPIO_PORTA_DIR_R &= ~0x4;
    GPIO_PORTA_DEN_R |= 0x4;
    GPIO_PORTA_PUR_R |= 0x4;
}

unsigned char get_SW3()
{
    return (GPIO_PORTA_DATA_R & 0x4);
}

unsigned char get_SW1()
{
    return GPIO_PORTF_DATA_R & 0x10;
}
unsigned char get_SW2()
{
    return GPIO_PORTF_DATA_R & 0x01;
}
