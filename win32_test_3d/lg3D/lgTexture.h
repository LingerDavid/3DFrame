#ifndef _FILE_LGTEXTURE_H
#define _FILE_LGTEXTURE_H

#include "lgBmp.h"

class lgColor;

class lgTexture
{
public:
	enum
	{
		BMP,
		PNG,
		TIF,
		JPG,
		JPEG
	};
	const static int m_lgMaxTexture = 3;
	lgBmp m_lgBmpTexture[m_lgMaxTexture];
public:
	lgTexture();
	~lgTexture();
	const lgColor lgGetTexturePixel(int, int, int, int);
	virtual void lgSetTexturePixel(int, int, int, int, const lgColor&);
	virtual unsigned  char* lgGetTextureBuffer(int, int, int&, int&, int&) const;
};
#endif