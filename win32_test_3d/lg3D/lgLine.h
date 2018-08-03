#ifndef _FILE_LGLINE_H
#define _FILE_LGLINE_H

#include "lgPoint.h"

#ifndef _LGDIRECT_CLASS
#define _LGDIRECT_CLASS
typedef lgPoint lgDirect;
#endif

class lgLine
{
protected:
	lgPoint m_lgOrgPoint;
	lgPoint m_lgDesPoint;
	double m_lgTMin;
	double m_lgTMax;
	lgControl m_lgControl;
public:
	lgLine();
	lgLine(const lgPoint&, const lgPoint&, double, double);
	lgLine(const lgLine&);

	virtual int lgIsParallel(const lgLine&);
	virtual bool lgIsIntersected(const lgLine&);
	virtual bool lgIsParallel(const lgFace&);
	virtual bool lgIsVertical(const lgLine&);
	virtual bool lgIsVertical(const lgFace&);

	virtual void lgSetOrgPoint(const lgPoint&);
	virtual void lgSetDesPoint(const lgPoint&);
	virtual const lgPoint lgGetOrgPoint() const;
	virtual const lgPoint lgGetDesPoint() const;
	virtual const lgDirect lgGetDirectVector() const;

	virtual bool lgGetIntersectedPoint(const lgLine&, lgPoint&);
	virtual bool lgGetIntersectedPoint(const lgFace&, lgPoint&);

	virtual bool operator ==(const lgLine&);
	virtual lgLine& operator =(const lgLine&);
};
#endif 