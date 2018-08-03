#ifndef _FILE_LGELUER_H
#define _FILE_LGELUER_H

#include "lgTransfer.h"

#ifndef PI
#define PI  3.1415926
#endif

class lgEluer
{
private:
	//y axis
	//[-PI,PI]
	double m_lgHeading;
	//x axis
	//[-PI/2£¬PI/2]
	double m_lgPitch;
	//z axis
	//[-PI,PI]
	double m_lgBank;
	lgTransfer m_lgTransfer;
public:
	lgEluer();
	lgEluer(double, double, double);
	lgEluer(const lgEluer&);

	virtual double lgGetHeading() const;
	virtual double lgGetPitch() const;
	virtual double lgGetBank() const;
	virtual void lgSetHeading(double);
	virtual void lgSetPitch(double);
	virtual void lgSetBank(double);

	virtual void lgEluerAngleTolgMatrix(lgMatrix&);
	virtual void lgEluerAngleTolgQuaternion(lgQuaternion&);

	virtual const lgEluer& operator =(const lgEluer&);
	virtual const lgEluer operator +(const lgEluer&);
	friend const lgEluer& operator -(lgEluer&);
};
#endif