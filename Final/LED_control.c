#include "LCDKeypad.h"

void led_Init(void) // IO port initialization
{
	SYSCTL_RCGCGPIO_R |= 0x20; // activate Port F clock
	while ((SYSCTL_PRGPIO_R & 0x20) == 0)
	{
		// wait until its status bit in PR register is true
	}
	GPIO_PORTF_DIR_R |= 0xE;	// PF3-1 Output
	GPIO_PORTF_DEN_R |= 0x1F;	// enable digital I/O on all PF pins
	GPIO_PORTF_DATA_R &= ~0x0E; // initialize LEDs to be off
}

void red()
{
	GPIO_PORTF_DATA_R |= 0x02;
}

void blue()
{
	GPIO_PORTF_DATA_R |= 0x04;
}

void green()
{
	GPIO_PORTF_DATA_R |= 0x08;
}

void off()
{
	GPIO_PORTF_DATA_R &= ~0x0E;
}

void set()
{
	GPIO_PORTF_DATA_R |= 0x0E;
}

void portf_Write(unsigned char data)
{
	GPIO_PORTF_DATA_R &= ~0x0E;
	GPIO_PORTF_DATA_R |= data;
}

void ledBlink()
{
	SW_Init();
	SW3_Init();
	unsigned char color = 0x02;
	while (1)
	{
		if (get_SW1() && get_SW2() && get_SW3())
		{
			if (color == 0x10)
			{
				color = 0x02;
			}
			portf_Write(color);
			color = color << 1;
			delayms(500);
			off();
			delayms(500);
		}
		else
		{
			break;
		}
	}
}

int ledBlink_Once()
{
	GPIO_PORTF_DATA_R ^= 0x0E;
	delayms(1000);
	GPIO_PORTF_DATA_R &= ~0xE; // clear LEDS
	delayms(1000);			   // wait 1 second
	GPIO_PORTF_DATA_R |= 0x02;
	delayms(1000);
	GPIO_PORTF_DATA_R &= ~0xE; // clear LEDS
	delayms(1000);
	GPIO_PORTF_DATA_R |= 0x04;
	delayms(1000);
	GPIO_PORTF_DATA_R &= ~0xE;
	delayms(1000);
	GPIO_PORTF_DATA_R |= 0x08;
	delayms(1000);
	GPIO_PORTF_DATA_R &= ~0xE;
}

void ledbuzzer()
{
	GPIO_PORTF_DATA_R ^= 0x0E; // white
	delayms(500);
	GPIO_PORTF_DATA_R &= ~0xE;	// clear LEDS
	GPIO_PORTA_DATA_R |= 0x08;	// buzzer
	delayms(500);				// wait 1 second
	GPIO_PORTA_DATA_R &= ~0x08; // stop buzzer
	GPIO_PORTF_DATA_R |= 0x02;	// red
	delayms(500);
	GPIO_PORTF_DATA_R &= ~0xE; // clear LEDS
	GPIO_PORTA_DATA_R |= 0x08; // buzzer
	delayms(500);
	GPIO_PORTA_DATA_R &= ~0x08; // stop buzzer
	GPIO_PORTF_DATA_R |= 0x04;	// blue
	delayms(500);
	GPIO_PORTF_DATA_R &= ~0xE; // clear LEDS
	GPIO_PORTA_DATA_R |= 0x08; // buzzer
	delayms(500);
	GPIO_PORTA_DATA_R &= ~0x08; // stop buzzer
	GPIO_PORTF_DATA_R |= 0x08;	// green
	delayms(500);
	GPIO_PORTF_DATA_R &= ~0xE; // clear LEDS
}
