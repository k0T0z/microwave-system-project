#ifndef LCDKEYPAD_H
#define LCDKEYPAD_H

#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#define RS 0x1     // PORT B Pin 0
#define RW 0x2     // PORT B Pin 1
#define Enable 0x4 // PORT B Pin 2

#define Clear 0x1
#define Cursorinit 0x80
#define Secondline 0xC0
#define Wakeup 0x30
#define fourbit 0x20
#define fourbittwoline 0x28
#define shiftright 0x6
#define blink 0xF

void SysTick_Init(void);
void SysTick_Wait(uint32_t delay);
void delayms(int n);
void delayus(int n);

void LCDnibblewrite(unsigned char data, unsigned char control);
void LCDcommand(uint32_t command);
void LCDdata(unsigned char data);
void LCDinit(void);
void LCDstring(unsigned char *str);
void LCDcus(char custom);
void LCDpos(uint8_t row, uint8_t col);

unsigned char keypress(void);
void keypadinit(void);
unsigned char getkey(void);
unsigned char getchar(void);

#endif
