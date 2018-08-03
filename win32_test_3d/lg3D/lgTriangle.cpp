#include <math.h>
#include "lgTriangle.h"
#include "lgLink.h"
#include "lgLink.cpp"

lgTriangle::lgTriangle()
{
	m_lgPoints[0].lgSetX(0.0);
	m_lgPoints[0].lgSetY(0.0);
	m_lgPoints[0].lgSetZ(0.0);

	m_lgPoints[1].lgSetX(0.0);
	m_lgPoints[1].lgSetY(0.0);
	m_lgPoints[1].lgSetZ(0.0);

	m_lgPoints[2].lgSetX(0.0);
	m_lgPoints[2].lgSetY(0.0);
	m_lgPoints[2].lgSetZ(0.0);

	m_lgPoints[0].lgSetU(0.0);
	m_lgPoints[0].lgSetV(0.0);
	m_lgPoints[0].lgSetN(0.0);

	m_lgPoints[1].lgSetU(0.0);
	m_lgPoints[1].lgSetV(0.0);
	m_lgPoints[1].lgSetN(0.0);

	m_lgPoints[2].lgSetU(0.0);
	m_lgPoints[2].lgSetV(0.0);
	m_lgPoints[2].lgSetN(0.0);

	m_lgPoints[0].lgSetTextureU(0.0);
	m_lgPoints[0].lgSetTextureV(0.0);

	m_lgPoints[1].lgSetTextureU(1.0);
	m_lgPoints[1].lgSetTextureV(0.0);

	m_lgPoints[2].lgSetTextureU(0.0);
	m_lgPoints[2].lgSetTextureV(1.0);

	m_plgTexture = nullptr;
}

lgTriangle::lgTriangle(double x1, double y1, double z1,
	double x2, double y2, double z2,
	double x3, double y3, double z3)
{
	m_lgPoints[0].lgSetX(x1);
	m_lgPoints[0].lgSetY(y1);
	m_lgPoints[0].lgSetZ(z1);

	m_lgPoints[1].lgSetX(x2);
	m_lgPoints[1].lgSetY(y2);
	m_lgPoints[1].lgSetZ(z2);

	m_lgPoints[2].lgSetX(x3);
	m_lgPoints[2].lgSetY(y3);
	m_lgPoints[2].lgSetZ(z3);

	m_lgPoints[0].lgSetU(0.0);
	m_lgPoints[0].lgSetV(0.0);
	m_lgPoints[0].lgSetN(0.0);

	m_lgPoints[1].lgSetU(0.0);
	m_lgPoints[1].lgSetV(0.0);
	m_lgPoints[1].lgSetN(0.0);

	m_lgPoints[2].lgSetU(0.0);
	m_lgPoints[2].lgSetV(0.0);
	m_lgPoints[2].lgSetN(0.0);

	m_lgPoints[0].lgSetTextureU(0.0);
	m_lgPoints[0].lgSetTextureV(0.0);

	m_lgPoints[1].lgSetTextureU(1.0);
	m_lgPoints[1].lgSetTextureV(0.0);

	m_lgPoints[2].lgSetTextureU(0.0);
	m_lgPoints[2].lgSetTextureV(1.0);

	m_plgTexture = nullptr;
}

lgTriangle::lgTriangle(const lgPoint& tlgPoint1, const lgPoint&  tlgPoint2, 
	const lgPoint& tlgPoint3) :lgFace(tlgPoint1, tlgPoint2, tlgPoint3)
{
	m_lgPoints[0] = tlgPoint1;
	m_lgPoints[1] = tlgPoint2;
	m_lgPoints[2] = tlgPoint3;

	m_lgPoints[0].lgSetTextureU(0.0);
	m_lgPoints[0].lgSetTextureV(0.0);

	m_lgPoints[1].lgSetTextureU(1.0);
	m_lgPoints[1].lgSetTextureV(0.0);

	m_lgPoints[2].lgSetTextureU(0.0);
	m_lgPoints[2].lgSetTextureV(1.0);

	m_plgTexture = nullptr;
}

lgTriangle::lgTriangle(const lgVector& tlgVector1, const lgVector& tlgVector2) 
: lgFace(tlgVector1, tlgVector2)
{
	m_lgPoints[0] = tlgVector1.lgGetOrgPoint();
	m_lgPoints[1] = tlgVector1.lgGetDesPoint();
	if (m_lgPoints[0] == tlgVector2.lgGetOrgPoint())
	{
		m_lgPoints[2] = tlgVector2.lgGetDesPoint();
	}
	else
	{
		m_lgPoints[2] = tlgVector2.lgGetOrgPoint();
	}

	m_lgPoints[0].lgSetTextureU(0.0);
	m_lgPoints[0].lgSetTextureV(0.0);

	m_lgPoints[1].lgSetTextureU(1.0);
	m_lgPoints[1].lgSetTextureV(0.0);

	m_lgPoints[2].lgSetTextureU(0.0);
	m_lgPoints[2].lgSetTextureV(1.0);

	m_plgTexture = nullptr;
}

lgTriangle::lgTriangle(const lgTriangle& tlgTriangle)
{
	m_lgPoints[0] = tlgTriangle[0];
	m_lgPoints[1] = tlgTriangle[1];
	m_lgPoints[2] = tlgTriangle[2];

	lgSetFaceColor(tlgTriangle.lgGetFaceColor());

	m_lgPoints[0].lgSetNormal(tlgTriangle[0].lgGetNormal());
	m_lgPoints[1].lgSetNormal(tlgTriangle[1].lgGetNormal());
	m_lgPoints[2].lgSetNormal(tlgTriangle[2].lgGetNormal());

	m_plgTexture = tlgTriangle.lgGetTexture();
}

lgTriangle::~lgTriangle()
{
}

lgPoint& lgTriangle::operator [](unsigned int index)
{
	return m_lgPoints[index];
}

const lgPoint& lgTriangle::operator [](unsigned int index) const
{
	return m_lgPoints[index];
}

bool operator ==(const lgTriangle& tlgTriangle1, const lgTriangle& tlgTriangle2)
{
	if (tlgTriangle2[0] != tlgTriangle1[0]
		|| tlgTriangle2[1] != tlgTriangle1[1]
		|| tlgTriangle2[2] != tlgTriangle1[2])
	{
		return false;
	}
	return true;
}

const lgTriangle lgTriangle::operator =(const lgTriangle& tlgTriangle)
{
	m_lgPoints[0] = tlgTriangle[0];
	m_lgPoints[1] = tlgTriangle[1];
	m_lgPoints[2] = tlgTriangle[2];

	lgSetFaceColor(tlgTriangle.lgGetFaceColor());
	lgSetNormalVector(tlgTriangle[0], tlgTriangle[1], tlgTriangle[2]);
	lgSetTexture(tlgTriangle.lgGetTexture());
	return *this;
}

const lgPoint lgTriangle::lgGetBarycentCoord(const lgPoint& tlgPoint)
{
	lgVector normal = lgGetNormal();
	lgDirect n = normal.lgGetDirectVector();
	lgPoint b;
	double u1, u2, u3, u4,
		v1, v2, v3, v4;
	double nx = n.lgGetX(), ny = n.lgGetY(), nz = n.lgGetZ();
	double x0 = m_lgPoints[0].lgGetX(), y0 = m_lgPoints[0].lgGetY(), z0 = m_lgPoints[0].lgGetZ(),
		x1 = m_lgPoints[1].lgGetX(), y1 = m_lgPoints[1].lgGetY(), z1 = m_lgPoints[1].lgGetZ(),
		x2 = m_lgPoints[2].lgGetX(), y2 = m_lgPoints[2].lgGetY(), z2 = m_lgPoints[2].lgGetZ(),
		xp = tlgPoint.lgGetX(), yp = tlgPoint.lgGetY(), zp = tlgPoint.lgGetZ();
	if (fabs(nx) >= fabs(ny) && fabs(nx) >= fabs(nz))
	{
		u1 = y0 - y2;
		u2 = y1 - y2;
		u3 = yp - y0;
		u4 = yp - y2;
		v1 = z0 - z2;
		v2 = z1 - z2;
		v3 = zp - z0;
		v4 = zp - z2;
	}
	else if (fabs(ny) >= fabs(nz))
	{
		u1 = z0 - z2;
		u2 = z1 - z2;
		u3 = zp - z0;
		u4 = zp - z2;
		v1 = x0 - x2;
		v2 = x1 - x2;
		v3 = xp - x0;
		v4 = xp - x2;
	}
	else
	{
		u1 = x0 - x2;
		u2 = x1 - x2;
		u3 = xp - x0;
		u4 = xp - x2;
		v1 = y0 - y2;
		v2 = y1 - y2;
		v3 = yp - y0;
		v4 = yp - y2;
	}
	double denom = v1 * u2 - v2 * u1;
	if (denom == 0.0f)
	{
		//?
	}
	double oneOverDenom = 1.0f / denom;
	b.lgSetX((v4 * u2 - v2 * u4) * oneOverDenom);
	b.lgSetY((v1 * u3 - v3 * u1) * oneOverDenom);
	b.lgSetZ(1.0F - b.lgGetX() - b.lgGetY());
	return b;
}

const lgPoint lgTriangle::lgGetBarycentPoint()
{
	double x1, y1, z1,
		x2, y2, z2,
		x3, y3, z3;
	lgPoint tlgPoint;

	x1 = m_lgPoints[0].lgGetX();
	y1 = m_lgPoints[0].lgGetY();
	z1 = m_lgPoints[0].lgGetZ();

	x2 = m_lgPoints[1].lgGetX();
	y2 = m_lgPoints[1].lgGetY();
	z2 = m_lgPoints[1].lgGetZ();

	x3 = m_lgPoints[2].lgGetX();
	y3 = m_lgPoints[2].lgGetY();
	z3 = m_lgPoints[2].lgGetZ();

	tlgPoint.lgSetX((x1 + x2 + x3) / 3);
	tlgPoint.lgSetY((y1 + y2 + y3) / 3);
	tlgPoint.lgSetZ((z1 + z2 + z3) / 3);
	return tlgPoint;
}

const lgPoint lgTriangle::lgGetInnerCentrePoint()
{
	double x1, y1, z1,
		x2, y2, z2,
		x3, y3, z3;
	lgPoint tlgPoint;

	x1 = m_lgPoints[0].lgGetX();
	y1 = m_lgPoints[0].lgGetY();
	z1 = m_lgPoints[0].lgGetZ();

	x2 = m_lgPoints[1].lgGetX();
	y2 = m_lgPoints[1].lgGetY();
	z2 = m_lgPoints[1].lgGetZ();

	x3 = m_lgPoints[2].lgGetX();
	y3 = m_lgPoints[2].lgGetY();
	z3 = m_lgPoints[2].lgGetZ();

	double l1 = m_lgPoints[2].lgGetDisPtToPt(m_lgPoints[1]),
		l2 = m_lgPoints[0].lgGetDisPtToPt(m_lgPoints[2]),
		l3 = m_lgPoints[1].lgGetDisPtToPt(m_lgPoints[0]),
		p = l1 + l2 + l3;

	tlgPoint.lgSetX((x1 + x2 + x3) * l1 / p);
	tlgPoint.lgSetY((y1 + y2 + y3) * l2 / p);
	tlgPoint.lgSetZ((z1 + z2 + z3) * l3 / p);

	return tlgPoint;
}

const lgPoint lgTriangle::lgGetCircumCenterPoint()
{
	lgPoint tlgPoint;

	return tlgPoint;
}

const lgTexture* lgTriangle::lgGetTexture() const
{
	return m_plgTexture;
}

void lgTriangle::lgSetTexture(const lgTexture* plgTexture)
{
	m_plgTexture = plgTexture;
}

double lgTriangle::lgGetTriangleArea()
{
	lgPoint p1 = m_lgPoints[0],
		p2 = m_lgPoints[1],
		p3 = m_lgPoints[2];
	lgVector v1(p1, p2), v2(p1, p3), v3 = v1 * v2;
	return v3.lgGetAbsoluteValue() / 2.0;
}

void lgTriangle::lgRotate(double tAngle, const lgVector& tlgVector)
{
	lgTriangle tlgTriangle = *this;;
	m_lgControl.lgRotate(tAngle, tlgVector, *this, tlgTriangle);
	*this = tlgTriangle;

	//the face must rotate with triangle
	lgRotateFace(tAngle, tlgVector);
}

void lgTriangle::lgRotate(const lgMatrix& tlgMatrix)
{
	lgTriangle tlgTriangle = *this;;
	m_lgControl.lgRotate(tlgMatrix, *this, tlgTriangle);
	*this = tlgTriangle;
	
	//the face must rotate with triangle
	lgRotateFace(tlgMatrix);
}

void lgTriangle::lgMove(const lgVector& tlgVector)
{
	lgTriangle tlgTriangle = *this;;
	m_lgControl.lgMove(tlgVector, *this, tlgTriangle);
	*this = tlgTriangle;
	lgMoveFace(tlgVector);
}

void lgTriangle::lgMove(const lgMatrix& tlgMatrix)
{
	lgTriangle tlgTriangle = *this;;
	m_lgControl.lgMove(tlgMatrix, *this, tlgTriangle);
	*this = tlgTriangle;
	lgMoveFace(tlgMatrix);
}

void lgTriangle::lgZoom(const lgVector& tlgVector)
{
	lgTriangle tlgTriangle = *this;;
	m_lgControl.lgZoom(tlgVector, *this, tlgTriangle);
	*this = tlgTriangle;
}

void lgTriangle::lgZoom(const lgMatrix& tlgMatrix)
{
	lgTriangle tlgTriangle = *this;;
	m_lgControl.lgZoom(tlgMatrix, *this, tlgTriangle);
	*this = tlgTriangle;
}

void lgTriangle::lgTransfer(const lgMatrix& tlgMatrix)
{
	lgTriangle tlgTriangle = *this;
	m_lgControl.lgTransfer(tlgMatrix, *this, tlgTriangle);
	*this = tlgTriangle;
}

void lgTriangle::lgDraw(void* dc, const lgPoint& tlgWorldPoint, const lgCamera& tlgCamera)
{
	lgPoint tlgPoints[3];
	lgPOINT tPoint[3];
	tlgPoints[0] = m_lgPoints[0];
	tlgPoints[1] = m_lgPoints[1];
	tlgPoints[2] = m_lgPoints[2];
	tlgPoints[0].lgLocalToWindow(tlgWorldPoint, tlgCamera);
	tlgPoints[1].lgLocalToWindow(tlgWorldPoint, tlgCamera);
	tlgPoints[2].lgLocalToWindow(tlgWorldPoint, tlgCamera);

	tPoint[0].x = (int)tlgPoints[0].lgGetX();
	tPoint[0].y = (int)tlgPoints[0].lgGetY();
	tPoint[1].x = (int)tlgPoints[1].lgGetX();
	tPoint[1].y = (int)tlgPoints[1].lgGetY();
	tPoint[2].x = (int)tlgPoints[2].lgGetX();
	tPoint[2].y = (int)tlgPoints[2].lgGetY();
	m_lgDisplay.lgDawTriangle(dc, tPoint[0], tPoint[1], tPoint[2]);
}