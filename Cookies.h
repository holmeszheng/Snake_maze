#ifndef COOKIES_H
#define COOKIES_H

#include <GLFrame.h>

#define MAX_COOKIES_NUM 18

class Cookies
{
public:
	void Initial();
	void Random_Set();

	GLFrame LocalSystem;
	float x,y;  //cookies position in OpenGL
};

extern Cookies cookies[MAX_COOKIES_NUM];

#endif