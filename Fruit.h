#ifndef FRUIT_H
#define FRUIT_H

#include <GLFrame.h>

#define FRUIT_TYPE_NUM = 5;
typedef enum fruit_type {NORMAL,DASH,LIFE,CHAOS,ANGEL};

class Fruit
{
public:
	void Initial();   //���ù�ʵ���꣬���ù�ʵ����ϵ�͹�ʵ����
	void Random_Set();

	fruit_type fruittype;
	GLFrame LocalSystem;
	float x,y;  //fruit position in OpenGL
};

extern Fruit fruit;


int Check_Valid(int , int );

#endif