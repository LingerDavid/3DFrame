#ifndef _FILE_LGBMP_H
#define _FILE_LGBMP_H

#include <Windows.h>

class lgBmp
{
public:
	BITMAPFILEHEADER m_lgBmpFileHeader;
	BITMAPINFO m_lgBmpInfo;
	unsigned char* m_lgBuffer;

	lgBmp();
	~lgBmp();

	virtual void lgFlipBitmap();
};
#endif