#ifndef _FILE_LGFACE_H
#define _FILE_LGFACE_H
#include <Windows.h>

#include "lgColor.h"
#include "lgVector.h"

class lgFace
{
private:

	void lgStandardFormatToPointNormalFormat(double, double, double, double, lgPoint&, lgVector&) const;
	void lgPointNormalFormatToStandardFormat(const lgPoint&, const lgVector&, 
		double&, double&, double&, double&) const;
protected:
	lgVector m_lgNormal;
	lgPoint m_lgPoint;
	lgControl m_lgControl;
	lgColor m_lgFaceColor;
	virtual void lgSetNormalVector(const lgPoint&, const lgPoint&, const lgPoint&);
	virtual void lgSetNormalVector(const lgVector&, const lgVector&);
public:
	lgFace();
	lgFace(double A, double B, double C, double D);
	lgFace(const lgPoint&, const lgPoint&, const lgPoint&);
	lgFace(const lgVector&, const lgVector&);
	lgFace(const lgFace&);

	virtual bool IsParallel(const lgFace&);
	virtual const lgLine lgGetIntersectedLine(const lgFace&);
	virtual void lgSetNormal(const lgVector&);
	virtual const lgVector lgGetNormal() const;
	virtual void lgSetPoint(const lgPoint&);
	virtual const lgPoint lgGetPoint() const;
	virtual void lgGetStandardFormat(double&, double&, double&, double&) const;
	virtual void lgGetPointNormalFormat(lgPoint&, lgVector&) const;
	virtual double lgGetParameterD();
	virtual lgColor lgGetFaceColor() const;
	virtual void lgSetFaceColor(lgColor);
	virtual void lgSetFaceColor(double, double, double);
	virtual void lgSetStandardFormat(double, double, double, double);
	virtual void lgSetPointNormalFormat(lgPoint, lgVector);
	virtual const lgPoint lgGetNearesetPoint(const lgPoint&);
	virtual bool lgIsVisible(const lgVector&);

	static const lgPoint lgGetIntersectedPoint(const lgFace&, const lgFace&, const lgFace&);

	friend bool operator ==(const lgFace&, const lgFace&);
	virtual const lgFace operator =(const lgFace&);

	virtual void lgRotateFace(double, const lgVector&);
	virtual void lgRotateFace(const lgMatrix&);
	virtual void lgMoveFace(const lgVector&);
	virtual void lgMoveFace(const lgMatrix&);
	virtual void lgTransferFace(const lgMatrix&);

};
#endif