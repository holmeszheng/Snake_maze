/*
//GLtools
#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>
#pragma comment(lib,"gltools.lib")
*/

#include "Barrier.h"
#include "Cookies.h"
#include "Font.h"
#include "Fruit.h"
#include "Maze.h"
#include "Object.h"
#include "Scene.h"
#include "SnakeLink.h"
#include "Sound.h"
#include "Turn.h"
#include "CTexture.h"
#include "Map.h"
#include "Textures.h"

//system
#include <time.h>
#include <iostream> 
#include <math.h>
using namespace std;

/*
//GLtools
#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>
#pragma comment(lib,"gltools.lib")

*/

//glut.h
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif


//////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering
// context. 
void SetupRC()
    {
	// Initialze Shader Manager
	shaderManager.InitializeStockShaders();
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//loading_I的容器和纹理
	DrawPicture(FixpBatch,960,540,1920, 1080,0);
	texture_fixp1.LoadFromFile("Pictures/loading_I.jpg");

	cameraframe[1].SetOrigin(0.0f,14.0f,0.0f);
	cameraframe[1].SetForwardVector(0.0f,-1.0f,0.0f);
	cameraframe[1].SetUpVector(0.0f,0.0f,-1.0f);

	//所有容器
	Initial_Batchs();


	M3DVector3f points[3] = {{1.0f, -0.41f, 0.0f},
	{-1.0f, -0.41f, 0.0f},
	{0.0f,-0.41f, 1.0f}};
	//构造投影平面
	M3DVector4f vPlaneEquation;
	m3dGetPlaneEquation(vPlaneEquation, points[0], points[1], points[2]);
	//计算投影矩阵
	m3dMakePlanarShadowMatrix(shadowMat, vPlaneEquation, vLightPos);
    }

        
// Called to draw scene
void RenderScene(void)
	{
		switch(Current_Scene)
		{
		case LOADING_I:
			Load_I_Scene();
			Initial_MapInfo();
			LoadfixedPictures();
			srand((unsigned int)time(NULL));			
			Current_Scene=INITIAL;
			glutPostRedisplay();
			break;

		case INITIAL:
			Init_Scene();
			break;

		case SELECT:
			Sel_Scene();
			break;

		case LOADING_E:
			Load_E_Scene();
			MapInfo[map_ID].loadmap();
			Current_Scene=LEVEL;
			mciSendString("play background repeat",NULL,0,NULL);
			mciSendString("seek starting to start",NULL,0,NULL);
			mciSendString("play starting",NULL,0,NULL);
			break;

		case LEVEL:
			switch(dash)
			{
			case 0:
				Go_Straight();
				break;
			case 1:
				maze.GetMove();
			}
			Level_Scene();
			break;

		case LOADING_D:
			Load_D_Scene();
			break;

		case GAMEOVER:
			Life = 3;
			Score = 0;
			GameOverScene();
			break;

		case CLEARED:
			Life = 3;
			Score = 0;
			Cleared_Scene();
			break;
		}
    }


// Respond to arrow keys 
void SpecialKeys(int key, int x, int y)
    {
		switch(Current_Scene)
		{
		case LOADING_I:
			break;
		case INITIAL:
			if(key == GLUT_KEY_UP)
			{
				scroll_num--;
				if(scroll_num<0)
					scroll_num=2;
			}

			if(key == GLUT_KEY_DOWN)
			{
				scroll_num++;
				scroll_num=scroll_num % 3;
			}

			if(key == GLUT_KEY_LEFT)
			{
				scroll_num--;
				if(scroll_num<0)
					scroll_num=2;
			}

			if(key == GLUT_KEY_RIGHT)
			{
				scroll_num++;
				scroll_num=scroll_num % 3;
			}

			glutPostRedisplay();
			break;
		case SELECT:
			if(key == GLUT_KEY_UP)
			{
				scroll_num--;
				if(scroll_num<0)
					scroll_num=4;
			}

			if(key == GLUT_KEY_DOWN)
			{
				scroll_num++;
				scroll_num=scroll_num % 5;
			}

			if(key == GLUT_KEY_LEFT)
			{
				scroll_num--;
				if(scroll_num<0)
					scroll_num=4;
			}

			if(key == GLUT_KEY_RIGHT)
			{
				scroll_num++;
				scroll_num=scroll_num % 5;
			}

			glutPostRedisplay();
			break;
		case LOADING_E:
			break;
		case LEVEL:
			if(camera_sel==1)
			{
				if(key == GLUT_KEY_UP)
				{
					cameraframe[1].MoveForward(1.0f);
				}

				if(key == GLUT_KEY_DOWN)
				{
					cameraframe[1].MoveForward(-1.0f);
				}
			}
			switch(dash)
			{
			case 0:
				if(key == GLUT_KEY_LEFT)
				{
					if(chaos == 0)
						Turn_Left();
					else
						Turn_Right();
				}

				if(key == GLUT_KEY_RIGHT)
				{
					if(chaos == 0)
						Turn_Right();
					else
						Turn_Left();
				}
				break;
			case 1:
				break;
			}
			break;
		case LOADING_D:
			if(key == GLUT_KEY_UP)
			{
				scroll_num--;
				if(scroll_num<0)
					scroll_num=2;
			}

			if(key == GLUT_KEY_DOWN)
			{
				scroll_num++;
				scroll_num=scroll_num % 3;
			}

			if(key == GLUT_KEY_LEFT)
			{
				scroll_num--;
				if(scroll_num<0)
					scroll_num=2;
			}

			if(key == GLUT_KEY_RIGHT)
			{
				scroll_num++;
				scroll_num=scroll_num % 3;
			}

			glutPostRedisplay();
			break;
		case GAMEOVER:
			if(key == GLUT_KEY_UP)
			{
				scroll_num--;
				if(scroll_num<0)
					scroll_num=1;
			}

			if(key == GLUT_KEY_DOWN)
			{
				scroll_num++;
				scroll_num=scroll_num % 2;
			}

			if(key == GLUT_KEY_LEFT)
			{
				scroll_num--;
				if(scroll_num<0)
					scroll_num=1;
			}

			if(key == GLUT_KEY_RIGHT)
			{
				scroll_num++;
				scroll_num=scroll_num % 2;
			}

			glutPostRedisplay();
			break;
		case CLEARED:
			if(key == GLUT_KEY_UP)
			{
				scroll_num--;
				if(scroll_num<0)
					scroll_num=1;
			}

			if(key == GLUT_KEY_DOWN)
			{
				scroll_num++;
				scroll_num=scroll_num % 2;
			}

			if(key == GLUT_KEY_LEFT)
			{
				scroll_num--;
				if(scroll_num<0)
					scroll_num=1;
			}

			if(key == GLUT_KEY_RIGHT)
			{
				scroll_num++;
				scroll_num=scroll_num % 2;
			}

			glutPostRedisplay();
			break;

		}
	
    }

//Reshape
void ChangeSize(int nWidth, int nHeight)
    {
	glViewport(0, 0, nWidth, nHeight);
	
	winWidth=nWidth;
	winHeight=nHeight;


	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);

	viewFrustum.SetPerspective(55.0f, float(nWidth)/float(nHeight), 0.1, 10000.0f);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());

	modelViewMatrix.LoadIdentity();

	viewFrustum.SetOrthographic(0,1920,0,1080,-5,+5);
	projectionMatrix_o.LoadMatrix(viewFrustum.GetProjectionMatrix());
	}

//KeyboardFunc
void KeyboardFunc(unsigned char key, int x, int y)
{
	if(key == 32)
	{
		if(Current_Scene==LEVEL)
		{
			if(camera_sel==0)
				camera_sel = 1;
			else
				camera_sel = 0;
		}
	}

	if(key == 13)
	{
		switch(Current_Scene)
		{
		case LOADING_I:
			break;
		case INITIAL:
			if(scroll_num==0)
			{
				map_ID=0;
				Current_Scene=LOADING_E;
				glutPostRedisplay();
			}
			if(scroll_num==1)
			{
				Current_Scene=SELECT;
				glutPostRedisplay();
			}
			if(scroll_num==2)
			{
				exit(0);
			}
			scroll_num=0;
			break;
		case SELECT:
			if(scroll_num==0)
			{
				map_ID=0;
				Current_Scene=LOADING_E;
				glutPostRedisplay();
			}
			if(scroll_num==1)
			{
				map_ID=1;
				Current_Scene=LOADING_E;
				glutPostRedisplay();
			}
			if(scroll_num==2)
			{
				map_ID=2;
				Current_Scene=LOADING_E;
				glutPostRedisplay();
			}
			if(scroll_num==3)
			{
				map_ID=3;
				Current_Scene=LOADING_E;
				glutPostRedisplay();
			}
			if(scroll_num==4)
			{
				map_ID=4;
				Current_Scene=LOADING_E;
				glutPostRedisplay();
			}
			scroll_num=0;
			break;
		case LOADING_E:
			break;
		case LEVEL:
			break;
		case LOADING_D:
			if(scroll_num==0)
			{
				Current_Scene=LOADING_E;
				glutPostRedisplay();
			}
			if(scroll_num==1)
			{
				Current_Scene=SELECT;
				glutPostRedisplay();
			}
			if(scroll_num==2)
			{
				exit(0);
			}
			scroll_num=0;
			break;
		case GAMEOVER:
			if(scroll_num==0)
			{
				Current_Scene=INITIAL;
				glutPostRedisplay();
			}
			if(scroll_num==1)
			{
				exit(0);
				
			}
			scroll_num=0;
			break;
		case CLEARED:
			if(scroll_num==0)
			{
				Current_Scene=INITIAL;
				glutPostRedisplay();
			}
			if(scroll_num==1)
			{
				exit(0);

			}
			scroll_num=0;
			break;
		}
	}
}

//TimerFunc
void MyTimer(int value)
{
	switch(Current_Scene)
	{
	case LEVEL:
		glutTimerFunc(INTERVAL,MyTimer,0);
		glutPostRedisplay();
		break;
	default:
		glutTimerFunc(INTERVAL,MyTimer,0);
	}
}





int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(0, 0); 
	glutInitWindowSize(1920,1080);
	glutCreateWindow("Snake World By Mr Merlyn");

	glutKeyboardFunc(KeyboardFunc);
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(SpecialKeys);
	glutTimerFunc(INTERVAL,MyTimer,0);


	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}


	SetupRC();
	glutMainLoop();    
	return 0;
}