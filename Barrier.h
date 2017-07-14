#ifndef BARRIER_H
#define BARRIER_H

#include <GLFrame.h>
#include "Maze.h"

#define MaxBarrierNum 41
#define BorderNum (COL+2)*2+ROW*2


class Barrier
{
public:
	GLFrame LocalSystem;
	float x,y; //barrier position in OpenGL
};


extern int Barrier_Num;
extern Barrier barrier[MaxBarrierNum];
extern Barrier border[BorderNum];

extern void Initial_Border();

#endif

