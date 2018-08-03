#include <limits.h>
#include <math.h>
#include "lgTexture.h"
#include "lgLink.cpp"
#include "lgMatrix.h"
#include "lgLight.h"
#include "lgObject.h"

lgLight glglLight;

const lgPoint lgBoundingRectBox::lgGetNearestPoint(const lgPoint& tlgPoint)
{
	lgPoint tlgPt = tlgPoint;
	if (tlgPt.lgGetX() < lgXL)
	{
		tlgPt.lgSetX(lgXL);
	}
	else if (tlgPt.lgGetX() > lgXR)
	{
		tlgPt.lgSetX(lgXR);
	}

	if (tlgPt.lgGetY() < lgYB)
	{
		tlgPt.lgSetY(lgYB);
	}
	else if (tlgPt.lgGetY() > lgYT)
	{
		tlgPt.lgSetY(lgYT);
	}

	if (tlgPt.lgGetZ() < lgZH)
	{
		tlgPt.lgSetZ(lgZH);
	}
	else if (tlgPt.lgGetZ() > lgZY)
	{
		tlgPt.lgSetZ(lgZY);
	}
	return tlgPt;
}

lgObject::lgObject() :m_lgDirection(0.0, 0.0, 0.0) ,
m_lgXVector(0.0, 0.0, 0.0, 1.0, 0.0, 0.0),
m_lgYVector(0.0, 0.0, 0.0, 0.0, 1.0, 0.0),
m_lgZVector(0.0, 0.0, 0.0, 0.0, 0.0, 1.0)
{
	lgInit();
}

lgObject::lgObject(const lgObject& tlgObject)
{
}

lgObject::~lgObject()
{
	if (m_lgObjectName)
	{
		delete m_lgObjectName;
	}
	m_lgFaces.lgDeleteAll();
	m_lgRenderFaces.lgDeleteAll();
}

void lgObject::lgInit()
{
	m_lgBoundingRectBox.lgXL = INT_MAX;
	m_lgBoundingRectBox.lgXR = INT_MIN;
	m_lgBoundingRectBox.lgYT = INT_MIN;
	m_lgBoundingRectBox.lgYB = INT_MAX;
	m_lgBoundingRectBox.lgZY = INT_MIN;
	m_lgBoundingRectBox.lgZH = INT_MAX;

	m_lgID = 0;
	m_lgCurFame = 0;
	m_lgFrameCount = 0;

	m_lgWorldPoint.lgSetX(0.0);
	m_lgWorldPoint.lgSetY(0.0);
	m_lgWorldPoint.lgSetZ(0.0);
	m_lgState = STATE_INVISIBLE;
}

//!
const lgBoundingRectBox& lgObject::lgGetBoundingRectBox()
{
	lgLinkPoint<lgTriangle>* x = m_lgFaces[m_lgCurFame].m_lgData.lgGetLinkHead();
	unsigned int i = 0;
	double tx, ty, tz;

	m_lgBoundingRectBox.lgXL = m_lgBoundingRectBox.lgYB = m_lgBoundingRectBox.lgZH = INT_MAX;
	m_lgBoundingRectBox.lgXR = m_lgBoundingRectBox.lgYT = m_lgBoundingRectBox.lgZY = INT_MIN;

	while (x)
	{
		for (i = 0; i < 3; i++)
		{
			tx = x->m_lgData[i].lgGetX();
			ty = x->m_lgData[i].lgGetY();
			tz = x->m_lgData[i].lgGetZ();

			if (tx < m_lgBoundingRectBox.lgXL)
			{
				m_lgBoundingRectBox.lgXL = tx;
			}
			if (tx > m_lgBoundingRectBox.lgXR)
			{
				m_lgBoundingRectBox.lgXR = tx;
			}
			if (ty < m_lgBoundingRectBox.lgYB)
			{
				m_lgBoundingRectBox.lgYB = ty;
			}
			if (ty > m_lgBoundingRectBox.lgYT)
			{
				m_lgBoundingRectBox.lgYT = ty;
			}
			if (tz < m_lgBoundingRectBox.lgZH)
			{
				m_lgBoundingRectBox.lgZH = tz;
			}
			if (tz > m_lgBoundingRectBox.lgZY)
			{
				m_lgBoundingRectBox.lgZY = tz;
			}
		}
		x = x->m_NextlgLink;
	}
	return m_lgBoundingRectBox;
}

//!
const lgBoundingSphereBox& lgObject::lgGetBoundingSphereBox()
{
	lgLinkPoint<lgTriangle>* x = m_lgFaces[m_lgCurFame].m_lgData.lgGetLinkHead();
	unsigned int i = 0;
	double tx = 0.0, ty = 0.0, tz = 0.0, dist = 0.0;

	m_lgBoundingSphereBox.lgRadius = 0.0;

	while (x)
	{
		for (i = 0; i < 3; i++)
		{
			tx = x->m_lgData[i].lgGetX();
			ty = x->m_lgData[i].lgGetY();
			tz = x->m_lgData[i].lgGetZ();

			dist = sqrt(tx * tx + ty * ty + tz * tz) * 0.5;

			if (dist > m_lgBoundingSphereBox.lgRadius)
			{
				m_lgBoundingSphereBox.lgRadius = dist;
			}
		}
		x = x->m_NextlgLink;
	}
	return m_lgBoundingSphereBox;
}

const lgPoint lgObject::lgGetWorldPoint() const
{
	return m_lgWorldPoint;
}

void lgObject::lgSetWorldPoint(const lgPoint& tlgPoint)
{
	m_lgWorldPoint = tlgPoint;
}

bool lgObject::lgIsVisible()
{
	return true;
}

void lgObject::lgInsertTriangle(int frame, double x1, double y1, double z1, 
	double x2, double y2, double z2, 
	double x3, double y3, double z3)
{
	lgTriangle tlgTriangle(x1, y1, z1, x2, y2, z2, x3, y3, z3);
	m_lgFaces[m_lgCurFame].m_lgData.lgInsert(tlgTriangle);
}

void lgObject::lgCreateFrames(int framecount)
{
	int i = 0;
	lgLink<lgTriangle> tlgFaces;
	for (i = 0; i < framecount; i++)
	{
		m_lgFaces.lgInsert(tlgFaces);
	}
	m_lgFrameCount = framecount;
}

void lgObject::lgCalVertexNormals(lgLink<lgTriangle>& tlgLinkTris)
{
	//this function finds all vertex normal
	lgLinkPoint<lgTriangle>* x = tlgLinkTris.lgGetLinkHead(), * y = x, * z = x;
	lgVector v1, v2, v3;
	lgLink<double> ls;
	lgLink<lgVector> lv;
	lgLink<int> lp;
	lgLinkPoint<lgVector>* plpv = nullptr;
	lgLinkPoint<double> lps;

	double s1 = 0.0, 
		s2 = 0.0,
		s = 0.0;
	int i = 0,
		j = 0,
		k = 0,
		p1 = -1, 
		p2 = -1;
	while (x)
	{
		for (i = 0; i < 3; i++)
		{
			y = z;
			while (y)
			{
				for (j = 0; j < 3; j++)
				{
					if (x->m_lgData[i] == y->m_lgData[j])
					{
						lv.lgInsert(y->m_lgData.lgGetNormal());
						ls.lgInsert(y->m_lgData.lgGetTriangleArea());
						s += y->m_lgData.lgGetTriangleArea();
						k++;
						break;
					}
				}
				y = y->m_NextlgLink;
			}


			if (k != 0 && s != 0)
			{
				plpv = lv.lgGetLinkHead();
				k = 0;

				v3.lgSetOrgPoint(lgPoint(0.0, 0.0, 0.0));
				v3.lgSetDesPoint(lgPoint(0.0, 0.0, 0.0));

				while (plpv)
				{
					lps = ls[k];

					v3 = v3 + plpv->m_lgData * lps.m_lgData / s;

					k++;
					plpv = plpv->m_NextlgLink;
				}

				x->m_lgData[i].lgSetNormal(v3);

				k = 0;
				s = 0.0;
				lv.lgDeleteAll();
				ls.lgDeleteAll();
			}
		}

		x = x->m_NextlgLink;
	}
}

void lgObject::lgCalPrimitiveVertexNormal()
{
	int i = 0;
	for (i = 0; i < m_lgFrameCount; i++)
	{
		lgCalVertexNormals(m_lgFaces[m_lgCurFame].m_lgData);
	}
}

void lgObject::lgMove(const lgVector& tlgVector)
{
	lgMatrix tlgMatrix, tlgSrcMatrix;
	lgMatrix::lgMakeMoveMatrix(tlgVector, tlgMatrix);
	m_lgWorldPoint.lgMove(tlgVector);
}

void lgObject::lgRotate(double tAngle, const lgVector& tlgVector)
{
	lgLinkPoint<lgTriangle>* x = m_lgFaces[m_lgCurFame].m_lgData.lgGetLinkHead();
	lgMatrix tlgMatrix;
	lgMatrix::lgMakeRotateMatrix(tAngle, tlgVector, tlgMatrix);
	lgVector tlgVect;
	int i = 0;
	while (x)
	{
		//rotate triangle
		x->m_lgData.lgRotate(tlgMatrix);
		//rotate vertex normal
		for (i = 0; i < 3; i++)
		{
			tlgVect = x->m_lgData[i].lgGetNormal();
			tlgVect.lgRotate(tlgMatrix);
			x->m_lgData[i].lgSetNormal(tlgVect);
		}
		x = x->m_NextlgLink;
	}

	m_lgXVector.lgRotate(tlgMatrix);
	m_lgYVector.lgRotate(tlgMatrix);
	m_lgZVector.lgRotate(tlgMatrix);
	lgGetBoundingRectBox();

	lgEluer tlgEluer;
	tlgMatrix.lgMatrixTolgEluerAngle(tlgEluer);
	m_lgDirection = m_lgDirection + tlgEluer;

}

void lgObject::lgZoom(const lgVector& tlgVector)
{
	lgLinkPoint<lgTriangle>* x = m_lgFaces[m_lgCurFame].m_lgData.lgGetLinkHead();
	lgMatrix tlgMatrix;
	lgMatrix::lgMakeZoomMatrix(tlgVector, tlgMatrix);
	while (x)
	{
		x->m_lgData.lgZoom(tlgMatrix);
		x = x->m_NextlgLink;
	}
}

void lgObject::lgCreateStandardCube(double width)
{

	m_lgFrameCount = 1;
	m_lgCurFame = 0;
	//1,2,3,4,5,6,7,8
	//2 1 3
	//1 4 3
	//5 6 8
	//6 7 8
	//1 4 8
	//5 8 1
	//6 2 3
	//3 7 6
	//1 6 5
	//1 2 6
	//4 8 7
	//4 7 3
	lgLink<lgTriangle> faces;
	lgPoint p1(width, width, width),
		p2(width, -width, width),
		p3(-width, -width, width),
		p4(-width, width, width),
		p5(width, width, -width),
		p6(width, -width, -width),
		p7(-width, -width, -width),
		p8(-width, width, -width);
	lgTriangle tlgTriangle1(p2, p1, p3),
		tlgTriangle2(p1, p4, p3),
		tlgTriangle3(p5, p6, p8),
		tlgTriangle4(p6, p7, p8),
		tlgTriangle5(p8, p4, p1),
		tlgTriangle6(p5, p8, p1),
		tlgTriangle7(p6, p2, p3),
		tlgTriangle8(p3, p7, p6),
		tlgTriangle9(p1, p6, p5),
		tlgTriangle10(p2, p6, p1),
		tlgTriangle11(p4, p8, p7),
		tlgTriangle12(p4, p7, p3);

	faces.lgDeleteAll();
	faces.lgInsert(tlgTriangle1);
	faces.lgInsert(tlgTriangle2);
	faces.lgInsert(tlgTriangle3);
	faces.lgInsert(tlgTriangle4);
	faces.lgInsert(tlgTriangle5);
	faces.lgInsert(tlgTriangle6);
	faces.lgInsert(tlgTriangle7);
	faces.lgInsert(tlgTriangle8);
	faces.lgInsert(tlgTriangle9);
	faces.lgInsert(tlgTriangle10);
	faces.lgInsert(tlgTriangle11);
	faces.lgInsert(tlgTriangle12);

	m_lgFaces.lgInsert(faces);

	lgGetBoundingRectBox();
}

void lgObject::lgInitAllFacesTexture(const lgTexture* plgTexture)
{
	int i = 0;
	lgLinkPoint<lgTriangle>* x = nullptr;
	for (i = 0; i < m_lgFrameCount; i++)
	{
		x = m_lgFaces[i].m_lgData.lgGetLinkHead();
		while (x)
		{
			x->m_lgData.lgSetTexture(plgTexture);
			x = x->m_NextlgLink;
		}
	}
}

void lgObject::lgCreateTerrian(int width, int height, const lgTexture& tlgTexture, int type, int tindex)
{
	int row = 0,
		column = 0,
		trow = 0,
		tcolumn = 0,
		bit = 0, 
		i = 0,
		j = 0,
		index = 0,
		vertex = 0,
		poly = 0;
	unsigned char* buffer = nullptr;
	double rowStep = 0.0,
		colStep = 0.0,
		dScale = 0.01,
		* x = nullptr, 
		* y = nullptr, 
		* z = nullptr,
		* u = nullptr,
		* v = nullptr;
	lgTriangle tlgTriangle;
	lgLink<lgTriangle> tlgFace;

	m_lgFrameCount = 1;
	m_lgCurFame = 0;

	buffer = tlgTexture.lgGetTextureBuffer(type, tindex, row, column, bit);

	trow = row / 10;
	tcolumn = column / 10;

	rowStep = height / trow;
	colStep = width / tcolumn;
	
	vertex = trow * tcolumn;
	poly = (trow - 1) * (tcolumn - 1) * 2;

	x = new double[trow * tcolumn];
	y = new double[trow * tcolumn];
	z = new double[trow * tcolumn];
	u = new double[trow * tcolumn];
	v = new double[trow * tcolumn];

	if (bit == 24)
	{
		for (i = 0; i < trow; i++)
		{
			for(j = 0; j < tcolumn; j++)
			{
				index = i * tcolumn + j;
				x[index] = j * colStep - width / 2;
				//y[index] = (int)((((int)(buffer[i * column * bit / 8 + j * bit / 8] / 256.0 * 4.0) << 6) 
				//	+ ((int)(buffer[i * column * bit / 8 + j * bit / 8 + 1] / 256.0 * 8) << 3)
				//	+ (buffer[i * column * bit / 8 + j * bit / 8 + 1] / 256.0 * 8)) / 256.0 * 3.0);
				y[index] = -2.0;
				//y[index] = (rand() % 2) - 3;
				z[index] = i * rowStep - height / 2;
				u[index] = i / row;
				v[index] = j / column;
			}
		}

		tlgFace.lgDeleteAll();
		for (i = 0; i < trow - 1; i++)
		{
			for (j = 0; j < tcolumn - 1; j++)
			{
				index = i * tcolumn + j;
				//right top
				tlgTriangle[0].lgSetX(x[index]);
				tlgTriangle[0].lgSetY(y[index]);
				tlgTriangle[0].lgSetZ(z[index]);
				tlgTriangle[0].lgSetTextureU(u[index]);
				tlgTriangle[0].lgSetTextureV(v[index]);

				tlgTriangle[1].lgSetX(x[index + tcolumn + 1]);
				tlgTriangle[1].lgSetY(y[index + tcolumn + 1]);
				tlgTriangle[1].lgSetZ(z[index + tcolumn + 1]);
				tlgTriangle[1].lgSetTextureU(u[index + tcolumn + 1]);
				tlgTriangle[1].lgSetTextureV(v[index + tcolumn + 1]);

				tlgTriangle[2].lgSetX(x[index + 1]);
				tlgTriangle[2].lgSetY(y[index + 1]);
				tlgTriangle[2].lgSetZ(z[index + 1]);
				tlgTriangle[2].lgSetTextureU(u[index + 1]);
				tlgTriangle[2].lgSetTextureV(v[index + 1]);

				tlgFace.lgInsert(tlgTriangle);

				//left bottom

				tlgTriangle[1].lgSetX(x[index + tcolumn]);
				tlgTriangle[1].lgSetY(y[index + tcolumn]);
				tlgTriangle[1].lgSetZ(z[index + tcolumn]);
				tlgTriangle[1].lgSetTextureU(u[index + tcolumn]);
				tlgTriangle[1].lgSetTextureV(v[index + tcolumn]);

				tlgTriangle[2].lgSetX(x[index + tcolumn + 1]);
				tlgTriangle[2].lgSetY(y[index + tcolumn + 1]);
				tlgTriangle[2].lgSetZ(z[index + tcolumn + 1]);
				tlgTriangle[2].lgSetTextureU(u[index + tcolumn + 1]);
				tlgTriangle[2].lgSetTextureV(v[index + tcolumn + 1]);

				tlgFace.lgInsert(tlgTriangle);
			}
		}
		m_lgFaces.lgInsert(tlgFace);
	}

	delete u;
	delete v;
	delete z;
	delete y;
	delete x;

	lgInitAllFacesTexture(&tlgTexture);
}

//first lcoal to world
//then cull object out the camera and insert the left faces to render list
//cull the back faces
//world to camera
//camera to transport
//finally to screen
void lgObject::lgRenderPipeLine(const lgCamera& tlgCamera)
{
	m_lgRenderFaces.lgDeleteAll();
	lgVector tlgVector1(lgPoint(0.0, 0.0, 0.0), m_lgWorldPoint),
	tlgVector2(lgPoint(0.0, 0.0, 0.0), tlgCamera.lgGetWorldPoint());
	tlgVector1 = tlgVector1 - tlgVector2;
	lgPoint newWorldPoint = tlgVector1.lgGetDesPoint();

	lgMatrix tlgObjLocalToWorldMatrix, tlgCameraRotateMatrix,
		tlgObjWorldToCameraMatrix, tlgObjCameraToViewMatrix,
		tlgObjViewMatrixToWorldMatrix;
	lgMatrix::lgMakeLocalToWorldMatrix(newWorldPoint, tlgObjLocalToWorldMatrix);
	lgMatrix::lgMakeWorldToCameraMatrix(tlgCamera, tlgObjWorldToCameraMatrix);
	lgMatrix::lgMakeCameraToViewMatrix(tlgCamera, tlgObjCameraToViewMatrix);
	lgMatrix::lgMakeViewToWindowMatrix(tlgCamera, tlgObjViewMatrixToWorldMatrix);
	lgMatrix tlgObjWorldToWindowMatrix = tlgObjWorldToCameraMatrix * tlgObjCameraToViewMatrix * tlgObjViewMatrixToWorldMatrix;

	lgEluer tlgEluer = tlgCamera.lgGetEluer();
	lgCamera::lgFrustum tlgFrustum = tlgCamera.lgGetFrustum();
	lgFace tlgLeftFace = tlgFrustum.m_lgLeftFace,
	tlgRightFace = tlgFrustum.m_lgRightFace,
	tlgTopFace = tlgFrustum.m_lgTopFace,
	tlgBottomFace = tlgFrustum.m_lgBottomFace;

	double tzh = tlgCamera.lgGetFrustum().m_lgZH, tzy = tlgCamera.lgGetFrustum().m_lgZY;
	tlgEluer.lgEluerAngleTolgMatrix(tlgCameraRotateMatrix);

	tlgLeftFace.lgRotateFace(tlgCameraRotateMatrix);
	tlgRightFace.lgRotateFace(tlgCameraRotateMatrix);
	tlgTopFace.lgRotateFace(tlgCameraRotateMatrix);
	tlgBottomFace.lgRotateFace(tlgCameraRotateMatrix);

	lgLinkPoint<lgTriangle>* x = m_lgFaces[m_lgCurFame].m_lgData.lgGetLinkHead();

	lgTriangle tlgTriangle;
	lgPoint tlgPoint;
	lgVector tlgVector, tlgNormal, tlgVertexNoraml[3];
	lgColor color;

	int i = 0;
	double z[3] = {0.0};
	while (x)
	{
		tlgTriangle = x->m_lgData;

		tlgTriangle.lgMove(tlgObjLocalToWorldMatrix);

		for (i = 0; i < 3; i++)
		{
			tlgVector2.lgSetDesPoint(tlgTriangle[i]);
			tlgVertexNoraml[i] = tlgTriangle[i].lgGetNormal();
			tlgVertexNoraml[i] = tlgVertexNoraml[i] + tlgVector2;
			tlgVertexNoraml[i].lgMove(tlgObjLocalToWorldMatrix);
		}

		tlgPoint = tlgTriangle.lgGetBarycentPoint();
		tlgVector.lgSetDesPoint(tlgPoint);

		tlgVector.lgSetOrgPoint(tlgLeftFace.lgGetPoint());
		tlgNormal = tlgLeftFace.lgGetNormal();
		if (tlgNormal.lgDotMultiply(tlgVector) > 0)
		{
			x = x->m_NextlgLink;
			continue;
		}

		tlgVector.lgSetOrgPoint(tlgRightFace.lgGetPoint());
		tlgNormal = tlgRightFace.lgGetNormal();
		if (tlgNormal.lgDotMultiply(tlgVector) > 0)
		{
			x = x->m_NextlgLink;
			continue;
		}

		tlgVector.lgSetOrgPoint(tlgTopFace.lgGetPoint());
		tlgNormal = tlgTopFace.lgGetNormal();
		if (tlgNormal.lgDotMultiply(tlgVector) > 0)
		{
			x = x->m_NextlgLink;
			continue;
		}

		tlgVector.lgSetOrgPoint(tlgBottomFace.lgGetPoint());
		tlgNormal = tlgBottomFace.lgGetNormal();
		if (tlgNormal.lgDotMultiply(tlgVector) > 0)
		{
			x = x->m_NextlgLink;
			continue;
		}

		if (tlgPoint.lgGetZ() < tlgFrustum.m_lgZH
			|| tlgPoint.lgGetZ() > tlgFrustum.m_lgZY)
		{
			x = x->m_NextlgLink;
			continue;
		}

		tlgVector.lgSetOrgPoint(lgPoint(0.0, 0.0, 0.0));
		tlgVector.lgSetDesPoint(tlgPoint);

		tlgNormal = tlgTriangle.lgGetNormal();

		if (tlgVector.lgDotMultiply(tlgNormal) > 0)
		{
			x = x->m_NextlgLink;
			continue;
		}

		glglLight.lgRenderAllLight(x->m_lgData.lgGetFaceColor(), x->m_lgData, color);
		tlgTriangle.lgSetFaceColor(color);

		for (i = 0; i < 3; i++)
		{
			glglLight.lgRenderAllLightByGouraud(x->m_lgData[i].lgGetPointColor(), x->m_lgData[i], color);
			tlgTriangle[i].lgSetPointColor(color);
		}

		tlgTriangle.lgTransfer(tlgObjWorldToCameraMatrix);
		for ( i = 0; i < 3; i++)
		{
			z[i] = tlgTriangle[i].lgGetZ();
		}

		tlgTriangle.lgTransfer(tlgObjCameraToViewMatrix * tlgObjViewMatrixToWorldMatrix);

		//save the z
		for (i = 0; i < 3; i++)
		{
			tlgTriangle[i].lgSetZ(z[i]);
		}

		for (i = 0; i < 3; i++)
		{
			tlgPoint = tlgVertexNoraml[i].lgGetDesPoint();
			tlgPoint.lgTransfer(tlgObjWorldToWindowMatrix);
			tlgTriangle[i].lgSetU(tlgPoint.lgGetX());
			tlgTriangle[i].lgSetV(tlgPoint.lgGetY());
		}

		m_lgRenderFaces.lgInsert(tlgTriangle);
		x = x->m_NextlgLink;
	}
}

const lgLink<lgTriangle>& lgObject::lgGetRenderList() const
{
	return m_lgRenderFaces;
}


lgLink<lgTriangle>& lgObject::lgGetFaceLink()
{
	return m_lgFaces[m_lgCurFame].m_lgData;
}

void lgObject::lgDraw(void* dc, lgCamera& tlgCamera, int type, int index)
{
	lgRenderPipeLine(tlgCamera);
	m_lgDisplay.lgDrawObject(dc, *this, type, index);
	//lgDrawVertexNormal(dc);
	//lgDrawAxises(dc, tlgCamera);
	//lgDrawBoundingBox(dc, tlgCamera);
}

void lgObject::lgDrawXAxis(void* dc, lgCamera& tlgCamera)
{
	lgVector tlgXVector;
	lgPoint tOrgPt, tDesPt;
	tlgXVector = m_lgXVector * AXIS_LENGTH;
	tOrgPt = m_lgWorldPoint - tlgCamera.lgGetWorldPoint();
	tDesPt = tOrgPt + tlgXVector.lgGetDirectVector();
	lgVector tlgAxisX(tOrgPt, tDesPt);
	m_lgDisplay.lgDrawLine(dc, tlgCamera, tlgAxisX, lgPoint(0.0, 0.0, 0.0));
}

void lgObject::lgDrawYAxis(void* dc, lgCamera& tlgCamera)
{
	lgVector tlgYVector;
	lgPoint tOrgPt, tDesPt;
	tlgYVector = m_lgYVector * AXIS_LENGTH;
	tOrgPt = m_lgWorldPoint - tlgCamera.lgGetWorldPoint();
	tDesPt = tOrgPt + tlgYVector.lgGetDirectVector();
	lgVector tlgAxisY(tOrgPt, tDesPt);
	m_lgDisplay.lgDrawLine(dc, tlgCamera, tlgAxisY, lgPoint(0.0, 0.0, 0.0));
}

void lgObject::lgDrawZAxis(void* dc, lgCamera& tlgCamera)
{
	lgVector tlgZVector;
	lgPoint tOrgPt, tDesPt;
	tlgZVector = m_lgZVector * AXIS_LENGTH;
	tOrgPt = m_lgWorldPoint - tlgCamera.lgGetWorldPoint();
	tDesPt = tOrgPt + tlgZVector.lgGetDirectVector();

	lgVector tlgAxisZ(tOrgPt, tDesPt);
	m_lgDisplay.lgDrawLine(dc, tlgCamera, tlgAxisZ, lgPoint(0.0, 0.0, 0.0));
}

void lgObject::lgDrawAxises(void* dc, lgCamera& tlgCamera)
{
	lgDrawXAxis(dc, tlgCamera);
	lgDrawYAxis(dc, tlgCamera);
	lgDrawZAxis(dc, tlgCamera);
}

//serach all vertexes
//get all vertexex normal
//move normal
//transfer normal
//draw normal
void lgObject::lgDrawVertexNormal(void* dc)
{
	lgLinkPoint<lgTriangle>* x = m_lgRenderFaces.lgGetLinkHead();
	lgPOINT p1, p2;
	int i = 0;
	while (x)
	{
		for (i = 0; i < 3; i++)
		{
			p1.x = (int)x->m_lgData[i].lgGetU();
			p1.y = (int)x->m_lgData[i].lgGetV();
			p2.x = (int)x->m_lgData[i].lgGetX();
			p2.y = (int)x->m_lgData[i].lgGetY();
			m_lgDisplay.lgDrawLine(dc, p2, p1);
		}
		x = x->m_NextlgLink;
	}
}

void lgObject::lgDrawBoundingBox(void* dc, lgCamera& tlgCamera)
{
	lgPoint p1(m_lgBoundingRectBox.lgXL, m_lgBoundingRectBox.lgYT, m_lgBoundingRectBox.lgZH),
		p2(m_lgBoundingRectBox.lgXL, m_lgBoundingRectBox.lgYT, m_lgBoundingRectBox.lgZY),
		p3(m_lgBoundingRectBox.lgXL, m_lgBoundingRectBox.lgYB, m_lgBoundingRectBox.lgZH),
		p4(m_lgBoundingRectBox.lgXL, m_lgBoundingRectBox.lgYB, m_lgBoundingRectBox.lgZY),
		p5(m_lgBoundingRectBox.lgXR, m_lgBoundingRectBox.lgYT, m_lgBoundingRectBox.lgZH),
		p6(m_lgBoundingRectBox.lgXR, m_lgBoundingRectBox.lgYT, m_lgBoundingRectBox.lgZY),
		p7(m_lgBoundingRectBox.lgXR, m_lgBoundingRectBox.lgYB, m_lgBoundingRectBox.lgZH),
		p8(m_lgBoundingRectBox.lgXR, m_lgBoundingRectBox.lgYB, m_lgBoundingRectBox.lgZY);
	
	lgPoint cameraWolrdPoint = tlgCamera.lgGetWorldPoint();
	lgVector v1(p1, p2), v2(p3, p4), v3(p1, p3), v4(p2, p4),
		v5(p5, p6), v6(p7, p8), v7(p5, p7), v8(p6, p8), 
		v9(p1, p5), v10(p2, p6), v11(p3, p7), v12(p4, p8);

	m_lgDisplay.lgDrawLine(dc, tlgCamera, v1, m_lgWorldPoint - cameraWolrdPoint);
	m_lgDisplay.lgDrawLine(dc, tlgCamera, v2, m_lgWorldPoint - cameraWolrdPoint);
	m_lgDisplay.lgDrawLine(dc, tlgCamera, v3, m_lgWorldPoint - cameraWolrdPoint);
	m_lgDisplay.lgDrawLine(dc, tlgCamera, v4, m_lgWorldPoint - cameraWolrdPoint);
	m_lgDisplay.lgDrawLine(dc, tlgCamera, v5, m_lgWorldPoint - cameraWolrdPoint);
	m_lgDisplay.lgDrawLine(dc, tlgCamera, v6, m_lgWorldPoint - cameraWolrdPoint);
	m_lgDisplay.lgDrawLine(dc, tlgCamera, v7, m_lgWorldPoint - cameraWolrdPoint);
	m_lgDisplay.lgDrawLine(dc, tlgCamera, v8, m_lgWorldPoint - cameraWolrdPoint);
	m_lgDisplay.lgDrawLine(dc, tlgCamera, v9, m_lgWorldPoint - cameraWolrdPoint);
	m_lgDisplay.lgDrawLine(dc, tlgCamera, v10, m_lgWorldPoint - cameraWolrdPoint);
	m_lgDisplay.lgDrawLine(dc, tlgCamera, v11, m_lgWorldPoint - cameraWolrdPoint);
	m_lgDisplay.lgDrawLine(dc, tlgCamera, v12, m_lgWorldPoint - cameraWolrdPoint);

}