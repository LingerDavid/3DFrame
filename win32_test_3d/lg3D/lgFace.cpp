#include <math.h>
#include "lgFace.h"


void lgFace::lgStandardFormatToPointNormalFormat(double A, double B, 
	double C, double D, lgPoint& tlgPoint, lgVector& tlgVector) const
{
	lgDirect tlgDirect(A, B, C);
	lgPoint tlgPot(0, 0, -D / C);
	tlgVector.lgSetOrgPoint(tlgPot);
	tlgVector.lgSetDesPoint(tlgPot + tlgDirect);
	tlgPoint = tlgPot;

}

void lgFace::lgPointNormalFormatToStandardFormat(const lgPoint& tlgPoint, const lgVector& tlgVector,
	double& A, double& B, double& C, double& D) const
{
	lgDirect tlgDirect = tlgVector.lgGetDirectVector();
	A = tlgDirect.lgGetX();
	B = tlgDirect.lgGetY();
	C = tlgDirect.lgGetZ();
	D = -A * tlgPoint.lgGetX() - B * tlgPoint.lgGetY() - C * tlgPoint.lgGetZ();
}

void lgFace::lgSetNormalVector(const lgPoint& tlgPoint1, const lgPoint& tlgPoint2, const lgPoint& tlgPoint3)
{
	lgVector tlgVector1(tlgPoint1, tlgPoint2), 
		tlgVector2(tlgPoint2, tlgPoint3);
	lgSetNormalVector(tlgVector1, tlgVector2);
	m_lgNormal = tlgVector1 * tlgVector2;
	m_lgNormal.lgNormalize();
	m_lgPoint = tlgPoint1;
}

void lgFace::lgSetNormalVector(const lgVector& tlgVector1, const lgVector& tlgVector2)
{
	m_lgNormal = tlgVector1 * tlgVector2;
	m_lgNormal.lgNormalize();
	m_lgPoint = tlgVector1.lgGetOrgPoint();
}

lgFace::lgFace()
{
	lgSetFaceColor(255.0, 0.0, 0.0);
}

lgFace::lgFace(double A, double B, double C, double D)
{
	lgStandardFormatToPointNormalFormat(A, B, C, D, m_lgPoint, m_lgNormal);
	m_lgNormal.lgNormalize();
	lgSetFaceColor(255.0, 0.0, 0.0);
}

lgFace::lgFace(const lgPoint& tlgPoint1, const lgPoint& tlgPoint2, const lgPoint& tlgPoint3)
{
	lgVector tlgVector1(tlgPoint1, tlgPoint2), tlgVector2(tlgPoint2, tlgPoint3);
	lgFace(tlgVector1, tlgVector2);
	lgSetFaceColor(255.0, 0.0, 0.0);
}

lgFace::lgFace(const lgVector& tlgVector1, const lgVector& tlgVector2)
{
	m_lgNormal = tlgVector1 * tlgVector2;
	m_lgPoint = tlgVector1.lgGetOrgPoint();
	m_lgNormal.lgNormalize();
	lgSetFaceColor(255.0, 0.0, 0.0);
}

lgFace::lgFace(const lgFace& tlgFace)
{
	m_lgNormal = tlgFace.lgGetNormal();
	m_lgPoint = tlgFace.lgGetPoint();
	m_lgNormal.lgNormalize();
	m_lgFaceColor = tlgFace.lgGetFaceColor();
}

bool lgFace::IsParallel(const lgFace& tlgFace)
{
	return true;
}

const lgLine lgFace::lgGetIntersectedLine(const lgFace& tlgFace)
{
	lgLine tlgLine;
	return tlgLine;
}

void lgFace::lgSetNormal(const lgVector& tlgVector)
{
	m_lgNormal = tlgVector;
	m_lgNormal.lgNormalize();
}

const lgVector lgFace::lgGetNormal() const
{
	return m_lgNormal;
}

void lgFace::lgSetPoint(const lgPoint& tlgPoint)
{
	m_lgPoint = tlgPoint;
}

const lgPoint lgFace::lgGetPoint() const
{
	return m_lgPoint;
}

void lgFace::lgGetStandardFormat(double& A, double& B, double& C, double& D) const
{
	lgPointNormalFormatToStandardFormat(m_lgPoint, m_lgNormal, A, B, C, D);
}

void lgFace::lgGetPointNormalFormat(lgPoint& tlgPoint, lgVector& tlgVector) const
{
	tlgPoint = m_lgPoint;
	tlgVector = m_lgNormal;
}

double lgFace::lgGetParameterD()
{
	lgVector tlgVector(lgPoint(0.0, 0.0, 0.0), m_lgPoint);
	return tlgVector.lgDotMultiply(m_lgNormal);
}


lgColor lgFace::lgGetFaceColor() const
{
	return m_lgFaceColor;
}

void lgFace::lgSetFaceColor(lgColor color)
{
	m_lgFaceColor = color;
}

void lgFace::lgSetFaceColor(double r, double g, double b)
{
	m_lgFaceColor.lgSetRed(r);
	m_lgFaceColor.lgSetGreen(g);
	m_lgFaceColor.lgSetBlue(b);
}

void lgFace::lgSetStandardFormat(double A, double B, double C, double D)
{
	lgStandardFormatToPointNormalFormat(A, B, C, D, m_lgPoint, m_lgNormal);
	m_lgNormal.lgNormalize();
}

void lgFace::lgSetPointNormalFormat(lgPoint tlgPoint, lgVector tlgVector)
{
	m_lgPoint = tlgPoint;
	m_lgNormal = tlgVector;
	m_lgNormal.lgNormalize();
}

const lgPoint lgFace::lgGetNearesetPoint(const lgPoint& tlgPoint)
{
	double dist = tlgPoint.lgGetDisToFace(*this);
	lgVector normal = m_lgNormal, ltgVector(lgPoint(0.0, 0.0, 0.0), tlgPoint);
	normal.lgNormalize();
	ltgVector = ltgVector + dist * normal;
	return (ltgVector.lgGetDesPoint());
}

bool lgFace::lgIsVisible(const lgVector& tlgVector)
{
	return true;
}

const lgPoint lgFace::lgGetIntersectedPoint(const lgFace& tlgFace1, const lgFace& tlgFace2, 
	const lgFace& tlgFace3)
{
	double a1, b1, c1, d1,
		a2, b2, c2, d2,
		a3, b3, c3, d3;
	tlgFace1.lgGetStandardFormat(a1, b1, c1, d1);
	tlgFace2.lgGetStandardFormat(a2, b2, c2, d2);
	tlgFace3.lgGetStandardFormat(a3, b3, c3, d3);

	lgVector n1, n2, n3, p;
	n1 = tlgFace1.lgGetNormal();
	n2 = tlgFace2.lgGetNormal();
	n3 = tlgFace3.lgGetNormal();

	p = (n1 * n2);

	p = (d1 * (n3 * n2) + d2 * (n3 * n1) + d3 * p) / (p.lgDotMultiply(n3));

	return p.lgGetDesPoint();
}

bool operator ==(const lgFace& tlgFace1, const lgFace& tlgFace2)
{
	double A1 = 0.0, B1 = 0.0, C1 = 0.0, D1 = 0.0,
		A2 = 0.0, B2 = 0.0, C2 = 0.0, D2 = 0.0;
	tlgFace1.lgGetStandardFormat(A1, B1, C1, D1);
	tlgFace2.lgGetStandardFormat(A2, B2, C2, D2);
	if (abs(A1 - A2) > 10E-10
		|| abs(B1 - B2) > 10E-10
		|| abs(C1 - C2) > 10E-10)
	{
		return false;
	}
	return true;
}

const lgFace lgFace::operator =(const lgFace& tlgFace)
{
	m_lgPoint = tlgFace.lgGetPoint();
	m_lgNormal = tlgFace.lgGetNormal();
	return *this;
}

void lgFace::lgRotateFace(double tAngle, const lgVector& tlgVector)
{
	//normal
	lgVector tlgNormal;
	m_lgControl.lgRotate(tAngle, tlgVector, m_lgNormal, tlgNormal);
	m_lgNormal = tlgNormal;
	//point
	lgPoint tlgPoint;
	m_lgControl.lgRotate(tAngle, tlgVector, m_lgPoint, tlgPoint);
	m_lgPoint = tlgPoint;
}

void lgFace::lgRotateFace(const lgMatrix& tlgMatrix)
{
	//normal
	lgVector tlgNormal;
	m_lgControl.lgRotate(tlgMatrix, m_lgNormal, tlgNormal);
	m_lgNormal = tlgNormal;
	//point
	lgPoint tlgPoint;
	m_lgControl.lgRotate(tlgMatrix, m_lgPoint, tlgPoint);
	m_lgPoint = tlgPoint;
}

void lgFace::lgMoveFace(const lgVector& tlgVector)
{
	//normal
	lgVector tlgNormal;
	m_lgControl.lgMove(tlgVector, m_lgNormal, tlgNormal);
	m_lgNormal = tlgNormal;
	//point
	lgPoint tlgPoint;
	m_lgControl.lgMove(tlgVector, m_lgPoint, tlgPoint);
	m_lgPoint = tlgPoint;
}

void lgFace::lgMoveFace(const lgMatrix& tlgMatrix)
{
	//normal
	lgVector tlgNormal;
	m_lgControl.lgMove(tlgMatrix, m_lgNormal, tlgNormal);
	m_lgNormal = tlgNormal;
	//point
	lgPoint tlgPoint;
	m_lgControl.lgMove(tlgMatrix, m_lgPoint, tlgPoint);
	m_lgPoint = tlgPoint;
}

void lgFace::lgTransferFace(const lgMatrix& tlgMatrix)
{
	//normal
	lgVector tlgNormal;
	m_lgControl.lgTransfer(tlgMatrix, m_lgNormal, tlgNormal);
	m_lgNormal = tlgNormal;
	//point
	lgPoint tlgPoint;
	m_lgControl.lgTransfer(tlgMatrix, m_lgPoint, tlgPoint);
	m_lgPoint = tlgPoint;
}