/*
 * matrix_keyboard.c
 *
 * Created: 18.08.2021 1:43:08
 *  Author: VAL
 */ 

#include "matrix_keyboard.h"

void init_matrix(matrix3x3_t* matrix)
{
	matrix->last_click = -1;
	for(uint8_t i = 0; i < 9; i++)
	{
		init_button( &matrix->matrix[i], &MATRIX_PIN, LINE_1+i%3, 0, 0, 0);		
	}
}

void check_matrix(matrix3x3_t* matrix)
{
	for(int8_t i = 0; i < 9; i++)
	{
		CHOOSE_BAR(i/3);
		_delay_us(1);
		check_button(&matrix->matrix[i]);
		if(get_bt_state(&matrix->matrix[i]) == BT_CLICK || get_bt_state(&matrix->matrix[i]) == BT_HOLD)
		{
			matrix->last_click = i;
		}
		if(get_bt_state(&matrix->matrix[i]) == BT_CLICK || get_bt_state(&matrix->matrix[i]) == BT_HOLD || get_bt_state(&matrix->matrix[i]) == BT_WORKED_OUT)
		{
			set_bt_state(&matrix->matrix[i], BT_FREE);
		}
	}
}

int8_t get_click(matrix3x3_t* matrix)
{
	int8_t buff = matrix->last_click;
	matrix->last_click = -1;
	return buff;
}