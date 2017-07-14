#ifndef OBJECT_H
#define OBJECT_H

#include <GLBatch.h>
#include <GLTriangleBatch.h>

//scene batch
//¼ýÍ·ÈÝÆ÷
extern GLBatch arrowBach2_1;
extern GLBatch arrowBach2_2;
extern GLBatch arrowBach2_3;

extern GLBatch arrowBach3_1;
extern GLBatch arrowBach3_2;
extern GLBatch arrowBach3_3;
extern GLBatch arrowBach3_4;
extern GLBatch arrowBach3_5;

extern GLBatch arrowBach6_1;
extern GLBatch arrowBach6_2;
extern GLBatch arrowBach6_3;

extern GLBatch arrowBach7_1;
extern GLBatch arrowBach7_2;

extern GLBatch arrowBach8_1;
extern GLBatch arrowBach8_2;

//ÕûÍ¼ÈÝÆ÷
extern GLBatch FixpBatch;

//level ÈÝÆ÷
extern GLTriangleBatch		torusBatch;			    //fruit
extern GLTriangleBatch		sphereBatch;		    //cookies
extern GLBatch				floorBatch[5];			//ground1-5

extern GLTriangleBatch		headSphereBatch;		//snake head
extern GLTriangleBatch		bodyCylinderBatch;		//snake body
extern GLTriangleBatch		chaosBallBatch;			//chaos ball
extern GLTriangleBatch		angelTorusBatch;		//angel torus
extern GLTriangleBatch		holeSphereBatch;		//hole
extern GLBatch				cubeBatch;				//barrier,border

extern GLBatch				picture1Batch;			//back picture
extern GLBatch				picture2Batch;			//front picture
extern GLBatch				picture3Batch;			//left picture
extern GLBatch				picture4Batch;			//right picture



void DrawPicture(GLBatch& picture,GLfloat x,GLfloat y,GLfloat w, GLfloat h,GLfloat z);
void Initial_Batchs();




#endif