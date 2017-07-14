#ifndef MAP_H
#define MAP_H

#include "CTexture.h"
#include "Barrier.h"
#define  MAX_MAP_NUM 5

class Map
{
public:
	void loadmap();

	int map_barrier_num;
	float barrier_point [MaxBarrierNum][2];
	char *pic_path[12];
	//0->ground;1->head;2->body;3->cookies;4->fruit_N;5->fruit_L;6->fruit_D;7->background;8->barrier;9->border;10->fruit_C;11->fruit_A
	CTexture *texture[12];
	// &texture_ground;&texture_head;&texture_body;&texture_cookies;&texture_fruit_N;
	//&texture_fruit_L;&texture_fruit_D;&texture_background;&texture_barrier;&texture_border;&texture_fruit_C;&texture_fruit_A;
	char *sound[10];
	//0->background;1->eating;2->starting;3->crosslevel;4->die;5->follow;6->laugh;7->chaos;8->normal_f;9->angel;

};


extern int map_ID;
extern Map MapInfo[MAX_MAP_NUM];



extern void Initial_MapInfo();

#endif