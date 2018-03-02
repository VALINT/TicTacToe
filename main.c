/*
 * 1611_TicTacToe.c
 *
 * Created: 02.11.2016 15:09:10
 * Author : VAL
 */ 

#include "Game.h"
#include "Common.h"
#include "SiemensA55LCD.h"


#define MatrixPORT PORTC
#define MatrixPin  PINC
#define MatrixDDR  DDRC
#define Coloum1 0
#define Coloum2 1
#define Coloum3 2
#define Line1 3
#define Line2 4
#define Line3 5
#define SetColoum1 MatrixPORT |= (1 << Coloum1);
#define SetColoum2 MatrixPORT |= (1 << Coloum2);
#define SetColoum3 MatrixPORT |= (1 << Coloum3);
#define DisColoum1 MatrixPORT &=~ (1 << Coloum1);
#define DisColoum2 MatrixPORT &=~ (1 << Coloum2);
#define DisColoum3 MatrixPORT &=~ (1 << Coloum3);


int8_t Check_ButtMat3x3(void);
void Timer0_Init(void);

void MCU_Init()														//Initialization MCU
{
	DDRD = 0x03;													//Set PORTD on output
	DDRB = 0xff;													//Set PORTB on output
	MatrixDDR = 0x00;
	MatrixDDR |= (1 << Coloum1)|(1 << Coloum2)|(1 << Coloum3);
	
	SPCR |= (1 << SPE)|(1 << MSTR)|(1 << SPR0);						//setting SPI
	
	asm("sei");														//SREG = (1 << I), global interrapt is enable
}

void Timer0_Init()
{
		TCCR0B |= (1 << CS01)|(1 << CS00);								//Timer 0 prescaler on 1024, interrupt 30 per second
		TIMSK0 |= (1 << TOIE0);											//Timer 0 interrupt enable
}

int8_t Check_ButtMat3x3(void)
{
	SetColoum1
	_delay_ms(5);
	if(MatrixPin & (1 << Line1))
	{
		return(7);
	}
	if(MatrixPin & (1 << Line2))
	{
		return(8);
	}
	if(MatrixPin & (1 << Line3))
	{
		return(9);
	}
	DisColoum1
	
	SetColoum2
	_delay_ms(5);
	if(MatrixPin & (1 << Line1))
	{
		return(4);
	}
	if(MatrixPin & (1 << Line2))
	{
		return(5);
	}
	if(MatrixPin & (1 << Line3))
	{
		return(6);
	}
	DisColoum2
	
	SetColoum3
	_delay_ms(5);
	if(MatrixPin & (1 << Line1))
	{
		return(1);
	}
	if(MatrixPin & (1 << Line2))
	{
		return(2);
	}
	if(MatrixPin & (1 << Line3))
	{
		return(3);
	}
	DisColoum3
}

ISR (TIMER0_OVF_vect)
{
	ButtonProcessor(0);
	BuildScreen();
	int x = Check_ButtMat3x3();
	ButtonProcessor(x);
}


int main(void)
{
	MCU_Init();
	LCD_Init();
	LCD_SCL();
	LCD_Start();
	_delay_ms(4000);
	LCD_Name();
	_delay_ms(4000);
	Menu();
	_delay_ms(500);
	LCD_SCL();
	Timer0_Init();
	while(1){}
}

