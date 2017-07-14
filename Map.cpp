#include "Sound.h"
#include "Barrier.h"
#include "SnakeLink.h"
#include "Scene.h"
#include "Cookies.h"
#include "Fruit.h"
#include "Map.h"
#include "Textures.h"


//全局变量
int map_ID = 0;
Map MapInfo[MAX_MAP_NUM]; //春，夏，秋，冬，太空

//初始化地图信息
void Initial_MapInfo()
{
	//Map_ID 0 春
	MapInfo[0].map_barrier_num=11;

	MapInfo[0].barrier_point[0][0]=-4;MapInfo[0].barrier_point[0][1]=-3;
	MapInfo[0].barrier_point[1][0]=-3;MapInfo[0].barrier_point[1][1]=-3;
	MapInfo[0].barrier_point[2][0]=-2;MapInfo[0].barrier_point[2][1]=-3;
	MapInfo[0].barrier_point[3][0]=-3;MapInfo[0].barrier_point[3][1]=-4;
	MapInfo[0].barrier_point[4][0]=-3;MapInfo[0].barrier_point[4][1]=-2;

	MapInfo[0].barrier_point[5][0]=-4;MapInfo[0].barrier_point[5][1]=2;
	MapInfo[0].barrier_point[6][0]=-3;MapInfo[0].barrier_point[6][1]=3;
	MapInfo[0].barrier_point[7][0]=-2;MapInfo[0].barrier_point[7][1]=4;

	MapInfo[0].barrier_point[8][0]=3;MapInfo[0].barrier_point[8][1]=2;
	MapInfo[0].barrier_point[9][0]=3;MapInfo[0].barrier_point[9][1]=3;
	MapInfo[0].barrier_point[10][0]=4;MapInfo[0].barrier_point[10][1]=2;

	MapInfo[0].pic_path[0]=photo_path0;
	MapInfo[0].pic_path[1]=photo_path5;
	MapInfo[0].pic_path[2]=photo_path10;
	MapInfo[0].pic_path[3]=photo_path15;
	MapInfo[0].pic_path[4]=photo_path20;
	MapInfo[0].pic_path[5]=photo_path25;
	MapInfo[0].pic_path[6]=photo_path30;
	MapInfo[0].pic_path[7]=photo_path35;
	MapInfo[0].pic_path[8]=photo_path40;
	MapInfo[0].pic_path[9]=photo_path45;
	MapInfo[0].pic_path[10]=photo_path50;
	MapInfo[0].pic_path[11]=photo_path55;

	MapInfo[0].texture[0]=&texture_ground;
	MapInfo[0].texture[1]=&texture_head;
	MapInfo[0].texture[2]=&texture_body;
	MapInfo[0].texture[3]=&texture_cookies;
	MapInfo[0].texture[4]=&texture_fruit_N;
	MapInfo[0].texture[5]=&texture_fruit_L;
	MapInfo[0].texture[6]=&texture_fruit_D;
	MapInfo[0].texture[7]=&texture_background;
	MapInfo[0].texture[8]=&texture_barrier;
	MapInfo[0].texture[9]=&texture_border;
	MapInfo[0].texture[10]=&texture_fruit_C;
	MapInfo[0].texture[11]=&texture_fruit_A;

	MapInfo[0].sound[0]=G_sound1;
	MapInfo[0].sound[1]=G_sound5;
	MapInfo[0].sound[2]=G_sound6;
	MapInfo[0].sound[3]=G_sound7;
	MapInfo[0].sound[4]=G_sound8;
	MapInfo[0].sound[5]=G_sound9;
	MapInfo[0].sound[6]=G_sound10;
	MapInfo[0].sound[7]=G_sound11;
	MapInfo[0].sound[8]=G_sound12;
	MapInfo[0].sound[9]=G_sound13;

	//Map_ID 1 夏
	MapInfo[1].map_barrier_num=18;

	MapInfo[1].barrier_point[0][0]=-1;MapInfo[1].barrier_point[0][1]=-4;
	MapInfo[1].barrier_point[1][0]=-2;MapInfo[1].barrier_point[1][1]=-3;

	MapInfo[1].barrier_point[2][0]=1;MapInfo[1].barrier_point[2][1]=-4;
	MapInfo[1].barrier_point[3][0]=2;MapInfo[1].barrier_point[3][1]=-3;

	MapInfo[1].barrier_point[4][0]=-1;MapInfo[1].barrier_point[4][1]=-1;
	MapInfo[1].barrier_point[5][0]=-2;MapInfo[1].barrier_point[5][1]=0;
	MapInfo[1].barrier_point[6][0]=-3;MapInfo[1].barrier_point[6][1]=1;
	MapInfo[1].barrier_point[7][0]=-4;MapInfo[1].barrier_point[7][1]=2;

	MapInfo[1].barrier_point[8][0]=1;MapInfo[1].barrier_point[8][1]=-1;
	MapInfo[1].barrier_point[9][0]=2;MapInfo[1].barrier_point[9][1]=0;
	MapInfo[1].barrier_point[10][0]=3;MapInfo[1].barrier_point[10][1]=1;
	MapInfo[1].barrier_point[11][0]=4;MapInfo[1].barrier_point[11][1]=2;

	MapInfo[1].barrier_point[12][0]=-1;MapInfo[1].barrier_point[12][1]=3;
	MapInfo[1].barrier_point[13][0]=0;MapInfo[1].barrier_point[13][1]=3;
	MapInfo[1].barrier_point[14][0]=1;MapInfo[1].barrier_point[14][1]=3;

	MapInfo[1].barrier_point[15][0]=-1;MapInfo[1].barrier_point[15][1]=4;
	MapInfo[1].barrier_point[16][0]=0;MapInfo[1].barrier_point[16][1]=4;
	MapInfo[1].barrier_point[17][0]=1;MapInfo[1].barrier_point[17][1]=4;

	MapInfo[1].pic_path[0]=photo_path1;
	MapInfo[1].pic_path[1]=photo_path6;
	MapInfo[1].pic_path[2]=photo_path11;
	MapInfo[1].pic_path[3]=photo_path16;
	MapInfo[1].pic_path[4]=photo_path21;
	MapInfo[1].pic_path[5]=photo_path26;
	MapInfo[1].pic_path[6]=photo_path31;
	MapInfo[1].pic_path[7]=photo_path36;
	MapInfo[1].pic_path[8]=photo_path41;
	MapInfo[1].pic_path[9]=photo_path46;
	MapInfo[1].pic_path[10]=photo_path51;
	MapInfo[1].pic_path[11]=photo_path56;

	MapInfo[1].texture[0]=&texture_ground;
	MapInfo[1].texture[1]=&texture_head;
	MapInfo[1].texture[2]=&texture_body;
	MapInfo[1].texture[3]=&texture_cookies;
	MapInfo[1].texture[4]=&texture_fruit_N;
	MapInfo[1].texture[5]=&texture_fruit_L;
	MapInfo[1].texture[6]=&texture_fruit_D;
	MapInfo[1].texture[7]=&texture_background;
	MapInfo[1].texture[8]=&texture_barrier;
	MapInfo[1].texture[9]=&texture_border;
	MapInfo[1].texture[10]=&texture_fruit_C;
	MapInfo[1].texture[11]=&texture_fruit_A;

	MapInfo[1].sound[0]=G_sound2;
	MapInfo[1].sound[1]=G_sound5;
	MapInfo[1].sound[2]=G_sound6;
	MapInfo[1].sound[3]=G_sound7;
	MapInfo[1].sound[4]=G_sound8;
	MapInfo[1].sound[5]=G_sound9;
	MapInfo[1].sound[6]=G_sound10;
	MapInfo[1].sound[7]=G_sound11;
	MapInfo[1].sound[8]=G_sound12;
	MapInfo[1].sound[9]=G_sound13;

	//Map_ID 2 秋
	MapInfo[2].map_barrier_num=22;

	MapInfo[2].barrier_point[0][0]=-4;MapInfo[2].barrier_point[0][1]=-3;
	MapInfo[2].barrier_point[1][0]=-3;MapInfo[2].barrier_point[1][1]=-3;
	MapInfo[2].barrier_point[2][0]=-2;MapInfo[2].barrier_point[2][1]=-3;

	MapInfo[2].barrier_point[3][0]=4;MapInfo[2].barrier_point[3][1]=-3;
	MapInfo[2].barrier_point[4][0]=3;MapInfo[2].barrier_point[4][1]=-3;
	MapInfo[2].barrier_point[5][0]=2;MapInfo[2].barrier_point[5][1]=-3;

	MapInfo[2].barrier_point[6][0]=-4;MapInfo[2].barrier_point[6][1]=3;
	MapInfo[2].barrier_point[7][0]=-3;MapInfo[2].barrier_point[7][1]=3;
	MapInfo[2].barrier_point[8][0]=-2;MapInfo[2].barrier_point[8][1]=3;

	MapInfo[2].barrier_point[9][0]=4;MapInfo[2].barrier_point[9][1]=3;
	MapInfo[2].barrier_point[10][0]=3;MapInfo[2].barrier_point[10][1]=3;
	MapInfo[2].barrier_point[11][0]=2;MapInfo[2].barrier_point[11][1]=3;

	MapInfo[2].barrier_point[12][0]=-3;MapInfo[2].barrier_point[12][1]=-1;
	MapInfo[2].barrier_point[13][0]=-3;MapInfo[2].barrier_point[13][1]=0;
	MapInfo[2].barrier_point[14][0]=-3;MapInfo[2].barrier_point[14][1]=1;

	MapInfo[2].barrier_point[15][0]=3;MapInfo[2].barrier_point[15][1]=-1;
	MapInfo[2].barrier_point[16][0]=3;MapInfo[2].barrier_point[16][1]=0;
	MapInfo[2].barrier_point[17][0]=3;MapInfo[2].barrier_point[17][1]=1;

	MapInfo[2].barrier_point[18][0]=-4;MapInfo[2].barrier_point[18][1]=0;
	MapInfo[2].barrier_point[19][0]=-2;MapInfo[2].barrier_point[19][1]=0;

	MapInfo[2].barrier_point[20][0]=4;MapInfo[2].barrier_point[20][1]=0;
	MapInfo[2].barrier_point[21][0]=2;MapInfo[2].barrier_point[21][1]=0;

	MapInfo[2].pic_path[0]=photo_path2;
	MapInfo[2].pic_path[1]=photo_path7;
	MapInfo[2].pic_path[2]=photo_path12;
	MapInfo[2].pic_path[3]=photo_path17;
	MapInfo[2].pic_path[4]=photo_path22;
	MapInfo[2].pic_path[5]=photo_path27;
	MapInfo[2].pic_path[6]=photo_path32;
	MapInfo[2].pic_path[7]=photo_path37;
	MapInfo[2].pic_path[8]=photo_path42;
	MapInfo[2].pic_path[9]=photo_path47;
	MapInfo[2].pic_path[10]=photo_path52;
	MapInfo[2].pic_path[11]=photo_path57;

	MapInfo[2].texture[0]=&texture_ground;
	MapInfo[2].texture[1]=&texture_head;
	MapInfo[2].texture[2]=&texture_body;
	MapInfo[2].texture[3]=&texture_cookies;
	MapInfo[2].texture[4]=&texture_fruit_N;
	MapInfo[2].texture[5]=&texture_fruit_L;
	MapInfo[2].texture[6]=&texture_fruit_D;
	MapInfo[2].texture[7]=&texture_background;
	MapInfo[2].texture[8]=&texture_barrier;
	MapInfo[2].texture[9]=&texture_border;
	MapInfo[2].texture[10]=&texture_fruit_C;
	MapInfo[2].texture[11]=&texture_fruit_A;

	MapInfo[2].sound[0]=G_sound3;
	MapInfo[2].sound[1]=G_sound5;
	MapInfo[2].sound[2]=G_sound6;
	MapInfo[2].sound[3]=G_sound7;
	MapInfo[2].sound[4]=G_sound8;
	MapInfo[2].sound[5]=G_sound9;
	MapInfo[2].sound[6]=G_sound10;
	MapInfo[2].sound[7]=G_sound11;
	MapInfo[2].sound[8]=G_sound12;
	MapInfo[2].sound[9]=G_sound13;

	//Map_ID 3 冬
	MapInfo[3].map_barrier_num=22;

	MapInfo[3].barrier_point[0][0]=-5;MapInfo[3].barrier_point[0][1]=-5;
	MapInfo[3].barrier_point[1][0]=-4;MapInfo[3].barrier_point[1][1]=-4;
	MapInfo[3].barrier_point[2][0]=-2;MapInfo[3].barrier_point[2][1]=-2;
	MapInfo[3].barrier_point[3][0]=-1;MapInfo[3].barrier_point[3][1]=-1;

	MapInfo[3].barrier_point[4][0]=-5;MapInfo[3].barrier_point[4][1]=5;
	MapInfo[3].barrier_point[5][0]=-4;MapInfo[3].barrier_point[5][1]=4;
	MapInfo[3].barrier_point[6][0]=-2;MapInfo[3].barrier_point[6][1]=2;
	MapInfo[3].barrier_point[7][0]=-1;MapInfo[3].barrier_point[7][1]=1;

	MapInfo[3].barrier_point[8][0]=5;MapInfo[3].barrier_point[8][1]=-5;
	MapInfo[3].barrier_point[9][0]=4;MapInfo[3].barrier_point[9][1]=-4;
	MapInfo[3].barrier_point[10][0]=2;MapInfo[3].barrier_point[10][1]=-2;
	MapInfo[3].barrier_point[11][0]=1;MapInfo[3].barrier_point[11][1]=-1;

	MapInfo[3].barrier_point[12][0]=5;MapInfo[3].barrier_point[12][1]=5;
	MapInfo[3].barrier_point[13][0]=4;MapInfo[3].barrier_point[13][1]=4;
	MapInfo[3].barrier_point[14][0]=2;MapInfo[3].barrier_point[14][1]=2;
	MapInfo[3].barrier_point[15][0]=1;MapInfo[3].barrier_point[15][1]=1;

	MapInfo[3].barrier_point[16][0]=-3;MapInfo[3].barrier_point[16][1]=0;
	MapInfo[3].barrier_point[17][0]=-5;MapInfo[3].barrier_point[17][1]=0;
	MapInfo[3].barrier_point[18][0]=-7;MapInfo[3].barrier_point[18][1]=0;

	MapInfo[3].barrier_point[19][0]=3;MapInfo[3].barrier_point[19][1]=0;
	MapInfo[3].barrier_point[20][0]=5;MapInfo[3].barrier_point[20][1]=0;
	MapInfo[3].barrier_point[21][0]=7;MapInfo[3].barrier_point[21][1]=0;

	MapInfo[3].pic_path[0]=photo_path3;
	MapInfo[3].pic_path[1]=photo_path8;
	MapInfo[3].pic_path[2]=photo_path13;
	MapInfo[3].pic_path[3]=photo_path18;
	MapInfo[3].pic_path[4]=photo_path23;
	MapInfo[3].pic_path[5]=photo_path28;
	MapInfo[3].pic_path[6]=photo_path33;
	MapInfo[3].pic_path[7]=photo_path38;
	MapInfo[3].pic_path[8]=photo_path43;
	MapInfo[3].pic_path[9]=photo_path48;
	MapInfo[3].pic_path[10]=photo_path53;
	MapInfo[3].pic_path[11]=photo_path58;

	MapInfo[3].texture[0]=&texture_ground;
	MapInfo[3].texture[1]=&texture_head;
	MapInfo[3].texture[2]=&texture_body;
	MapInfo[3].texture[3]=&texture_cookies;
	MapInfo[3].texture[4]=&texture_fruit_N;
	MapInfo[3].texture[5]=&texture_fruit_L;
	MapInfo[3].texture[6]=&texture_fruit_D;
	MapInfo[3].texture[7]=&texture_background;
	MapInfo[3].texture[8]=&texture_barrier;
	MapInfo[3].texture[9]=&texture_border;
	MapInfo[3].texture[10]=&texture_fruit_C;
	MapInfo[3].texture[11]=&texture_fruit_A;

	MapInfo[3].sound[0]=G_sound4;
	MapInfo[3].sound[1]=G_sound5;
	MapInfo[3].sound[2]=G_sound6;
	MapInfo[3].sound[3]=G_sound7;
	MapInfo[3].sound[4]=G_sound8;
	MapInfo[3].sound[5]=G_sound9;
	MapInfo[3].sound[6]=G_sound10;
	MapInfo[3].sound[7]=G_sound11;
	MapInfo[3].sound[8]=G_sound12;
	MapInfo[3].sound[9]=G_sound13;

	//Map_ID 4 太空
	MapInfo[4].map_barrier_num=28;

	MapInfo[4].barrier_point[0][0]=-4;MapInfo[4].barrier_point[0][1]=-4;
	MapInfo[4].barrier_point[1][0]=-4;MapInfo[4].barrier_point[1][1]=-3;
	MapInfo[4].barrier_point[2][0]=-4;MapInfo[4].barrier_point[2][1]=-2;
	MapInfo[4].barrier_point[3][0]=-4;MapInfo[4].barrier_point[3][1]=-1;
	MapInfo[4].barrier_point[4][0]=-3;MapInfo[4].barrier_point[4][1]=-1;
	MapInfo[4].barrier_point[5][0]=-2;MapInfo[4].barrier_point[5][1]=-1;

	MapInfo[4].barrier_point[6][0]=4;MapInfo[4].barrier_point[6][1]=-4;
	MapInfo[4].barrier_point[7][0]=4;MapInfo[4].barrier_point[7][1]=-3;
	MapInfo[4].barrier_point[8][0]=4;MapInfo[4].barrier_point[8][1]=-2;
	MapInfo[4].barrier_point[9][0]=4;MapInfo[4].barrier_point[9][1]=-1;
	MapInfo[4].barrier_point[10][0]=3;MapInfo[4].barrier_point[10][1]=-1;
	MapInfo[4].barrier_point[11][0]=2;MapInfo[4].barrier_point[11][1]=-1;

	MapInfo[4].barrier_point[12][0]=4;MapInfo[4].barrier_point[12][1]=4;
	MapInfo[4].barrier_point[13][0]=4;MapInfo[4].barrier_point[13][1]=3;
	MapInfo[4].barrier_point[14][0]=4;MapInfo[4].barrier_point[14][1]=2;
	MapInfo[4].barrier_point[15][0]=4;MapInfo[4].barrier_point[15][1]=1;
	MapInfo[4].barrier_point[16][0]=3;MapInfo[4].barrier_point[16][1]=1;
	MapInfo[4].barrier_point[17][0]=2;MapInfo[4].barrier_point[17][1]=1;

	MapInfo[4].barrier_point[18][0]=-4;MapInfo[4].barrier_point[18][1]=4;
	MapInfo[4].barrier_point[19][0]=-4;MapInfo[4].barrier_point[19][1]=3;
	MapInfo[4].barrier_point[20][0]=-4;MapInfo[4].barrier_point[20][1]=2;
	MapInfo[4].barrier_point[21][0]=-4;MapInfo[4].barrier_point[21][1]=1;
	MapInfo[4].barrier_point[22][0]=-3;MapInfo[4].barrier_point[22][1]=1;
	MapInfo[4].barrier_point[23][0]=-2;MapInfo[4].barrier_point[23][1]=1;

	MapInfo[4].barrier_point[24][0]=-1;MapInfo[4].barrier_point[24][1]=4;
	MapInfo[4].barrier_point[25][0]=1;MapInfo[4].barrier_point[25][1]=4;

	MapInfo[4].barrier_point[26][0]=-1;MapInfo[4].barrier_point[26][1]=-4;
	MapInfo[4].barrier_point[27][0]=1;MapInfo[4].barrier_point[27][1]=-4;


	MapInfo[4].pic_path[0]=photo_path4;
	MapInfo[4].pic_path[1]=photo_path9;
	MapInfo[4].pic_path[2]=photo_path14;
	MapInfo[4].pic_path[3]=photo_path19;
	MapInfo[4].pic_path[4]=photo_path24;
	MapInfo[4].pic_path[5]=photo_path29;
	MapInfo[4].pic_path[6]=photo_path34;
	MapInfo[4].pic_path[7]=photo_path39;
	MapInfo[4].pic_path[8]=photo_path44;
	MapInfo[4].pic_path[9]=photo_path49;
	MapInfo[4].pic_path[10]=photo_path54;
	MapInfo[4].pic_path[11]=photo_path59;

	MapInfo[4].texture[0]=&texture_ground;
	MapInfo[4].texture[1]=&texture_head;
	MapInfo[4].texture[2]=&texture_body;
	MapInfo[4].texture[3]=&texture_cookies;
	MapInfo[4].texture[4]=&texture_fruit_N;
	MapInfo[4].texture[5]=&texture_fruit_L;
	MapInfo[4].texture[6]=&texture_fruit_D;
	MapInfo[4].texture[7]=&texture_background;
	MapInfo[4].texture[8]=&texture_barrier;
	MapInfo[4].texture[9]=&texture_border;
	MapInfo[4].texture[10]=&texture_fruit_C;
	MapInfo[4].texture[11]=&texture_fruit_A;

	MapInfo[4].sound[0]=G_sound0;
	MapInfo[4].sound[1]=G_sound5;
	MapInfo[4].sound[2]=G_sound6;
	MapInfo[4].sound[3]=G_sound7;
	MapInfo[4].sound[4]=G_sound8;
	MapInfo[4].sound[5]=G_sound9;
	MapInfo[4].sound[6]=G_sound10;
	MapInfo[4].sound[7]=G_sound11;
	MapInfo[4].sound[8]=G_sound12;
	MapInfo[4].sound[9]=G_sound13;

}

//加载地图信息 
void Map::loadmap()
{
	
	//加载12种纹理
	texture[0]->LoadFromFile(pic_path[0]);
	texture[1]->LoadFromFile(pic_path[1]);
	texture[2]->LoadFromFile(pic_path[2]);
	texture[3]->LoadFromFile(pic_path[3]);
	texture[4]->LoadFromFile(pic_path[4]);
	texture[5]->LoadFromFile(pic_path[5]);
	texture[6]->LoadFromFile(pic_path[6]);
	texture[7]->LoadFromFile(pic_path[7]);
	texture[8]->LoadFromFile(pic_path[8]);
	texture[9]->LoadFromFile(pic_path[9]);
	texture[10]->LoadFromFile(pic_path[10]);
	texture[11]->LoadFromFile(pic_path[11]);

	//加载barrier_point的值给barrier[MaxBarrierNum]
	Barrier_Num = map_barrier_num;
	for(int i=0;i<Barrier_Num;i++)
	{
		barrier[i].x=barrier_point[i][0];
		barrier[i].y=barrier_point[i][1];
		barrier[i].LocalSystem.SetOrigin(barrier[i].x,0,barrier[i].y);
	}
	
	//声音初始化（Close&Open）
	mciSendString("close background", NULL, 0, NULL);//关闭声音
	mciSendString("close eating", NULL, 0, NULL);
	mciSendString("close starting", NULL, 0, NULL);
	mciSendString("close crosslevel", NULL, 0, NULL);
	mciSendString("close die", NULL, 0, NULL);
	mciSendString("close follow", NULL, 0, NULL);
	mciSendString("close laugh", NULL, 0, NULL);
	mciSendString("close chaos", NULL, 0, NULL);
	mciSendString("close normal_f", NULL, 0, NULL);
	mciSendString("close angel", NULL, 0, NULL);

	mciSendString(sound[0], NULL, 0, NULL);//打开声音
	mciSendString(sound[1], NULL, 0, NULL);
	mciSendString(sound[2], NULL, 0, NULL);
	mciSendString(sound[3], NULL, 0, NULL);
	mciSendString(sound[4], NULL, 0, NULL);
	mciSendString(sound[5], NULL, 0, NULL);
	mciSendString(sound[6], NULL, 0, NULL);
	mciSendString(sound[7], NULL, 0, NULL);
	mciSendString(sound[8], NULL, 0, NULL);
	mciSendString(sound[9], NULL, 0, NULL);
	
	//reset 蛇头，蛇节，方向，cameraframe,chaos,angel
	Link_Num=3;
	camera_sel=0;
	chaos=0;
	angel=0;

	snake[0].LocalSystem.SetOrigin(0.0f,0.0f,0.0f);
	snake[0].LocalSystem.SetForwardVector(0,0,-1);
	snake[0].x=0;snake[0].y=0;
	snake[1].LocalSystem.SetOrigin(0.0f,0.0f,1.0f);
	snake[1].LocalSystem.SetForwardVector(0,0,-1);
	snake[1].x=0;snake[1].y=1;
	snake[2].LocalSystem.SetOrigin(0.0f,0.0f,2.0f);
	snake[2].LocalSystem.SetForwardVector(0,0,-1);
	snake[2].x=0;snake[2].y=2;
			//视点与蛇头坐标系一致
	cameraframe[0].SetOrigin(snake[0].x,0,snake[0].y);
	float temp_vector[3];
	snake[0].LocalSystem.GetForwardVector(temp_vector);
	cameraframe[0].SetForwardVector(temp_vector);
			//移动视点到蛇头后上方
	cameraframe[0].MoveForward(CAMERABACK);
	cameraframe[0].MoveUp(CAMERAUP);

	//fruit初始
	fruit.Initial();

	//cookies初始

	for(int i=0 ;i< MAX_COOKIES_NUM ; i++)
	{
		cookies[i].Initial();
	}
	
	//border初始
	Initial_Border();
	
}