#include "Font.h"
#include <gltools.h>
#include <GL/glut.h>
#pragma comment (lib , "gltools.lib")
//ȫ�ֱ���  
int winWidth, winHeight;  
int Score = 0;
int Life = 3;

//��ʾ�ص�����  
void DisplayWords(int x_p,int y_p,char* words)  
{  

	glUseProgram(0);
	glMatrixMode(GL_PROJECTION);    //ͶӰģʽ  
	glLoadIdentity();               //���뵥λ�����Գ�ʼ����ǰ����  

	gluOrtho2D(0, winWidth ,0 , winHeight); //����ǰ��ͼ��������Ϊ��ά����ͶӰ  

	glMatrixMode(GL_MODELVIEW);     //ģ����ͼģʽ  
	glLoadIdentity();               //��ʼ����ǰ����  

	selectFont(48, ANSI_CHARSET, "Comic Sans MS");  //���������ϵͳ�ļ���Ѱ��  

	glColor3f(1.0f, 1.0f, 1.0f);     //������ɫ  
	glRasterPos2i( x_p , y_p);  //��ʼλ��  
	drawString(words);   //������ַ���  

	 
}   




void drawString(const char* str) //��Ļ��ʾ����  
{  
	static int isFirstCall = 1;  
	static GLuint lists;  

	if (isFirstCall) {  
		isFirstCall = 0;  
		// ����MAX_CHAR����������ʾ�б���  
		lists = glGenLists(MAX_CHAR);  
		// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���  
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);  
	}  
	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�  
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
