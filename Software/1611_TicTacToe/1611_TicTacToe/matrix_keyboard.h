/*
 * matrix_keyboard.h
 *
 * Created: 18.08.2021 1:43:26
 *  Author: VAL
 */ 
#ifndef MATRIX_KEYBOARD_H_
#define MATRIX_KEYBOARD_H_

#include "Common.h"
#include "buttons.h"


#define MATRIX_PORT PORTC
#define MATRIX_PIN  PINC
#define MATRIX_DDR  DDRC
#define BAR_1		2
#define BAR_2		1
#define BAR_3		0
#define LINE_1		3
#define LINE_2		4
#define LINE_3		5

#define CHOOSE_BAR(bar)	MATRIX_PORT = (MATRIX_PIN &=~ ((1 << BAR_1) | (1 << BAR_2) | (1 << BAR_3))) | (1 << bar)

#define CHOOSE_BAR_1	MATRIX_PORT |= (1 << BAR_1)
#define CHOOSE_BAR_2	MATRIX_PORT |= (1 << BAR_2)
#define CHOOSE_BAR_3	MATRIX_PORT |= (1 << BAR_3)
#define RELEASE_BAR_1	MATRIX_PORT &=~ (1 << BAR_1)
#define RELEASE_BAR_2	MATRIX_PORT &=~ (1 << BAR_2)
#define RELEASE_BAR_3	MATRIX_PORT &=~ (1 << BAR_3)

typedef struct  
{
	int8_t	last_click;
	Button	matrix[9];
}matrix3x3_t;

void init_matrix(matrix3x3_t*);
void check_matrix(matrix3x3_t*);
int8_t get_click(matrix3x3_t*);


#endif /* MATRIX_KEYBOARD_H_ */