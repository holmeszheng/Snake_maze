#ifndef MAZE_H
#define MAZE_H

#include<iostream>  
#include<queue>  
#include<string>  
#include<GLFrame.h>

#define ROW 13
#define COL 21

using namespace std; 

struct point{  
	int x;  
	int y;  
	point *last;//上一步的坐标  
};  

class TrackMap
{
public:
	void Maze_Initial();	//生成循迹数组
	void GetMove();			//根据位置蛇身移动
	int trackzone[COL+2][ROW+2];  //带墙的二维数组 1,2坐标是x，y坐标 +-（COL+1)/2->OpenGL坐标
};

extern TrackMap maze;

#endif