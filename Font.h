#ifndef FONT_H
#define FONT_H

#define MAX_CHAR 128 

extern int winWidth, winHeight;  
extern int Score;
extern int Life;

//��������ԭ��  

void DisplayWords(int,int,char*);   
void selectFont(int size, int charset, const char* face);
void drawString(const char* str);  


#endif