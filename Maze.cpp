#include "Maze.h"
#include "Fruit.h"
#include "SnakeLink.h"
#include "Barrier.h"
#include "Scene.h"
#include "Cookies.h"
#include "Font.h"
#include "Map.h"
#include "Turn.h"
#include "Sound.h"

//全局变量
TrackMap maze;

void TrackMap::Maze_Initial()
{  
	int i,j,k;
	for(i=0;i<COL+2;i++)			//数组初始0
		for(j=0;j<ROW+2;j++)
			trackzone[i][j] = 0;

	for(i = 0; i < ROW+2; ++i){		//左右加墙  
		trackzone[0][i] = 1;  
		trackzone[COL+1][i] = 1;  
	}  
	for(i = 1; i <COL+1; ++i){			//上下加墙  
		trackzone[i][0] = 1;  
		trackzone[i][ROW+1] = 1;  
	}  
	for(k = 0; k < Barrier_Num; k++)		//BARRIER[K]的值手赋，所以不会有截断的问题
	{
		trackzone[(int)barrier[k].LocalSystem.GetOriginX()+(COL+1)/2][(int)barrier[k].LocalSystem.GetOriginZ()+(ROW+1)/2]=1;
	}
	queue<point*> q;  
	point *start = (point*)malloc(sizeof(point));//起点  
	start->x=(int)(snake[0].LocalSystem.GetOriginX()+(COL+1)/2+0.5);
	start->y=(int)(snake[0].LocalSystem.GetOriginZ()+(ROW+1)/2+0.5); 

	start->last = start;  
	q.push(start);  

	trackzone[start->x][start->y] = 2;  

	point end;//终点  
	end.x=(int)(fruit.LocalSystem.GetOriginX()+(COL+1)/2+0.5);
	end.y=(int)(fruit.LocalSystem.GetOriginZ()+(ROW+1)/2+0.5);

	int aspect[4][2] = {{0, -1},{0, 1},{-1, 0},{1, 0}};//转向：上下左右  
	int flag = 0;//是否有路可走的标志  
	while(!q.empty()){  
		point *front = q.front();  
		q.pop();//弹出队头  
		if(front->x == end.x && front->y == end.y){  
			flag = 1;  
			cout<<"成功找到出路."<<"最少需要"<<trackzone[front->x][front->y]-2<<"步。如下所示："<<endl;  
			trackzone[front->x][front->y] = -6;  
			//cout<<"倒退回去："<<(front)->x<<","<<(front)->y;  
			point *lastPoint = front;  
			front = front->last;  
			while((front->x != start->x) || (front->y != start->y)){  
				//cout<<"->"<<front->x<<","<<front->y;  
				if(lastPoint->x - front->x == 1){  
					trackzone[front->x][front->y] = -1;  
				}else if(lastPoint->x - front->x == -1){  
					trackzone[front->x][front->y] = -2;  
				}else if(lastPoint->y - front->y == 1){  
					trackzone[front->x][front->y] = -3;  
				}else{  
					trackzone[front->x][front->y] = -4;  
				}  
				lastPoint = front;  
				front = front->last;  
			}  
			//cout<<"->"<<start->x<<","<<start->y<<endl;  
			trackzone[start->x][start->y] = -5;  
			break;  

		}else{  
			for(int i = 0; i < 4 ; ++i){  
				point *temp = new point;  
				temp->x = front->x + aspect[i][0];  
				temp->y = front->y + aspect[i][1];  
				if(trackzone[temp->x][temp->y] == 0){  
					temp->last = front;  
					q.push(temp);  
					trackzone[temp->x][temp->y] = trackzone[front->x ][front->y] + 1;  
				}  
			}  
		}  
	}  
	if(!flag)  
		cout<<"无路可走！"<<endl;  
	else{  
		string s[6] = {"★", "☆", "↑","↓","←","→" };  
		for(int j = 0; j < ROW+2; ++j){  
			for(int i = 0; i < COL+2; ++i){  
				if(trackzone[i][j]==1){  
					cout<<"■";  
				}else if(trackzone[i][j]<0){  
					int temp = trackzone[i][j]+6;  
					cout<<s[temp];  
				}else{  
					cout<<"  ";  
				}  
			}  
			cout<<endl;  
		}  
	}  
}  
void TrackMap::GetMove()
{
	point start;
	point next;
	int i;

	start.x=(int)(snake[0].LocalSystem.GetOriginX()+(COL+1)/2+0.5);
	start.y=(int)(snake[0].LocalSystem.GetOriginZ()+(ROW+1)/2+0.5); 


		cout<<snake[0].LocalSystem.GetOriginX()<<","<<snake[0].LocalSystem.GetOriginZ()<<"///////////";
		cout<<snake[1].LocalSystem.GetOriginX()<<","<<snake[1].LocalSystem.GetOriginZ()<<"///////////";
		cout<<snake[2].LocalSystem.GetOriginX()<<","<<snake[2].LocalSystem.GetOriginZ()<<endl;
		//判断上下左右是否有箭头
		//下面
	if(trackzone[start.x][start.y+1] < 0 && trackzone[start.x][start.y+1] > -5 )
	{
		next.x=start.x;
		next.y=start.y+1;
		for(i=Link_Num; i>1 ;i--)
		{
			snake[i-1]=snake[i-2];
		}
		snake[0].LocalSystem.SetOrigin((float)(next.x-(COL+1)/2),0.0f,(float)(next.y-(ROW+1)/2));
		snake[0].x=(float)(next.x-(COL+1)/2);
		snake[0].y=(float)(next.y-(ROW+1)/2);

		switch(trackzone[next.x][next.y])
		{
		case -4:
			snake[0].LocalSystem.SetForwardVector(0.0f,0.0f,-1.0f);
			break;
			case -3:
				snake[0].LocalSystem.SetForwardVector(0.0f,0.0f,1.0f);
				break;
				case -2:
					snake[0].LocalSystem.SetForwardVector(-1.0f,0.0f,0.0f);
					break;
					case -1:
						snake[0].LocalSystem.SetForwardVector(1.0f,0.0f,0.0f);
						break;
		}
		//修正第一节方向
		snake[1].LocalSystem.SetForwardVector(0.0f,0.0f,1.0f);
		//清除trackzone二维数组start位置变量
		trackzone[start.x][start.y] = 0;

		//视点与蛇头坐标系一致
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//移动视点到蛇头后上方
		cameraframe[0].MoveForward(CAMERABACK);
		cameraframe[0].MoveUp(CAMERAUP);

		//cookies
		for(i=0;i<MAX_COOKIES_NUM;i++)
		{
			if(float_equals(cookies[i].x, snake[0].x) && float_equals(cookies[i].y, snake[0].y))
			{
				mciSendString("seek eating to start",NULL,0,NULL);
				mciSendString("play eating",NULL,0,NULL);
				Score += 20;
				cookies[i].Initial();
				break;
			}
		}
	}

	//上面
	if(trackzone[start.x][start.y-1] < 0 &&  trackzone[start.x][start.y-1] > -5)
	{
		next.x=start.x;
		next.y=start.y-1;
		for(i=Link_Num; i>1 ;i--)
		{
			snake[i-1]=snake[i-2];
		}
		snake[0].LocalSystem.SetOrigin((float)(next.x-(COL+1)/2),0.0f,(float)(next.y-(ROW+1)/2));
		snake[0].x=(float)(next.x-(COL+1)/2);
		snake[0].y=(float)(next.y-(ROW+1)/2);

		switch(trackzone[next.x][next.y])
		{
		case -4:
			snake[0].LocalSystem.SetForwardVector(0.0f,0.0f,-1.0f);
			break;
		case -3:
			snake[0].LocalSystem.SetForwardVector(0.0f,0.0f,1.0f);
			break;
		case -2:
			snake[0].LocalSystem.SetForwardVector(-1.0f,0.0f,0.0f);
			break;
		case -1:
			snake[0].LocalSystem.SetForwardVector(1.0f,0.0f,0.0f);
			break;
		}
		snake[1].LocalSystem.SetForwardVector(0.0f,0.0f,-1.0f);
		trackzone[start.x][start.y] = 0;

		//视点与蛇头坐标系一致
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//移动视点到蛇头后上方
		cameraframe[0].MoveForward(CAMERABACK);
		cameraframe[0].MoveUp(CAMERAUP);

		//cookies
		for(i=0;i<MAX_COOKIES_NUM;i++)
		{
			if(float_equals(cookies[i].x, snake[0].x )&& float_equals(cookies[i].y, snake[0].y))
			{
				mciSendString("seek eating to start",NULL,0,NULL);
				mciSendString("play eating",NULL,0,NULL);
				Score += 20;
				cookies[i].Initial();
				break;
			}
		}
	}
	//右面
	if(trackzone[start.x+1][start.y] < 0 && trackzone[start.x+1][start.y] > -5)
	{
		next.x=start.x+1;
		next.y=start.y;
		for(i=Link_Num; i>1 ;i--)
		{
			snake[i-1]=snake[i-2];
		}
		snake[0].LocalSystem.SetOrigin((float)(next.x-(COL+1)/2),0.0f,(float)(next.y-(ROW+1)/2));
		snake[0].x=(float)(next.x-(COL+1)/2);
		snake[0].y=(float)(next.y-(ROW+1)/2);

		switch(trackzone[next.x][next.y])
		{
		case -4:
			snake[0].LocalSystem.SetForwardVector(0.0f,0.0f,-1.0f);
			break;
		case -3:
			snake[0].LocalSystem.SetForwardVector(0.0f,0.0f,1.0f);
			break;
		case -2:
			snake[0].LocalSystem.SetForwardVector(-1.0f,0.0f,0.0f);
			break;
		case -1:
			snake[0].LocalSystem.SetForwardVector(1.0f,0.0f,0.0f);
			break;
		}
		snake[1].LocalSystem.SetForwardVector(1.0f,0.0f,0.0f);
		trackzone[start.x][start.y] = 0;

		//视点与蛇头坐标系一致
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//移动视点到蛇头后上方
		cameraframe[0].MoveForward(CAMERABACK);
		cameraframe[0].MoveUp(CAMERAUP);

		//cookies
		for(i=0;i<MAX_COOKIES_NUM;i++)
		{
			if(float_equals(cookies[i].x, snake[0].x)&& float_equals(cookies[i].y, snake[0].y))
			{
				mciSendString("seek eating to start",NULL,0,NULL);
				mciSendString("play eating",NULL,0,NULL);
				Score += 20;
				cookies[i].Initial();
				break;
			}
		}
	}
	//左面
	if( trackzone[start.x-1][start.y] < 0 && trackzone[start.x-1][start.y] > -5 )
	{
		next.x=start.x-1;
		next.y=start.y;
		for(i=Link_Num; i>1 ;i--)
		{
			snake[i-1]=snake[i-2];
		}
		snake[0].LocalSystem.SetOrigin((float)(next.x-(COL+1)/2),0.0f,(float)(next.y-(ROW+1)/2));
		snake[0].x=(float)(next.x-(COL+1)/2);
		snake[0].y=(float)(next.y-(ROW+1)/2);

		switch(trackzone[next.x][next.y])
		{
		case -4:
			snake[0].LocalSystem.SetForwardVector(0.0f,0.0f,-1.0f);
			break;
		case -3:
			snake[0].LocalSystem.SetForwardVector(0.0f,0.0f,1.0f);
			break;
		case -2:
			snake[0].LocalSystem.SetForwardVector(-1.0f,0.0f,0.0f);
			break;
		case -1:
			snake[0].LocalSystem.SetForwardVector(1.0f,0.0f,0.0f);
			break;
		}
		snake[1].LocalSystem.SetForwardVector(-1.0f,0.0f,0.0f);
		trackzone[start.x][start.y] = 0;

		//视点与蛇头坐标系一致
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//移动视点到蛇头后上方
		cameraframe[0].MoveForward(CAMERABACK);
		cameraframe[0].MoveUp(CAMERAUP);

		//cookies
		for(i=0;i<MAX_COOKIES_NUM;i++)
		{
			if(float_equals(cookies[i].x, snake[0].x) && float_equals(cookies[i].y, snake[0].y))
			{
				mciSendString("seek eating to start",NULL,0,NULL);
				mciSendString("play eating",NULL,0,NULL);
				Score += 20;
				cookies[i].Initial();
				break;
			}
		}
	}

	//判断上下左右是否有终点
	//下面
	if( trackzone[start.x][start.y+1] == -6)
	{
		next.x=start.x;
		next.y=start.y+1;
		Link_Num++;
		for(i=Link_Num; i>1 ;i--)
		{
			snake[i-1]=snake[i-2];
		}
		snake[0].LocalSystem.SetForwardVector(0.0f,0.0f,1.0f);
		snake[0].LocalSystem.MoveForward(1.0f);
		snake[0].x=(float)(next.x-(COL+1)/2);
		snake[0].y=(float)(next.y-(ROW+1)/2);
		dash = 0;

		//视点与蛇头坐标系一致
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//移动视点到蛇头后上方
		cameraframe[0].MoveForward(CAMERABACK);
		cameraframe[0].MoveUp(CAMERAUP);

		//吃到果子的操作
		if(Link_Num!=MaxLinkNum)
		{
			if(fruit.fruittype==NORMAL)
			{
				Score += 50;
				mciSendString("seek normal_f to start",NULL,0,NULL);
				mciSendString("play normal_f",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==LIFE)
			{
				Score += 80;
				Life++;
				mciSendString("seek laugh to start",NULL,0,NULL);
				mciSendString("play laugh",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==ANGEL)
			{
				Score += 100;
				angel = 1;
				mciSendString("seek angel to start",NULL,0,NULL);
				mciSendString("play angel",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==CHAOS)
			{
				Score += 100;
				chaos = 1;
				mciSendString("seek chaos to start",NULL,0,NULL);
				mciSendString("play chaos",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==DASH)
			{
				Score += 100;
				mciSendString("seek follow to start",NULL,0,NULL);
				mciSendString("play follow",NULL,0,NULL);
				fruit.Initial();
				if(Link_Num == MaxLinkNum)
				{
					dash=0; //最后一个果实是DASH
				}
				else
				{
					dash = 1;			//进入冲刺状态
					maze.Maze_Initial();
				}
			}
		}
		else
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
	}

	//上面
	if( trackzone[start.x][start.y-1] == -6)
	{
		next.x=start.x;
		next.y=start.y-1;
		Link_Num++;
		for(i=Link_Num; i>1 ;i--)
		{
			snake[i-1]=snake[i-2];
		}
		snake[0].LocalSystem.SetForwardVector(0.0f,0.0f,-1.0f);
		snake[0].LocalSystem.MoveForward(1.0f);
		snake[0].x=(float)(next.x-(COL+1)/2);
		snake[0].y=(float)(next.y-(ROW+1)/2);
		dash = 0;

		//视点与蛇头坐标系一致
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//移动视点到蛇头后上方
		cameraframe[0].MoveForward(CAMERABACK);
		cameraframe[0].MoveUp(CAMERAUP);

		//吃到果子的操作
		if(Link_Num!=MaxLinkNum)
		{
			if(fruit.fruittype==NORMAL)
			{
				Score += 50;
				mciSendString("seek normal_f to start",NULL,0,NULL);
				mciSendString("play normal_f",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==LIFE)
			{
				Score += 80;
				Life++;
				mciSendString("seek laugh to start",NULL,0,NULL);
				mciSendString("play laugh",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==ANGEL)
			{
				Score += 100;
				angel = 1;
				mciSendString("seek angel to start",NULL,0,NULL);
				mciSendString("play angel",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==CHAOS)
			{
				Score += 100;
				chaos = 1;
				mciSendString("seek chaos to start",NULL,0,NULL);
				mciSendString("play chaos",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==DASH)
			{
				Score += 100;
				mciSendString("seek follow to start",NULL,0,NULL);
				mciSendString("play follow",NULL,0,NULL);
				fruit.Initial();
				if(Link_Num == MaxLinkNum)
				{
					dash=0; //最后一个果实是DASH
				}
				else
				{
					dash = 1;			//进入冲刺状态
					maze.Maze_Initial();
				}
			}
		}
		else
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

	}
	//右面
	if( trackzone[start.x+1][start.y] == -6)
	{
		next.x=start.x+1;
		next.y=start.y;
		Link_Num++;
		for(i=Link_Num; i>1 ;i--)
		{
			snake[i-1]=snake[i-2];
		}
		snake[0].LocalSystem.SetForwardVector(1.0f,0.0f,0.0f);
		snake[0].LocalSystem.MoveForward(1.0f);
		snake[0].x=(float)(next.x-(COL+1)/2);
		snake[0].y=(float)(next.y-(ROW+1)/2);
		dash = 0;

		//视点与蛇头坐标系一致
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//移动视点到蛇头后上方
		cameraframe[0].MoveForward(CAMERABACK);
		cameraframe[0].MoveUp(CAMERAUP);

		//吃到果子的操作
		if(Link_Num!=MaxLinkNum)
		{
			if(fruit.fruittype==NORMAL)
			{
				Score += 50;
				mciSendString("seek normal_f to start",NULL,0,NULL);
				mciSendString("play normal_f",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==LIFE)
			{
				Score += 80;
				Life++;
				mciSendString("seek laugh to start",NULL,0,NULL);
				mciSendString("play laugh",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==ANGEL)
			{
				Score += 100;
				angel = 1;
				mciSendString("seek angel to start",NULL,0,NULL);
				mciSendString("play angel",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==CHAOS)
			{
				Score += 100;
				chaos = 1;
				mciSendString("seek chaos to start",NULL,0,NULL);
				mciSendString("play chaos",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==DASH)
			{
				Score += 100;
				mciSendString("seek follow to start",NULL,0,NULL);
				mciSendString("play follow",NULL,0,NULL);
				fruit.Initial();
				if(Link_Num == MaxLinkNum)
				{
					dash=0; //最后一个果实是DASH
				}
				else
				{
					dash = 1;			//进入冲刺状态
					maze.Maze_Initial();
				}
			}
		}
		else
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
	}
	//左面
	if( trackzone[start.x-1][start.y] == -6)
	{
		next.x=start.x-1;
		next.y=start.y;
		Link_Num++;
		for(i=Link_Num; i>1 ;i--)
		{
			snake[i-1]=snake[i-2];
		}
		snake[0].LocalSystem.SetForwardVector(-1.0f,0.0f,0.0f);
		snake[0].LocalSystem.MoveForward(1.0f);
		snake[0].x=(float)(next.x-(COL+1)/2);
		snake[0].y=(float)(next.y-(ROW+1)/2);
		dash = 0;

		//视点与蛇头坐标系一致
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//移动视点到蛇头后上方
		cameraframe[0].MoveForward(CAMERABACK);
		cameraframe[0].MoveUp(CAMERAUP);

		//吃到果子的操作
		if(Link_Num!=MaxLinkNum)
		{
			if(fruit.fruittype==NORMAL)
			{
				Score += 50;
				mciSendString("seek normal_f to start",NULL,0,NULL);
				mciSendString("play normal_f",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==LIFE)
			{
				Score += 80;
				Life++;
				mciSendString("seek laugh to start",NULL,0,NULL);
				mciSendString("play laugh",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==ANGEL)
			{
				Score += 100;
				angel = 1;
				mciSendString("seek angel to start",NULL,0,NULL);
				mciSendString("play angel",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==CHAOS)
			{
				Score += 100;
				chaos = 1;
				mciSendString("seek chaos to start",NULL,0,NULL);
				mciSendString("play chaos",NULL,0,NULL);
				//fruit初始
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==DASH)
			{
				Score += 100;
				mciSendString("seek follow to start",NULL,0,NULL);
				mciSendString("play follow",NULL,0,NULL);
				fruit.Initial();
				if(Link_Num == MaxLinkNum)
				{
					dash=0; //最后一个果实是DASH
				}
				else
				{
					dash = 1;			//进入冲刺状态
					maze.Maze_Initial();
				}
			}
		}
		else
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
	}
HERE1:
	start=next;
}