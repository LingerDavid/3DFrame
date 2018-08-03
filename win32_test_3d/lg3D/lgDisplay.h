#ifndef _FILE_LGDISPLAY_H
#define _FILE_LGDISPLAY_H
#include <Windows.h>

#include "lgClip.h"
#include "lgColor.h"

class lgObject;
class lgVector;
class lgCamera;
class lgTriangle;
template<typename T>
class lgLink;

#ifndef WORLD_AXIS_LENGTH 
#define WORLD_AXIS_LENGTH 10
#endif


typedef struct _lgPOINT
{
	int x;
	int y;
}lgPOINT, *plgPOINT;

class lgDisplay
{
private:
	lgClip m_lgClip;
	int lgSign(int);
	lgColor m_lgColor;
public:
	lgDisplay();

	virtual void lgDrawWorldAxises(void*, const lgCamera&);

	virtual void lgDrawPoint(void*, int, int);
	virtual void lgDrawPoint(void*, const lgPOINT&);
	virtual void lgDrawPoint(void*, int, int, int, int, int);
	virtual void lgDrawLine(void*, int, int, int, int);
	virtual void lgDrawLine(void*, const lgPOINT&, const lgPOINT&);
	virtual void lgDrawLine(void*, int, int, int, int, int, int, int);
	virtual void lgDawTriangle(void*, const lgPOINT&, const lgPOINT&, const lgPOINT&);

	virtual void lgDrawPoint(void*, const lgCamera&, const lgPoint&, const lgPoint&);
	virtual void lgDrawLine(void*, const lgCamera&, const lgVector&, const lgPoint&);
	virtual void lgDrawObject(void*, const lgCamera&, lgObject& tlgObject);

	virtual void lgDrawObject(void*, const lgObject&, int, int);

	virtual void lgFillTopTriangle(void*, double, double, double, double, double, double);
	virtual void lgFillBottomTriangle(void*, double, double, double, double, double, double);
	virtual void lgFillTriangle(void*, const lgPOINT&, const lgPOINT&, const lgPOINT&);

	virtual void lgFillTopTriangleByGouraud(void*, double, double, double, double, double, 
		double, double, double, double, double, 
		double, double,double, double, double);
	virtual void lgFillBottomTriangleByGouraud(void*, double, double, double, double, double,
		double, double, double, double, double,
		double, double, double, double, double);
	virtual void lgFillTriangleByGouraud(void*, const lgPOINT&, const lgColor&, 
		const lgPOINT&, const lgColor&, const lgPOINT&, const lgColor&);

	virtual void lgFillTopTriangleTexture(void*, double, double, double, double, 
		double, double, double, double,
		double, double, double, double,
		unsigned char*, int, int, int);
	virtual void lgFillBottomTriangleTexture(void*, double, double, double, double,
		double, double, double, double,
		double, double, double, double,
		unsigned char*, int, int, int);
	virtual void lgFillTriangleTexture(void*, const lgPOINT&, double, double, 
		const lgPOINT&, double, double, 
		const lgPOINT&, double, double, 
		unsigned char*, int, int, int);

	virtual void lgFillTopTriangleTextureByGouraud(void*, double, double, double, double, double, double, double,
		double, double, double, double, double, double, double,
		double, double, double, double, double, double, double,
		unsigned char*, int, int, int);
	virtual void lgFillBottomTriangleTextureByGouraud(void*, double, double, double, double, double, double, double,
		double, double, double, double, double, double, double,
		double, double, double, double, double, double, double,
		unsigned char*, int, int, int);
	virtual void lgFillTriangleTextureByGouraud(void*, const lgPOINT&, const lgColor&, double, double,
		const lgPOINT&, const lgColor&, double, double,
		const lgPOINT&, const lgColor&, double, double,
		unsigned char*, int, int, int);

	virtual void lgFillTopTriangleFixedTextureByGouraud(void*, double, double, double, double, double, double, double, double,
		double, double, double, double, double, double, double, double,
		double, double, double, double, double, double, double, double,
		unsigned char*, int, int, int);
	virtual void lgFillBottomTriangleFixedTextureByGouraud(void*, double, double, double, double, double, double, double, double,
		double, double, double, double, double, double, double, double,
		double, double, double, double, double, double, double, double,
		unsigned char*, int, int, int);
	virtual void lgFillTriangleFixedTextureByGouraud(void*, const lgPOINT&, double, const lgColor&, double, double,
		const lgPOINT&, double, const lgColor&, double, double,
		const lgPOINT&, double, const lgColor&, double, double,
		unsigned char*, int, int, int);

};
#endif