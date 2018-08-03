#ifndef _FILE_LG_COLOR_H
#define _FILE_LG_COLOR_H

class lgColor
{
private:
	double m_lgR;
	double m_lgG;
	double m_lgB;
public:
	lgColor();
	lgColor(double, double, double);
	lgColor(const lgColor&);
	~lgColor();
	virtual double lgGetRed() const;
	virtual double lgGetGreen() const;
	virtual double lgGetBlue() const;
	virtual void lgGetRGB(double&, double&, double&) const;
	virtual void lgSetRed(double);
	virtual void lgSetGreen(double);
	virtual void lgSetBlue(double);
	virtual void lgSetRGB(double, double, double);
	virtual const lgColor operator *(const lgColor&);
	virtual const lgColor& operator =(const lgColor&);
	friend const lgColor operator *(const lgColor&, const lgColor&);
	friend const lgColor operator *(const lgColor&, double);
	friend const lgColor operator /(const lgColor&, double);
	friend const lgColor operator *(double, const lgColor&);
	friend const lgColor operator +(const lgColor&, const lgColor&);
};

#endif