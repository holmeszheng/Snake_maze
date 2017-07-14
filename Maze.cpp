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

//ȫ�ֱ���
TrackMap maze;

void TrackMap::Maze_Initial()
{  
	int i,j,k;
	for(i=0;i<COL+2;i++)			//�����ʼ0
		for(j=0;j<ROW+2;j++)
			trackzone[i][j] = 0;

	for(i = 0; i < ROW+2; ++i){		//���Ҽ�ǽ  
		trackzone[0][i] = 1;  
		trackzone[COL+1][i] = 1;  
	}  
	for(i = 1; i <COL+1; ++i){			//���¼�ǽ  
		trackzone[i][0] = 1;  
		trackzone[i][ROW+1] = 1;  
	}  
	for(k = 0; k < Barrier_Num; k++)		//BARRIER[K]��ֵ�ָ������Բ����нضϵ�����
	{
		trackzone[(int)barrier[k].LocalSystem.GetOriginX()+(COL+1)/2][(int)barrier[k].LocalSystem.GetOriginZ()+(ROW+1)/2]=1;
	}
	queue<point*> q;  
	point *start = (point*)malloc(sizeof(point));//���  
	start->x=(int)(snake[0].LocalSystem.GetOriginX()+(COL+1)/2+0.5);
	start->y=(int)(snake[0].LocalSystem.GetOriginZ()+(ROW+1)/2+0.5); 

	start->last = start;  
	q.push(start);  

	trackzone[start->x][start->y] = 2;  

	point end;//�յ�  
	end.x=(int)(fruit.LocalSystem.GetOriginX()+(COL+1)/2+0.5);
	end.y=(int)(fruit.LocalSystem.GetOriginZ()+(ROW+1)/2+0.5);

	int aspect[4][2] = {{0, -1},{0, 1},{-1, 0},{1, 0}};//ת����������  
	int flag = 0;//�Ƿ���·���ߵı�־  
	while(!q.empty()){  
		point *front = q.front();  
		q.pop();//������ͷ  
		if(front->x == end.x && front->y == end.y){  
			flag = 1;  
			cout<<"�ɹ��ҵ���·."<<"������Ҫ"<<trackzone[front->x][front->y]-2<<"����������ʾ��"<<endl;  
			trackzone[front->x][front->y] = -6;  
			//cout<<"���˻�ȥ��"<<(front)->x<<","<<(front)->y;  
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
		cout<<"��·���ߣ�"<<endl;  
	else{  
		string s[6] = {"��", "��", "��","��","��","��" };  
		for(int j = 0; j < ROW+2; ++j){  
			for(int i = 0; i < COL+2; ++i){  
				if(trackzone[i][j]==1){  
					cout<<"��";  
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
		//�ж����������Ƿ��м�ͷ
		//����
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
		//������һ�ڷ���
		snake[1].LocalSystem.SetForwardVector(0.0f,0.0f,1.0f);
		//���trackzone��ά����startλ�ñ���
		trackzone[start.x][start.y] = 0;

		//�ӵ�����ͷ����ϵһ��
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//�ƶ��ӵ㵽��ͷ���Ϸ�
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

	//����
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

		//�ӵ�����ͷ����ϵһ��
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//�ƶ��ӵ㵽��ͷ���Ϸ�
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
	//����
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

		//�ӵ�����ͷ����ϵһ��
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//�ƶ��ӵ㵽��ͷ���Ϸ�
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
	//����
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

		//�ӵ�����ͷ����ϵһ��
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//�ƶ��ӵ㵽��ͷ���Ϸ�
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

	//�ж����������Ƿ����յ�
	//����
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

		//�ӵ�����ͷ����ϵһ��
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//�ƶ��ӵ㵽��ͷ���Ϸ�
		cameraframe[0].MoveForward(CAMERABACK);
		cameraframe[0].MoveUp(CAMERAUP);

		//�Ե����ӵĲ���
		if(Link_Num!=MaxLinkNum)
		{
			if(fruit.fruittype==NORMAL)
			{
				Score += 50;
				mciSendString("seek normal_f to start",NULL,0,NULL);
				mciSendString("play normal_f",NULL,0,NULL);
				//fruit��ʼ
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==LIFE)
			{
				Score += 80;
				Life++;
				mciSendString("seek laugh to start",NULL,0,NULL);
				mciSendString("play laugh",NULL,0,NULL);
				//fruit��ʼ
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==ANGEL)
			{
				Score += 100;
				angel = 1;
				mciSendString("seek angel to start",NULL,0,NULL);
				mciSendString("play angel",NULL,0,NULL);
				//fruit��ʼ
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==CHAOS)
			{
				Score += 100;
				chaos = 1;
				mciSendString("seek chaos to start",NULL,0,NULL);
				mciSendString("play chaos",NULL,0,NULL);
				//fruit��ʼ
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
					dash=0; //���һ����ʵ��DASH
				}
				else
				{
					dash = 1;			//������״̬
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

	//����
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

		//�ӵ�����ͷ����ϵһ��
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//�ƶ��ӵ㵽��ͷ���Ϸ�
		cameraframe[0].MoveForward(CAMERABACK);
		cameraframe[0].MoveUp(CAMERAUP);

		//�Ե����ӵĲ���
		if(Link_Num!=MaxLinkNum)
		{
			if(fruit.fruittype==NORMAL)
			{
				Score += 50;
				mciSendString("seek normal_f to start",NULL,0,NULL);
				mciSendString("play normal_f",NULL,0,NULL);
				//fruit��ʼ
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==LIFE)
			{
				Score += 80;
				Life++;
				mciSendString("seek laugh to start",NULL,0,NULL);
				mciSendString("play laugh",NULL,0,NULL);
				//fruit��ʼ
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==ANGEL)
			{
				Score += 100;
				angel = 1;
				mciSendString("seek angel to start",NULL,0,NULL);
				mciSendString("play angel",NULL,0,NULL);
				//fruit��ʼ
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==CHAOS)
			{
				Score += 100;
				chaos = 1;
				mciSendString("seek chaos to start",NULL,0,NULL);
				mciSendString("play chaos",NULL,0,NULL);
				//fruit��ʼ
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
					dash=0; //���һ����ʵ��DASH
				}
				else
				{
					dash = 1;			//������״̬
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
	//����
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

		//�ӵ�����ͷ����ϵһ��
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//�ƶ��ӵ㵽��ͷ���Ϸ�
		cameraframe[0].MoveForward(CAMERABACK);
		cameraframe[0].MoveUp(CAMERAUP);

		//�Ե����ӵĲ���
		if(Link_Num!=MaxLinkNum)
		{
			if(fruit.fruittype==NORMAL)
			{
				Score += 50;
				mciSendString("seek normal_f to start",NULL,0,NULL);
				mciSendString("play normal_f",NULL,0,NULL);
				//fruit��ʼ
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==LIFE)
			{
				Score += 80;
				Life++;
				mciSendString("seek laugh to start",NULL,0,NULL);
				mciSendString("play laugh",NULL,0,NULL);
				//fruit��ʼ
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==ANGEL)
			{
				Score += 100;
				angel = 1;
				mciSendString("seek angel to start",NULL,0,NULL);
				mciSendString("play angel",NULL,0,NULL);
				//fruit��ʼ
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==CHAOS)
			{
				Score += 100;
				chaos = 1;
				mciSendString("seek chaos to start",NULL,0,NULL);
				mciSendString("play chaos",NULL,0,NULL);
				//fruit��ʼ
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
					dash=0; //���һ����ʵ��DASH
				}
				else
				{
					dash = 1;			//������״̬
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
	//����
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

		//�ӵ�����ͷ����ϵһ��
		cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
		float temp_vector[3];
		snake[0].LocalSystem.GetForwardVector(temp_vector);
		cameraframe[0].SetForwardVector(temp_vector);
		//�ƶ��ӵ㵽��ͷ���Ϸ�
		cameraframe[0].MoveForward(CAMERABACK);
		cameraframe[0].MoveUp(CAMERAUP);

		//�Ե����ӵĲ���
		if(Link_Num!=MaxLinkNum)
		{
			if(fruit.fruittype==NORMAL)
			{
				Score += 50;
				mciSendString("seek normal_f to start",NULL,0,NULL);
				mciSendString("play normal_f",NULL,0,NULL);
				//fruit��ʼ
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==LIFE)
			{
				Score += 80;
				Life++;
				mciSendString("seek laugh to start",NULL,0,NULL);
				mciSendString("play laugh",NULL,0,NULL);
				//fruit��ʼ
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==ANGEL)
			{
				Score += 100;
				angel = 1;
				mciSendString("seek angel to start",NULL,0,NULL);
				mciSendString("play angel",NULL,0,NULL);
				//fruit��ʼ
				fruit.Initial();
				goto HERE1;
			}
			if(fruit.fruittype==CHAOS)
			{
				Score += 100;
				chaos = 1;
				mciSendString("seek chaos to start",NULL,0,NULL);
				mciSendString("play chaos",NULL,0,NULL);
				//fruit��ʼ
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
					dash=0; //���һ����ʵ��DASH
				}
				else
				{
					dash = 1;			//������״̬
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