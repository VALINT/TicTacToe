/*
 * 1611_TicTacToe.c
 *
 * Created: 02.11.2016 15:09:10
 * Author : VAL
 */ 

#include "Game.h"
#include "Common.h"
#include "SiemensA55LCD.h"
#include "matrix_keyboard.h"
#include <stdbool.h>
#include "graphics.h"

void Timer0_Init(void);

matrix3x3_t keyboard;
volatile bool new_frame = false;
volatile uint8_t cntr = 0; 

void MCU_Init()														//Initialization MCU
{
	DDRD = 0x0f;													//Set PORTD on output
	DDRB = 0xff;													//Set PORTB on output
	MATRIX_DDR = 0x00;
	MATRIX_DDR |= (1 << BAR_1)|(1 << BAR_2)|(1 << BAR_3);
	
	SPCR |= (1 << SPE)|(1 << MSTR);									//setting SPI
	
	asm("sei");														//SREG = (1 << I), global interrapt is enable
}

void Timer0_Init()
{
		TCCR0 |= (1 << CS01)|(1 << CS00)|(SPI2X);					//Timer 0 prescaler on 1024, interrupt 30 per second
		TIMSK |= (1 << TOIE0);										//Timer 0 interrupt enable
		asm("sei");						
}

ISR (TIMER0_OVF_vect)
{
	new_frame = true;
	cntr++;
	cntr &= 4;
}


int main(void)
{
	// Start initialization
	MCU_Init();
	LCD_Init();
	//Clear LCD
	LCD_clear();
	init_matrix(&keyboard);
	// Print start screen
	LCD_print_screen(&StartPage[0]);
	_delay_ms(4000);
	// Print Game's name screen
	LCD_print_screen(&Name[0]);
	_delay_ms(4000);
	// Go to menu
	Menu();
	_delay_ms(200);
	LCD_clear();

	_delay_ms(1000);
	
	Timer0_Init();

	while(1)
	{	
		if (new_frame)
		{
			new_frame = false;
			check_matrix(&keyboard);
			int8_t x = get_click(&keyboard);
			ButtonProcessor(x);
			if(!cntr)
			{
				printer();
			}
		}
	}
}

