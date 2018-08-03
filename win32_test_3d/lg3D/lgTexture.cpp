#include "lgColor.h"
#include "lgTexture.h"

lgTexture::lgTexture()
{
}

lgTexture::~lgTexture()
{
}

const lgColor lgTexture::lgGetTexturePixel(int, int, int, int)
{
	lgColor tlgColor;
	return tlgColor;
}

void lgTexture::lgSetTexturePixel(int, int, int, int, const lgColor&)
{}

unsigned char* lgTexture::lgGetTextureBuffer(int type, int index, int& height, int& width, int& bit) const
{
	switch (type)
	{
	case BMP:
		width = m_lgBmpTexture[index].m_lgBmpInfo.bmiHeader.biWidth;
		height = m_lgBmpTexture[index].m_lgBmpInfo.bmiHeader.biWidth;
		bit = m_lgBmpTexture[index].m_lgBmpInfo.bmiHeader.biBitCount;
		return m_lgBmpTexture[index].m_lgBuffer;
	default:
		return nullptr;
	}
}