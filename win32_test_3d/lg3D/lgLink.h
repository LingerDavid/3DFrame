#ifndef _FILE_LGLINK_H
#define _FILE_LGLINK_H

#include "lgTriangle.h"

template<typename T>
class lgLinkPoint
{
public:
	lgLinkPoint<T>* m_PrelgLink;
	lgLinkPoint<T>* m_NextlgLink;
	T m_lgData;

	lgLinkPoint();
};

template<typename T>
class lgLink
{
private:
	lgLinkPoint<T>* m_lgLinkHead;
	unsigned int m_lgCounts;

	void lgInsert(lgLinkPoint<T>&);
public:
	lgLink();
	lgLink(const lgLink<T>&);
	~lgLink();
	const lgLinkPoint<T>& lgSearch(const T&);
	void lgInsert(const T&);
	lgLinkPoint<T> lgDelete(const lgLinkPoint<T>);
	const unsigned int lgGetLinkCount();
	void lgDeleteAll();
	lgLinkPoint<T>* lgGetLinkHead() const;

	lgLinkPoint<T>& operator [](unsigned int);
	lgLink<T> operator =(const lgLink<T>&);
};
#endif