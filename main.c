//Program: Count Increment
//Details: Program will increment through a count of 0 - 9 using 
//a button for input and 7 segment led for output.
//MCU: STM32F103C8T6
//INPUT PINS: A1
//OUTPUT PINS: A5 - A11
//Programmed by Jourdan Rampoldi

#include <stdint.h>
#include <stdbool.h>

struct rcc{
	//struct for rcc with address spacing according to datasheet
	volatile uint32_t CR, CFGR, CIR, APB2RSTR, APB1RSTR, AHBENR, APB2ENR, APB1ENR, BDCR, CSR;
};

struct gpio{
	//struct for gpio with address spacing according to datasheet
	volatile uint32_t CRL, CRH, IDR, ODR, BSRR, BRR, LCKR;
};

// define BASE ADDRESS
#define GPIOA		((struct gpio *) 0x40010800)      
#define RCC			((struct rcc *) 0x40021000)

//define CLOCK ENABLE PORT A
#define RCC_IOPAEN	(1<<2)

// define pin bit location
#define GPIOA_5		(1UL<<5)	// segment C
#define GPIOA_6		(1UL<<6)	// segment D
#define GPIOA_7		(1UL<<7)	// segment E
#define GPIOA_8		(1UL<<8)	// segment G
#define GPIOA_9		(1UL<<9)	// segment F
#define GPIOA_10	(1UL<<10)	// segment A
#define GPIOA_11	(1UL<<11)	// segment B

//declaration of assist functions
void clearSegments(); // use of GPIOA->BSRR to reset output pins 
void turnOnCount(int); // takes in count and fires up appropriate segments 

void main(void)
{
	int count = 0; // count initialized
	bool pressed = false; // increment control variable

	// enable clock for port A
	RCC->APB2ENR |= RCC_IOPAEN;

	// set pin modes for Output: A5 - A11 Input: A1
	GPIOA->CRH &= 0xFFFF0000; // clear needed pins 8 - 15
	GPIOA->CRH |= 0x00002222; // sets mode of pins 8 - 15
	GPIOA->CRL &= 0x000FFF0F; // clear needed pins 0 - 7
	GPIOA->CRL |= 0x22200080; // sets mode of pins 0 - 7


	while(1)
	{
		// GPIOA->IDR at bit 1 reads pin 1
		if ((GPIOA->IDR & (1<<1)) != 0)
		{
			// button pressed
			if (!pressed)
			{
				// reset count 
				if (count >= 9)
				{
					count = 0;
				}
				// increment count
				else
				{
					count++;
				}
			}
			pressed = true; // control button read
		}
		else
		{
			// button released
			clearSegments();
			turnOnCount(count);
			pressed = false;
		}
	}
}
void clearSegments()
{
	// reset output pins A5 - A11, keep input pin A1
	GPIOA->BSRR = 0xFFFD0000; 
}

void turnOnCount(int value)
{
	// prepare for output of pins A5 - A11
	GPIOA->BSRR = 0x00000002;
	switch(value)
	{
		case 0:
			GPIOA->BSRR |= (GPIOA_5 | GPIOA_6 | GPIOA_7 | GPIOA_9 | GPIOA_10 | GPIOA_11);
			break;
		case 1:
			GPIOA->BSRR |= (GPIOA_11 | GPIOA_5);
			break;
		case 2:
			GPIOA->BSRR |= (GPIOA_6 | GPIOA_7 | GPIOA_8 | GPIOA_10 | GPIOA_11);
			break;
		case 3:
			GPIOA->BSRR |= (GPIOA_5 | GPIOA_6 | GPIOA_8 | GPIOA_10 | GPIOA_11);
			break;
		case 4:
			GPIOA->BSRR |= (GPIOA_5 | GPIOA_8 | GPIOA_9 | GPIOA_11);
			break;
		case 5:
			GPIOA->BSRR |= (GPIOA_5 | GPIOA_6 | GPIOA_8 | GPIOA_9 | GPIOA_10);
			break;
		case 6:
			GPIOA->BSRR |= (GPIOA_5 | GPIOA_6 | GPIOA_7 | GPIOA_8 | GPIOA_9 | GPIOA_10);
			break;
		case 7:
			GPIOA->BSRR |= (GPIOA_5 | GPIOA_10 | GPIOA_11);
			break;
		case 8:
			GPIOA->BSRR |= (GPIOA_5 | GPIOA_6 | GPIOA_7 | GPIOA_8 | GPIOA_9 | GPIOA_10 | GPIOA_11);
			break;
		case 9:
			GPIOA->BSRR |= (GPIOA_5 | GPIOA_8 | GPIOA_9 | GPIOA_10 | GPIOA_11);
			break;
	}
}
