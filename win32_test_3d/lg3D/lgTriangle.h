#ifndef _FILE_TRIANGLE_H
#define _FILE_TRIANGLE_H

#include "lgFace.h"

class lgTexture;

class lgTriangle:public lgFace
{
private:
	lgPoint	m_lgPoints[3];
	const lgTexture* m_plgTexture;
	lgDisplay m_lgDisplay;
public:
	lgTriangle();
	lgTriangle(double, double, double, 
		double, double, double, 
		double, double, double);
	lgTriangle(const lgPoint&, const lgPoint&, const lgPoint&);
	lgTriangle(const lgVector&, const lgVector&);
	lgTriangle(const lgTriangle&);

	~lgTriangle();
	
	virtual lgPoint& operator [](unsigned int);
	virtual const lgPoint& operator [](unsigned int) const;
	friend bool operator ==(const lgTriangle&, const lgTriangle&);
	virtual const lgTriangle operator =(const lgTriangle&);

	virtual const lgPoint lgGetBarycentCoord(const lgPoint&);
	virtual const lgPoint lgGetBarycentPoint();
	virtual const lgPoint lgGetInnerCentrePoint();
	virtual const lgPoint lgGetCircumCenterPoint();
	virtual const lgTexture* lgGetTexture() const;
	virtual void lgSetTexture(const lgTexture*);
	virtual double lgGetTriangleArea();

	virtual void lgRotate(double, const lgVector&);
	virtual void lgRotate(const lgMatrix&);
	virtual void lgMove(const lgVector&);
	virtual void lgMove(const lgMatrix&);
	virtual void lgZoom(const lgVector&);
	virtual void lgZoom(const lgMatrix&);

	virtual void lgTransfer(const lgMatrix&);

	virtual void lgDraw(void*, const lgPoint&, const lgCamera&);
};
#endif