#include <limits.h>
#include <math.h>
#include "lgTriangle.h"
#include "lgFace.h"
#include "lgLine.h"

lgLine::lgLine()
{
	m_lgOrgPoint.lgSetX(0);
	m_lgOrgPoint.lgSetY(0);
	m_lgOrgPoint.lgSetZ(0);

	m_lgDesPoint.lgSetX(0);
	m_lgDesPoint.lgSetY(0);
	m_lgDesPoint.lgSetZ(0);

	m_lgTMin = INT_MIN;
	m_lgTMax = INT_MAX;
}

lgLine::lgLine(const lgPoint& lgOrgPoint, const lgPoint& tlgDesPoint, 
	double tTMin = INT_MIN, double tTMax = INT_MAX)
{
	m_lgOrgPoint = lgOrgPoint;
	m_lgDesPoint = tlgDesPoint;
	m_lgTMin = tTMin;
	m_lgTMax = tTMax;
}

lgLine::lgLine(const lgLine& tlgLine)
{
	m_lgOrgPoint = tlgLine.lgGetOrgPoint();
	m_lgDesPoint = tlgLine.lgGetDesPoint();
}

int lgLine::lgIsParallel(const lgLine& tlgLine)
{
	lgDirect tlgDirect1 = lgGetDirectVector(), 
		tlgDirect2 = tlgLine.lgGetDirectVector();
	lgPoint tlgPoint1 = m_lgOrgPoint, 
		tlgPoint2 = tlgLine.lgGetOrgPoint();
	double x1 = tlgPoint1.lgGetX(),
		y1 = tlgPoint1.lgGetY(),
		z1 = tlgPoint1.lgGetZ(),
		x2 = tlgPoint2.lgGetX(),
		y2 = tlgPoint2.lgGetY(),
		z2 = tlgPoint2.lgGetZ(), 
		dx1 = tlgDirect1.lgGetX(),
		dy1 = tlgDirect1.lgGetY(),
		dz1 = tlgDirect1.lgGetZ(),
		dx2 = tlgDirect2.lgGetX(),
		dy2 = tlgDirect2.lgGetY(),
		dz2 = tlgDirect2.lgGetZ(),
		kx = (x2 - x1) / dx1, 
		ky = (y2 - y1) / dy1, 
		kz = (z2 - z1) / dz1,
		kdx = dx2 / dx1, 
		kdy = dy2 / dy1, 
		kdz = dz2 / dz1;
	if (abs(kdx - kdy) < 10E-10
		&& abs(kdx - kdz) < 10E-10
		&& abs(kdy - kdz) < 10E-10)
	{
		if (abs(kx - ky) < 10E-10
			&& abs(kx - kz) < 10E-10
			&& abs(ky - kz) < 10E-10)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}

	return 1;
}

bool lgLine::lgIsIntersected(const lgLine& tlgLine)
{
	lgPoint tlgPoint1 = m_lgOrgPoint,
		tlgPoint2 = tlgLine.lgGetOrgPoint();
	lgDirect tlgDirect1 = lgGetDirectVector(),
		tlgDirect2 = lgGetDirectVector();
	
	return true;
}

bool lgLine::lgIsParallel(const lgFace& tlgFace)
{

	return true;
}

bool lgLine::lgIsVertical(const lgLine& tlgLine)
{
	return true;
}

bool lgLine::lgIsVertical(const lgFace& tlgFace)
{
	return true;
}

void lgLine::lgSetOrgPoint(const lgPoint& tlgPoint)
{
	m_lgOrgPoint = tlgPoint;
}

void lgLine::lgSetDesPoint(const lgPoint& tlgPoint)
{
	m_lgDesPoint = tlgPoint;
}

const lgPoint lgLine::lgGetOrgPoint() const
{
	return m_lgOrgPoint;
}

const lgPoint lgLine::lgGetDesPoint() const
{
	return m_lgDesPoint;
}

const lgDirect lgLine::lgGetDirectVector() const
{
	return m_lgDesPoint - m_lgOrgPoint;
}

bool lgLine::lgGetIntersectedPoint(const lgLine& tLine, lgPoint& tlgPoint)
{
	if (!lgIsIntersected(tLine))
	{
		return false;
	}
	return true;
}

bool lgLine::lgGetIntersectedPoint(const lgFace& tlgFace, lgPoint& tlgPoint)
{
	if (lgIsParallel(tlgFace))
	{
		return false;
	}
	double a, b, c, d;
	tlgFace.lgGetStandardFormat(a, b, c, d);
	lgVector p0(lgPoint(0.0, 0.0, 0.0), lgGetOrgPoint()), 
		n = tlgFace.lgGetNormal(), 
		td(lgPoint(0.0, 0.0, 0.0), lgGetDirectVector()), p;
	double t = (d - p0.lgDotMultiply(n)) / td.lgDotMultiply(n);
	p = p0 + td;
	tlgPoint = p.lgGetDesPoint();
	return true;
}

bool lgLine::operator ==(const lgLine& tlgLine)
{
	return true;
}

lgLine& lgLine::operator =(const lgLine& tlgLine)
{
	m_lgOrgPoint = tlgLine.lgGetOrgPoint();
	m_lgDesPoint = tlgLine.lgGetDesPoint();
	return *this;
}