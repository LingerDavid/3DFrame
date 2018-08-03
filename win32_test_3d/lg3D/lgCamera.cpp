#include "lgCamera.h"

/////////////////////////////////////////////////////////////////
lgCamera::lgFrustum::lgFrustum()
{
	m_lgZCP = 0.0;
	m_lgZY = 1.0;
	m_lgZH = 2.0;
	m_lgX = 1.0;
	m_lgY = 1.0;
	lgUpdateCullFace();
}

lgCamera::lgFrustum::lgFrustum(double tzy, double tzh, double tx, double ty)
{
	m_lgZY = tzy;
	m_lgZH = tzh;
	m_lgX = tx;
	m_lgY = ty;
	lgUpdateCullFace();
}

lgCamera::lgFrustum::lgFrustum(const lgFrustum& tlgFrustum)
{
	m_lgZCP = tlgFrustum.lgGetZCP();
	m_lgZY = tlgFrustum.m_lgZY;
	m_lgZH = tlgFrustum.m_lgZH;
	m_lgX = tlgFrustum.m_lgX;
	m_lgY = tlgFrustum.m_lgY;
	lgUpdateCullFace();
}

double lgCamera::lgFrustum::lgGetZCP() const
{
	return m_lgZCP;
}

void lgCamera::lgFrustum::lgUpdateCullFace()
{
	lgVector l1(lgPoint(0.0, 0.0, 0.0), lgPoint(0.0, 1.0, 0.0)),
		l2(lgPoint(0.0, 0.0, 0.0), lgPoint(m_lgX, 0.0, m_lgZH)),
		l3(lgPoint(0.0, 0.0, 0.0), lgPoint(1.0, 0.0, 0.0)),
		l4(lgPoint(0.0, 0.0, 0.0), lgPoint(0.0, m_lgY, m_lgZH)),
		left, 
		right, 
		top, 
		bottom;
	lgPoint tlgDirect;
	left = l1 * l2;
	left.lgNormalize();
	tlgDirect = left.lgGetDirectVector();
	tlgDirect.lgSetX(-tlgDirect.lgGetX());
	right.lgSetOrgPoint(lgPoint(0.0, 0.0, 0.0));
	right.lgSetDesPoint(tlgDirect);

	top = l4 * l3;
	top.lgNormalize();
	tlgDirect = top.lgGetDirectVector();
	tlgDirect.lgSetY(-tlgDirect.lgGetY());
	bottom.lgSetOrgPoint(lgPoint(0.0, 0.0, 0.0));
	bottom.lgSetDesPoint(tlgDirect);

	m_lgLeftFace.lgSetNormal(left);
	m_lgLeftFace.lgSetPoint(lgPoint(0.0, 0.0, 0.0));

	m_lgRightFace.lgSetNormal(right);
	m_lgRightFace.lgSetPoint(lgPoint(0.0, 0.0, 0.0));

	m_lgTopFace.lgSetNormal(top);
	m_lgTopFace.lgSetPoint(lgPoint(0.0, 0.0, 0.0));

	m_lgBottomFace.lgSetNormal(bottom);
	m_lgBottomFace.lgSetPoint(lgPoint(0.0, 0.0, 0.0));
}

const lgCamera::lgFrustum& lgCamera::lgFrustum::operator=(const lgFrustum& tlgFrustum)
{
	m_lgZCP = tlgFrustum.lgGetZCP();
	m_lgZY = tlgFrustum.m_lgZY;
	m_lgZH = tlgFrustum.m_lgZH;
	m_lgX = tlgFrustum.m_lgX;
	m_lgY = tlgFrustum.m_lgY;
	return *this;
}

/////////////////////////////////////////////////////////////////
lgCamera::lgView::lgView()
{
	m_ViewWidth = 0.0;
	m_ViewHeight = 0.0;
}

lgCamera::lgView::lgView(double tvw, double tvh)
{
	m_ViewWidth = tvw;
	m_ViewHeight = tvh;
}

lgCamera::lgView::lgView(const lgView& tlgView)
{
	m_ViewWidth = tlgView.m_ViewWidth;
	m_ViewHeight = tlgView.m_ViewHeight;
}

const lgCamera::lgView& lgCamera::lgView::operator =(const lgView& tlgView)
{
	m_ViewWidth = tlgView.m_ViewWidth;
	m_ViewHeight = tlgView.m_ViewHeight;
	return *this;
}

/////////////////////////////////////////////////////////////////
lgCamera::lgWindow::lgWindow()
{
	m_WindowWidth = 100;
	m_WindowHeight = 100;
	m_WindowX = 0;
	m_WindowY = 0;
}

lgCamera::lgWindow::lgWindow(int ww, int wh, int wx, int wy)
{
	m_WindowWidth = ww;
	m_WindowHeight = wh;
	m_WindowX = wx;
	m_WindowY = wy;
}

lgCamera::lgWindow::lgWindow(const lgWindow& tlgWindow)
{
	m_WindowWidth = tlgWindow.m_WindowWidth;
	m_WindowHeight = tlgWindow.m_WindowHeight;
	m_WindowX = tlgWindow.m_WindowX;
	m_WindowY = tlgWindow.m_WindowY;
}

const lgCamera::lgWindow& lgCamera::lgWindow::operator=(const lgWindow& tlgWindow)
{
	m_WindowWidth = tlgWindow.m_WindowWidth;
	m_WindowHeight = tlgWindow.m_WindowHeight;
	m_WindowX = tlgWindow.m_WindowX;
	m_WindowY = tlgWindow.m_WindowY;
	return *this;
}


/////////////////////////////////////////////////////////////////

lgCamera::lgCamera()
{
	lgInit();
}

lgCamera::lgCamera(const lgCamera& tlgCamera)
{
	m_lgEluer = tlgCamera.lgGetEluer();

	m_lgWorldPoint = tlgCamera.lgGetWorldPoint();

	m_lgFrustum = tlgCamera.lgGetFrustum();

	m_lgView = tlgCamera.lgGetView();

	m_lgWindow = tlgCamera.lgGetWindow();
}

void lgCamera::lgInit()
{
#ifndef PI
#define PI 3.1415926
#endif
	m_lgEluer.lgSetHeading(0.0);
	m_lgEluer.lgSetPitch(0.0);
	m_lgEluer.lgSetBank(0.0);

	m_lgWorldPoint.lgSetX(0.0);
	m_lgWorldPoint.lgSetY(0.0);
	m_lgWorldPoint.lgSetZ(0.0);

	//Frustum
	m_lgFrustum.m_lgZY = 1000.0;
	m_lgFrustum.m_lgZH = 1.0;
	m_lgFrustum.m_lgX = 1.0;
	m_lgFrustum.m_lgY = 1.0;
	m_lgFrustum.lgUpdateCullFace();

	//viewport is 300.0x300.0
	m_lgView.m_ViewHeight = 1.0;
	m_lgView.m_ViewWidth = 1.0;

	//assumpt the screnn window size is 500x500
	m_lgWindow.m_WindowX = 0;
	m_lgWindow.m_WindowY = 0;
	m_lgWindow.m_WindowHeight = 500;
	m_lgWindow.m_WindowWidth = 500;
}

const lgEluer& lgCamera::lgGetEluer() const
{
	return m_lgEluer;
}

const lgPoint& lgCamera::lgGetWorldPoint() const
{
	return m_lgWorldPoint;
}

const lgCamera::lgFrustum& lgCamera::lgGetFrustum() const
{
	return m_lgFrustum;
}

const lgCamera::lgView& lgCamera::lgGetView() const
{
	return m_lgView;
}

const lgCamera::lgWindow& lgCamera::lgGetWindow() const
{
	return m_lgWindow;
}

void lgCamera::lgSetEluer(const lgEluer& tlgEluer)
{
	m_lgEluer = tlgEluer;
}

void lgCamera::lgSetWorldPoint(const lgPoint& tlgWorldPoint)
{
	m_lgWorldPoint = tlgWorldPoint;
}

void lgCamera::lgSetFrustum(const lgFrustum& tlgFrustum)
{
	m_lgFrustum = tlgFrustum;
}

void lgCamera::lgSetView(const lgView& tlgView)
{
	m_lgView = tlgView;
}

void lgCamera::lgSetWindow(const lgWindow& tlgWindow)
{
	m_lgWindow = tlgWindow;
}

void lgCamera::lgSetWindowOrg(int x, int y)
{
	m_lgWindow.m_WindowX = x;
	m_lgWindow.m_WindowY = y;
}
