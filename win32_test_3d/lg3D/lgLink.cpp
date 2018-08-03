#include "lgLink.h"

template<typename T>
lgLinkPoint<T>::lgLinkPoint()
{
	m_PrelgLink = nullptr;
	m_NextlgLink = nullptr;
}

template<typename T>
lgLink<T>::lgLink()
{
	m_lgLinkHead = nullptr;
	m_lgCounts = 0;
}

template<typename T>
lgLink<T>::lgLink(const lgLink<T>& tlgLink)
{
	m_lgLinkHead = nullptr;
	lgDeleteAll();
	lgLinkPoint<T>* x = tlgLink.lgGetLinkHead();
	while (x && x->m_NextlgLink)
	{
		x = x->m_NextlgLink;
	}
	while (x)
	{
		lgInsert(x->m_lgData);
		x = x->m_PrelgLink;
	}
}

template<typename T>
lgLink<T>::~lgLink()
{
	lgDeleteAll();
}

template<typename T>
const lgLinkPoint<T>& lgLink<T>::lgSearch(const T& k)
{
	lgLinkPoint<T>* x = m_lgLinkHead;
	while (x != nullptr && x->m_lgData != k)
	{
		x = x->m_NextlgLink;
	}
	return *x;
}

template<typename T>
void lgLink<T>::lgInsert(lgLinkPoint<T>& x)
{
	x.m_NextlgLink = m_lgLinkHead;
	if (m_lgLinkHead != nullptr)
	{
		m_lgLinkHead->m_PrelgLink = &x;
	}
	m_lgLinkHead = &x;
	x.m_PrelgLink = nullptr;
	m_lgCounts++;
}

template<typename T>
void lgLink<T>::lgInsert(const T& k)
{
	lgLinkPoint<T>* x = new lgLinkPoint<T>;
	x->m_NextlgLink = x->m_PrelgLink = nullptr;
	x->m_lgData = k;
	lgInsert(*x);
}

template<typename T>
lgLinkPoint<T> lgLink<T>::lgDelete(const lgLinkPoint<T> x)
{
	if (x.m_PrelgLink != nullptr)
	{
		x.m_PrelgLink->m_NextlgLink = x.m_NextlgLink;
	}
	else
	{
		m_lgLinkHead = x.m_NextlgLink;
	}
	if (x.m_NextlgLink != nullptr)
	{
		x.m_NextlgLink->m_PrelgLink = x.m_PrelgLink;
	}
	m_lgCounts--;
	return x;
}

template<typename T>
const unsigned int lgLink<T>::lgGetLinkCount()
{
	return m_lgCounts;
}

template<typename T>
lgLinkPoint<T>& lgLink<T>::operator [](unsigned int index)
{
	unsigned int i = 0;
	lgLinkPoint<T>* x = m_lgLinkHead;
	while (x != nullptr && i < index)
	{
		x = x->m_NextlgLink;
		i++;
	}
	return *x;
}

template<typename T>
void lgLink<T>::lgDeleteAll()
{
	lgLinkPoint<T>* x = nullptr;
	while (m_lgLinkHead)
	{
		x = m_lgLinkHead;
		lgDelete(*m_lgLinkHead);
		delete x;
	}
}

template<typename T>
lgLinkPoint<T>* lgLink<T>::lgGetLinkHead() const
{
	return m_lgLinkHead;
}

template<typename T>
lgLink<T> lgLink<T>::operator =(const lgLink<T>& tlgLinkPoint)
{
	lgDeleteAll();
	lgLinkPoint<T>* x = tlgLinkPoint.lgGetLinkHead();
	while (x)
	{
		lgInsert(x->m_lgData);
		x = x->m_NextlgLink;
	}
	return tlgLinkPoint;
}