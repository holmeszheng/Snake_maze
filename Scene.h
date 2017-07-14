#ifndef SCENE_H
#define SCENE_H

//GLtools
#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>
#include <GLFrame.h>
#pragma comment(lib,"gltools.lib")

#define BG_PC_FACTOR_X 1
#define BG_PC_FACTOR_Y 1
#define BG_UP_OFFSET 60
#define BG_DISTANCE 1000.0f

#define CAMERABACK -2.8f
#define CAMERAUP 1.3f

#define INTERVAL 300
typedef enum Scene_Manager {LOADING_I,INITIAL,SELECT,LOADING_E,LEVEL,LOADING_D,GAMEOVER,CLEARED};

extern Scene_Manager Current_Scene;

extern GLShaderManager		shaderManager;			// Shader Manager
extern GLMatrixStack		modelViewMatrix;		// Modelview Matrix
extern GLMatrixStack		projectionMatrix;		// Perspective Projection Matrix
extern GLMatrixStack		projectionMatrix_o;		// Orthographic Projection Matrix
extern GLFrustum			viewFrustum;			// View Frustum
extern GLGeometryTransform	transformPipeline;		// Geometry Transform Pipeline
extern GLFrame				cameraframe[2];			// Camera frame

extern int dash;								 //���
extern int chaos;								//����
extern int angel;								//�޵�
extern int scroll_num;							 //�˵���
extern int camera_sel;							//���ѡ��
extern GLfloat	vLightPos[4];					//�ƹ�λ��
extern M3DMatrix44f		shadowMat;				//��Ӱ����

void DrawSongAndDance(GLfloat );	
void Load_I_Scene();
void Init_Scene();
void Sel_Scene();
void Load_E_Scene();
void Level_Scene();
void Load_D_Scene();
void GameOverScene();
void Cleared_Scene();

#endif