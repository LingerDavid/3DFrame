#ifndef _FILE_LGPOINT_H
#define _FILE_LGPOINT_H

#include "lgControl.h"
#include "lgTransfer.h"
#include "lgDisplay.h"

class lgMatrix;
template<typename T>
class lgLink;
class lgQuaternion;
class lgCamera;

//This class is just for designer because it's time-spending
//and space-spending.
class lgPoint
{
private:
	//position
	double m_lgXYZ[3];
	//normal
	double m_lgUVN[3];
	//texture uv
	double m_lgTextureUV[2];
	lgControl m_lgControl;
	lgTransfer m_lgTransfer;
	lgDisplay m_lgDisplay;
	lgColor m_lgPointColor;
	enum{ X = 0, Y = 1, Z = 2 };
public:

	lgPoint();
	lgPoint(double x, double y, double z);
	lgPoint(const lgPoint& );
	~lgPoint();
	
	friend bool operator ==(const lgPoint&, const lgPoint&);
	friend bool operator !=(const lgPoint&, const lgPoint&);
	virtual const lgPoint& operator /(double);
	virtual double& operator [](unsigned int);
	virtual const lgPoint& operator =(const lgPoint&);
	virtual const lgPoint& operator =(lgMatrix&);
	friend const lgPoint operator +(const lgPoint&, const lgPoint&);
	friend const lgPoint operator -(lgPoint&);
	friend const lgPoint operator -(const lgPoint&, const lgPoint&);

	virtual double lgGetDisPtToPt(const lgPoint&) const;
	virtual double lgGetDisPtToLine(const lgLine&);
	virtual double lgGetDisToFace(const lgFace&) const;
	virtual lgColor lgGetPointColor() const;
	virtual double lgGetTextureU() const;
	virtual double lgGetTextureV() const;
	virtual void lgSetTextureU(double);
	virtual void lgSetTextureV(double);
	virtual void lgSetPointColor(const lgColor&);

	virtual const lgPoint lgLocalToWindow(const lgPoint&, const lgCamera&);
	const lgPoint lgLocalToWindow(const lgMatrix&);

	virtual void lgPointTolgQuaternion(lgQuaternion&);
	
	virtual double lgGetX() const;
	virtual double lgGetY() const;
	virtual double lgGetZ() const;
	virtual double lgGetU() const;
	virtual double lgGetV() const;
	virtual double lgGetN() const;
	virtual lgVector lgGetNormal() const;
	virtual void lgGetSphericalCoords(double&,double&, double&) const;
	virtual void lgSetX(double);
	virtual void lgSetY(double);
	virtual void lgSetZ(double);
	virtual void lgSetU(double);
	virtual void lgSetV(double);
	virtual void lgSetN(double);
	virtual void lgSetNormal(const lgVector&);

	virtual void lgRotate(double, const lgVector&);
	virtual void lgRotate(const lgMatrix&);
	virtual void lgMove(const lgVector&);
	virtual void lgMove(const lgMatrix&);
	virtual void lgZoom(const lgVector&);
	virtual void lgZoom(const lgMatrix&);
	virtual void lgTransfer(const lgMatrix&);

	virtual void lgDraw(void*, lgCamera&);
};
#endif