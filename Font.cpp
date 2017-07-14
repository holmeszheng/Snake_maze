#include "Font.h"
#include <gltools.h>
#include <GL/glut.h>
#pragma comment (lib , "gltools.lib")
//全局变量  
int winWidth, winHeight;  
int Score = 0;
int Life = 3;

//显示回调函数  
void DisplayWords(int x_p,int y_p,char* words)  
{  

	glUseProgram(0);
	glMatrixMode(GL_PROJECTION);    //投影模式  
	glLoadIdentity();               //载入单位矩阵以初始化当前矩阵  

	gluOrtho2D(0, winWidth ,0 , winHeight); //将当前绘图区域设置为二维正交投影  

	glMatrixMode(GL_MODELVIEW);     //模型视图模式  
	glLoadIdentity();               //初始化当前矩阵  

	selectFont(48, ANSI_CHARSET, "Comic Sans MS");  //字体可以在系统文件里寻找  

	glColor3f(1.0f, 1.0f, 1.0f);     //字体颜色  
	glRasterPos2i( x_p , y_p);  //起始位置  
	drawString(words);   //输出的字符串  

	 
}   




void drawString(const char* str) //屏幕显示字体  
{  
	static int isFirstCall = 1;  
	static GLuint lists;  

	if (isFirstCall) {  
		isFirstCall = 0;  
		// 申请MAX_CHAR个连续的显示列表编号  
		lists = glGenLists(MAX_CHAR);  
		// 把每个字符的绘制命令都装到对应的显示列表中  
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);  
	}  
	// 调用每个字符对应的显示列表，绘制每个字符  
	for (; *str != '\0'; ++str) {  
		glCallList(lists + *str);  
	}  
}  

void selectFont(int size, int charset, const char* face) {  
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,  
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,  
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);  
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);  
	DeleteObject(hOldFont);  
}  
