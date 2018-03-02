#include "SiemensA55LCD.h"
#include "Common.h"

#define SentDATA LCD_PORT |= (1<<D_C);					//Pin DATA/COMMAND set in 1, sent DATA
#define SentCOMMAND LCD_PORT&=~(1<<D_C);				//Pin DATA/COMMAND set in 0, sent COMMAND
#define STROBEON LCD_PORT|=(1<<SCE);					//PIN STROBE set in 1, end of transmitting
#define STROBEOFF LCD_PORT&=~(1<<SCE);					//Pin STROBE set in 0, start of transmitting
#define RESETHigh LCD_PORT|=(1<<RESET);					//Pin RESET set in 1, work mode 
#define RESETLow LCD_PORT&=~(1<<RESET);					//Pin RESET set in 0, mode of reset


const unsigned char Symbols[60][5] PROGMEM =			//table of ASCII symbols(need correction)
														//Write data on flash use "pgmspase.h" library
{
	{0x00,0x00,0x00,0x00,0x00},	//32//SPASE
	{0x00,0x00,0x5f,0x00,0x00},	//33//!
	{0x00,0x07,0x00,0x07,0x00},	//34//"
	{0x14,0x7f,0x14,0x7f,0x14},	//35//#
	{0x24,0x2a,0x7f,0x2a,0x12},	//36//$
	{0x23,0x13,0x08,0x64,0x62},	//37//%
	{0x36,0x49,0x55,0x22,0x50},	//38//&
	{0x00,0x05,0x03,0x00,0x00},	//39//'
	{0x00,0x1c,0x22,0x41,0x00},	//40//(
	{0x00,0x41,0x22,0x1c,0x00},	//41//)
	{0x14,0x08,0x3e,0x08,0x14},	//42//*
	{0x08,0x08,0x3e,0x08,0x08},	//43//+
	{0x00,0x50,0x30,0x00,0x00},	//44//,
	{0x08,0x08,0x08,0x08,0x08},	//45//-
	{0x00,0x60,0x60,0x00,0x00},	//46//.
	{0x20,0x10,0x08,0x04,0x02},	//47///
	{0x3E,0x41,0x41,0x41,0x3E},	//48//0
	{0x00,0x04,0x02,0x7F,0x00},	//49//1
	{0x42,0x61,0x51,0x49,0x46},	//50//2
	{0x22,0x41,0x41,0x49,0x36},	//51//3
	{0x18,0x14,0x12,0x11,0x7F},	//52//4
	{0x47,0x45,0x45,0x45,0x39},	//53//5
	{0x3E,0x49,0x49,0x49,0x32},	//54//6
	{0x01,0x01,0x61,0x19,0x07},	//55//7
	{0x36,0x49,0x49,0x49,0x36},	//56//8
	{0x26,0x49,0x49,0x49,0x3E},	//57//9
	{0x00,0x36,0x36,0x00,0x00},	//58//:
	{0x00,0x56,0x36,0x00,0x00},	//59//;
	{0x08,0x14,0x22,0x41,0x00},	//60//<
	{0x14,0x14,0x14,0x14,0x14},	//61//=
	{0x00,0x41,0x22,0x14,0x08},	//62//>
	{0x02,0x01,0x51,0x09,0x06},	//63//?
	{0x32,0x49,0x79,0x41,0x3e},	//64//@
	{0x7C,0x12,0x11,0x12,0x7C},	//65//A
	{0x7F,0x49,0x49,0x4E,0x30},	//66//B
	{0x3E,0x41,0x41,0x41,0x22},	//67//C
	{0x7F,0x41,0x41,0x22,0x1C},	//68//D
	{0x7F,0x49,0x49,0x49,0x41},	//69//E
	{0x7F,0x09,0x09,0x09,0x01},	//70//F
	{0x3E,0x41,0x51,0x51,0x32},	//71//G
	{0x7F,0x08,0x08,0x08,0x7F},	//72//H
	{0x00,0x41,0x7F,0x41,0x00},	//73//I
	{0x20,0x40,0x41,0x3F,0x01},	//74//J
	{0x7F,0x08,0x14,0x22,0x41},	//75//K
	{0x7F,0x40,0x40,0x40,0x40},	//76//L
	{0x7F,0x02,0x04,0x02,0x7F},	//77//M
	{0x7F,0x04,0x08,0x10,0x7F},	//78//N
	{0x3E,0x41,0x41,0x41,0x3E},	//79//O
	{0x7E,0x11,0x11,0x11,0x0E},	//80//P
	{0x3E,0x41,0x51,0x61,0x7E},	//81//Q
	{0x7E,0x11,0x11,0x21,0x4E},	//82//R
	{0x26,0x49,0x49,0x49,0x32},	//83//S
	{0x01,0x01,0x7F,0x01,0x01},	//84//T
	{0x3F,0x40,0x40,0x40,0x3F},	//85//U
	{0x0F,0x30,0x40,0x30,0x0F},	//86//V
	{0x3F,0x40,0x30,0x40,0x3F},	//87//W
	{0x63,0x14,0x08,0x14,0x63},	//88//X
	{0x03,0x04,0x78,0x04,0x03},	//89//Y
	
};		//
																

void LCD_Init()											//Initial. LCD
{
	LCD_Reset();
	LCD_Sent_Byte(0x21,COMMAND);
	LCD_Sent_Byte(0x09,COMMAND);
	LCD_Sent_Byte(0xE0,COMMAND);
	LCD_Sent_Byte(0x15,COMMAND);
	LCD_Sent_Byte(0x06,COMMAND);
	LCD_Sent_Byte(0x20,COMMAND);
	LCD_Sent_Byte(0x0C,COMMAND);
}

void LCD_Sent_Byte(int byte,int status)					//sent 1 byte in LCD by hardware SPI 
{
	if (status == COMMAND)SentCOMMAND
	else SentDATA
	STROBEOFF
	SPDR = byte;
	while(!(SPSR & (1<<SPIF)));
	STROBEON
}

void LCD_Reset()										//Reset LCD, RAM LCD after reset, not set, need clear
{
	RESETLow
	_delay_us(1);
	RESETHigh
	STROBEON
	_delay_ms(1);
}

void LCD_Set_Cordinates(int YY,int XX)
{
	LCD_Sent_Byte(0x40+YY,COMMAND);
	LCD_Sent_Byte(0x80+XX,COMMAND);
	_delay_ms(5);
}

void LCD_SCL()											//Clear LCD,fill RAM LCD by empty bytes
{
	LCD_Set_Cordinates(0,0);
	for(int smbl = 0; smbl < 816; smbl++)
	{
		LCD_Sent_Byte(0,DATA);
	}
}

void LCD_print(int symbol)								//Print symbol on LCD, need division symbols for one is main cycle
{														//Use symbols from Flash ROM
														//Need using "pgmspase.h" library
	
	int buffer;											 
	for(int part = 0; part < 5; part++)
	{
		buffer = pgm_read_byte(&(Symbols[symbol-32][part]));
		LCD_Sent_Byte(buffer,DATA);
	}
	LCD_Sent_Byte(0,DATA);
}

