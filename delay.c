#include "Prototype.h"

//all required delay functions

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
    { /* wait for the COUNT flag 16th bit */ }
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