/*
 * CFile1.c
 *
 * Created: 02.11.2016 17:27:35
 *  Author: VAL
 */ 

#include "Common.h"
#include "Button.h"

#define SetColoum1 MatrixPORT |= (1 << Coloum1);
#define SetColoum2 MatrixPORT |= (1 << Coloum2);
#define SetColoum3 MatrixPORT |= (1 << Coloum3);
#define DisColoum1 MatrixPORT &=~ (1 << Coloum1);
#define DisColoum2 MatrixPORT &=~ (1 << Coloum2);
#define DisColoum3 MatrixPORT &=~ (1 << Coloum3);

char B_Numb,BC,Butt_Numb;

char Check_ButtMat3x3(int butt_save)
{
	char Butt_Pressed = 0;
	Butt_Numb = butt_save;
	
	MatrixDDR = 0x00;
	MatrixDDR |= (1 << Coloum1)|(1 << Coloum2)|(1 << Coloum3);
	
	SetColoum1
	if(MatrixPin & (1 << Line1))
	{Butt_Numb = press_button_please(1);
	Butt_Pressed = 1;}
	if(MatrixPin & (1 << Line2))
	{Butt_Numb = press_button_please(4);
	Butt_Pressed = 1;}
	if(MatrixPin & (1 << Line3))
	{Butt_Numb = press_button_please(7);
	Butt_Pressed = 1;}	
	DisColoum1
	
	SetColoum2
	if(MatrixPin & (1 << Line1))
	{Butt_Numb = press_button_please(2);
	Butt_Pressed = 1;}
	if(MatrixPin & (1 << Line2))
	{Butt_Numb = press_button_please(5);
	Butt_Pressed = 1;}
	if(MatrixPin & (1 << Line3))
	{Butt_Numb = press_button_please(8);
	Butt_Pressed = 1;}
	DisColoum2
	
	SetColoum3
	if(MatrixPin & (1 << Line1))
	{Butt_Numb = press_button_please(3);
	Butt_Pressed = 1;}
	if(MatrixPin & (1 << Line2))
	{Butt_Numb = press_button_please(6);
	Butt_Pressed = 1;}
	if(MatrixPin & (1 << Line3))
	{Butt_Numb = press_button_please(9);
	Butt_Pressed = 1;}
	DisColoum3
	

	
	if(Butt_Pressed == 0)
	{
		press_button_please(0);
		return(Butt_Numb);
	}
	
	return (0);
}


char press_button_please(int button) //Функція обробки кнопок
{
	
	switch(button)
	{	
		case 0:
			B_Numb = 0;
			BC=0;
			return 0;
			
			
		case 1:
			if((B_Numb == 0)|(B_Numb == button))
			{
				B_Numb = button;
				BC++;
				if(BC > 5)
				{
					return(button);
				}
			}
			break;
			
			
		case 2:
			if((B_Numb == 0)|(B_Numb == button))
			{
				B_Numb = button;
				BC++;
				if(BC > 5)
				{
					return(button);
				}
			}
			break;
			
			
		case 3:
			if((B_Numb == 0)|(B_Numb == button))
			{
				B_Numb = button;
				BC++;
				if(BC > 5)
				{
					return(button);
				}
			}
			break;
			
		case 4:
		if((B_Numb == 0)|(B_Numb == button))
		{
			B_Numb = button;
			BC++;
			if(BC > 5)
			{
				return(button);
			}
		}
		break;
		
		
		case 5:
		if((B_Numb == 0)|(B_Numb == button))
		{
			B_Numb = button;
			BC++;
			if(BC > 5)
			{
				return(button);
			}
		}
		break;
		
		
		case 6:
		if((B_Numb == 0)|(B_Numb == button))
		{
			B_Numb = button;
			BC++;
			if(BC > 5)
			{
				return(button);
			}
		}
		break;
		
		
		case 7:
		if((B_Numb == 0)|(B_Numb == button))
		{
			B_Numb = button;
			BC++;
			if(BC > 5)
			{
				return(button);
			}
		}
		break;
		
		
		case 8:
		if((B_Numb == 0)|(B_Numb == button))
		{
			B_Numb = button;
			BC++;
			if(BC > 5)
			{
				return(button);
			}
		}
		break;
		
		
		case 9:
		if((B_Numb == 0)|(B_Numb == button))
		{
			B_Numb = button;
			BC++;
			if(BC > 5)
			{
				return(button);
			}
		}
		break;
	}

}
