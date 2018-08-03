#ifndef _FILE_LGMATRIX_H
#define _FILE_LGMATRIX_H

#include "lgPoint.h"
#include "lgCamera.h"

class lgQuaternion;

class lgMatrix
{
private:
	double** m_lgMatrix;
	unsigned int m_lgR;
	unsigned int m_lgC;
	lgTransfer m_lgTransfer;

	void lgGetDetMatrix(const lgMatrix&, lgMatrix&, lgMatrix&, unsigned int, 
		unsigned int, lgMatrix&, double&);
public:
	lgMatrix();
	lgMatrix(unsigned int, unsigned int);
	lgMatrix(const lgMatrix&);
	~lgMatrix();

	virtual void lgInit();
	virtual void lgCopy(const lgMatrix&);
	virtual void lgMakeZeroMatrix(unsigned int, unsigned int);
	virtual void lgMakeDiagonalMatrix(unsigned int, double);
	virtual void lgMakeUnitMatrix(unsigned int);
	virtual const lgMatrix lgDotMultiply(const lgMatrix&);
	virtual void lgEmptyMatrix(double);
	virtual void lgDeleteMatrix();
	virtual const lgMatrix lgTransposMatrix();
	virtual bool lgGetReversibleMatrix(lgMatrix&);
	virtual const lgMatrix lgGetAdjMatrix();
	virtual double lgGetDetMatrix();
	virtual const lgMatrix lgGetOrthogonalMatrix(unsigned int count, double k);
	virtual bool lgIsOrthogonal();
	virtual bool lgIsReversible();
	virtual unsigned int lgSgn(const lgMatrix&) const;
	virtual void lgReAlloc(unsigned int, unsigned int);
	virtual const lgQuaternion lgMatrixCopyToQuaternion();

	virtual void lgMatrixTolgEluerAngle(lgEluer& tlgEluer);
	virtual void lgMatrixTolgQuaternion(lgQuaternion& tlgQuaternion);

	virtual unsigned int lgGetRow() const;
	virtual unsigned int lgGetColumn() const;
	virtual bool lgCopyFromMatrix(unsigned int, unsigned int, 
		const lgMatrix&, unsigned int, 
		unsigned int, unsigned int, unsigned int);

	static  void lgMakeLocalToWorldMatrix(const lgPoint&, lgMatrix&);
	static void lgMakeWorldToCameraMatrix(const lgCamera&, lgMatrix&);
	static void lgMakeCameraToViewMatrix(const lgCamera&, lgMatrix&);
	static void lgMakeViewToWindowMatrix(const lgCamera&, lgMatrix&);
	static void lgMakeRotateMatrix(double, const lgVector&, lgMatrix&);
	static void lgMakeLocalToWindowMatrix(const lgPoint&, const lgCamera&, lgMatrix&);
	static void lgMakeZoomMatrix(const lgVector&, lgMatrix&);
	static void lgMakeMoveMatrix(const lgVector&, lgMatrix&);
	static double lgGetInnerProduct(const lgMatrix&, const lgMatrix&);

	virtual const lgMatrix operator +(const lgMatrix&);
	virtual const lgMatrix operator -(const lgMatrix&);
	virtual const lgMatrix operator *(const lgMatrix&);
	friend const lgMatrix operator *(const lgMatrix&, const lgMatrix&);
	friend const lgMatrix operator *(double, const lgMatrix&);
	const lgMatrix operator *(double);
	virtual const lgMatrix operator /(double) const;
	virtual const lgMatrix operator =(const lgMatrix&);
	virtual const lgMatrix operator =(const lgPoint&);
	virtual double* operator [](unsigned index) const;

	//!
	virtual void lgPrintMatrix() const;
};
#endif