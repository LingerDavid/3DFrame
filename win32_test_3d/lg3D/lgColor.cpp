#include "lgColor.h"

lgColor::lgColor()
{
	m_lgR = 0.0;
	m_lgG = 0.0;
	m_lgB = 0.0;
}

lgColor::lgColor(double r, double g, double b)
{
	m_lgR = r;
	m_lgG = g;
	m_lgB = b;
}

lgColor::lgColor(const lgColor& tlgColor)
{
	tlgColor.lgGetRGB(m_lgR, m_lgG, m_lgB);
}

lgColor::~lgColor()
{}

double lgColor::lgGetRed() const
{
	return m_lgR;
}

double lgColor::lgGetGreen() const
{
	return m_lgG;
}

double lgColor::lgGetBlue() const
{
	return m_lgB;
}

void lgColor::lgGetRGB(double& r, double& g, double& b) const
{
	r = lgGetRed();
	g = lgGetGreen();
	b = lgGetBlue();
}

void lgColor::lgSetRed(double red)
{
	m_lgR = red > 250.0 ? 250.0 : red;
}

void lgColor::lgSetGreen(double green)
{
	m_lgG = green > 250.0 ? 250.0 : green;
}

void lgColor::lgSetBlue(double blue)
{
	m_lgB = blue > 250.0 ? 250.0 : blue;
}

void lgColor::lgSetRGB(double r, double g, double b)
{
	if (r < 0.0)
	{
		r = 0.0;
	}
	if (r > 255.0)
	{
		r = 255.0;
	}
	if (g < 0.0)
	{
		g = 0.0;
	}
	if (g > 255.0)
	{
		g = 255.0;
	}
	if (b < 0.0)
	{
		b = 0.0;
	}
	if (b > 255.0)
	{
		b = 255.0;
	}
	lgSetRed(r);
	lgSetGreen(g);
	lgSetBlue(b);
}

const lgColor& lgColor::operator =(const lgColor& tlgRGB)
{
	m_lgR = tlgRGB.lgGetRed();
	m_lgG = tlgRGB.lgGetGreen();
	m_lgB = tlgRGB.lgGetBlue();
	return *this;
}

const lgColor lgColor::operator *(const lgColor& tlgRGB)
{
	lgColor tRGB;
	tRGB.lgSetRed(m_lgR * tlgRGB.lgGetRed());
	tRGB.lgSetGreen(m_lgG * tlgRGB.lgGetGreen());
	tRGB.lgSetBlue(m_lgB * tlgRGB.lgGetBlue());
	return tRGB;
}

const lgColor operator +(const lgColor& tlgRGB1, const lgColor& tlgRGB2)
{
	lgColor tRGB;
	tRGB.lgSetRed(tlgRGB2.lgGetRed() + tlgRGB1.lgGetRed());
	tRGB.lgSetGreen(tlgRGB2.lgGetGreen() + tlgRGB1.lgGetGreen());
	tRGB.lgSetBlue(tlgRGB2.lgGetBlue() + tlgRGB1.lgGetBlue());
	return tRGB;
}

const lgColor operator *(const lgColor& tlgRGB, double i)
{
	lgColor tRGB;
	tRGB.lgSetRed(tlgRGB.lgGetRed() * i);
	tRGB.lgSetGreen(tlgRGB.lgGetGreen() * i);
	tRGB.lgSetBlue(tlgRGB.lgGetBlue() * i);
	return tRGB;
}

const lgColor operator /(const lgColor& tlgRGB, double i)
{
	lgColor tRGB;
	tRGB.lgSetRed(tlgRGB.lgGetRed() / i);
	tRGB.lgSetGreen(tlgRGB.lgGetGreen() / i);
	tRGB.lgSetBlue(tlgRGB.lgGetBlue() / i);
	return tRGB;;
}

const lgColor operator *(const lgColor& tlgRGB, const lgColor& lgrRGB)
{
	lgColor tRGB;
	tRGB.lgSetRed(tlgRGB.lgGetRed() * lgrRGB.lgGetRed());
	tRGB.lgSetGreen(tlgRGB.lgGetGreen() * lgrRGB.lgGetGreen());
	tRGB.lgSetBlue(tlgRGB.lgGetBlue() * lgrRGB.lgGetBlue());
	return tRGB;
}

const lgColor operator *(double i, const lgColor& tlgRGB)
{
	lgColor tRGB;
	tRGB.lgSetRed(tlgRGB.lgGetRed() * i);
	tRGB.lgSetGreen(tlgRGB.lgGetGreen() * i);
	tRGB.lgSetBlue(tlgRGB.lgGetBlue() * i);
	return tRGB;
}
