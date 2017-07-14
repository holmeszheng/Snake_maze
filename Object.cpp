#include "Object.h"
#include "gltools.h"
#include "Scene.h"
#include "Maze.h"

//全局变量

//scene batch
//箭头容器
GLBatch arrowBach2_1;
GLBatch arrowBach2_2;
GLBatch arrowBach2_3;

GLBatch arrowBach3_1;
GLBatch arrowBach3_2;
GLBatch arrowBach3_3;
GLBatch arrowBach3_4;
GLBatch arrowBach3_5;

GLBatch arrowBach6_1;
GLBatch arrowBach6_2;
GLBatch arrowBach6_3;

GLBatch arrowBach7_1;
GLBatch arrowBach7_2;

GLBatch arrowBach8_1;
GLBatch arrowBach8_2;

//整图容器
GLBatch FixpBatch;

//level 容器
GLTriangleBatch		torusBatch;			    //fruit
GLTriangleBatch		sphereBatch;		    //cookies
GLBatch				floorBatch[5];			//ground1;ground2;ground3;ground4;ground5

GLTriangleBatch		headSphereBatch;		//snake head
GLTriangleBatch		holeSphereBatch;		//hole
GLTriangleBatch		bodyCylinderBatch;		//snake body
GLTriangleBatch		chaosBallBatch;			//chaos ball
GLTriangleBatch		angelTorusBatch;		//angel torus
GLBatch				cubeBatch;				//barrier,border

GLBatch				picture1Batch;			//back picture
GLBatch				picture2Batch;			//front picture
GLBatch				picture3Batch;			//left picture
GLBatch				picture4Batch;			//right picture



void DrawPicture(GLBatch& picture,GLfloat x,GLfloat y,GLfloat w, GLfloat h,GLfloat z)//x,y为坐标，正视投影，左下角为（0，0）
{

	picture.Begin(GL_TRIANGLES, 6, 1);

	// Bottom of pyramid
	picture.Normal3f(0.0f, 0.0f, 1.0f);
	picture.MultiTexCoord2f(0, 0.0f, 0.0f);
	picture.Vertex3f(x-w/2, y-h/2, z);

	picture.Normal3f(0.0f, 0.0f, 1.0f);
	picture.MultiTexCoord2f(0, 1.0f, 0.0f);
	picture.Vertex3f(x+w/2, y-h/2, z);

	picture.Normal3f(0.0f, 0.0f, 1.0f);
	picture.MultiTexCoord2f(0, 1.0f, 1.0f);
	picture.Vertex3f(x+w/2, y+h/2, z);

	picture.Normal3f(0.0f, 0.0f, 1.0f);
	picture.MultiTexCoord2f(0, 0.0f, 1.0f);
	picture.Vertex3f(x-w/2, y+h/2,z);

	picture.Normal3f(0.0f, 0.0f, 1.0f);
	picture.MultiTexCoord2f(0, 0.0f, 0.0f);
	picture.Vertex3f(x-w/2, y-h/2, z);

	picture.Normal3f(0.0f, 0.0f, 1.0f);
	picture.MultiTexCoord2f(0, 1.0f, 1.0f);
	picture.Vertex3f(x+w/2, y+h/2, z);

	picture.End();
}

void Initial_Batchs()
{
	//scene batch

	//Initial scene
	DrawPicture(arrowBach2_1,820 , 625,140, 144,1);
	DrawPicture(arrowBach2_2,940 , 450,140, 144,1);
	DrawPicture(arrowBach2_3,990 , 260,140, 144,1);

	//Select Scene
	DrawPicture(arrowBach3_1,100 , 630 ,140, 144,1);
	DrawPicture(arrowBach3_2,1810 , 630 ,140, 144,1);
	DrawPicture(arrowBach3_3,185 , 195 ,140, 144,1);
	DrawPicture(arrowBach3_4,1700 , 195 ,140, 144,1);
	DrawPicture(arrowBach3_5,625 , 940 ,140, 144,1);

	//loading_D Scene
	DrawPicture(arrowBach6_1,1300 , 860,140, 144,1);
	DrawPicture(arrowBach6_2,1350 , 540,140, 144,1);
	DrawPicture(arrowBach6_3,1350 , 250,140, 144,1);

	//GameOver Scene
	DrawPicture(arrowBach7_1,1250 , 675,140, 144,1);
	DrawPicture(arrowBach7_2,1375 , 400,140, 144,1);

	//Cleared Scene
	DrawPicture(arrowBach8_1,770 , 675,140, 144,1);
	DrawPicture(arrowBach8_2,600 , 475,140, 144,1);

	//level batch
	//torusBatch;			    //fruit
	gltMakeTorus(torusBatch, 0.25f, 0.10f, 80, 40);

	//sphereBatch;		    //cookies
	gltMakeSphere(sphereBatch, 0.20f, 26, 13);

	//floorBatch1;			//ground1
	GLfloat texSize = (COL-1)/2;
	floorBatch[0].Begin(GL_TRIANGLE_FAN, 4, 1);
		floorBatch[0].MultiTexCoord2f(0, 0.0f, 0.0f);
		floorBatch[0].Vertex3f(-(COL+2)/2, -0.41f, (ROW+2)/2);

		floorBatch[0].MultiTexCoord2f(0, texSize, 0.0f);
		floorBatch[0].Vertex3f((COL+2)/2, -0.41f, (ROW+2)/2);

		floorBatch[0].MultiTexCoord2f(0, texSize, texSize);
		floorBatch[0].Vertex3f((COL+2)/2, -0.41f, -(ROW+2)/2);

		floorBatch[0].MultiTexCoord2f(0, 0.0f, texSize);
		floorBatch[0].Vertex3f(-(COL+2)/2, -0.41f, -(ROW+2)/2);
	floorBatch[0].End();

	//floorBatch2;			//ground2
	floorBatch[1].Begin(GL_TRIANGLE_FAN, 4, 1);
		floorBatch[1].MultiTexCoord2f(0, 0.0f, 0.0f);
		floorBatch[1].Vertex3f(-(COL+2)/2, -0.41f, (ROW+2)/2);

		floorBatch[1].MultiTexCoord2f(0, texSize, 0.0f);
		floorBatch[1].Vertex3f((COL+2)/2, -0.41f, (ROW+2)/2);

		floorBatch[1].MultiTexCoord2f(0, texSize, texSize);
		floorBatch[1].Vertex3f((COL+2)/2, -0.41f, -(ROW+2)/2);

		floorBatch[1].MultiTexCoord2f(0, 0.0f, texSize);
		floorBatch[1].Vertex3f(-(COL+2)/2, -0.41f, -(ROW+2)/2);
	floorBatch[1].End();

	//floorBatch3;			//ground3
	floorBatch[2].Begin(GL_TRIANGLE_FAN, 4, 1);
		floorBatch[2].MultiTexCoord2f(0, 0.0f, 0.0f);
		floorBatch[2].Vertex3f(-(COL+2)/2, -0.41f, (ROW+2)/2);

		floorBatch[2].MultiTexCoord2f(0, texSize, 0.0f);
		floorBatch[2].Vertex3f((COL+2)/2, -0.41f, (ROW+2)/2);

		floorBatch[2].MultiTexCoord2f(0, texSize, texSize);
		floorBatch[2].Vertex3f((COL+2)/2, -0.41f, -(ROW+2)/2);
	
		floorBatch[2].MultiTexCoord2f(0, 0.0f, texSize);
		floorBatch[2].Vertex3f(-(COL+2)/2, -0.41f, -(ROW+2)/2);
	floorBatch[2].End();

	//floorBatch4;			//ground4
	floorBatch[3].Begin(GL_TRIANGLE_FAN, 4, 1);
		floorBatch[3].MultiTexCoord2f(0, 0.0f, 0.0f);
		floorBatch[3].Vertex3f(-(COL+2)/2, -0.41f, (ROW+2)/2);

		floorBatch[3].MultiTexCoord2f(0, texSize, 0.0f);
		floorBatch[3].Vertex3f((COL+2)/2, -0.41f, (ROW+2)/2);

		floorBatch[3].MultiTexCoord2f(0, texSize, texSize);
		floorBatch[3].Vertex3f((COL+2)/2, -0.41f, -(ROW+2)/2);
	
		floorBatch[3].MultiTexCoord2f(0, 0.0f, texSize);
		floorBatch[3].Vertex3f(-(COL+2)/2, -0.41f, -(ROW+2)/2);
	floorBatch[3].End();

	//floorBatch5;			//ground5
	texSize=1.0f;
	floorBatch[4].Begin(GL_TRIANGLE_FAN, 4, 1);
		floorBatch[4].MultiTexCoord2f(0, 0.0f, 0.0f);
		floorBatch[4].Vertex3f(-(COL+2)/2, -0.41f, (ROW+2)/2);

		floorBatch[4].MultiTexCoord2f(0, texSize, 0.0f);
		floorBatch[4].Vertex3f((COL+2)/2, -0.41f, (ROW+2)/2);

		floorBatch[4].MultiTexCoord2f(0, texSize, texSize);
		floorBatch[4].Vertex3f((COL+2)/2, -0.41f, -(ROW+2)/2);
	
		floorBatch[4].MultiTexCoord2f(0, 0.0f, texSize);
		floorBatch[4].Vertex3f(-(COL+2)/2, -0.41f, -(ROW+2)/2);
	floorBatch[4].End();

	//cubeBatch;				//barrier,border
	gltMakeCube(cubeBatch,0.5f);

	//snake head
	gltMakeSphere(headSphereBatch,0.30f,26,13);	

	//snake body
	gltMakeCylinder(bodyCylinderBatch,0.34f,0.28f,1.0f,80,40);		

	//chaos ball
	gltMakeSphere(chaosBallBatch,0.10f,26,13);

	//angel torus
	gltMakeTorus(angelTorusBatch,0.36f,0.06f,80,40);

	//hole
	gltMakeSphere(holeSphereBatch,0.30f ,26,13);

	//picture1Batch;			//back picture
	picture1Batch.Begin(GL_TRIANGLES, 6, 1);

	picture1Batch.Normal3f(0.0f, 0.0f, 1.0f);
	picture1Batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	picture1Batch.Vertex3f(-960*BG_PC_FACTOR_X, -540*BG_PC_FACTOR_Y, -BG_DISTANCE);

	picture1Batch.Normal3f(0.0f, 0.0f, 1.0f);
	picture1Batch.MultiTexCoord2f(0, 1.0f, 0.0f);
	picture1Batch.Vertex3f(960*BG_PC_FACTOR_X, -540*BG_PC_FACTOR_Y, -BG_DISTANCE);

	picture1Batch.Normal3f(0.0f, 0.0f, 1.0f);
	picture1Batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	picture1Batch.Vertex3f(960*BG_PC_FACTOR_X, 540*BG_PC_FACTOR_Y, -BG_DISTANCE);

	picture1Batch.Normal3f(0.0f, 0.0f, 1.0f);
	picture1Batch.MultiTexCoord2f(0, 0.0f, 1.0f);
	picture1Batch.Vertex3f(-960*BG_PC_FACTOR_X, 540*BG_PC_FACTOR_Y, -BG_DISTANCE);

	picture1Batch.Normal3f(0.0f, 0.0f, 1.0f);
	picture1Batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	picture1Batch.Vertex3f(-960*BG_PC_FACTOR_X, -540*BG_PC_FACTOR_Y, -BG_DISTANCE);

	picture1Batch.Normal3f(0.0f, 0.0f, 1.0f);
	picture1Batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	picture1Batch.Vertex3f(960*BG_PC_FACTOR_X, 540*BG_PC_FACTOR_Y, -BG_DISTANCE);

	picture1Batch.End();

	//picture2Batch;			//front picture
	picture2Batch.Begin(GL_TRIANGLES, 6, 1);
	picture2Batch.Normal3f(0.0f, 0.0f, -1.0f);
	picture2Batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	picture2Batch.Vertex3f(960*BG_PC_FACTOR_X, -540*BG_PC_FACTOR_Y, BG_DISTANCE);

	picture2Batch.Normal3f(0.0f, 0.0f, -1.0f);
	picture2Batch.MultiTexCoord2f(0, 1.0f, 0.0f);
	picture2Batch.Vertex3f(-960*BG_PC_FACTOR_X, -540*BG_PC_FACTOR_Y, BG_DISTANCE);

	picture2Batch.Normal3f(0.0f, 0.0f, -1.0f);
	picture2Batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	picture2Batch.Vertex3f(-960*BG_PC_FACTOR_X, 540*BG_PC_FACTOR_Y, BG_DISTANCE);

	picture2Batch.Normal3f(0.0f, 0.0f, -1.0f);
	picture2Batch.MultiTexCoord2f(0, 0.0f, 1.0f);
	picture2Batch.Vertex3f(960*BG_PC_FACTOR_X, 540*BG_PC_FACTOR_Y, BG_DISTANCE);

	picture2Batch.Normal3f(0.0f, 0.0f, -1.0f);
	picture2Batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	picture2Batch.Vertex3f(960*BG_PC_FACTOR_X, -540*BG_PC_FACTOR_Y, BG_DISTANCE);

	picture2Batch.Normal3f(0.0f, 0.0f, -1.0f);
	picture2Batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	picture2Batch.Vertex3f(-960*BG_PC_FACTOR_X, 540*BG_PC_FACTOR_Y, BG_DISTANCE);

	picture2Batch.End();

	//picture3Batch;			//left picture
	picture3Batch.Begin(GL_TRIANGLES, 6, 1);

	picture3Batch.Normal3f(1.0f, 0.0f, 0.0f);
	picture3Batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	picture3Batch.Vertex3f(-BG_DISTANCE, -540*BG_PC_FACTOR_Y, 960.0f*BG_PC_FACTOR_X);

	picture3Batch.Normal3f(1.0f, 0.0f, 0.0f);
	picture3Batch.MultiTexCoord2f(0, 1.0f, 0.0f);
	picture3Batch.Vertex3f(-BG_DISTANCE, -540*BG_PC_FACTOR_Y, -960.0f*BG_PC_FACTOR_X);

	picture3Batch.Normal3f(1.0f, 0.0f, 0.0f);
	picture3Batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	picture3Batch.Vertex3f(-BG_DISTANCE, 540*BG_PC_FACTOR_Y, -960.0f*BG_PC_FACTOR_X);

	picture3Batch.Normal3f(1.0f, 0.0f, 0.0f);
	picture3Batch.MultiTexCoord2f(0, 0.0f, 1.0f);
	picture3Batch.Vertex3f(-BG_DISTANCE, 540*BG_PC_FACTOR_Y, 960.0f*BG_PC_FACTOR_X);

	picture3Batch.Normal3f(1.0f, 0.0f, 0.0f);
	picture3Batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	picture3Batch.Vertex3f(-BG_DISTANCE, -540*BG_PC_FACTOR_Y, 960.0f*BG_PC_FACTOR_X);

	picture3Batch.Normal3f(1.0f, 0.0f, 0.0f);
	picture3Batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	picture3Batch.Vertex3f(-BG_DISTANCE, 540*BG_PC_FACTOR_Y, -960.0f*BG_PC_FACTOR_X);

	picture3Batch.End();


	//picture4Batch;			//right picture
	picture4Batch.Begin(GL_TRIANGLES, 6, 1);

	picture4Batch.Normal3f(-1.0f, 0.0f, 0.0f);
	picture4Batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	picture4Batch.Vertex3f(BG_DISTANCE, -540*BG_PC_FACTOR_Y, -960.0f*BG_PC_FACTOR_X);

	picture4Batch.Normal3f(-1.0f, 0.0f, 0.0f);
	picture4Batch.MultiTexCoord2f(0, 1.0f, 0.0f);
	picture4Batch.Vertex3f(BG_DISTANCE, -540*BG_PC_FACTOR_Y, 960.0f*BG_PC_FACTOR_X);

	picture4Batch.Normal3f(-1.0f, 0.0f, 0.0f);
	picture4Batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	picture4Batch.Vertex3f(BG_DISTANCE, 540*BG_PC_FACTOR_Y, 960.0f*BG_PC_FACTOR_X);

	picture4Batch.Normal3f(-1.0f, 0.0f, 0.0f);
	picture4Batch.MultiTexCoord2f(0, 0.0f, 1.0f);
	picture4Batch.Vertex3f(BG_DISTANCE, 540*BG_PC_FACTOR_Y, -960.0f*BG_PC_FACTOR_X);

	picture4Batch.Normal3f(-1.0f, 0.0f, 0.0f);
	picture4Batch.MultiTexCoord2f(0, 0.0f, 0.0f);
	picture4Batch.Vertex3f(BG_DISTANCE, -540*BG_PC_FACTOR_Y, -960.0f*BG_PC_FACTOR_X);

	picture4Batch.Normal3f(-1.0f, 0.0f, 0.0f);
	picture4Batch.MultiTexCoord2f(0, 1.0f, 1.0f);
	picture4Batch.Vertex3f(BG_DISTANCE, 540*BG_PC_FACTOR_Y, 960.0f*BG_PC_FACTOR_X);

	picture4Batch.End();


}
