/*
 * Code_Giao_Thong.c
*/
#include <avr/io.h>
#define DATA PORTA
#define CONTROL PORTB
#define TIME 30
#define A1_PIN 0
#define A2_PIN 1
#define A3_PIN 2
#define A4_PIN 3
#define LED PORTC
#define RED1_PIN    5
#define YELLOW1_PIN 4
#define GREEN1_PIN  3
#define RED2_PIN    2
#define YELLOW2_PIN 1
#define GREEN2_PIN  0

unsigned char code_seg[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
uint8_t timeGreen = 15;
uint8_t timeRed = 20;

void delay_ms(unsigned long t);
void display_number(uint8_t m, uint8_t n);
void set_pin(uint8_t pin);
void reset_pin(uint8_t pin);
void loop1(int8_t m, int8_t n);
void loop2(int8_t m, int8_t n);
void red1_light();
void yellow1_light();
void green1_light();
void red2_light();
void yellow2_light();
void green2_light();
int main(void)
{
    DDRD = 0xFF;
	DDRC = 0xFF;
	DDRA = 0xFF;
	DDRB = 0xFF;
    while (1) 
    {
		loop1(timeGreen , timeRed);
		loop2(timeRed , timeGreen);
    }
}

void delay_ms(unsigned long t)
{
	while(t --)
	{
		int i = 37;
		while(i--)
		{
			TCNT2 = 0x38;
			TCCR2 |= (1 << CS20);
			while ((TIFR & 0b01000000) == 0);
			TCCR2 &= ~(1 << CS20);
			TIFR = 0b01000000;
		}
	}
}
void set_pin(uint8_t pin)
{
	CONTROL |= (1 << pin);
}
void reset_pin(uint8_t pin)
{
	CONTROL &= ~(1 << pin);
}
void display_number(uint8_t m, uint8_t n)
{
	DATA = code_seg[m/10];
	set_pin(A1_PIN);
	delay_ms(5);
	reset_pin(A1_PIN);

	DATA = code_seg[m%10];
	set_pin(A2_PIN);
	delay_ms(5);
	reset_pin(A2_PIN);

	DATA = code_seg[n/10];
	set_pin(A3_PIN);
	delay_ms(5);
	reset_pin(A3_PIN);
	
	DATA = code_seg[n%10];
	set_pin(A4_PIN);
	delay_ms(5);
	reset_pin(A4_PIN);	
}

void loop1(int8_t m, int8_t n)
{
	while(n >= 0)
	{
		uint8_t t = TIME;
		if(m < 0)
		{
			m = 4;
			yellow1_light();
			red2_light();
		}
		else
		{
			if(n > 4)
			{
				green1_light();
				red2_light();
			}
		}
		while(t --)
		{
			display_number(m, n);
		}
		m --;
		n --;
	}	
}

void loop2(int8_t m, int8_t n)
{
	while(m >= 0)
	{
		uint8_t t = TIME;

		if(n < 0)
		{
			n = 4;
			red1_light();
			yellow2_light();
		}
		else
		{
			if (m > 4)
			{
				red1_light();
				green2_light();
			}	
		}
		while(t--)
		{
			display_number(m, n);
		}
		m --;
		n --;
	}
}

void red1_light()
{
	LED |= (1 << RED1_PIN);
	LED &= ~(1 << YELLOW1_PIN);
	LED &= ~(1 << GREEN1_PIN);
}
void yellow1_light()
{
	LED &= ~(1 << RED1_PIN);
	LED |= (1 << YELLOW1_PIN);
	LED &= ~(1 << GREEN1_PIN);	
}
void green1_light()
{
	LED &= ~(1 << RED1_PIN);
	LED &= ~(1 << YELLOW1_PIN);
	LED |= (1 << GREEN1_PIN);
}

void red2_light()
{
	LED |= (1 << RED2_PIN);
	LED &= ~(1 << YELLOW2_PIN);
	LED &= ~(1 << GREEN2_PIN);
}
void yellow2_light()
{
	LED &= ~(1 << RED2_PIN);
	LED |= (1 << YELLOW2_PIN);
	LED &= ~(1 << GREEN2_PIN);
}
void green2_light()
{
	LED &= ~(1 << RED2_PIN);
	LED &= ~(1 << YELLOW2_PIN);
	LED |= (1 << GREEN2_PIN);
}
