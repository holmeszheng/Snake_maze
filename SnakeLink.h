#ifndef SNAKELINK_H
#define SNAKELINK_H

#include <GLFrame.h>
#define MaxLinkNum 18


class SnakeLink
{
public:
	GLFrame LocalSystem;
	float x,y; //Snake Link position in OpenGL
};

extern int Link_Num;
extern SnakeLink snake[MaxLinkNum];

#endif