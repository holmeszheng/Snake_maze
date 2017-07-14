#include "Turn.h"
#include "SnakeLink.h"
#include "Scene.h"
#include "Font.h"
#include "Barrier.h"
#include "Cookies.h"
#include "Fruit.h"
#include "Maze.h"
#include "Map.h"

static float angular = float(m3dDegToRad(90.0f));

bool float_equals(float a,float b)
{
	if (abs(a-b)<=0.01)
		return true;
	return false;
}

void Turn_Left()
{
	snake[0].LocalSystem.RotateWorld(angular, 0.0f, 1.0f, 0.0f);
}

void Turn_Right()
{
	snake[0].LocalSystem.RotateWorld(-angular, 0.0f, 1.0f, 0.0f);
}

void Go_Straight()
{
	int i;
	Link_Num++;
	for(i=Link_Num; i>1 ;i--)
	{
		snake[i-1]=snake[i-2];
	}
	snake[0].LocalSystem.MoveForward(1.0f);
	snake[0].x=snake[0].LocalSystem.GetOriginX();
	snake[0].y=snake[0].LocalSystem.GetOriginZ();

	//视点与蛇头坐标系一致
	cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
	float temp_vector[3];
	snake[0].LocalSystem.GetForwardVector(temp_vector);
	cameraframe[0].SetForwardVector(temp_vector);
	//移动视点到蛇头后上方
	cameraframe[0].MoveForward(CAMERABACK);
	cameraframe[0].MoveUp(CAMERAUP);


	//判断此位置触发的物体
	
	//fruit
	if(float_equals(fruit.x,snake[0].x) && float_equals(fruit.y , snake[0].y))
	{
		switch(fruit.fruittype)
		{
		case NORMAL:
			Score += 50;
			chaos=0;
			angel=0;
			mciSendString("seek normal_f to start",NULL,0,NULL);
			mciSendString("play normal_f",NULL,0,NULL);
			//fruit初始
			fruit.Initial();
			break;
		case LIFE:
			Score += 80;
			chaos=0;
			angel=0;
			Life++;
			mciSendString("seek laugh to start",NULL,0,NULL);
			mciSendString("play laugh",NULL,0,NULL);
			//fruit初始
			fruit.Initial();
			break;
		case ANGEL:
			Score += 100;
			chaos=0;
			mciSendString("seek angel to start",NULL,0,NULL);
			mciSendString("play angel",NULL,0,NULL);
			//fruit初始
			fruit.Initial();
			if(Link_Num == MaxLinkNum)
				angel=0; //最后一个果实是ANGEL
			else
				angel=1;	//进入无敌状态
			break;
		case CHAOS:
			Score += 100;
			angel=0;
			mciSendString("seek chaos to start",NULL,0,NULL);
			mciSendString("play chaos",NULL,0,NULL);
			//fruit初始
			fruit.Initial();
			if(Link_Num == MaxLinkNum)
				chaos=0; //最后一个果实是CHAOS
			else
				chaos=1;	//进入混乱状态
			break;
		case DASH:
			Score += 100;
			chaos=0;
			angel=0;
			mciSendString("seek follow to start",NULL,0,NULL);
			mciSendString("play follow",NULL,0,NULL);
			fruit.Initial();
			if(Link_Num == MaxLinkNum)
			{
				mciSendString("seek crosslevel to start",NULL,0,NULL);
				mciSendString("play crosslevel",NULL,0,NULL);
				dash=0; //最后一个果实是DASH
			}
			else
			{
				dash = 1;			//进入冲刺状态
				maze.Maze_Initial();
			}
			break;
		}	
	}
	else
	{
		Link_Num--;
	}


	if(Link_Num == MaxLinkNum)
	{
		mciSendString("close background",NULL,0,NULL);
		mciSendString("seek crosslevel to start",NULL,0,NULL);
		mciSendString("play crosslevel",NULL,0,NULL);
		Current_Scene= LOADING_E;
		map_ID++;
		if(map_ID==MAX_MAP_NUM)
		{
			map_ID=0;
			Current_Scene= CLEARED;
		}
		glutPostRedisplay();
	}
	else
	{
		if(angel==0)
		{
			//border
	for(i=0; i<BorderNum ;i++)
	{
		if(float_equals(border[i].x,snake[0].x)&&float_equals(border[i].y,snake[0].y))
		{
			mciSendString("seek die to start",NULL,0,NULL);
			mciSendString("play die",NULL,0,NULL);
			mciSendString("close background",NULL,0,NULL);
			Life--;
			Current_Scene=LOADING_D;
			if (Life == 0)
				Current_Scene = GAMEOVER;
			glutPostRedisplay();
			break;
		}
	}
	//barrier
	for(i=0; i<Barrier_Num ;i++)
	{
		if(float_equals(barrier[i].x,snake[0].x)&&float_equals(barrier[i].y,snake[0].y))
		{
			mciSendString("seek die to start",NULL,0,NULL);
			mciSendString("play die",NULL,0,NULL);
			mciSendString("close background",NULL,0,NULL);
			Life--;
			Current_Scene=LOADING_D;
			if (Life == 0)
				Current_Scene = GAMEOVER;
			glutPostRedisplay();
			break;
		}
	}

	/*
	cout<<endl<<"蛇头"<<snake[0].LocalSystem.GetOriginX()<<","<<snake[0].LocalSystem.GetOriginZ()<<endl;
	cout<<endl<<"蛇身"<<snake[1].LocalSystem.GetOriginX()<<","<<snake[1].LocalSystem.GetOriginZ()<<endl;
	*/

	//snakelink
	
	for(i=1; i<Link_Num; i++)
	{
		if(float_equals(snake[i].x,snake[0].x)&& float_equals(snake[i].y,snake[0].y))
		{
			mciSendString("seek die to start",NULL,0,NULL);
			mciSendString("play die",NULL,0,NULL);
			mciSendString("close background",NULL,0,NULL);
			Life--;
			Current_Scene=LOADING_D;
			if (Life == 0)
				Current_Scene = GAMEOVER;
			glutPostRedisplay();
			break;
		}
	}
		}
	//cookies
	for(i=0;i<MAX_COOKIES_NUM;i++)
	{
		if(float_equals(cookies[i].x,snake[0].x)&& float_equals(cookies[i].y,snake[0].y))
		{
			mciSendString("seek eating to start",NULL,0,NULL);
			mciSendString("play eating",NULL,0,NULL);
			Score += 20;
			cookies[i].Initial();
			break;
		}
	}
	}
}