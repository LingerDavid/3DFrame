#ifndef _FILE_LGVECTOR_H
#define _FILE_LGVECTOR_H

class lgPoint;
#include "lgLine.h"

#ifndef _LGDIRECT_CLASS
#define _LGDIRECT_CLASS
typedef lgPoint lgDirect;
#endif

class lgVector:public lgLine
{
private:
	lgDisplay m_lgDispaly;
public:
	lgVector();
	lgVector(const lgPoint&, const lgPoint&);
	lgVector(double, double, double, double, double, double);
	lgVector(const lgVector&);
	virtual const lgVector lgNormalize();
	virtual double lgGetAbsoluteValue() const;
	virtual void lgProjToLine(const lgLine&, lgVector&);
	virtual void lgProjToFace(const lgFace&, lgVector&);
	virtual const double lgDotMultiply(const lgVector&) const;

	virtual bool operator ==(const lgVector&);
	virtual bool operator !=(const lgVector&);
	virtual const lgVector operator =(const lgVector&);
	virtual const lgVector operator +(const lgVector&);
	friend const lgVector operator +(const lgVector&, const lgVector&);
	virtual const lgVector operator -(const lgVector&);
	friend const lgVector operator -(lgVector&);
	virtual const lgVector operator *(const lgVector&);
	friend const lgVector operator *(const lgVector&, const lgVector&);
	friend const lgVector operator *(double, const lgVector&);
	virtual const lgVector operator *(double) const;
	virtual const lgVector operator /(double) const;
	
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