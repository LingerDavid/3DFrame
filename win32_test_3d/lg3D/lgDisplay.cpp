#include <math.h>
#include <windows.h>

#include "lgLink.h"
#include "lgLink.cpp"
#include "lgObject.h"
#include "lgCamera.h"
#include "lgMatrix.h"
#include "lgTexture.h"
#include "lgDisplay.h"

lgDisplay::lgDisplay()
{
}

void lgDisplay::lgDrawWorldAxises(void* dc, const lgCamera& tlgCamera)
{
	lgVector lgXVector(0.0, 0.0, 1.0, 1.0, .0, 1.0),
		lgYVector(0.0, 0.0, 0.0, 0.0, 1.0, 1.0), 
		lgZVector(0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	lgPoint tlgWorldPoint(0.0, 0.0, 0.0);
	//lgDrawLine(dc, tlgCamera, lgXVector, lgPoint(0, 0, 0));
	//lgDrawLine(dc, tlgCamera, lgYVector);
	//lgDrawLine(dc, tlgCamera, lgZVector);
}

void lgDisplay::lgDrawPoint(void* dc, int x, int y)
{
	COLORREF clr = GetPixel((HDC)dc, x, y);
	int r = clr & 0x0000FF,
		g = (clr >> 8) & 0x0000FF,
		b = (clr >> 16) & 0x0000FF;
	double alpha = 0.5;
	SetPixel((HDC)dc, x, y, RGB((int)(m_lgColor.lgGetRed() * alpha + r * (1 - alpha)),
		(int)(m_lgColor.lgGetGreen() * alpha + g * (1 - alpha)), 
		(int)(m_lgColor.lgGetBlue() * alpha + b * (1 - alpha))));
}

void lgDisplay::lgDrawPoint(void* dc, const lgPOINT& tlgPOINT)
{
	lgDrawPoint(dc, tlgPOINT.x, tlgPOINT.y);
}

void lgDisplay::lgDrawPoint(void* dc, int x, int y, int r, int g, int b)
{
	COLORREF clr = GetPixel((HDC)dc, x, y);
	int tr = clr & 0x0000FF,
		tg = (clr >> 8) & 0x0000FF,
		tb = (clr >> 16) & 0x0000FF;
	double alpha = 0.0;
	SetPixel((HDC)dc, x, y, RGB((int)(tr * alpha + r * (1 - alpha)),
		(int)(tg * alpha + g * (1 - alpha)),
		(int)(tb * alpha + b * (1 - alpha))));
}

int lgDisplay::lgSign(int x)
{
	if (x > 0)
	{
		return 1;
	}
	else if (x == 0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
};

void lgDisplay::lgDrawLine(void* dc, const lgPOINT& tPoint1, const lgPOINT& tPoint2)
{
	int x = tPoint1.x,
		y = tPoint1.y,
		dx = abs(tPoint2.x - x),
		dy = abs(tPoint2.y - y),
		s1 = lgSign(tPoint2.x - tPoint1.x),
		s2 = lgSign(tPoint2.y - tPoint1.y);
	int interchange = 0, i = 0;
	if (dy > dx)
	{
		int temp = dx;
		dx = dy;
		dy = temp;
		interchange = 1;
	}
	else
	{
		interchange = 0;
	}
	double e = 2 * dy - dx;
	for (i = 1; i <= dx; i++)
	{
		lgDrawPoint(dc, x, y);
		while (e > 0)
		{
			if (interchange == 1)
			{
				x = x + s1;
			}
			else
			{
				y = y + s2;
			}
			e = e - 2 * dx;
		}
		if (interchange == 1)
		{
			y = y + s2;
		}
		else
		{
			x = x + s1;
		}
		e = e + 2 * dy;
	}
}

void lgDisplay::lgDrawLine(void* dc, int x1, int y1, int x2, int y2, int r, int g, int b)
{
	int x = x1,
		y = y1,
		dx = abs(x2 - x),
		dy = abs(y2 - y),
		s1 = lgSign(x2 - x1),
		s2 = lgSign(y2 - y1);
	int interchange = 0, i = 0;
	if (dy > dx)
	{
		int temp = dx;
		dx = dy;
		dy = temp;
		interchange = 1;
	}
	else
	{
		interchange = 0;
	}
	double e = 2 * dy - dx;
	for (i = 1; i <= dx; i++)
	{
		lgDrawPoint(dc, x, y, r, g, b);
		while (e > 0)
		{
			if (interchange == 1)
			{
				x = x + s1;
			}
			else
			{
				y = y + s2;
			}
			e = e - 2 * dx;
		}
		if (interchange == 1)
		{
			y = y + s2;
		}
		else
		{
			x = x + s1;
		}
		e = e + 2 * dy;
	}
}

void lgDisplay::lgDrawLine(void* dc, int x1, int y1, int x2, int y2)
{
	lgPOINT p1, p2;
	p1.x = x1;
	p1.y = y1;
	p2.x = x2;
	p2.y = y2;
	lgDrawLine(dc, p1, p2);
}

void lgDisplay::lgDawTriangle(void* dc, const lgPOINT& tPoint1,
	const lgPOINT& tPoint2, const lgPOINT& tPoint3)
{
	lgDrawLine(dc, tPoint1, tPoint2);
	lgDrawLine(dc, tPoint2, tPoint3);
	lgDrawLine(dc, tPoint3, tPoint1);
}

void lgDisplay::lgDrawPoint(void* dc, const lgCamera& tlgCamera, const lgPoint& tlgPoint, const lgPoint& tlgWorldPoint = lgPoint(0, 0, 0))
{
	lgPOINT lgpt;
	lgMatrix tlgMatrix;
	lgMatrix::lgMakeLocalToWindowMatrix(tlgPoint, tlgCamera, tlgMatrix);
	lgPoint tlgPt = tlgPoint;
	tlgPt.lgLocalToWindow(tlgMatrix);
	lgpt.x = (int)tlgPt.lgGetX();
	lgpt.y = (int)tlgPt.lgGetY();
	lgDrawPoint(dc, lgpt);
}

void lgDisplay::lgDrawLine(void* dc, const lgCamera& tlgCamera, const lgVector& tlgVector, const lgPoint& tlgWorldPoint = lgPoint(0, 0, 0))
{
	if (tlgVector.lgGetAbsoluteValue() < 10E-10)
	{
		return;
	}
	lgPoint pt1 = tlgVector.lgGetOrgPoint(),
		pt2 = tlgVector.lgGetDesPoint();
	lgPOINT p1, p2;
	lgMatrix tlgMatrix;
	lgMatrix::lgMakeLocalToWindowMatrix(tlgWorldPoint, tlgCamera, tlgMatrix);
	pt1.lgLocalToWindow(tlgMatrix);
	pt2.lgLocalToWindow(tlgMatrix);
	p1.x = (int)pt1.lgGetX();
	p1.y = (int)pt1.lgGetY();
	p2.x = (int)pt2.lgGetX();
	p2.y = (int)pt2.lgGetY();
	lgDrawLine(dc, p1, p2);
}

void lgDisplay::lgDrawObject(void* dc, const lgCamera& tlgCamera, lgObject& tlgObject)
{
	lgLink<lgTriangle> link = tlgObject.lgGetFaceLink();
	lgLinkPoint<lgTriangle>* x = link.lgGetLinkHead();
	lgPoint tlgWorldPoint = tlgObject.lgGetWorldPoint();
	lgPoint tlgPoints[3];
	lgPOINT tlgPOINT[3];
	lgMatrix tlgMatrix;
	lgMatrix::lgMakeLocalToWindowMatrix(tlgWorldPoint, tlgCamera, tlgMatrix);
	while (x)
	{
		tlgPoints[0] = x->m_lgData[0];
		tlgPoints[1] = x->m_lgData[1];
		tlgPoints[2] = x->m_lgData[2];

		tlgPoints[0].lgLocalToWindow(tlgMatrix);
		tlgPoints[1].lgLocalToWindow(tlgMatrix);
		tlgPoints[2].lgLocalToWindow(tlgMatrix);

		tlgPOINT[0].x = (int)tlgPoints[0].lgGetX();
		tlgPOINT[0].y = (int)tlgPoints[0].lgGetY();
		tlgPOINT[1].x = (int)tlgPoints[1].lgGetX();
		tlgPOINT[1].y = (int)tlgPoints[1].lgGetY();
		tlgPOINT[2].x = (int)tlgPoints[2].lgGetX();
		tlgPOINT[2].y = (int)tlgPoints[2].lgGetY();

		//lgFillTriangle(dc, tlgPOINT[0], tlgPOINT[1], tlgPOINT[2]);
		lgDawTriangle(dc, tlgPOINT[0], tlgPOINT[1], tlgPOINT[2]);
		x = x->m_NextlgLink;
	}
}

void lgDisplay::lgDrawObject(void* dc, const lgObject& tlgObject, int type, int index)
{
	lgLinkPoint<lgTriangle>* x = tlgObject.lgGetRenderList().lgGetLinkHead();
	lgPOINT tlgPOINT[3];
	lgPoint tlgPoints[3];
	lgColor color = m_lgColor;
	const lgTexture* tlgTexture = nullptr;
	int row = 0,
		column = 0,
		bit = 0;
	unsigned char* buffer = nullptr;
	while (x)
	{
		tlgPoints[0] = x->m_lgData[0];
		tlgPoints[1] = x->m_lgData[1];
		tlgPoints[2] = x->m_lgData[2];

		tlgPOINT[0].x = (int)tlgPoints[0].lgGetX();
		tlgPOINT[0].y = (int)tlgPoints[0].lgGetY();
		tlgPOINT[1].x = (int)tlgPoints[1].lgGetX();
		tlgPOINT[1].y = (int)tlgPoints[1].lgGetY();
		tlgPOINT[2].x = (int)tlgPoints[2].lgGetX();
		tlgPOINT[2].y = (int)tlgPoints[2].lgGetY();

		m_lgColor = x->m_lgData.lgGetFaceColor();
		//lgDawTriangle(dc, tlgPOINT[0], tlgPOINT[1], tlgPOINT[2]);

		//lgFillTriangle(dc, tlgPOINT[0], tlgPOINT[1], tlgPOINT[2]);
		lgFillTriangleByGouraud(dc, tlgPOINT[0], tlgPoints[0].lgGetPointColor(),
			tlgPOINT[1], tlgPoints[1].lgGetPointColor(),
			tlgPOINT[2], tlgPoints[2].lgGetPointColor());
		//tlgTexture = x->m_lgData.lgGetTexture();
		//if (tlgTexture)
		//{
		//	buffer = tlgTexture->lgGetTextureBuffer(type, index, row, column, bit);
		//	if (buffer)
		//	{
		//		//lgFillTriangleTexture(dc, tlgPOINT[0], tlgPoints[0].lgGetTextureU(), tlgPoints[0].lgGetTextureV(),
		//		//	tlgPOINT[1], tlgPoints[1].lgGetTextureU(), tlgPoints[1].lgGetTextureV(),
		//		//	tlgPOINT[2], tlgPoints[2].lgGetTextureU(), tlgPoints[2].lgGetTextureV(),
		//		//	buffer, row, column, bit);
		//		//lgFillTriangleTextureByGouraud(dc, tlgPOINT[0], tlgPoints[0].lgGetPointColor(), tlgPoints[0].lgGetTextureU(), tlgPoints[0].lgGetTextureV(),
		//		//	tlgPOINT[1], tlgPoints[1].lgGetPointColor(), tlgPoints[1].lgGetTextureU(), tlgPoints[1].lgGetTextureV(),
		//		//	tlgPOINT[2], tlgPoints[2].lgGetPointColor(), tlgPoints[2].lgGetTextureU(), tlgPoints[2].lgGetTextureV(),
		//		//	buffer, row, column, bit);
		//		lgFillTriangleFixedTextureByGouraud(dc, tlgPOINT[0], tlgPoints[0].lgGetZ(),  tlgPoints[0].lgGetPointColor(), tlgPoints[0].lgGetTextureU(), tlgPoints[0].lgGetTextureV(),
		//			tlgPOINT[1], tlgPoints[1].lgGetZ(), tlgPoints[1].lgGetPointColor(), tlgPoints[1].lgGetTextureU(), tlgPoints[1].lgGetTextureV(),
		//			tlgPOINT[2], tlgPoints[2].lgGetZ(), tlgPoints[2].lgGetPointColor(), tlgPoints[2].lgGetTextureU(), tlgPoints[2].lgGetTextureV(),
		//			buffer, row, column, bit);
		//	}
		//}
		//else
		//{
		//	lgDawTriangle(dc, tlgPOINT[0], tlgPOINT[1], tlgPOINT[2]);
		//}

		x = x->m_NextlgLink;
	}
	m_lgColor = color;
}

//asuumpt points have been ordered by y axis
//and ignore the z value of the triangle
void lgDisplay::lgFillTopTriangle(void* dc, double x1, double y1, double x2, double y2, double x3, double y3)
{
	double dxRight = 0.0,
		dxLeft = 0.0,
		xs = 0.0,
		xe = 0.0,
		tempX = 0.0,
		height = 0.0,
		tempY = 0.0,
		ty3 = 0.0;

	if (x2 < x1)
	{
		tempX = x2;
		x2 = x1;
		x1 = tempX;
	}

	height = y3 - y1;

	dxLeft = (x3 - x1) / height;
	dxRight = (x3 - x2) / height;

	xs = x1;
	xe = x2 + 0.5;

	//clip
	//...

	ty3 = y3;

	for (tempY = y1; tempY <= ty3; tempY++)
	{
		lgDrawLine(dc, (int)xs, (int)tempY, (int)xe, (int)tempY);
		xs += dxLeft;
		xe += dxRight;
	}
}

//asuumpt points have been ordered by y axis
//and ignore the z value of the triangle
void lgDisplay::lgFillBottomTriangle(void* dc, double x1, double y1, double x2, double y2, double x3, double y3)
{
	double dxRight = 0.0,
		dxLeft = 0.0,
		xs = 0.0,
		xe = 0.0,
		tempX = 0.0,
		height = 0.0,
		tempY = 0.0,
		ty3 = 0.0;

	if (x3 < x2)
	{
		tempX = x2;
		x2 = x3;
		x3 = tempX;
	}

	height = y3 - y1;

	dxLeft = (x2 - x1) / height;
	dxRight = (x3 - x1) / height;

	xs = x1;
	xe = x1;

	//clip
	//...

	ty3 = y3;

	for (tempY = y1; tempY <= ty3; tempY++)
	{
		lgDrawLine(dc, (int)xs, (int)tempY, (int)xe, (int)tempY);
		xs += dxLeft;
		xe += dxRight;
	}
}

//sort,cut and draw
void lgDisplay::lgFillTriangle(void* dc, const lgPOINT& tpt1, const lgPOINT& tpt2, const lgPOINT& tpt3)
{
	double x1 = tpt1.x, 
		y1 = tpt1.y,
		x2 = tpt2.x, 
		y2 = tpt2.y,
		x3 = tpt3.x, 
		y3 = tpt3.y,
		tempX = 0.0,
		tempY = 0.0,
		newX = 0.0;

	if ((fabs(x2 - x1) < 10E-10
		&& fabs(x2 - x3) < 10E-10)
		|| (fabs(y1 - y2) < 10E-10
		&& fabs(y2 - y3) < 10E-10))
	{
		return;
	}

	//y1<y2<y3
	if (y2 < y1)
	{
		tempX = x2;
		tempY = y2;
		x2 = x1;
		y2 = y1;
		x1 = tempX;
		y1 = tempY;
	}
	if (y3 < y1)
	{
		tempX = x3;
		tempY = y3;
		x3 = x1;
		y3 = y1;
		x1 = tempX;
		y1 = tempY;
	}
	if (y3 < y2)
	{
		tempX = x3;
		tempY = y3;
		x3 = x2;
		y3 = y2;
		x2 = tempX;
		y2 = tempY;
	}

	if (fabs(y2 - y1) < 10E-10)
	{
		//top
		lgFillTopTriangle(dc, x1, y1, x2, y2,  x3, y3);
	}
	else if (fabs(y3 - y2) < 10E-10)
	{
		//bottom
		lgFillBottomTriangle(dc, x1, y1, x2, y2, x3, y3);
	}
	else
	{
		newX = x1 + (y2 - y1) * (x3 - x1) / (y3 - y1);
		lgFillTopTriangle(dc, x2, y2, newX, y2, x3, y3);
		lgFillBottomTriangle(dc, x1, y1, newX, y2, x2, y2);
	}
}

void lgDisplay::lgFillTopTriangleByGouraud(void* dc, double x1, double y1, double r1, double g1, double b1,
	double x2, double y2, double r2, double g2, double b2,
	double x3, double y3, double r3, double g3, double b3)
{
	double dxRight = 0.0,
		dxLeft = 0.0,
		drRight = 0.0,
		drLeft = 0.0,
		dgRight = 0.0,
		dgLeft = 0.0,
		dbRight = 0.0,
		dbLeft = 0.0,
		xs = 0.0,
		xe = 0.0,
		rs = 0.0,
		re = 0.0,
		gs = 0.0,
		ge = 0.0,
		dr = 0.0,
		dg = 0.0,
		db = 0.0,
		bs = 0.0,
		be = 0.0,
		tempX = 0.0,
		tempR = 0.0,
		tempG = 0.0,
		tempB = 0.0,
		height = 0.0,
		tempY = 0.0,
		ty3 = 0.0;

	if (x2 < x1)
	{
		tempX = x2;
		x2 = x1;
		x1 = tempX;

		tempR = r2;
		r2 = r1;
		r1 = tempR;

		tempG = g2;
		g2 = g1;
		g1 = tempG;

		tempB = b2;
		b2 = b1;
		b1 = tempB;
	}

	height = y3 - y1;

	dxLeft = (x3 - x1) / height;
	dxRight = (x3 - x2) / height;
	drLeft = (r3 - r1) / height;
	drRight = (r3 - r2) / height;
	dgLeft = (g3 - g1) / height;
	dgRight = (g3 - g2) / height;
	dbLeft = (b3 - b1) / height;
	dbRight = (b3 - b2) / height;

	xs = x1;
	xe = x2 + 0.5;
	rs = r1;
	re = r2 + 0.5;
	gs = g1;
	ge = g2 + 0.5;
	bs = b1;
	be = b2 + 0.5;

	//clip
	//...

	ty3 = y3;

	for (tempY = y1; tempY <= ty3; tempY++)
	{
		if (fabs(xe - xs) > 10E-7)
		{
			dr = (re - rs) / (xe - xs);
			dg = (ge - gs) / (xe - xs);
			db = (be - bs) / (xe - xs);
		}
		for (tempX = xs, tempR = rs, tempG = gs, tempB = bs; tempX < xe; tempX++, tempR += dr, tempG += dg, tempB += db)
		{
			lgDrawPoint(dc, (int)tempX, (int)tempY, (int)(tempR), (int)(tempG), (int)(tempB));
		}
		xs += dxLeft;
		xe += dxRight;
		rs += drLeft;
		re += drRight;
		gs += dgLeft;
		ge += dgRight;
		bs += dbLeft;
		be += dbRight;
	}
}

void lgDisplay::lgFillBottomTriangleByGouraud(void* dc, double x1, double y1, double r1, double g1, double b1,
	double x2, double y2, double r2, double g2, double b2,
	double x3, double y3, double r3, double g3, double b3)
{
	double dxRight = 0.0,
		dxLeft = 0.0,
		drRight = 0.0,
		drLeft = 0.0,
		dgRight = 0.0,
		dgLeft = 0.0,
		dbRight = 0.0,
		dbLeft = 0.0,
		xs = 0.0,
		xe = 0.0,
		rs = 0.0,
		re = 0.0,
		gs = 0.0,
		ge = 0.0,
		dr = 0.0,
		dg = 0.0,
		db = 0.0,
		bs = 0.0,
		be = 0.0,
		tempX = 0.0,
		tempR = 0.0,
		tempG = 0.0,
		tempB = 0.0,
		height = 0.0,
		tempY = 0.0,
		ty3 = 0.0;

	if (x3 < x2)
	{
		tempX = x2;
		x2 = x3;
		x3 = tempX;

		tempR = r2;
		r2 = r3;
		r3 = tempR;

		tempG = g2;
		g2 = g3;
		g3 = tempG;

		tempB = b2;
		b2 = b3;
		b3 = tempB;
	}

	height = y3 - y1;

	dxLeft = (x2 - x1) / height;
	dxRight = (x3 - x1) / height;
	drLeft = (r2 - r1) / height;
	drRight = (r3 - r1) / height;
	dgLeft = (g2 - g1) / height;
	dgRight = (g3 - g1) / height;
	dbLeft = (b2 - b1) / height;
	dbRight = (b3 - b1) / height;

	xs = x1;
	xe = x1;
	rs = r1;
	re = r1;
	gs = g1;
	ge = g1;
	bs = b1;
	be = b1;

	//clip
	//...

	ty3 = y3;

	for (tempY = y1; tempY <= ty3; tempY++)
	{
		if (fabs(xe - xs) > 10E-7)
		{
			dr = (re - rs) / (xe - xs);
			dg = (ge - gs) / (xe - xs);
			db = (be - bs) / (xe - xs);
		}
		for (tempX = xs, tempR = rs, tempG = gs, tempB = bs; tempX < xe; tempX++, tempR += dr, tempG += dg, tempB += db)
		{
			lgDrawPoint(dc, (int)tempX, (int)tempY, (int)(tempR), (int)(tempG), (int)(tempB));
		}
		xs += dxLeft;
		xe += dxRight;
		rs += drLeft;
		re += drRight;
		gs += dgLeft;
		ge += dgRight;
		bs += dbLeft;
		be += dbRight;
	}
}

void lgDisplay::lgFillTriangleByGouraud(void* dc, const lgPOINT& tpt1, const lgColor& clr1,
	const lgPOINT& tpt2, const lgColor& clr2, const lgPOINT& tpt3, const lgColor& clr3)
{
	double x1 = tpt1.x, 
		y1 = tpt1.y,
		x2 = tpt2.x, 
		y2 = tpt2.y,
		x3 = tpt3.x, 
		y3 = tpt3.y,
		tempX = 0.0,
		tempY = 0.0,
		newX = 0.0;
	lgColor c1 = clr1, 
		c2 = clr2, 
		c3 = clr3, 
		tc, 
		newc;

	if ((fabs(x2 - x1) < 10E-10
		&& fabs(x2 - x3) < 10E-10)
		|| (fabs(y1 - y2) < 10E-10
		&& fabs(y2 - y3) < 10E-10))
	{
		return;
	}

	//y1<y2<y3
	if (y2 < y1)
	{
		tempX = x2;
		tempY = y2;
		x2 = x1;
		y2 = y1;
		x1 = tempX;
		y1 = tempY;
		tc = c2;
		c2 = c1;
		c1 = tc;
	}
	if (y3 < y1)
	{
		tempX = x3;
		tempY = y3;
		x3 = x1;
		y3 = y1;
		x1 = tempX;
		y1 = tempY;
		tc = c3;
		c3 = c1;
		c1 = tc;
	}
	if (y3 < y2)
	{
		tempX = x3;
		tempY = y3;
		x3 = x2;
		y3 = y2;
		x2 = tempX;
		y2 = tempY;
		tc = c3;
		c3 = c2;
		c2 = tc;
	}

	if (fabs(y2 - y1) < 10E-10)
	{
		//top
		lgFillTopTriangleByGouraud(dc, x1, y1, c1.lgGetRed(), c1.lgGetGreen(), c1.lgGetBlue(),
			x2, y2, c2.lgGetRed(), c2.lgGetGreen(), c2.lgGetBlue(),
			x3, y3, c3.lgGetRed(), c3.lgGetGreen(), c3.lgGetBlue());
	}
	else if (fabs(y3 - y2) < 10E-10)
	{
		//bottom
		lgFillBottomTriangleByGouraud(dc, x1, y1, c1.lgGetRed(), c1.lgGetGreen(), c1.lgGetBlue(),
			x2, y2, c2.lgGetRed(), c2.lgGetGreen(), c2.lgGetBlue(),
			x3, y3, c3.lgGetRed(), c3.lgGetGreen(), c3.lgGetBlue());
	}
	else
	{
		newX = x1 + (y2 - y1) * (x3 - x1) / (y3 - y1);
		newc.lgSetRed(c1.lgGetRed() + (y2 - y1) * (c3.lgGetRed() - c1.lgGetRed()) / (y3 - y1));
		newc.lgSetGreen(c1.lgGetGreen() + (y2 - y1) * (c3.lgGetGreen() - c1.lgGetGreen()) / (y3 - y1));
		newc.lgSetBlue(c1.lgGetBlue() + (y2 - y1) * (c3.lgGetBlue() - c1.lgGetBlue()) / (y3 - y1));

		lgFillTopTriangleByGouraud(dc, x2, y2, c2.lgGetRed(), c2.lgGetGreen(), c2.lgGetBlue(),
			newX, y2, newc.lgGetRed(), newc.lgGetGreen(), newc.lgGetBlue(),
			x3, y3, c3.lgGetRed(), c3.lgGetGreen(), c3.lgGetBlue());
		lgFillBottomTriangleByGouraud(dc, x1, y1, c1.lgGetRed(), c1.lgGetGreen(), c1.lgGetBlue(),
			newX, y2, newc.lgGetRed(), newc.lgGetGreen(), newc.lgGetBlue(),
			x2, y2, c2.lgGetRed(), c2.lgGetGreen(), c2.lgGetBlue());
	}
}
/*
*x1-------x2
*  |     |
*	|   |
*	 | |
*	  x3
*/
void lgDisplay::lgFillTopTriangleTexture(void* dc, double x1, double y1, double u1, double v1,
	double x2, double y2, double u2, double v2,
	double x3, double y3, double u3, double v3,
	unsigned char* buffer, int row, int column, int bit)
{
	double dxRight = 0.0,
		dxLeft = 0.0,
		duLeft = 0.0, 
		duRight = 0.0,
		dvLeft = 0.0,
		dvRight = 0.0,
		xs = 0.0,
		xe = 0.0,
		us = 0.0,
		ue = 0.0,
		vs = 0.0,
		ve = 0.0,
		height = 0.0,
		tempX = 0.0,
		tempY = 0.0,
		tempU = 0.0,
		tempV = 0.0,
		ty3 = 0.0,
		du = 0.0,
		dv = 0.0;

	int r = 0,
		g = 0,
		b = 0;

	if (x2 < x1)
	{
		tempX = x2;
		x2 = x1;
		x1 = tempX;

		tempU = u2;
		u2 = u1;
		u1 = tempU;

		tempV = v2;
		v2 = v1;
		v1 = tempV;
	}

	height = y3 - y1;

	dxLeft = (x3 - x1) / height;
	dxRight = (x3 - x2) / height;
	duLeft = (u3 - u1) / height;
	duRight = (u3 - u2) / height;
	dvLeft = (v3 - v1) / height;
	dvRight = (v3 - v2) / height;

	xs = x1;
	xe = x2 + 0.5;
	us = u1;
	ue = u2;
	vs = v1;
	ve = v2;

	//clip
	//...

	ty3 = y3;

	for (tempY = y1; tempY <= ty3; tempY++)
	{
		if (fabs(xe - xs) > 10E-7)
		{
			du = (ue - us) * column / (xe - xs);
			dv = (ve - vs) * row / (xe - xs);
		}
		if (bit == 24)
		{
			for (tempX = xs, tempU = us * column, tempV = vs * row; tempX < xe; tempX++, tempU += du, tempV += dv)
			{
				r = *(buffer + (int)tempV * column * bit / 8 + (int)tempU * bit / 8);
				g = *(buffer + (int)tempV * column * bit / 8 + (int)tempU * bit / 8 + 1);
				b = *(buffer + (int)tempV * column * bit / 8 + (int)tempU * bit / 8 + 2);
				lgDrawPoint(dc, (int)tempX, (int)tempY, r, g, b);
			}
		}
		xs += dxLeft;
		xe += dxRight;
		us += duLeft;
		ue += duRight;
		vs += dvLeft;
		ve += dvRight;
	}
}

/*
*		x1
*	   | |
*	  |   |
*	 |     |
*	|		|
*  x2-------x3
*/
void lgDisplay::lgFillBottomTriangleTexture(void* dc, double x1, double y1, double u1, double v1,
	double x2, double y2, double u2, double v2,
	double x3, double y3, double u3, double v3,
	unsigned char* buffer, int row, int column, int bit)
{
	double dxRight = 0.0,
		dxLeft = 0.0,
		duLeft = 0.0,
		duRight = 0.0,
		dvLeft = 0.0,
		dvRight = 0.0,
		xs = 0.0,
		xe = 0.0,
		us = 0.0,
		ue = 0.0,
		vs = 0.0,
		ve = 0.0,
		height = 0.0,
		tempX = 0.0,
		tempY = 0.0,
		tempU = 0.0,
		tempV = 0.0,
		ty3 = 0.0,
		du = 0.0,
		dv = 0.0;

	int r = 0,
		g = 0,
		b = 0;

	if (x3 < x2)
	{
		tempX = x3;
		x3 = x2;
		x2 = tempX;

		tempU = u3;
		u3 = u2;
		u2 = tempU;

		tempV = v3;
		v3 = v2;
		v2 = tempV;
	}

	height = y3 - y1;

	dxLeft = (x2 - x1) / height;
	dxRight = (x3 - x1) / height;
	duLeft = (u2 - u1) / height;
	duRight = (u3 - u1) / height;
	dvLeft = (v2 - v1) / height;
	dvRight = (v3 - v1) / height;

	xs = x1;
	xe = x1;
	us = u1;
	ue = u1;
	vs = v1;
	ve = v1;

	//clip
	//...

	ty3 = y3;

	for (tempY = y1; tempY <= ty3; tempY++)
	{
		if (fabs(xe - xs) > 10E-7)
		{
			du = (ue - us) * column / (xe - xs);
			dv = (ve - vs) * row / (xe - xs);
		}
		if (bit == 24)
		{
			for (tempX = xs, tempU = us * column, tempV = vs * row; tempX < xe; tempX++, tempU += du, tempV += dv)
			{
				r = *(buffer + (int)tempV * column * bit / 8 + (int)tempU * bit / 8);
				g = *(buffer + (int)tempV * column * bit / 8 + (int)tempU * bit / 8 + 1);
				b = *(buffer + (int)tempV * column * bit / 8 + (int)tempU * bit / 8 + 2);
				lgDrawPoint(dc, (int)tempX, (int)tempY, r, g, b);
			}
		}
		xs += dxLeft;
		xe += dxRight;
		us += duLeft;
		ue += duRight;
		vs += dvLeft;
		ve += dvRight;
	}
}

void lgDisplay::lgFillTriangleTexture(void* dc, const lgPOINT& tpt1, double u1, double v1,
	const lgPOINT& tpt2, double u2, double v2,
	const lgPOINT& tpt3, double u3, double v3,
	unsigned char* buffer, int row, int column, int bit)
{
	double x1 = tpt1.x, 
		y1 = tpt1.y,
		x2 = tpt2.x, 
		y2 = tpt2.y,
		x3 = tpt3.x, 
		y3 = tpt3.y,
		tempX = 0.0,
		tempY = 0.0,
		newX = 0.0,
		tempU = 0.0,
		tempV = 0.0,
		newU = 0.0,
		newV = 0.0;

	if ((fabs(x2 - x1) < 10E-10
		&& fabs(x2 - x3) < 10E-10)
		|| (fabs(y1 - y2) < 10E-10
		&& fabs(y2 - y3) < 10E-10))
	{
		return;
	}

	//y1<y2<y3
	if (y2 < y1)
	{
		tempX = x2;
		tempY = y2;
		x2 = x1;
		y2 = y1;
		x1 = tempX;
		y1 = tempY;

		tempU = u2;
		tempV = v2;
		u2 = u1;
		v2 = v1;
		u1 = tempU;
		v1 = tempV;
	}
	if (y3 < y1)
	{
		tempX = x3;
		tempY = y3;
		x3 = x1;
		y3 = y1;
		x1 = tempX;
		y1 = tempY;

		tempU = u3;
		tempV = v3;
		u3 = u1;
		v3 = v1;
		u1 = tempU;
		v1 = tempV;
	}
	if (y3 < y2)
	{
		tempX = x3;
		tempY = y3;
		x3 = x2;
		y3 = y2;
		x2 = tempX;
		y2 = tempY;

		tempU = u3;
		tempV = v3;
		u3 = u2;
		v3 = v2;
		u2 = tempU;
		v2 = tempV;
	}

	if (fabs(y2 - y1) < 10E-10)
	{
		//top
		lgFillTopTriangleTexture(dc, x1, y1, u1, v1, 
			x2, y2, u2, v2, 
			x3, y3, u3, v3, 
			buffer, row, column, bit);
	}
	else if (fabs(y3 - y2) < 10E-10)
	{
		//bottom
		lgFillBottomTriangleTexture(dc, x1, y1, u1, v1,
			x2, y2, u2, v2,
			x3, y3, u3, v3,
			buffer, row, column, bit);
	}
	else
	{
		newX = x1 + (y2 - y1) * (x3 - x1) / (y3 - y1);

		newU = u1 + (y2 - y1) * (u3 - u1) / (y3 - y1);
		newV = v1 + (y2 - y1) * (v3 - v1) / (y3 - y1);

		lgFillTopTriangleTexture(dc, x2, y2, u2, v2, 
			newX, y2, newU, newV, 
			x3, y3, u3, v3,
			buffer, row, column, bit);
		lgFillBottomTriangleTexture(dc, x1, y1, u1, v1, 
			newX, y2, newU, newV, 
			x2, y2, u2, v2,
			buffer, row, column, bit);
	}
}


void lgDisplay::lgFillTopTriangleTextureByGouraud(void* dc, double x1, double y1, double r1, double g1, double b1, double u1, double v1,
	double x2, double y2, double r2, double g2, double b2, double u2, double v2,
	double x3, double y3, double r3, double g3, double b3, double u3, double v3,
	unsigned char* buffer, int row, int column, int bit)
{
	double dxRight = 0.0,
		dxLeft = 0.0,
		drRight = 0.0,
		drLeft = 0.0,
		dgRight = 0.0,
		dgLeft = 0.0,
		dbRight = 0.0,
		dbLeft = 0.0,
		duLeft = 0.0,
		duRight = 0.0,
		dvLeft = 0.0,
		dvRight = 0.0,
		xs = 0.0,
		xe = 0.0,
		rs = 0.0,
		re = 0.0,
		gs = 0.0,
		ge = 0.0,
		bs = 0.0,
		be = 0.0,
		us = 0.0,
		ue = 0.0,
		vs = 0.0,
		ve = 0.0,
		dr = 0.0,
		dg = 0.0,
		db = 0.0,
		du = 0.0,
		dv = 0.0,
		tempX = 0.0,
		tempR = 0.0,
		tempG = 0.0,
		tempB = 0.0,
		tempU = 0.0,
		tempV = 0.0,
		height = 0.0,
		tempY = 0.0,
		ty3 = 0.0;

	int r = 0,
		g = 0,
		b = 0;
	if (x2 < x1)
	{
		tempX = x2;
		x2 = x1;
		x1 = tempX;

		tempR = r2;
		r2 = r1;
		r1 = tempR;

		tempG = g2;
		g2 = g1;
		g1 = tempG;

		tempB = b2;
		b2 = b1;
		b1 = tempB;

		tempU = u2;
		u2 = u1;
		u1 = tempU;

		tempV = v2;
		v2 = v1;
		v1 = tempV;
	}

	height = y3 - y1;

	dxLeft = (x3 - x1) / height;
	dxRight = (x3 - x2) / height;
	drLeft = (r3 - r1) / height;
	drRight = (r3 - r2) / height;
	dgLeft = (g3 - g1) / height;
	dgRight = (g3 - g2) / height;
	dbLeft = (b3 - b1) / height;
	dbRight = (b3 - b2) / height;
	duLeft = (u3 - u1) / height;
	duRight = (u3 - u2) / height;
	dvLeft = (v3 - v1) / height;
	dvRight = (v3 - v2) / height;

	xs = x1;
	xe = x2 + 0.5;
	rs = r1;
	re = r2 + 0.5;
	gs = g1;
	ge = g2 + 0.5;
	bs = b1;
	be = b2 + 0.5;
	us = u1;
	ue = u2;
	vs = v1;
	ve = v2;

	//clip
	//...

	ty3 = y3;

	for (tempY = y1; tempY <= ty3; tempY++)
	{
		if (fabs(xe - xs) > 10E-7)
		{
			dr = (re - rs) / (xe - xs);
			dg = (ge - gs) / (xe - xs);
			db = (be - bs) / (xe - xs);
			du = (ue - us) * column / (xe - xs);
			dv = (ve - vs) * row / (xe - xs);
		}
		if (bit == 24)
		{
			for (tempX = xs, tempR = rs, tempG = gs, tempB = bs, tempU = us * column, tempV = vs * row; tempX < xe; tempX++, tempR += dr, tempG += dg, tempB += db, tempU += du, tempV += dv)
			{
				r = *(buffer + (int)tempV * column * bit / 8 + (int)tempU * bit / 8);
				g = *(buffer + (int)tempV * column * bit / 8 + (int)tempU * bit / 8 + 1);
				b = *(buffer + (int)tempV * column * bit / 8 + (int)tempU * bit / 8 + 2);
				lgDrawPoint(dc, (int)tempX, (int)tempY, (int)(tempR * r / 256), (int)(tempG * g / 256), (int)(tempB * b / 256));
			}
		}
		xs += dxLeft;
		xe += dxRight;
		rs += drLeft;
		re += drRight;
		gs += dgLeft;
		ge += dgRight;
		bs += dbLeft;
		be += dbRight;
		us += duLeft;
		ue += duRight;
		vs += dvLeft;
		ve += dvRight;
	}
}

void lgDisplay::lgFillBottomTriangleTextureByGouraud(void* dc, double x1, double y1, double r1, double g1, double b1, double u1, double v1,
	double x2, double y2, double r2, double g2, double b2, double u2, double v2,
	double x3, double y3, double r3, double g3, double b3, double u3, double v3,
	unsigned char* buffer, int row, int column, int bit)
{
	double dxRight = 0.0,
		dxLeft = 0.0,
		drRight = 0.0,
		drLeft = 0.0,
		dgRight = 0.0,
		dgLeft = 0.0,
		dbRight = 0.0,
		dbLeft = 0.0,
		duLeft = 0.0,
		duRight = 0.0,
		dvLeft = 0.0,
		dvRight = 0.0,
		xs = 0.0,
		xe = 0.0,
		rs = 0.0,
		re = 0.0,
		gs = 0.0,
		ge = 0.0,
		bs = 0.0,
		be = 0.0,
		us = 0.0,
		ue = 0.0,
		vs = 0.0,
		ve = 0.0,
		dr = 0.0,
		dg = 0.0,
		db = 0.0,
		du = 0.0,
		dv = 0.0,
		tempX = 0.0,
		tempR = 0.0,
		tempG = 0.0,
		tempB = 0.0,
		tempU = 0.0,
		tempV = 0.0,
		height = 0.0,
		tempY = 0.0,
		ty3 = 0.0;

	int r = 0,
		g = 0,
		b = 0;
	if (x3 < x2)
	{
		tempX = x2;
		x2 = x3;
		x3 = tempX;

		tempR = r2;
		r2 = r3;
		r3 = tempR;

		tempG = g2;
		g2 = g3;
		g3 = tempG;

		tempB = b2;
		b2 = b3;
		b3 = tempB;

		tempU = u2;
		u2 = u3;
		u3 = tempU;

		tempV = v2;
		v2 = v3;
		v3 = tempV;
	}

	height = y3 - y1;

	dxLeft = (x2 - x1) / height;
	dxRight = (x3 - x1) / height;
	drLeft = (r2 - r1) / height;
	drRight = (r3 - r1) / height;
	dgLeft = (g2 - g1) / height;
	dgRight = (g3 - g1) / height;
	dbLeft = (b2 - b1) / height;
	dbRight = (b3 - b1) / height;
	duLeft = (u2 - u1) / height;
	duRight = (u3 - u1) / height;
	dvLeft = (v2 - v1) / height;
	dvRight = (v3 - v1) / height;

	xs = x1;
	xe = x1;
	rs = r1;
	re = r1;
	gs = g1;
	ge = g1;
	bs = b1;
	be = b1;
	us = u1;
	ue = u1;
	vs = v1;
	ve = v1;

	//clip
	//...

	ty3 = y3;

	for (tempY = y1; tempY <= ty3; tempY++)
	{
		if (fabs(xe - xs) > 10E-7)
		{
			dr = (re - rs) / (xe - xs);
			dg = (ge - gs) / (xe - xs);
			db = (be - bs) / (xe - xs);
			du = (ue - us) * column / (xe - xs);
			dv = (ve - vs) * row / (xe - xs);
		}
		if (bit == 24)
		{
			for (tempX = xs, tempR = rs, tempG = gs, tempB = bs, tempU = us * column, tempV = vs * row; tempX < xe; tempX++, tempR += dr, tempG += dg, tempB += db, tempU += du, tempV += dv)
			{
				r = *(buffer + (int)tempV * column * bit / 8 + (int)tempU * bit / 8);
				g = *(buffer + (int)tempV * column * bit / 8 + (int)tempU * bit / 8 + 1);
				b = *(buffer + (int)tempV * column * bit / 8 + (int)tempU * bit / 8 + 2);

				lgDrawPoint(dc, (int)tempX, (int)tempY, (int)(tempR * r / 256), (int)(tempG * g / 256), (int)(tempB * b / 256));
			}
		}
		xs += dxLeft;
		xe += dxRight;
		rs += drLeft;
		re += drRight;
		gs += dgLeft;
		ge += dgRight;
		bs += dbLeft;
		be += dbRight;
		us += duLeft;
		ue += duRight;
		vs += dvLeft;
		ve += dvRight;
	}
}

void lgDisplay::lgFillTriangleTextureByGouraud(void* dc, const lgPOINT& tpt1, const lgColor& clr1, double u1, double v1,
	const lgPOINT& tpt2, const lgColor& clr2, double u2, double v2,
	const lgPOINT& tpt3, const lgColor& clr3, double u3, double v3,
	unsigned char* buffer, int row, int column, int bit)
{
	double x1 = tpt1.x,
		y1 = tpt1.y,
		x2 = tpt2.x,
		y2 = tpt2.y,
		x3 = tpt3.x,
		y3 = tpt3.y,
		tempX = 0.0,
		tempY = 0.0,
		tempR = 0.0,
		tempG = 0.0,
		tempB = 0.0,
		tempU = 0.0,
		tempV = 0.0,
		newX = 0.0,
		newU = 0.0,
		newV = 0.0;
	lgColor c1 = clr1,
		c2 = clr2,
		c3 = clr3,
		tc,
		newc;

	if ((fabs(x2 - x1) < 10E-10
		&& fabs(x2 - x3) < 10E-10)
		|| (fabs(y1 - y2) < 10E-10
		&& fabs(y2 - y3) < 10E-10))
	{
		return;
	}

	//y1<y2<y3
	if (y2 < y1)
	{
		tempX = x2;
		tempY = y2;
		x2 = x1;
		y2 = y1;
		x1 = tempX;
		y1 = tempY;
		tc = c2;
		c2 = c1;
		c1 = tc;

		tempU = u2;
		tempV = v2;
		u2 = u1;
		v2 = v1;
		u1 = tempU;
		v1 = tempV;
	}
	if (y3 < y1)
	{
		tempX = x3;
		tempY = y3;
		x3 = x1;
		y3 = y1;
		x1 = tempX;
		y1 = tempY;
		tc = c3;
		c3 = c1;
		c1 = tc;

		tempU = u3;
		tempV = v3;
		u3 = u1;
		v3 = v1;
		u1 = tempU;
		v1 = tempV;
	}
	if (y3 < y2)
	{
		tempX = x3;
		tempY = y3;
		x3 = x2;
		y3 = y2;
		x2 = tempX;
		y2 = tempY;
		tc = c3;
		c3 = c2;
		c2 = tc;

		tempU = u3;
		tempV = v3;
		u3 = u2;
		v3 = v2;
		u2 = tempU;
		v2 = tempV;
	}

	if (fabs(y2 - y1) < 10E-10)
	{
		//top
		lgFillTopTriangleTextureByGouraud(dc, x1, y1, c1.lgGetRed(), c1.lgGetGreen(), c1.lgGetBlue(), u1, v1,
			x2, y2, c2.lgGetRed(), c2.lgGetGreen(), c2.lgGetBlue(), u2, v2,
			x3, y3, c3.lgGetRed(), c3.lgGetGreen(), c3.lgGetBlue(), u3, v3,
			buffer, row, column, bit);
	}	
	else if (fabs(y3 - y2) < 10E-10)
	{
		//bottom
		lgFillBottomTriangleTextureByGouraud(dc, x1, y1, c1.lgGetRed(), c1.lgGetGreen(), c1.lgGetBlue(), u1, v1,
			x2, y2, c2.lgGetRed(), c2.lgGetGreen(), c2.lgGetBlue(), u2, v2,
			x3, y3, c3.lgGetRed(), c3.lgGetGreen(), c3.lgGetBlue(), u3, v3,
			buffer, row, column, bit);
	}
	else
	{
		newX = x1 + (y2 - y1) * (x3 - x1) / (y3 - y1);
		newc.lgSetRed(c1.lgGetRed() + (y2 - y1) * (c3.lgGetRed() - c1.lgGetRed()) / (y3 - y1));
		newc.lgSetGreen(c1.lgGetGreen() + (y2 - y1) * (c3.lgGetGreen() - c1.lgGetGreen()) / (y3 - y1));
		newc.lgSetBlue(c1.lgGetBlue() + (y2 - y1) * (c3.lgGetBlue() - c1.lgGetBlue()) / (y3 - y1));

		newU = u1 + (y2 - y1) * (u3 - u1) / (y3 - y1);
		newV = v1 + (y2 - y1) * (v3 - v1) / (y3 - y1);

		lgFillTopTriangleTextureByGouraud(dc, x2, y2, c2.lgGetRed(), c2.lgGetGreen(), c2.lgGetBlue(), u2, v2,
			newX, y2, newc.lgGetRed(), newc.lgGetGreen(), newc.lgGetBlue(), newU, newV,
			x3, y3, c3.lgGetRed(), c3.lgGetGreen(), c3.lgGetBlue(), u3, v3,
			buffer, row, column, bit);
		lgFillBottomTriangleTextureByGouraud(dc, x1, y1, c1.lgGetRed(), c1.lgGetGreen(), c1.lgGetBlue(),u1, v1,
			newX, y2, newc.lgGetRed(), newc.lgGetGreen(), newc.lgGetBlue(), newU, newV,
			x2, y2, c2.lgGetRed(), c2.lgGetGreen(), c2.lgGetBlue(), u2, v2,
			buffer, row, column, bit);
	}
}

void lgDisplay::lgFillTopTriangleFixedTextureByGouraud(void* dc, double x1, double y1, double z1, double r1, double g1, double b1, double u1, double v1,
	double x2, double y2, double z2, double r2, double g2, double b2, double u2, double v2,
	double x3, double y3, double z3, double r3, double g3, double b3, double u3, double v3,
	unsigned char* buffer, int row, int column, int bit)
{
	double dxRight = 0.0,
		dxLeft = 0.0,
		drRight = 0.0,
		drLeft = 0.0,
		dgRight = 0.0,
		dgLeft = 0.0,
		dbRight = 0.0,
		dbLeft = 0.0,
		duLeft = 0.0,
		duRight = 0.0,
		dvLeft = 0.0,
		dvRight = 0.0,
		dzLeft = 0.0,
		dzRight = 0.0,
		xs = 0.0,
		xe = 0.0,
		rs = 0.0,
		re = 0.0,
		gs = 0.0,
		ge = 0.0,
		bs = 0.0,
		be = 0.0,
		us = 0.0,
		ue = 0.0,
		vs = 0.0,
		ve = 0.0,
		zs = 0.0,
		ze = 0.0,
		dr = 0.0,
		dg = 0.0,
		db = 0.0,
		du = 0.0,
		dv = 0.0,
		dz = 0.0,
		tempX = 0.0,
		tempY = 0.0,
		tempR = 0.0,
		tempG = 0.0,
		tempB = 0.0,
		tempU = 0.0,
		tempV = 0.0,
		tempZ = 0.0,
		height = 0.0,
		ty3 = 0.0;

	int r = 0,
		g = 0,
		b = 0;
	if (x2 < x1)
	{
		tempX = x2;
		x2 = x1;
		x1 = tempX;

		tempR = r2;
		r2 = r1;
		r1 = tempR;

		tempG = g2;
		g2 = g1;
		g1 = tempG;

		tempB = b2;
		b2 = b1;
		b1 = tempB;

		tempU = u2;
		u2 = u1;
		u1 = tempU;

		tempV = v2;
		v2 = v1;
		v1 = tempV;

		tempZ = z2;
		z2 = z1;
		z1 = tempZ;
	}

	height = y3 - y1;

	dxLeft = (x3 - x1) / height;
	dxRight = (x3 - x2) / height;
	drLeft = (r3 - r1) / height;
	drRight = (r3 - r2) / height;
	dgLeft = (g3 - g1) / height;
	dgRight = (g3 - g2) / height;
	dbLeft = (b3 - b1) / height;
	dbRight = (b3 - b2) / height;
	duLeft = (u3 / z3 - u1 / z1) / height;
	duRight = (u3 / z3 - u2 / z2) / height;
	dvLeft = (v3 / z3 - v1 / z1) / height;
	dvRight = (v3 / z3 - v2 / z2) / height;
	dzLeft = (1 / z3 - 1 / z1) / height;
	dzRight = (1 / z3 - 1 / z2) / height;

	xs = x1;
	xe = x2;
	rs = r1;
	re = r2;
	gs = g1;
	ge = g2;
	bs = b1;
	be = b2;
	us = u1 / z1;
	ue = u2 / z2;
	vs = v1 / z1;
	ve = v2 / z2;
	zs = 1 / z1;
	ze = 1 / z2;

	//clip
	//...

	ty3 = y3;

	for (tempY = y1; tempY <= ty3; tempY++)
	{
		if (fabs(xe - xs) > 10E-7)
		{
			dr = (re - rs) / (xe - xs);
			dg = (ge - gs) / (xe - xs);
			db = (be - bs) / (xe - xs);
			du = (ue - us) * column / (xe - xs);
			dv = (ve - vs) * row / (xe - xs);
			dz = (ze - zs) / (xe - xs);


		}
		if (bit == 24)
		{
			for (tempX = xs, tempR = rs, tempG = gs, tempB = bs, tempU = us * column, tempV = vs * row, tempZ = zs; tempX < xe; tempX++, tempR += dr, tempG += dg, tempB += db, tempU += du, tempV += dv, tempZ += dz)
			{
				r = *(buffer + (int)(tempV / tempZ) * column * bit / 8 + (int)(tempU / tempZ) * bit / 8);
				g = *(buffer + (int)(tempV / tempZ) * column * bit / 8 + (int)(tempU / tempZ) * bit / 8 + 1);
				b = *(buffer + (int)(tempV / tempZ) * column * bit / 8 + (int)(tempU / tempZ) * bit / 8 + 2);

				lgDrawPoint(dc, (int)tempX, (int)tempY, (int)(tempR * r / 256), (int)(tempG * g / 256), (int)(tempB * b / 256));
			}
		}
		xs += dxLeft;
		xe += dxRight;
		rs += drLeft;
		re += drRight;
		gs += dgLeft;
		ge += dgRight;
		bs += dbLeft;
		be += dbRight;
		us += duLeft;
		ue += duRight;
		vs += dvLeft;
		ve += dvRight;
		zs += dzLeft;
		ze += dzRight;
	}
}

void lgDisplay::lgFillBottomTriangleFixedTextureByGouraud(void* dc, double x1, double y1, double z1, double r1, double g1, double b1, double u1, double v1,
	double x2, double y2, double z2, double r2, double g2, double b2, double u2, double v2,
	double x3, double y3, double z3, double r3, double g3, double b3, double u3, double v3,
	unsigned char* buffer, int row, int column, int bit)
{
	double dxRight = 0.0,
		dxLeft = 0.0,
		drRight = 0.0,
		drLeft = 0.0,
		dgRight = 0.0,
		dgLeft = 0.0,
		dbRight = 0.0,
		dbLeft = 0.0,
		duLeft = 0.0,
		duRight = 0.0,
		dvLeft = 0.0,
		dvRight = 0.0,
		dzLeft = 0.0,
		dzRight = 0.0,
		xs = 0.0,
		xe = 0.0,
		rs = 0.0,
		re = 0.0,
		gs = 0.0,
		ge = 0.0,
		bs = 0.0,
		be = 0.0,
		us = 0.0,
		ue = 0.0,
		vs = 0.0,
		ve = 0.0,
		zs = 0.0,
		ze = 0.0,
		dr = 0.0,
		dg = 0.0,
		db = 0.0,
		du = 0.0,
		dv = 0.0,
		dz = 0.0,
		tempX = 0.0,
		tempY = 0.0,
		tempR = 0.0,
		tempG = 0.0,
		tempB = 0.0,
		tempU = 0.0,
		tempV = 0.0,
		tempZ = 0.0,
		height = 0.0,
		ty3 = 0.0;

	int r = 0,
		g = 0,
		b = 0;
	if (x3 < x2)
	{
		tempX = x2;
		x2 = x3;
		x3 = tempX;

		tempR = r2;
		r2 = r3;
		r3 = tempR;

		tempG = g2;
		g2 = g3;
		g3 = tempG;

		tempB = b2;
		b2 = b3;
		b3 = tempB;

		tempU = u2;
		u2 = u3;
		u3 = tempU;

		tempV = v2;
		v2 = v3;
		v3 = tempV;

		tempZ = z2;
		z2 = z3;
		z3 = tempZ;
	}

	height = y3 - y1;

	dxLeft = (x2 - x1) / height;
	dxRight = (x3 - x1) / height;
	drLeft = (r2 - r1) / height;
	drRight = (r3 - r1) / height;
	dgLeft = (g2 - g1) / height;
	dgRight = (g3 - g1) / height;
	dbLeft = (b2 - b1) / height;
	dbRight = (b3 - b1) / height;
	duLeft = (u2 / z2 - u1 / z1) / height;
	duRight = (u3 / z3 - u1 / z1) / height;
	dvLeft = (v2 / z2 - v1 / z1) / height;
	dvRight = (v3 / z3 - v1 / z1) / height;
	dzLeft = (1 / z2 - 1 / z1) / height;
	dzRight = (1 / z3 - 1 / z1) / height;

	xs = x1;
	xe = x1;
	rs = r1;
	re = r1;
	gs = g1;
	ge = g1;
	bs = b1;
	be = b1;
	us = u1 / z1;
	ue = u1 / z1;
	vs = v1 / z1;
	ve = v1 / z1;
	zs = 1 / z1;
	ze = 1 / z1;

	//clip
	//...

	ty3 = y3;

	for (tempY = y1; tempY <= ty3; tempY++)
	{
		if (fabs(xe - xs) > 10E-7)
		{
			dr = (re - rs) / (xe - xs);
			dg = (ge - gs) / (xe - xs);
			db = (be - bs) / (xe - xs);
			du = (ue - us) * column / (xe - xs);
			dv = (ve - vs) * row / (xe - xs);
			dz = (ze - zs) / (xe - xs);
		}
		if (bit == 24)
		{
			for (tempX = xs, tempR = rs, tempG = gs, tempB = bs, tempU = us * column, tempV = vs * row, tempZ = zs; tempX < xe; tempX++, tempR += dr, tempG += dg, tempB += db, tempU += du, tempV += dv, tempZ += dz)
			{
				r = *(buffer + (int)(tempV / tempZ) * column * bit / 8 + (int)(tempU / tempZ) * bit / 8);
				g = *(buffer + (int)(tempV / tempZ) * column * bit / 8 + (int)(tempU / tempZ) * bit / 8 + 1);
				b = *(buffer + (int)(tempV / tempZ) * column * bit / 8 + (int)(tempU / tempZ) * bit / 8 + 2);

				lgDrawPoint(dc, (int)tempX, (int)tempY, (int)(tempR * r / 256), (int)(tempG * g / 256), (int)(tempB * b / 256));
			}
		}
		xs += dxLeft;
		xe += dxRight;
		rs += drLeft;
		re += drRight;
		gs += dgLeft;
		ge += dgRight;
		bs += dbLeft;
		be += dbRight;
		us += duLeft;
		ue += duRight;
		vs += dvLeft;
		ve += dvRight;
		zs += dzLeft;
		ze += dzRight;
	}
}

void lgDisplay::lgFillTriangleFixedTextureByGouraud(void* dc, const lgPOINT& tpt1, double z1, const lgColor& clr1, double u1, double v1,
	const lgPOINT& tpt2, double z2, const lgColor& clr2, double u2, double v2,
	const lgPOINT& tpt3, double z3, const lgColor& clr3, double u3, double v3,
	unsigned char* buffer, int row, int column, int bit)
{
	double x1 = tpt1.x,
		y1 = tpt1.y,
		x2 = tpt2.x,
		y2 = tpt2.y,
		x3 = tpt3.x,
		y3 = tpt3.y,
		tempX = 0.0,
		tempY = 0.0,
		tempR = 0.0,
		tempG = 0.0,
		tempB = 0.0,
		tempU = 0.0,
		tempV = 0.0,
		tempZ = 0.0,
		newX = 0.0,
		newU = 0.0,
		newV = 0.0,
		newZ = 0.0;
	lgColor c1 = clr1,
		c2 = clr2,
		c3 = clr3,
		tc,
		newc;

	if ((fabs(x2 - x1) < 10E-10
		&& fabs(x2 - x3) < 10E-10)
		|| (fabs(y1 - y2) < 10E-10
		&& fabs(y2 - y3) < 10E-10))
	{
		return;
	}

	//y1<y2<y3
	if (y2 < y1)
	{
		tempX = x2;
		tempY = y2;
		x2 = x1;
		y2 = y1;
		x1 = tempX;
		y1 = tempY;
		tc = c2;
		c2 = c1;
		c1 = tc;

		tempU = u2;
		tempV = v2;
		u2 = u1;
		v2 = v1;
		u1 = tempU;
		v1 = tempV;

		tempZ = z2;
		z2 = z1;
		z1 = tempZ;
	}
	if (y3 < y1)
	{
		tempX = x3;
		tempY = y3;
		x3 = x1;
		y3 = y1;
		x1 = tempX;
		y1 = tempY;
		tc = c3;
		c3 = c1;
		c1 = tc;

		tempU = u3;
		tempV = v3;
		u3 = u1;
		v3 = v1;
		u1 = tempU;
		v1 = tempV;

		tempZ = z3;
		z3 = z1;
		z1 = tempZ;
	}
	if (y3 < y2)
	{
		tempX = x3;
		tempY = y3;
		x3 = x2;
		y3 = y2;
		x2 = tempX;
		y2 = tempY;
		tc = c3;
		c3 = c2;
		c2 = tc;

		tempU = u3;
		tempV = v3;
		u3 = u2;
		v3 = v2;
		u2 = tempU;
		v2 = tempV;

		tempZ = z3;
		z3 = z2;
		z2 = tempZ;
	}

	if (fabs(y2 - y1) < 10E-10)
	{
		//top
		lgFillTopTriangleFixedTextureByGouraud(dc, x1, y1, z1, c1.lgGetRed(), c1.lgGetGreen(), c1.lgGetBlue(), u1, v1,
			x2, y2, z2, c2.lgGetRed(), c2.lgGetGreen(), c2.lgGetBlue(), u2, v2,
			x3, y3, z3, c3.lgGetRed(), c3.lgGetGreen(), c3.lgGetBlue(), u3, v3,
			buffer, row, column, bit);
	}
	else if (fabs(y3 - y2) < 10E-10)
	{
		//bottom
		lgFillBottomTriangleFixedTextureByGouraud(dc, x1, y1, z1, c1.lgGetRed(), c1.lgGetGreen(), c1.lgGetBlue(), u1, v1,
			x2, y2, z2, c2.lgGetRed(), c2.lgGetGreen(), c2.lgGetBlue(), u2, v2,
			x3, y3, z3, c3.lgGetRed(), c3.lgGetGreen(), c3.lgGetBlue(), u3, v3,
			buffer, row, column, bit);
	}
	else
	{
		newX = x1 + (y2 - y1) * (x3 - x1) / (y3 - y1);
		newc.lgSetRed(c1.lgGetRed() + (y2 - y1) * (c3.lgGetRed() - c1.lgGetRed()) / (y3 - y1));
		newc.lgSetGreen(c1.lgGetGreen() + (y2 - y1) * (c3.lgGetGreen() - c1.lgGetGreen()) / (y3 - y1));
		newc.lgSetBlue(c1.lgGetBlue() + (y2 - y1) * (c3.lgGetBlue() - c1.lgGetBlue()) / (y3 - y1));

		newZ = 1 / z1 + (y2 - y1) * (1 / z3 - 1 / z1) / (y3 - y1);
		newU = (u1 / z1 + (y2 - y1) * (u3 / z3 - u1 / z1) / (y3 - y1)) / newZ;
		newV = (v1 / z1 + (y2 - y1) * (v3 / z3 - v1 / z1) / (y3 - y1)) / newZ;

		lgFillTopTriangleFixedTextureByGouraud(dc, x2, y2, z2, c2.lgGetRed(), c2.lgGetGreen(), c2.lgGetBlue(), u2, v2,
			newX, y2, 1 / newZ, newc.lgGetRed(), newc.lgGetGreen(), newc.lgGetBlue(), newU, newV,
			x3, y3, z3, c3.lgGetRed(), c3.lgGetGreen(), c3.lgGetBlue(), u3, v3,
			buffer, row, column, bit);
		lgFillBottomTriangleFixedTextureByGouraud(dc, x1, y1, z1, c1.lgGetRed(), c1.lgGetGreen(), c1.lgGetBlue(), u1, v1,
			newX, y2, 1 / newZ, newc.lgGetRed(), newc.lgGetGreen(), newc.lgGetBlue(), newU, newV,
			x2, y2, z2, c2.lgGetRed(), c2.lgGetGreen(), c2.lgGetBlue(), u2, v2,
			buffer, row, column, bit);
	}
}
