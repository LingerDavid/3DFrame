#ifndef _FILE_LGPLURAL_H
#define _FILE_LGPLURAL_H
class lgPlural
{
private:
	double m_lgR;
	double m_lgV;
public:
	lgPlural();
	lgPlural(double, double);
	lgPlural(const lgPlural&);

	virtual const lgPlural operator +(const lgPlural&);
	virtual const lgPlural operator -(const lgPlural&);
	virtual const lgPlural operator *(const lgPlural&);
	virtual const lgPlural operator /(const lgPlural&);
	virtual const lgPlural operator +(double, const lgPlural&);
	virtual const lgPlural operator +(double);
	virtual const lgPlural operator -(double,const lgPlural&);
	virtual const lgPlural operator -(double);
	virtual bool lgPlural operator ==(const lgPlural&);
	virtual const lgPlural operator =(const lgPlural&);
}
#endif