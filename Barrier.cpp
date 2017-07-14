#include "Barrier.h"

//全局变量
int Barrier_Num;
Barrier barrier[MaxBarrierNum];
Barrier border[BorderNum];

void Initial_Border()
{	
	int i,j;
	//上面
	for(j=-(COL+1)/2,i=0;i<COL+2;i++,j++)	//13
	{
		
		border[i].x=j; border[i].y=-(ROW+1)/2;border[i].LocalSystem.SetOrigin(j,0,-(ROW+1)/2);
		
	}
	//下面
	for(j=-(COL+1)/2;i<(COL+2)*2;i++,j++)	//26
	{

		border[i].x=j;border[i].y=(ROW+1)/2;border[i].LocalSystem.SetOrigin(j,0,(ROW+1)/2);

	}
	//左面
	for(j=-(ROW-1)/2;i<(COL+2)*2+ROW;i++,j++)		//37
	{

		border[i].x=-(COL+1)/2;border[i].y=j;border[i].LocalSystem.SetOrigin(-(COL+1)/2,0,j);

	}
	//右面
	for(j=-(ROW-1)/2;i<(COL+2)*2+ROW*2;i++,j++)		//48
	{

		border[i].x=(COL+1)/2;border[i].y=j;border[i].LocalSystem.SetOrigin((COL+1)/2,0,j);
	
	}
}