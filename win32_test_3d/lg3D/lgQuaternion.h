#ifndef _FILE_LGQUATERNION_H
#define _FILE_LGQUATERNION_H

#include "lgVector.h"
#include "lgMatrix.h"

class lgQuaternion
{
private:
	lgVector m_lgVector;
	double m_lgTheta;
	lgTransfer m_lgTransfer;
public:
	lgQuaternion();
	lgQuaternion(const lgVector&, double);
	lgQuaternion(double, double, double, double);
	lgQuaternion(const lgQuaternion&);

	virtual const lgQuaternion operator +(const lgQuaternion&);
	virtual const lgQuaternion operator -(const lgQuaternion&);
	friend const lgQuaternion operator -(lgQuaternion&);
	virtual const lgQuaternion operator *(const lgQuaternion&) const;
	virtual const lgQuaternion operator /(double);
	friend const lgQuaternion operator *(double, const lgQuaternion&);
	virtual bool operator ==(const lgQuaternion&);
	virtual bool operator !=(const lgQuaternion&);
	virtual const lgQuaternion operator =(const lgQuaternion&);
	virtual const lgQuaternion operator*(const lgMatrix&);
	
	virtual void lgQuaternionTolgEluerAngle(lgEluer&);
	virtual void lgQuaternionTolgMatrix(lgMatrix&);
	virtual void lgQuaternionTolgPoint(lgPoint&);
	
	virtual const lgQuaternion lgGetConjugateQuaternion() const;
	virtual const lgQuaternion lgGetNormalQuaternion() const;
	virtual double lgGetAbsoluteValue() const;
	virtual const lgVector& lgGetVector() const;
	virtual double lgGetW() const;
	virtual double lgGetX() const;
	virtual double lgGetY() const;
	virtual double lgGetZ() const;
	virtual double lgGetTheta() const;
	virtual void lgSetVector(const lgVector&);
	virtual void lgSetTheta(double);
	virtual const lgMatrix lgQuaternionCopyToMatrx();
	virtual const lgQuaternion lgGetReversibleQuaternion() const;
	
	static void lgLog(const lgQuaternion&, lgQuaternion&);
	static void lgExp(const lgQuaternion&, lgQuaternion&);
	static void lgPower(const lgQuaternion&, double tT, lgQuaternion&);
	static void lgSlerp(const lgQuaternion&, const lgQuaternion&, double tT, lgQuaternion&);
	static void lgSquad(const lgQuaternion&, const lgQuaternion&, double tT, lgQuaternion&);

};
#endif