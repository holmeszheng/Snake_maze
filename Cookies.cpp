#include "Fruit.h"
#include "Cookies.h"
#include  <time.h>
#include <stdlib.h>
#include "Maze.h"

//全局变量
Cookies cookies[MAX_COOKIES_NUM];

void Cookies::Initial()
{
	Random_Set();
	LocalSystem.SetOrigin(x,0.0f,y);

}

void Cookies::Random_Set()
{
	int x,y;
	do{
		x=rand() % COL - (COL-1)/2;
		y=rand() % ROW - (ROW-1)/2;
	}while(Check_Valid(x , y)==0);
	Cookies::x= x;
	Cookies::y= y;

}
