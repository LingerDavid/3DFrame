#include "lgBmp.h"


lgBmp::~lgBmp()
{
	if (m_lgBuffer)
	{
		delete m_lgBuffer;
		m_lgBuffer = nullptr;
	}
}

lgBmp::lgBmp()
{
}

void lgBmp::lgFlipBitmap()
{
	int r = m_lgBmpInfo.bmiHeader.biHeight,
		c = m_lgBmpInfo.bmiHeader.biWidth,
		tr = r /2,
		w = m_lgBmpInfo.bmiHeader.biWidth,
		bit = m_lgBmpInfo.bmiHeader.biBitCount,
		tw = w * bit / 8,
		i = 0,
		j = 0,
		index = 0,
		temp = 0;

	char* tempbuffer = new char[tw];

	for (i = 0; i < tr; i++)
	{
		memcpy(tempbuffer, m_lgBuffer + i * tw, tw);
		memcpy(m_lgBuffer + i * tw, m_lgBuffer + (r - i - 1) * tw, tw);
		memcpy(m_lgBuffer + (r - i - 1) * tw, tempbuffer, tw);
	}
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			index = i * c * bit / 8 + j * bit / 8;
			temp = m_lgBuffer[index];
			m_lgBuffer[index] = m_lgBuffer[index + 2];
			m_lgBuffer[index + 2] = temp;
		}
	}

	delete tempbuffer;
	tempbuffer = nullptr;
}