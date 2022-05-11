#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "stdlib.h"

#define RS 0x1     // PORT B Pin 0
#define RW 0x2     // PORT B Pin 1
#define Enable 0x4 // PORT B Pin 2

#define clearScreen 0x1 // changed name from Clear to clearScreen for bug fixes by saifkandil
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
void LCDcommand(unsigned char command);
void LCDdata(unsigned char data);
void LCDinit(void);
void LCDstring(unsigned char *str, unsigned char len);
void LCDcus(void);
void LCDpos(uint8_t col, uint8_t row);

unsigned char keypress(void);
void keypadinit(void);
unsigned char getkey(void);
unsigned char getchar(void);

int Intstr(unsigned char *str, unsigned char len);