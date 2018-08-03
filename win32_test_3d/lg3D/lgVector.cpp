#include <math.h>
#include "lgMatrix.h"
#include "lgVector.h"

lgVector::lgVector() :lgLine()
{
	m_lgTMin = 0.0;
	m_lgTMax = 1.0;
}

lgVector::lgVector(const lgPoint& tlgOrgPoint, const lgPoint& tlgDesPoint)
{
	lgSetOrgPoint(tlgOrgPoint);
	lgSetDesPoint(tlgDesPoint);
}

lgVector::lgVector(double p1x, double p1y, double p1z, 
	double p2x, double p2y, double p2z)
{
	lgPoint tlgOrgPoint(p1x, p1y, p1z), tlgDesPoint(p2x, p2y, p2z);
	lgSetOrgPoint(tlgOrgPoint);
	lgSetDesPoint(tlgDesPoint);
}

lgVector::lgVector(const lgVector& tlgVector) : lgLine(tlgVector)
{
}

const lgVector lgVector::lgNormalize()
{
	double len = lgGetAbsoluteValue();
	lgDirect tlgDirect = lgGetDirectVector();
	if (len > 10E-10)
	{
		tlgDirect = tlgDirect / len;
	}
	lgSetDesPoint(lgGetOrgPoint() + tlgDirect);
	return *this;
}

double lgVector::lgGetAbsoluteValue() const
{
	double a = 0.0;
	lgDirect tlgDirect = lgGetDirectVector();
	a = tlgDirect.lgGetX() * tlgDirect.lgGetX()
		+ tlgDirect.lgGetY() * tlgDirect.lgGetY()
		+ tlgDirect.lgGetZ() * tlgDirect.lgGetZ();
	a = pow(a, 0.5);
	return a;
}

void lgVector::lgProjToLine(const lgLine& tlgLine, lgVector& tlgVector)
{
	double len = lgGetAbsoluteValue();
	lgVector n = tlgVector.lgNormalize();
	*this = lgDotMultiply(n) * n;
}

void lgVector::lgProjToFace(const lgFace&, lgVector& tlgVector)
{
}

const double lgVector::lgDotMultiply(const lgVector& tlgVector) const
{
	double res = 0.0;
	lgDirect tlgDirect1 = lgGetDirectVector(), 
		tlgDirect2 = tlgVector.lgGetDirectVector();
	double x1 = tlgDirect1.lgGetX(),
		y1 = tlgDirect1.lgGetY(),
		z1 = tlgDirect1.lgGetZ(),
		x2 = tlgDirect2.lgGetX(),
		y2 = tlgDirect2.lgGetY(),
		z2 = tlgDirect2.lgGetZ();
	res = x1 * x2 + y1 * y2 + z1 * z2;
	return res;
}

bool lgVector::operator ==(const lgVector& tlgVector)
{
	if (tlgVector.lgGetOrgPoint() != lgGetOrgPoint()
		|| tlgVector.lgGetDesPoint() != lgGetDesPoint())
	{
		return false;
	}
	return true;
}
bool lgVector::operator !=(const lgVector& tlgVector)
{
	return !(*this == tlgVector);
}

const lgVector lgVector::operator =(const lgVector& tlgVector)
{
	lgSetOrgPoint(tlgVector.lgGetOrgPoint());
	lgSetDesPoint(tlgVector.lgGetDesPoint());
	return *this;
}

const lgVector lgVector::operator +(const lgVector& tlgVector)
{
	lgVector tlgVect;
	lgDirect tlgDirect1 = lgGetDirectVector(),
		tlgDirect2 = tlgVector.lgGetDirectVector();
	tlgVect.lgSetOrgPoint(lgGetOrgPoint());
	tlgVect.lgSetDesPoint(lgGetOrgPoint() + (tlgDirect1 + tlgDirect2));
	return tlgVect;
}

const lgVector operator +(const lgVector& tlgVector1, const lgVector& tlgVector2)
{
	lgVector tlgVector3;
	lgDirect tlgDirect1 = tlgVector1.lgGetDirectVector(),
		tlgDirect2 = tlgVector2.lgGetDirectVector();
	tlgVector3.lgSetOrgPoint(tlgVector1.lgGetOrgPoint());
	tlgVector3.lgSetDesPoint(tlgVector1.lgGetOrgPoint() + (tlgDirect1 + tlgDirect2));
	return tlgVector3;
}

const lgVector lgVector::operator -(const lgVector& tlgVector)
{
	lgVector tlgVect = tlgVector;
	tlgVect = -tlgVect;
	tlgVect = (*this) + tlgVect;
	return tlgVect;
}
const lgVector operator -(lgVector& tlgVector)
{
	lgVector tlgVect;
	lgDirect tlgDirect = tlgVector.lgGetDirectVector();
	tlgDirect = -tlgDirect;
	tlgVect.lgSetOrgPoint(tlgVector.lgGetOrgPoint());
	tlgVect.lgSetDesPoint(tlgVector.lgGetOrgPoint() + tlgDirect);
	return tlgVect;
}

const lgVector lgVector::operator *(const lgVector& tlgVector)
{
	lgDirect tlgDirect1 = lgGetDirectVector(), 
		tlgDirect2 = tlgVector.lgGetDirectVector();
	double x1 = tlgDirect1.lgGetX(),
		y1 = tlgDirect1.lgGetY(),
		z1 = tlgDirect1.lgGetZ(),
		x2 = tlgDirect2.lgGetX(),
		y2 = tlgDirect2.lgGetY(),
		z2 = tlgDirect2.lgGetZ();
	lgVector tlgVect(0.0, 0.0, 0.0, 
		y1 * z2 - z1 * y2, 
		z1 * x2 - x1 * z2, 
		x1 * y2 - y1 * x2);
	return tlgVect;
}

const lgVector operator *(const lgVector& tlgVector1, const lgVector& tlgVector2)
{
	lgDirect tlgDirect1 = tlgVector1.lgGetDirectVector(),
		tlgDirect2 = tlgVector2.lgGetDirectVector();
	double x1 = tlgDirect1.lgGetX(),
		y1 = tlgDirect1.lgGetY(),
		z1 = tlgDirect1.lgGetZ(),
		x2 = tlgDirect1.lgGetX(),
		y2 = tlgDirect1.lgGetY(),
		z2 = tlgDirect1.lgGetZ();
	lgVector tlgVect(0.0, 0.0, 0.0,
		y1 * z2 - z1 * y2,
		z1 * x2 - x1 * z2,
		x1 * y2 * y1 * x2);
	return tlgVect;
}

const lgVector lgVector::operator *(double tK) const
{
	lgVector tlgVect = *this;
	lgDirect tlgDirect = lgGetDirectVector();
	double x = tlgDirect.lgGetX(),
		y = tlgDirect.lgGetY(),
		z = tlgDirect.lgGetZ();
	tlgDirect.lgSetX(x * tK);
	tlgDirect.lgSetY(y * tK);
	tlgDirect.lgSetZ(z * tK);
	tlgVect.lgSetDesPoint(tlgVect.lgGetOrgPoint() + tlgDirect);
	return tlgVect;
}

const lgVector operator *(double tK, const lgVector& tlgVector)
{
	lgVector tlgVect;
	lgDirect tlgDirect = tlgVector.lgGetDirectVector();
	double x = tlgDirect.lgGetX(),
		y = tlgDirect.lgGetY(),
		z = tlgDirect.lgGetZ();
	tlgDirect.lgSetX(x * tK);
	tlgDirect.lgSetY(y * tK);
	tlgDirect.lgSetZ(z * tK);
	tlgVect.lgSetDesPoint(tlgVector.lgGetOrgPoint() + tlgDirect);
	return tlgVect;
}

const lgVector lgVector::operator /(double tK) const
{
	lgVector tlgVect = *this;
	lgDirect tlgDirect = lgGetDirectVector();
	double x = tlgDirect.lgGetX(),
		y = tlgDirect.lgGetY(),
		z = tlgDirect.lgGetZ();
	tlgDirect.lgSetX(x / tK);
	tlgDirect.lgSetY(y / tK);
	tlgDirect.lgSetZ(z / tK);
	tlgVect.lgSetDesPoint(lgGetOrgPoint() + tlgDirect);
	return tlgVect;
}

void lgVector::lgRotate(double tAngle, const lgVector& tlgVector)
{
	lgVector tlgVect;
	m_lgControl.lgRotate(tAngle, tlgVector, *this, tlgVect);
	*this = tlgVect;
}

void lgVector::lgRotate(const lgMatrix& tlgMatrix)
{
	lgVector tlgVect;
	m_lgControl.lgRotate(tlgMatrix, *this, tlgVect);
	*this = tlgVect;
}

void lgVector::lgMove(const lgVector& tlgVector)
{
	lgVector tlgVect;
	m_lgControl.lgMove(tlgVector, *this, tlgVect);
	*this = tlgVect;
}

void lgVector::lgMove(const lgMatrix& tlgMatrix)
{
	lgVector tlgVect;
	m_lgControl.lgMove(tlgMatrix, *this, tlgVect);
	*this = tlgVect;
}

void lgVector::lgZoom(const lgVector& tlgVector)
{
	lgVector tlgVect;
	m_lgControl.lgZoom(tlgVector, *this, tlgVect);
	*this = tlgVect;
}

void lgVector::lgZoom(const lgMatrix& tlgMatrix)
{
	lgVector tlgVect;
	m_lgControl.lgZoom(tlgMatrix, *this, tlgVect);
	*this = tlgVect;
}

void lgVector::lgTransfer(const lgMatrix& tlgMatrix)
{
	lgVector tlgVector;
	m_lgControl.lgTransfer(tlgMatrix, *this, tlgVector);
	*this = tlgVector;
}

void lgVector::lgDraw(void* dc, lgCamera& tlgCamera)
{
	m_lgDispaly.lgDrawLine(dc,tlgCamera, *this, lgPoint(0.0, 0.0, 0.0));
}
