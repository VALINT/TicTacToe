#ifndef SIEMENSA55LCD_H_
#define SIEMENSA55LCD_H_

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////
//Select PINs which connect D_C, STROBE< RESET
//Select PORT which control display
//Data and commands sent to LCD by hardware SPI 
#define DATA 1
#define COMMAND 0
#define RESET 2
#define D_C 0
#define SCE 1
#define LCD_PORT PORTD

void LCD_Init();
void LCD_Sent_Byte();
void LCD_Set_Cordinates();
void LCD_Reset();
void LCD_clear();
void LCD_print();
void LCD_print_screen(const char*);
void LCD_print_picture(const char*, uint8_t, uint8_t, uint8_t, uint8_t);


#endif /* SIEMENSA55LCD_H_ */