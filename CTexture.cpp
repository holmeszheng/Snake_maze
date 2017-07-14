#include "CTexture.h"

int CTexture::LoadFromFile(const char* pcszFileName)
{
	if (pcszFileName != NULL)
	{
		strcpy(m_szTexName, pcszFileName);
	}
	CxImage image;
	image.Load(pcszFileName);
	if (image.IsValid() == false)
	{
		return 0;
	}
	m_nWidth = image.GetWidth();
	m_nHeight = image.GetHeight();
	if (m_byData)
	{
		delete m_byData;
	}
	m_byData = new char[m_nWidth * m_nHeight * 3];
	for (int i = 0; i < m_nHeight; ++i)
	{
		for (int j = 0; j < m_nWidth; ++j)
		{
			RGBQUAD rgb = image.GetPixelColor(j, i);
			m_byData[(i * m_nWidth + j) * 3] = rgb.rgbRed;
			m_byData[(i * m_nWidth + j) * 3 + 1] = rgb.rgbGreen;
			m_byData[(i * m_nWidth + j) * 3 + 2] = rgb.rgbBlue;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &m_uTexName);
	glBindTexture(GL_TEXTURE_2D, m_uTexName);

	int nRet = gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_nWidth, m_nHeight, GL_RGB, GL_UNSIGNED_BYTE,m_byData);
	if (nRet != 0)
	{
		exit(0);
	}
	return 1;
}

void CTexture::Init2DTex(GLenum wrapMode)
{
	glBindTexture(GL_TEXTURE_2D, m_uTexName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void CTexture::Init1DVertTex()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &m_uTexName);
	glBindTexture(GL_TEXTURE_1D, m_uTexName);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	char* pbyData = new char[m_nHeight * 3];
	int nAdd = m_nWidth / 2;
	for (int i = 0; i < m_nHeight; ++i)
	{
		pbyData[i * 3] = m_byData[(i * m_nWidth + nAdd) * 3];
		pbyData[i * 3 + 1] = m_byData[(i * m_nWidth + nAdd) * 3 + 1];
		pbyData[i * 3 + 2] = m_byData[(i * m_nWidth + nAdd) * 3 + 2];
	}
	int nRet = gluBuild1DMipmaps(GL_TEXTURE_1D, 3, m_nHeight, GL_RGB, GL_UNSIGNED_BYTE,pbyData);
	if (nRet != 0)
	{
		exit(0);
	}
	delete pbyData;
}
CTexture::~CTexture()
{
	if (m_byData)
		delete m_byData;
}

