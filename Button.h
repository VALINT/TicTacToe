/*
 * IncFile1.h
 *
 * Created: 02.11.2016 17:27:30
 *  Author: VAL
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_


#define MatrixPORT PORTC
#define MatrixPin  PINC
#define MatrixDDR  DDRC
#define Coloum1 0
#define Coloum2 1
#define Coloum3 2
#define Line1 3
#define Line2 4
#define Line3 5


char Check_ButtMat3x3(int);
char press_button_please(int);


#endif /* INCFILE1_H_ */