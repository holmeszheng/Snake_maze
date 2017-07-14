#include "Object.h"
#include "Sound.h"
#include "Barrier.h"
#include "SnakeLink.h"
#include "Scene.h"
#include "Cookies.h"
#include "Fruit.h"
#include "Font.h"
#include "Map.h"
#include "Textures.h"



GLShaderManager		shaderManager;			// Shader Manager
GLMatrixStack		modelViewMatrix;		// Modelview Matrix
GLMatrixStack		projectionMatrix;		// Perspective Projection Matrix
GLMatrixStack		projectionMatrix_o;		// Orthographic Projection Matrix
GLFrustum			viewFrustum;			// View Frustum
GLGeometryTransform	transformPipeline;		// Geometry Transform Pipeline
GLFrame				cameraframe[2];			// Camera frame

M3DMatrix44f		shadowMat;				//阴影矩阵
GLfloat				vLightPos[4] = {-5.0f ,5.0f, 0.0f, 0.0f};//光照位置

GLfloat vWhite[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat vBlue[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat vGreen[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat vYellow[] = { 1.0f, 1.0f, 0.0f, 1.0f };
GLfloat vRed[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat vMagenta[] = { 1.0f, 0.0f, 1.0f, 1.0f };
GLfloat vCyan[] = { 0.0f, 1.0f, 1.0f, 1.0f };

Scene_Manager Current_Scene = LOADING_I;

int dash = 0;  //0 没有冲刺    1  冲刺状态
int chaos = 0; //0 没有混乱    1  混乱状态
int angel = 0; //0 没有无敌	   1  无敌状态
int scroll_num=0;  //菜单条

int camera_sel=0;	//相机选择

void DrawSongAndDance(GLfloat yRot)		// Called to draw dancing objects
{

	// Get the light position in eye space
	M3DVector4f	vLightTransformed;
	M3DMatrix44f mCamera;
	modelViewMatrix.GetMatrix(mCamera);
	m3dTransformVector4(vLightTransformed, vLightPos, mCamera);

	// Draw the light source
	/*
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translatev(vLightPos);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, 
		transformPipeline.GetModelViewProjectionMatrix(),
		vWhite);
	sphereBatch.Draw();
	modelViewMatrix.PopMatrix();
	*/

	//cookies
	texture_cookies.Init2DTex(GL_CLAMP_TO_EDGE);
	for(int i = 0; i < MAX_COOKIES_NUM; i++) {
		modelViewMatrix.PushMatrix();
		modelViewMatrix.MultMatrix(cookies[i].LocalSystem);
		shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
			modelViewMatrix.GetMatrix(),
			transformPipeline.GetProjectionMatrix(),
			vLightTransformed, 
			vWhite,
			0);
		sphereBatch.Draw();
		modelViewMatrix.PopMatrix();
	}

	modelViewMatrix.PushMatrix();	// Saves the camera;
	// Song and dance
	modelViewMatrix.MultMatrix(fruit.LocalSystem);
	modelViewMatrix.Translate(0.0f,0.2f,0.0f);
	modelViewMatrix.PushMatrix();	// Saves the translated origin
	modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);

	// Draw stuff relative to the camera
	//Draw fruit
	switch(fruit.fruittype)
	{
	case NORMAL:
			texture_fruit_N.Init2DTex(GL_CLAMP_TO_EDGE);
			break;
	case LIFE:
			texture_fruit_L.Init2DTex(GL_CLAMP_TO_EDGE);
			break;
	case CHAOS:
			texture_fruit_C.Init2DTex(GL_CLAMP_TO_EDGE);
			break;
	case ANGEL:
			texture_fruit_A.Init2DTex(GL_CLAMP_TO_EDGE);
			break;
	case DASH:
			texture_fruit_D.Init2DTex(GL_CLAMP_TO_EDGE);
	}

	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
		modelViewMatrix.GetMatrix(),
		transformPipeline.GetProjectionMatrix(),
		vLightTransformed, 
		vWhite,
		0);
	torusBatch.Draw();
	modelViewMatrix.PopMatrix(); // Erased the rotate

	//Draw stuff moving around the torus(fruit)

	modelViewMatrix.Rotate(yRot * -2.0f, 0.0f, 1.0f, 0.0f);
	modelViewMatrix.Translate(0.7f, 0.0f, 0.0f);


	texture_cookies.Init2DTex(GL_CLAMP_TO_EDGE);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
		modelViewMatrix.GetMatrix(),
		transformPipeline.GetProjectionMatrix(),
		vLightTransformed, 
		vWhite,
		0);
	sphereBatch.Draw();

	modelViewMatrix.PopMatrix(); 

	//barrier
	texture_barrier.Init2DTex(GL_CLAMP_TO_EDGE);
	for(int i = 0; i < Barrier_Num; i++) {
		modelViewMatrix.PushMatrix();
		modelViewMatrix.MultMatrix(barrier[i].LocalSystem);
		shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
			modelViewMatrix.GetMatrix(),
			transformPipeline.GetProjectionMatrix(),
			vLightTransformed, 
			vWhite,
			0);
		cubeBatch.Draw();
		modelViewMatrix.PopMatrix();
	}

	//border
	texture_border.Init2DTex(GL_CLAMP_TO_EDGE);
	for(int i = 0; i < BorderNum; i++) {
		modelViewMatrix.PushMatrix();
		modelViewMatrix.MultMatrix(border[i].LocalSystem);
		shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
			modelViewMatrix.GetMatrix(),
			transformPipeline.GetProjectionMatrix(),
			vLightTransformed, 
			vWhite,
			0);
		cubeBatch.Draw();
		modelViewMatrix.PopMatrix();
	}

}

void DrawSongAndDanceShadow(GLfloat yRot)		// Called to draw dancing objects
{
	

	// Draw the light source
	/*
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translatev(vLightPos);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, 
		transformPipeline.GetModelViewProjectionMatrix(),
		vWhite);
	sphereBatch.Draw();
	modelViewMatrix.PopMatrix();
	*/

	//cookies
	for(int i = 0; i < MAX_COOKIES_NUM; i++) {
		modelViewMatrix.PushMatrix();
		modelViewMatrix.MultMatrix(cookies[i].LocalSystem);
		shaderManager.UseStockShader(GLT_SHADER_FLAT, 
			transformPipeline.GetModelViewProjectionMatrix(),
			vBlack);
		sphereBatch.Draw();
		modelViewMatrix.PopMatrix();
	}

	modelViewMatrix.PushMatrix();	// Saves the camera;
	// Song and dance
	modelViewMatrix.MultMatrix(fruit.LocalSystem);
	modelViewMatrix.Translate(0.0f,0.2f,0.0f);
	modelViewMatrix.PushMatrix();	// Saves the translated origin
	modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);

	// Draw stuff relative to the camera
	//Draw fruit
	shaderManager.UseStockShader(GLT_SHADER_FLAT, 
		transformPipeline.GetModelViewProjectionMatrix(),
		vBlack);
	torusBatch.Draw();
	modelViewMatrix.PopMatrix(); // Erased the rotate

	//Draw stuff moving around the torus(fruit)

	modelViewMatrix.Rotate(yRot * -2.0f, 0.0f, 1.0f, 0.0f);
	modelViewMatrix.Translate(0.7f, 0.0f, 0.0f);

	shaderManager.UseStockShader(GLT_SHADER_FLAT, 
		transformPipeline.GetModelViewProjectionMatrix(),
		vBlack);
	sphereBatch.Draw();

	modelViewMatrix.PopMatrix(); 

	//barrier
	for(int i = 0; i < Barrier_Num; i++) {
		modelViewMatrix.PushMatrix();
		modelViewMatrix.MultMatrix(barrier[i].LocalSystem);
		shaderManager.UseStockShader(GLT_SHADER_FLAT, 
			transformPipeline.GetModelViewProjectionMatrix(),
			vBlack);
		cubeBatch.Draw();
		modelViewMatrix.PopMatrix();
	}


}
void Load_I_Scene()
{
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix_o);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	texture_fixp1.Init2DTex(GL_REPEAT);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE,
		transformPipeline.GetModelViewProjectionMatrix());
	FixpBatch.Draw();
	// Do the buffer Swap
	glutSwapBuffers();
}

void Init_Scene()
{

	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix_o);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	texture_fixp2.Init2DTex(GL_REPEAT);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE,
		transformPipeline.GetModelViewProjectionMatrix());
	FixpBatch.Draw();
	if(scroll_num==0)
	{
		texture_arrowW1.Init2DTex(GL_REPEAT);
		arrowBach2_1.Draw();
	}
	if(scroll_num==1)
	{
		texture_arrowW1.Init2DTex(GL_REPEAT);
		arrowBach2_2.Draw();
	}
	if(scroll_num==2)
	{
		texture_arrowW1.Init2DTex(GL_REPEAT);
		arrowBach2_3.Draw();
	}
	// Do the buffer Swap
	glutSwapBuffers();
}

void Sel_Scene()
{
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix_o);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	texture_fixp3.Init2DTex(GL_REPEAT);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE,
		transformPipeline.GetModelViewProjectionMatrix());
	FixpBatch.Draw();

	if(scroll_num==0)
	{
		texture_arrowB1.Init2DTex(GL_REPEAT);
		arrowBach3_1.Draw();
	}
	if(scroll_num==1)
	{
		texture_arrowB2.Init2DTex(GL_REPEAT);
		arrowBach3_2.Draw();
	}
	if(scroll_num==2)
	{
		texture_arrowB1.Init2DTex(GL_REPEAT);
		arrowBach3_3.Draw();
	}
	if(scroll_num==3)
	{
		texture_arrowB2.Init2DTex(GL_REPEAT);
		arrowBach3_4.Draw();
	}
	if(scroll_num==4)
	{
		texture_arrowB1.Init2DTex(GL_REPEAT);
		arrowBach3_5.Draw();
	}
	// Do the buffer Swap
	glutSwapBuffers();
}

void Load_E_Scene()
{
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix_o);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	texture_fixp4.Init2DTex(GL_REPEAT);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE,
		transformPipeline.GetModelViewProjectionMatrix());
	FixpBatch.Draw();
	// Do the buffer Swap
	glutSwapBuffers();

}

void Level_Scene()
{
	
	transformPipeline.SetMatrixStacks(modelViewMatrix,projectionMatrix);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static CStopWatch	rotTimer;
	float yRot = rotTimer.GetElapsedSeconds() * 20.0f;

	//load camera
	modelViewMatrix.PushMatrix();	
	M3DMatrix44f mCamera;
	cameraframe[camera_sel].GetCameraMatrix(mCamera);
	modelViewMatrix.MultMatrix(mCamera);

	// Get the light position in eye space
	M3DVector4f	vLightTransformed;
	m3dTransformVector4(vLightTransformed, vLightPos, mCamera);
	if(map_ID==0||map_ID==1||map_ID==2)
	{
	// Draw the solid ground
	texture_ground.Init2DTex(GL_REPEAT);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE,
		transformPipeline.GetModelViewProjectionMatrix(),

		0);
	floorBatch[map_ID].Draw();

	//draw shadows
	modelViewMatrix.PushMatrix();
	modelViewMatrix.MultMatrix(shadowMat);	
	glDisable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE, GL_ZERO);
	
	
	DrawSongAndDanceShadow(yRot);

	//snake head shadow
	modelViewMatrix.PushMatrix();
	modelViewMatrix.MultMatrix(snake[0].LocalSystem);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, 
		transformPipeline.GetModelViewProjectionMatrix(),
		vBlack);
	headSphereBatch.Draw();
	modelViewMatrix.PopMatrix();


	//snake body shadow
	for(int i = 1; i < Link_Num; i++) {
		modelViewMatrix.PushMatrix();
		modelViewMatrix.MultMatrix(snake[i].LocalSystem);
		shaderManager.UseStockShader(GLT_SHADER_FLAT, 
			transformPipeline.GetModelViewProjectionMatrix(),
			vBlack);
		bodyCylinderBatch.Draw();
		modelViewMatrix.PopMatrix();
	}

	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_BLEND);
	modelViewMatrix.PopMatrix(); //pop shadow


	//Draw background
	texture_background.Init2DTex(GL_REPEAT);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE,
		transformPipeline.GetModelViewProjectionMatrix(),
		0);

	picture1Batch.Draw();
	picture2Batch.Draw();
	picture3Batch.Draw();
	picture4Batch.Draw();


	//正向物体
	DrawSongAndDance(yRot);

	//snake head
	texture_head.Init2DTex(GL_CLAMP_TO_EDGE);
	modelViewMatrix.PushMatrix();
	modelViewMatrix.MultMatrix(snake[0].LocalSystem);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
		modelViewMatrix.GetMatrix(),
		transformPipeline.GetProjectionMatrix(),
		vLightTransformed, 
		vWhite,
		0);
	headSphereBatch.Draw();
	modelViewMatrix.PopMatrix();


	//snake body
	texture_body.Init2DTex(GL_CLAMP_TO_EDGE);
	for(int i = 1; i < Link_Num; i++) {
		modelViewMatrix.PushMatrix();
		modelViewMatrix.MultMatrix(snake[i].LocalSystem);
		shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
			modelViewMatrix.GetMatrix(),
			transformPipeline.GetProjectionMatrix(),
			vLightTransformed, 
			vWhite,
			0);
		bodyCylinderBatch.Draw();
		modelViewMatrix.PopMatrix();
	}

	//snake rear hole
	texture_body.Init2DTex(GL_CLAMP_TO_EDGE);
	modelViewMatrix.PushMatrix();
	modelViewMatrix.MultMatrix(snake[Link_Num-1].LocalSystem);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
		modelViewMatrix.GetMatrix(),
		transformPipeline.GetProjectionMatrix(),
		vLightTransformed, 
		vWhite,
		0);
	headSphereBatch.Draw();
	modelViewMatrix.PopMatrix();

	//fix the holes
	texture_body.Init2DTex(GL_CLAMP_TO_EDGE);
	for(int i = 1; i < Link_Num-1; i++)
	{
		modelViewMatrix.PushMatrix();
		modelViewMatrix.MultMatrix(snake[i].LocalSystem);
		shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
			modelViewMatrix.GetMatrix(),
			transformPipeline.GetProjectionMatrix(),
			vLightTransformed, 
			vWhite,
			0);
		holeSphereBatch.Draw();
		modelViewMatrix.PopMatrix();
	}


	}
	else
	{
		// Draw the world upside down 反向物体
		modelViewMatrix.PushMatrix();
		modelViewMatrix.Scale(1.0f, -1.0f, 1.0f); // Flips the Y Axis
		modelViewMatrix.Translate(0.0f, 0.8f, 0.0f); // Scootch the world down a bit...
		glFrontFace(GL_CW);
		DrawSongAndDance(yRot);
		glFrontFace(GL_CCW);
		modelViewMatrix.PopMatrix();

		// Draw the solid ground
		glEnable(GL_BLEND);
		texture_ground.Init2DTex(GL_REPEAT);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		static GLfloat vFloorColor[] = { 1.0f, 1.0f, 1.0f, 0.75f};
		shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
			transformPipeline.GetModelViewProjectionMatrix(),
			vFloorColor,
			0);
		floorBatch[map_ID].Draw();
		glDisable(GL_BLEND);

		//Draw background
		texture_background.Init2DTex(GL_REPEAT);
		shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE,
			transformPipeline.GetModelViewProjectionMatrix(),
			0);

		picture1Batch.Draw();
		picture2Batch.Draw();
		picture3Batch.Draw();
		picture4Batch.Draw();

		//正向物体
		DrawSongAndDance(yRot);

		//snake head
		texture_head.Init2DTex(GL_CLAMP_TO_EDGE);
		modelViewMatrix.PushMatrix();
		modelViewMatrix.MultMatrix(snake[0].LocalSystem);
		shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
			modelViewMatrix.GetMatrix(),
			transformPipeline.GetProjectionMatrix(),
			vLightTransformed, 
			vWhite,
			0);
		headSphereBatch.Draw();
		modelViewMatrix.PopMatrix();


		//snake body
		texture_body.Init2DTex(GL_CLAMP_TO_EDGE);
		for(int i = 1; i < Link_Num; i++) {
			modelViewMatrix.PushMatrix();
			modelViewMatrix.MultMatrix(snake[i].LocalSystem);
			shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
				modelViewMatrix.GetMatrix(),
				transformPipeline.GetProjectionMatrix(),
				vLightTransformed, 
				vWhite,
				0);
			bodyCylinderBatch.Draw();
			modelViewMatrix.PopMatrix();
		}

		//snake rear hole
		texture_body.Init2DTex(GL_CLAMP_TO_EDGE);
		modelViewMatrix.PushMatrix();
		modelViewMatrix.MultMatrix(snake[Link_Num-1].LocalSystem);
		shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
			modelViewMatrix.GetMatrix(),
			transformPipeline.GetProjectionMatrix(),
			vLightTransformed, 
			vWhite,
			0);
		headSphereBatch.Draw();
		modelViewMatrix.PopMatrix();

		//fix the holes
		texture_body.Init2DTex(GL_CLAMP_TO_EDGE);
		for(int i = 1; i < Link_Num-1; i++)
		{
			modelViewMatrix.PushMatrix();
			modelViewMatrix.MultMatrix(snake[i].LocalSystem);
			shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
				modelViewMatrix.GetMatrix(),
				transformPipeline.GetProjectionMatrix(),
				vLightTransformed, 
				vWhite,
				0);
			holeSphereBatch.Draw();
			modelViewMatrix.PopMatrix();
		}

		

}

	//显示CHAOS_BALL
	if(chaos)
	{

		GLfloat vAlpha[] = { 1.0f, 1.0f, 1.0f, 0.85f };

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLFrame chaos_ball_pos;
		chaos_ball_pos = snake[0].LocalSystem;
		modelViewMatrix.PushMatrix();			//保存相机矩阵
		modelViewMatrix.MultMatrix(chaos_ball_pos);
		modelViewMatrix.Translate(0.0f,0.6f,0.0f);
		texture_fruit_C.Init2DTex(GL_CLAMP_TO_EDGE);

	//球1
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Rotate(yRot+60.0f,0.0,1.0f,0.0f);
	modelViewMatrix.Translate(0.6f,0.0f,0.0f);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
		transformPipeline.GetModelViewProjectionMatrix(),
		vAlpha,
		0);
	chaosBallBatch.Draw();
	modelViewMatrix.PopMatrix();

	//球2
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Rotate(yRot+120.0f,0.0,1.0f,0.0f);
	modelViewMatrix.Translate(0.6f,0.0f,0.0f);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
		transformPipeline.GetModelViewProjectionMatrix(),
		vAlpha,
		0);
	chaosBallBatch.Draw();
	modelViewMatrix.PopMatrix();

	//球3
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Rotate(yRot+180.0f,0.0,1.0f,0.0f);
	modelViewMatrix.Translate(0.6f,0.0f,0.0f);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
		transformPipeline.GetModelViewProjectionMatrix(),
		vAlpha,
		0);
	chaosBallBatch.Draw();
	modelViewMatrix.PopMatrix();

	//球4
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Rotate(yRot+240.0f,0.0,1.0f,0.0f);
	modelViewMatrix.Translate(0.6f,0.0f,0.0f);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
		transformPipeline.GetModelViewProjectionMatrix(),
		vAlpha,
		0);
	chaosBallBatch.Draw();
	modelViewMatrix.PopMatrix();

	//球5
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Rotate(yRot+300.0f,0.0,1.0f,0.0f);
	modelViewMatrix.Translate(0.6f,0.0f,0.0f);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
		transformPipeline.GetModelViewProjectionMatrix(),
		vAlpha,
		0);
	chaosBallBatch.Draw();
	modelViewMatrix.PopMatrix();

	//球6
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Rotate(yRot+0.0f,0.0,1.0f,0.0f);
	modelViewMatrix.Translate(0.6f,0.0f,0.0f);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
		transformPipeline.GetModelViewProjectionMatrix(),
		vAlpha,
		0);
	chaosBallBatch.Draw();
	modelViewMatrix.PopMatrix();

	glDisable(GL_BLEND);

	modelViewMatrix.PopMatrix(); //返回相机矩阵
	}

	//angel torus
	if(angel)
	{
		modelViewMatrix.PushMatrix();
		modelViewMatrix.MultMatrix(snake[0].LocalSystem);
		modelViewMatrix.Translate(0.0f,0.6f,0.0f);
		modelViewMatrix.Rotate(90.0f,1.0f,0.0f,0.0f);
		modelViewMatrix.Rotate(yRot,0.0f,0.0f,1.0f);

		glEnable(GL_BLEND);
		texture_fruit_A.Init2DTex(GL_CLAMP_TO_EDGE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		GLfloat vFloorColor[] = { 1.0f, 1.0f, 1.0f, 0.75f};
		shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
			transformPipeline.GetModelViewProjectionMatrix(),
			vFloorColor,
			0);
		angelTorusBatch.Draw();
		glDisable(GL_BLEND);

		modelViewMatrix.PopMatrix();
	}





	modelViewMatrix.PopMatrix(); //return to Identity Matrix

	//显示文字
	char temp_char[20];
	DisplayWords(20,winHeight-48,"Score:");
	itoa(Score,temp_char,10);
	DisplayWords(150,winHeight-48,temp_char);

	DisplayWords(20,winHeight-100,"Life:");
	itoa(Life,temp_char,10);
	DisplayWords(150,winHeight-100,temp_char);

	DisplayWords(20,winHeight-150,"Status:");
	switch(dash)
	{
	case 0:
		switch(chaos)
		{
		case 0:
			switch(angel)
			{
			case 0:
				DisplayWords(150,winHeight-150,"Running!");
				break;
			case 1:
				DisplayWords(150,winHeight-150,"Angel!");
			}
			break;
		case 1:
			DisplayWords(150,winHeight-150,"Chaos!");
		}
		break;
	case 1:
		DisplayWords(150,winHeight-150,"Intellectual Dashing!");
	}

	DisplayWords(20,winHeight-200,"Link Num:");
	itoa(Link_Num,temp_char,10);
	DisplayWords(200,winHeight-200,temp_char);		
	// Do the buffer Swap
	glutSwapBuffers();
}

void Load_D_Scene()
{
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix_o);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	texture_fixp6.Init2DTex(GL_REPEAT);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE,
		transformPipeline.GetModelViewProjectionMatrix());
	FixpBatch.Draw();
	if(scroll_num==0)
	{
		texture_arrowB1.Init2DTex(GL_REPEAT);
		arrowBach6_1.Draw();
	}
	if(scroll_num==1)
	{
		texture_arrowB1.Init2DTex(GL_REPEAT);
		arrowBach6_2.Draw();
	}
	if(scroll_num==2)
	{
		texture_arrowB1.Init2DTex(GL_REPEAT);
		arrowBach6_3.Draw();
	}
	// Do the buffer Swap
	glutSwapBuffers();
}

void GameOverScene()
{
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix_o);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	texture_fixp7.Init2DTex(GL_REPEAT);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE,
		transformPipeline.GetModelViewProjectionMatrix());
	FixpBatch.Draw();
	if(scroll_num==0)
	{
		texture_arrowW1.Init2DTex(GL_REPEAT);
		arrowBach7_1.Draw();
	}
	if(scroll_num==1)
	{
		texture_arrowW1.Init2DTex(GL_REPEAT);
		arrowBach7_2.Draw();
	}
	// Do the buffer Swap
	glutSwapBuffers();

}

void Cleared_Scene()
{
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix_o);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	texture_fixp8.Init2DTex(GL_REPEAT);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE,
		transformPipeline.GetModelViewProjectionMatrix());
	FixpBatch.Draw();
	if(scroll_num==0)
	{
		texture_arrowW1.Init2DTex(GL_REPEAT);
		arrowBach8_1.Draw();
	}
	if(scroll_num==1)
	{
		texture_arrowW1.Init2DTex(GL_REPEAT);
		arrowBach8_2.Draw();
	}

	// Do the buffer Swap
	glutSwapBuffers();
}