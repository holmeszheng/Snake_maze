#ifndef CTEXTURE_H
#define CTEXTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ximage.h>
#include <GL/glut.h>
#define MAX_PATH_L 20

#pragma  comment (lib, "cximagecrt.lib")

class CTexture
{
public:
	CTexture() { m_byData = NULL; m_szTexName[0] = 0; }
	CTexture(const char* pcszFileName) { m_byData = 0; LoadFromFile(pcszFileName); }
	~CTexture();
	int LoadFromFile(const char* pcszFileName);
	void Init2DTex(GLenum);
	void Init1DVertTex();
private:
	int m_nWidth;
	int m_nHeight;
	char* m_byData;
	char m_szTexName[MAX_PATH_L];
	unsigned m_uTexName;
	GLenum wrapMode;
};

#endif