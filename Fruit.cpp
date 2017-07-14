#include "Fruit.h"
#include "Cookies.h"
#include "SnakeLink.h"
#include "Barrier.h"
#include <stdlib.h>
#include <time.h>
#include "Turn.h"
#include "Maze.h"
//全局变量
Fruit fruit;

void Fruit::Initial()
{
	Random_Set();
	LocalSystem.SetOrigin(x,0.0f,y);
	
}

void Fruit::Random_Set()
{
	int x,y;
	int temp_type;
	do{
		x=rand() % COL - (COL-1)/2;   //不会有border情况
		y=rand() % ROW - (ROW-1)/2;
	}while(Check_Valid(x , y)==0);
	Fruit::x= x;
	Fruit::y= y;

	temp_type = rand() % 10;
	
	
	switch(temp_type)
	{
	case 0:
	case 1:
	case 2:
		fruittype = NORMAL;
		break;
	case 3:
	case 4:
		fruittype = ANGEL;
		break;
	case 5:	
	case 6: 
		fruittype = CHAOS;
		break;
	case 7:
	case 8:	
		fruittype = DASH;
		break;
	case 9: 
		fruittype = LIFE;
	}
	
	
	/*
	switch(temp_type)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:	
	case 6: 	
	case 7:
	case 8:	
	case 9: 
		fruittype = ANGEL;
	}
	*/
}

int Check_Valid(int x , int y)
{
	int i;

	//no barrier
	for(i=0; i<Barrier_Num ;i++)
	{
		if(float_equals(barrier[i].x,x) && float_equals(barrier[i].y,y))
			return 0;
	}
	//no snakelink
	for(i=0; i<Link_Num; i++)
	{
		if(float_equals(snake[i].x,x) &&float_equals(snake[i].y,y))
			return 0;
	}
	//no cookies
	for(i=0;i<MAX_COOKIES_NUM;i++)
	{
		if(float_equals(cookies[i].x,x) && float_equals(cookies[i].y,y))
		return 0;
	}
	//no fruit
	if(float_equals(fruit.x, x) && float_equals(fruit.y , y))
		return 0;

	return 1;
}