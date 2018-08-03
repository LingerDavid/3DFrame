#include <math.h>

#include "lgMatrix.h"
#include "lgVector.h"
#include "lgFace.h"
#include "lgPoint.h"

class lgMatrix;
template<typename T>
class lgLink;
class lgQuaternion;
class lgCamera;


lgPoint::lgPoint()
{
	m_lgXYZ[X] = 0.0;
	m_lgXYZ[Y] = 0.0;
	m_lgXYZ[Z] = 0.0;

	m_lgUVN[X] = 0.0;
	m_lgUVN[Y] = 0.0;
	m_lgUVN[Z] = 0.0;

	m_lgTextureUV[0] = 0.0;
	m_lgTextureUV[1] = 0.0;

	m_lgPointColor.lgSetRGB(255.0, 0.0, 0.0);
}

lgPoint::lgPoint(double x, double y, double z)
{
	m_lgXYZ[X] = x;
	m_lgXYZ[Y] = y;
	m_lgXYZ[Z] = z;

	m_lgUVN[X] = 0.0;
	m_lgUVN[Y] = 0.0;
	m_lgUVN[Z] = 0.0;

	m_lgTextureUV[0] = 0.0;
	m_lgTextureUV[1] = 0.0;

	m_lgPointColor.lgSetRGB(255.0, 0.0, 0.0);
}

lgPoint::lgPoint(const lgPoint& tlgPoint)
{
	m_lgXYZ[X] = tlgPoint.lgGetX();
	m_lgXYZ[Y] = tlgPoint.lgGetY();
	m_lgXYZ[Z] = tlgPoint.lgGetZ();

	m_lgUVN[X] = tlgPoint.lgGetU();
	m_lgUVN[Y] = tlgPoint.lgGetV();
	m_lgUVN[Z] = tlgPoint.lgGetN();

	m_lgTextureUV[0] = tlgPoint.lgGetTextureU();
	m_lgTextureUV[1] = tlgPoint.lgGetTextureV();

	m_lgPointColor = tlgPoint.lgGetPointColor();
}

lgPoint::~lgPoint()
{
}

bool operator ==(const lgPoint& tlgPoint1, const lgPoint& tlgPoint2)
{
	return ((abs(tlgPoint2.lgGetX() - tlgPoint1.lgGetX()) < 10E-10)
		&& (abs(tlgPoint2.lgGetY() - tlgPoint1.lgGetY()) < 10E-10)
		&& (abs(tlgPoint2.lgGetZ() - tlgPoint1.lgGetZ()) < 10E-10));
}

bool operator !=(const lgPoint& tlgPoint1, const lgPoint& tlgPoint2)
{
	return ((abs(tlgPoint2.lgGetX() - tlgPoint1.lgGetX()) > 10E-10)
		|| (abs(tlgPoint2.lgGetY() - tlgPoint1.lgGetY()) > 10E-10)
		|| (abs(tlgPoint2.lgGetZ() - tlgPoint1.lgGetZ()) > 10E-10));
}

const lgPoint& lgPoint::operator /(double tK)
{
	m_lgXYZ[X] /= tK;
	m_lgXYZ[Y] /= tK;
	m_lgXYZ[Z] /= tK;
	return *this;
}

const lgPoint& lgPoint::operator =(const lgPoint& tlgPoint)
{
	m_lgXYZ[X] = tlgPoint.lgGetX();
	m_lgXYZ[Y] = tlgPoint.lgGetY();
	m_lgXYZ[Z] = tlgPoint.lgGetZ();

	m_lgUVN[X] = tlgPoint.lgGetU();
	m_lgUVN[Y] = tlgPoint.lgGetV();
	m_lgUVN[Z] = tlgPoint.lgGetN();

	m_lgTextureUV[0] = tlgPoint.lgGetTextureU();
	m_lgTextureUV[1] = tlgPoint.lgGetTextureV();

	m_lgPointColor = tlgPoint.lgGetPointColor();

	return *this;
}

const lgPoint& lgPoint::operator =(lgMatrix& tlgMatrix)
{
	m_lgXYZ[X] = tlgMatrix[0][0] / tlgMatrix[0][3];
	m_lgXYZ[Y] = tlgMatrix[0][1] / tlgMatrix[0][3];
	m_lgXYZ[Z] = tlgMatrix[0][2] / tlgMatrix[0][3];

	return *this;
}

const lgPoint operator +(const lgPoint& tlgPoint1, const lgPoint& tlgPoint2)
{
	lgPoint tlgRestPoint;
	tlgRestPoint.lgSetX(tlgPoint1.lgGetX() + tlgPoint2.lgGetX());
	tlgRestPoint.lgSetY(tlgPoint1.lgGetY() + tlgPoint2.lgGetY());
	tlgRestPoint.lgSetZ(tlgPoint1.lgGetZ() + tlgPoint2.lgGetZ());
	return tlgRestPoint;
}

const lgPoint operator -(lgPoint& tlgPoint)
{
	tlgPoint.lgSetX(-tlgPoint.lgGetX());
	tlgPoint.lgSetY(-tlgPoint.lgGetY());
	tlgPoint.lgSetZ(-tlgPoint.lgGetZ());
	return tlgPoint;
}

const lgPoint operator - (const lgPoint& tlgPoint1, const lgPoint& tlgPoint2)
{
	lgPoint tlgRestPoint;
	tlgRestPoint.lgSetX(tlgPoint1.lgGetX() - tlgPoint2.lgGetX());
	tlgRestPoint.lgSetY(tlgPoint1.lgGetY() - tlgPoint2.lgGetY());
	tlgRestPoint.lgSetZ(tlgPoint1.lgGetZ() - tlgPoint2.lgGetZ());
	return tlgRestPoint;
}

double& lgPoint::operator [](unsigned int index)
{
	return m_lgXYZ[index];
}

double lgPoint::lgGetDisPtToPt(const lgPoint& tlgPoint) const
{
	double dist = 0.0;
	dist = sqrt(m_lgXYZ[X] * tlgPoint.lgGetX() + m_lgXYZ[Y] * tlgPoint.lgGetY() + m_lgXYZ[Z] * tlgPoint.lgGetZ());
	return dist;
}

double lgPoint::lgGetDisPtToLine(const lgLine&)
{
	double dist = 0.0;
	return dist;
}

double lgPoint::lgGetDisToFace(const lgFace& tlgFace) const
{
	double dist = 0.0, a, b, c, d;
	tlgFace.lgGetStandardFormat(a, b, c, d);
	
	lgVector tlgVector(lgPoint(0.0, 0.0, 0.0), *this), normal = tlgFace.lgGetNormal();
	normal.lgNormalize();
	dist = tlgVector.lgDotMultiply(tlgVector) - d;
	return dist;
}

lgColor lgPoint::lgGetPointColor() const
{
	return m_lgPointColor;
}

double lgPoint::lgGetTextureU() const
{
	return m_lgTextureUV[0];
}

double lgPoint::lgGetTextureV() const
{
	return m_lgTextureUV[1];
}

void lgPoint::lgSetTextureU(double u)
{
	m_lgTextureUV[0] = u;
}

void lgPoint::lgSetTextureV(double v)
{
	m_lgTextureUV[1] = v;
}

void lgPoint::lgSetPointColor(const lgColor& tlgColor)
{
	m_lgPointColor = tlgColor;
}

const lgPoint lgPoint::lgLocalToWindow(const lgPoint& tlgWorldPoint, const lgCamera& tlgCamera)
{
	lgMatrix tlgMatrix, tlgMat;
	tlgMat.lgMakeZeroMatrix(1, 4);
	tlgMat[0][0] = m_lgXYZ[0];
	tlgMat[0][1] = m_lgXYZ[1];
	tlgMat[0][2] = m_lgXYZ[2];
	tlgMat[0][3] = 1.0;
	lgMatrix::lgMakeLocalToWindowMatrix(tlgWorldPoint, tlgCamera, tlgMatrix);
	m_lgXYZ[0] = tlgMat[0][0];
	m_lgXYZ[1] = tlgMat[0][1];
	m_lgXYZ[2] = tlgMat[0][2];
	if (tlgMat[0][3])
	{
		m_lgXYZ[0] /= tlgMat[0][3];
		m_lgXYZ[1] /= tlgMat[0][3];
		m_lgXYZ[2] /= tlgMat[0][3];
	}
	return *this;
}

const lgPoint lgPoint::lgLocalToWindow(const lgMatrix& tlgMatrix)
{
	lgMatrix tlgMat;
	tlgMat.lgMakeZeroMatrix(1, 4);
	tlgMat[0][0] = m_lgXYZ[0];
	tlgMat[0][1] = m_lgXYZ[1];
	tlgMat[0][2] = m_lgXYZ[2];
	tlgMat[0][3] = 1.0;
	tlgMat = tlgMat * tlgMatrix;
	m_lgXYZ[0] = tlgMat[0][0];
	m_lgXYZ[1] = tlgMat[0][1];
	m_lgXYZ[2] = tlgMat[0][2];
	if (tlgMat[0][3])
	{
		m_lgXYZ[0] /= tlgMat[0][3];
		m_lgXYZ[1] /= tlgMat[0][3];
		m_lgXYZ[2] /= tlgMat[0][3];
	}
	return *this;
}

void lgPoint::lgPointTolgQuaternion(lgQuaternion& tlgQuaternion)
{
	m_lgTransfer.lgPointTolgQuaternion(*this, tlgQuaternion);
}

double lgPoint::lgGetX() const
{
	return m_lgXYZ[X];
}

double lgPoint::lgGetY() const
{
	return m_lgXYZ[Y];
}

double lgPoint::lgGetZ() const
{
	return m_lgXYZ[Z];
}

double lgPoint::lgGetU() const
{
	return m_lgUVN[0];
}

double lgPoint::lgGetV() const
{
	return m_lgUVN[1];
}

double lgPoint::lgGetN() const
{
	return m_lgUVN[2];
}

lgVector lgPoint::lgGetNormal() const
{
	return lgVector(0.0, 0.0, 0.0, 
		m_lgUVN[0], m_lgUVN[1], m_lgUVN[2]);
}

void lgPoint::lgGetSphericalCoords(double& low, double& theta, double& fin) const
{
	double r = sqrt(m_lgXYZ[X] * m_lgXYZ[X] + m_lgXYZ[Z] * m_lgXYZ[Z]);
	low = lgGetDisPtToPt(lgPoint(0.0, 0.0, 0.0));
	fin = asin(r / low);
	theta = asin(-m_lgXYZ[X] / r);
}

void lgPoint::lgSetX(double tX)
{
	m_lgXYZ[X] = tX;
}

void lgPoint::lgSetY(double tY)
{
	m_lgXYZ[Y] = tY;
}

void lgPoint::lgSetZ(double tZ)
{
	m_lgXYZ[Z] = tZ;
}

void lgPoint::lgSetU(double tU)
{
	m_lgUVN[X] = tU;
}

void lgPoint::lgSetV(double tV)
{
	m_lgUVN[Y] = tV;
}

void lgPoint::lgSetN(double tN)
{
	m_lgUVN[Z] = tN;
}

void lgPoint::lgSetNormal(const lgVector& tlgNormal)
{
	lgDirect tlgDirect = tlgNormal.lgGetDirectVector();
	m_lgUVN[0] = tlgDirect.lgGetX();
	m_lgUVN[1] = tlgDirect.lgGetY();
	m_lgUVN[2] = tlgDirect.lgGetZ();
}

void lgPoint::lgRotate(double tAngle, const lgVector& tlgVector)
{
	lgPoint tlgPoint;
	m_lgControl.lgRotate(tAngle, tlgVector, *this, tlgPoint);

	*this = tlgPoint;
}

void lgPoint::lgRotate(const lgMatrix& tlgMatrix)
{
	lgPoint tlgPoint;
	m_lgControl.lgRotate(tlgMatrix, *this, tlgPoint);

	*this = tlgPoint;
}

void lgPoint::lgMove(const lgVector& tlgVector)
{
	lgPoint tlgPoint;
	m_lgControl.lgMove(tlgVector, *this, tlgPoint);
	*this = tlgPoint;
}

void lgPoint::lgMove(const lgMatrix& tlgMatrix)
{
	lgPoint tlgPoint;
	m_lgControl.lgMove(tlgMatrix, *this, tlgPoint);
	*this = tlgPoint;
}

void lgPoint::lgZoom(const lgVector& tlgVector)
{
	lgPoint tlgPoint;
	m_lgControl.lgZoom(tlgVector, *this, tlgPoint);
	*this = tlgPoint;
}

void lgPoint::lgZoom(const lgMatrix& tlgMatrix)
{
	lgPoint tlgPoint;
	m_lgControl.lgZoom(tlgMatrix, *this, tlgPoint);
	*this = tlgPoint;
}

void lgPoint::lgTransfer(const lgMatrix& tlgMatrix)
{
	lgPoint tlgPoint;
	m_lgControl.lgTransfer(tlgMatrix, *this, tlgPoint);
	*this = tlgPoint;
}

void lgPoint::lgDraw(void* dc, lgCamera& tlgCamera)
{
	m_lgDisplay.lgDrawPoint(dc, tlgCamera, *this, lgPoint(0 ,0, 0));
}