#include "LCDKeypad.h"

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

void LCDnibblewrite(unsigned char data, unsigned char control)
{                                       // control = 0 ? command , control = 1 ? data
    data &= 0xF0;                       // clear lower nibble for control
    control &= 0x0F;                    // clear upper nibble for data
    GPIO_PORTB_DATA_R = data | control; // R/W always = 0 , RS either 1 (data) or 0 (command)
    delayus(1);
    GPIO_PORTB_DATA_R = data | control | Enable; // Pulse E
    delayus(1);
    GPIO_PORTB_DATA_R = data; // turn off enable
    GPIO_PORTB_DATA_R = 0;    // clear data
}

void LCDcommand(uint32_t command)
{
    LCDnibblewrite(command & 0xF0, 0); // upper nibble first
    LCDnibblewrite(command << 4, 0);   // then lower nibble

    if (command < 4)
    { // command 1 and 2 needs upto 1.64ms rest needs 40us
        delayms(2);
    }
    else
    {
        delayus(40);
    }
}

void LCDdata(unsigned char data)
{
    LCDnibblewrite(data & 0xF0, RS); // upper nibble
    LCDnibblewrite(data << 4, RS);   // then lower nibble
    delayus(40);
}

void SysTick_Init(void)
{
    NVIC_ST_CTRL_R = 0;          // 1) disable SysTick during setup until initialization
    NVIC_ST_RELOAD_R = 0xFFFFFF; // 2) maximum reload value
    NVIC_ST_CURRENT_R = 0;       // 3) any write to CURRENT clears it
    NVIC_ST_CTRL_R = 0x5;        // 4) enable SysTick with core clock ENABLE=1, CLK_SRC=1
}

// this delay function parameter is in units of core clock 16MHz (62.5 ns)
void SysTick_Wait(uint32_t delay)
{
    NVIC_ST_RELOAD_R = delay - 1; // number of counts (1 unit = 62.5 ns)
    NVIC_ST_CURRENT_R = 0;        // clear any value written to CURRENT
    while ((NVIC_ST_CTRL_R & 0x00010000) == 0)
    { // wait for the COUNT flag 16th bit
    }
}

void delayms(int n)
{
    SysTick_Init();
    for (int i = 0; i < n; i++)
    {
        SysTick_Wait(16000); // wait 1 ms
    }
    NVIC_ST_CTRL_R = 0; // disable systic timer
}

void delayus(int n)
{
    SysTick_Init();
    for (int i = 0; i < n; i++)
    {
        SysTick_Wait(16); // wait 1 us
    }
    NVIC_ST_CTRL_R = 0; // disable systick timer
}

void LCDstring(unsigned char *str) // passing pointer to the first character of a string literal
{
    // cannot be altered
    int len = strlen(str);
    for (char i = 0; i < len; i++)
    {
        LCDdata(str[i]);
    }
}

void LCDcus(char custom)
{
    char popcorn[] = {
        0x15,
        0x0A,
        0x15,
        0x0A,
        0x0E,
        0x0E,
        0x0E,
        0x0E};
    char heart[] = {
        0x00,
        0x00,
        0x1B,
        0x1B,
        0x1F,
        0x0E,
        0x0E,
        0x04};

    char chicken[] = {
        0x04,
        0x0E,
        0x1F,
        0x1F,
        0x0E,
        0x04,
        0x04,
        0x0E};

    char beef[] = {
        0x04,
        0x0E,
        0x1B,
        0x1F,
        0x1F,
        0x1F,
        0x0E,
        0x04};

    char clock[] = {
        0x0E,
        0x11,
        0x15,
        0x15,
        0x17,
        0x11,
        0x11,
        0x0E};

    char error[] = {
        0x0E,
        0x0E,
        0x0E,
        0x0E,
        0x0E,
        0x00,
        0x0E,
        0x0E};
    char sandtimer[] = {
        0x1F,
        0x11,
        0x11,
        0x0A,
        0x04,
        0x0A,
        0x15,
        0x1F};
    char alarm[] = {
        0x04,
        0x0E,
        0x0E,
        0x0E,
        0x1F,
        0x00,
        0x04,
        0x00};
    switch (custom)
    {
    case 'A':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(heart[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;

    case 'B':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(popcorn[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;

    case 'C':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(chicken[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;

    case 'D':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(beef[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;

    case 'E':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(clock[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;

    case 'F':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(error[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;

    case 'G':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(sandtimer[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;

    case 'H':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(alarm[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;
    }
}

void LCDpos(uint8_t row, uint8_t col)
{
    if (row == 0)
        LCDcommand(0x80 + col);
    else
        LCDcommand(0xC0 + col);
}

void keypadinit(void) // row port E , column port C
{
    SYSCTL_RCGCGPIO_R |= 0x14; // enable clock of port E, C
    while ((SYSCTL_PRGPIO_R & 0x14) == 0)
    {
    } // wait until port is activated

    GPIO_PORTE_DIR_R |= 0x1E; // set row pins 1-4 as output
    GPIO_PORTE_DEN_R |= 0x1E; // set row pins 1-4 as digital
    GPIO_PORTE_ODR_R |= 0x1E; // set row pins 1-4 as open drain

    GPIO_PORTC_DIR_R &= ~0xF0; // set column pins 7-4 as input
    GPIO_PORTC_DEN_R |= 0xF0;  // set column pins 7-4 as digital
    GPIO_PORTC_PUR_R |= 0xF0;  // enable pull up resistors for pins 7-4
}

unsigned char keypress(void) // test
{                            // if a key is pressed it returns true otherwise it returns false
    int col;
    // check if a key is pressed
    GPIO_PORTE_DATA_R = 0;          // enable all rows
    col = GPIO_PORTC_DATA_R & 0xF0; // read all columns
    if (col == 0xF0)
    {
        return 0; // not pressed
    }
    else
    {
        return 1; // pressed
    }
}

unsigned char getkey(void)
{
    const unsigned char keymap[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'},
    };

    int row, col;
    // check to see if a key is pressed

    GPIO_PORTE_DATA_R = 0; // enable all rows

    col = GPIO_PORTC_DATA_R & 0xF0; // read all columns
    if (col == 0xF0)
        return 0; // no keys are pressed

    while (1)
    {
        row = 0;
        GPIO_PORTE_DATA_R = 0x1D; // enable row 0 (negative logic 1st bit = 0)
        delayus(2);               // wait for signal to settle
        col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0)
            break;

        //----------------------------------------------
        row = 1;
        GPIO_PORTE_DATA_R = 0x1B; // enable row 1 (negative logic 2nd bit = 0)
        delayus(2);               // wait for signal to settle
        col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0)
            break;

        //-------------------------------------------
        row = 2;
        GPIO_PORTE_DATA_R = 0x17; // enable row 2 (negative logic 3rd bit = 0)
        delayus(2);               // wait for signal to settle
        col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0)
            break;
        //----------------------------------------------
        row = 3;
        GPIO_PORTE_DATA_R = 0xF; // enable row 3 (negative logic 4th bit = 0)
        delayus(2);              // wait for signal to settle
        col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0)
            break;

        return 0; // if no key is pressed
    }
    // get here only when a key is pressed
    if (col == 0xE0)
        return keymap[row][0]; // key in column 0
    if (col == 0xD0)
        return keymap[row][1]; // key in column 1
    if (col == 0xB0)
        return keymap[row][2]; // key in column 2
    if (col == 0x70)
        return keymap[row][3]; // key in column 3

    return 0; // double check
}

unsigned char getchar(void)
{
    unsigned char key;

    // wait until previous key is released
    //  getkey() returns 0 when no key is pressed
    do
    {
        while (getkey() != 0) // previous key pressed
            ;
        delayms(20); // wait for debounce
    } while (getkey() != 0);

    do
    {
        key = getkey();
        delayms(20); // wait for debounce
    } while (getkey() != key);

    return key;
}
