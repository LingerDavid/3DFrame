#ifndef _FILE_LGCAMERA_H
#define _FILE_LGCAMERA_H

#include "lgEluer.h"
#include "lgFace.h"

class lgCamera
{
public:
	class lgFrustum
	{
	private:
		double m_lgZCP;
	public:
		double m_lgZY;
		double m_lgZH;
		double m_lgX;
		double m_lgY;

		lgFace m_lgLeftFace;
		lgFace m_lgRightFace;
		lgFace m_lgTopFace;
		lgFace m_lgBottomFace;
	public:
		lgFrustum();
		lgFrustum(double, double, double, double);
		lgFrustum(const lgFrustum&);

		virtual double lgGetZCP() const;

		virtual void lgUpdateCullFace();

		virtual const lgFrustum& operator=(const lgFrustum&);
	};

	class lgView
	{
	public:
		double m_ViewWidth;
		double m_ViewHeight;
	public:
		lgView();
		lgView(double, double);
		lgView(const lgView&);
		virtual const lgView& operator=(const lgView&);
	};

	class lgWindow
	{
	public:
		//the own window size
		int m_WindowWidth;
		int m_WindowHeight;

		//the position in parent window
		int m_WindowX;
		int m_WindowY;
	public:
		lgWindow();
		lgWindow(int, int, int, int);
		lgWindow(const lgWindow&);
		virtual const lgWindow& operator=(const lgWindow&);
	};

private:
	lgEluer m_lgEluer;
	lgPoint m_lgWorldPoint;
	lgFrustum m_lgFrustum;
	lgView m_lgView;
	lgWindow m_lgWindow;

public:
	lgCamera();
	lgCamera(const lgCamera&);
	virtual void lgInit();
	virtual const lgEluer& lgGetEluer() const;
	virtual const lgPoint& lgGetWorldPoint() const;
	virtual const lgFrustum& lgGetFrustum() const;
	virtual const lgView& lgGetView() const;
	virtual const lgWindow& lgGetWindow() const;
	virtual void lgSetEluer(const lgEluer&);
	virtual void lgSetWorldPoint(const lgPoint&);
	virtual void lgSetFrustum(const lgFrustum&);
	virtual void lgSetView(const lgView&);
	virtual void lgSetWindow(const lgWindow&);
	virtual void lgSetWindowOrg(int x, int y);
};
#endif