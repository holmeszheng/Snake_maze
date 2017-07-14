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
	point *last;//��һ��������  
};  

class TrackMap
{
public:
	void Maze_Initial();	//����ѭ������
	void GetMove();			//����λ�������ƶ�
	int trackzone[COL+2][ROW+2];  //��ǽ�Ķ�ά���� 1,2������x��y���� +-��COL+1)/2->OpenGL����
};

extern TrackMap maze;

#endif