#ifndef _FILE_LGIO_H
#define _FILE_LGIO_H
#include <stdio.h>
#include <stdlib.h>
#include "lgBmp.h"

class lgObject;
class lgBmp;

#define PLX_RGB_MASK	0x8000
#define PLX_SHADE_MODE_MASK	0x6000
#define PLX_2SIDED_MASK 0x1000
#define PLX_COLOR_MASK 0x0fff

#define PLX_COLOR_MODE_RGB_FLAG 0x8000
#define PLX_COLOR_MODE_INDEXED_FLAG 0x0000

#define PLX_2SIDED_FLAG 0x1000
#define PLX_1SIDED_FLAG 0X0000

#define PLX_SHADE_MODE_PURE_FLAG 0x0000
#define PLX_SHADE_MODE_FLAT_FLAG 0x2000
#define PLX_SHADE_MODE_GOURAUD_FLAG 0x4000
#define PLX_SHADE_MODE_PHONG_FLAG 0x6000

/*
typedef struct tagBITMAPFILEHEADER
{
	WORD bfType;
	DWORD bfSize;
	WORD bfReversed1;
	WORD bfReversed2;
	DWORD bfOffBits;

}BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
}BITMAPINFOHEADER;

typedef struct tagRGBQUAD
{
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReversed;
}RGBQUAD;

typedef struct tagBITMAPINFO
{
	BITMAPINFOHEADER bmiHeader;
	RGBQUAD bmiColors[1];
}BITMAPINFO;*/


class lgIO
{
	//PLG is a simple file,
	//so we can just finish plg file
	// nanalyse in IO operation process
	//but as for the .3ds or other more
	// complex model file,we need analyse
	//ascii string by a analyse factory.
private:
	char* lgGetLineFromPLGFile(char*, int, FILE*);
	char* lgGetLineFromASCFile(char*, int, FILE*);
public:
	lgIO();
	~lgIO();

	virtual bool lgGetObjectFromPLGFile(char*, lgObject&);
	virtual bool lgGetObjectFromASCFile(char*, lgObject&);
	virtual bool lgGetBitmapFromFile(char*, lgBmp&);
};

#endif