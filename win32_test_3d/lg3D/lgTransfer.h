#ifndef _FILE_LGTRANSFER_H
#define _FILE_LGTRANSFER_H

class lgEluer;
class lgMatrix;
class lgQuaternion;
class lgPoint;

class lgTransfer
{
public:
	virtual void lgEluerAngleTolgMatrix(const lgEluer&, lgMatrix&);
	virtual void lgMatrixTolgEluerAngle(const lgMatrix&, lgEluer&);
	virtual void lgQuaternionTolgMatrix(const lgQuaternion&, lgMatrix&);
	virtual void lgMatrixTolgQuaternion(const lgMatrix&, lgQuaternion&);
	virtual void lgEluerAngleTolgQuaternion(const lgEluer&, lgQuaternion&);
	virtual void lgQuaternionTolgEluerAngle(const lgQuaternion&, lgEluer&);

	virtual void lgPointTolgQuaternion(const lgPoint&, lgQuaternion&);
	virtual void lgQuaternionTolgPoint(const lgQuaternion&, lgPoint&);

};

#endif